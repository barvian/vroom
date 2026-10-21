// The idle animation the loading line rides while a series is being fetched.
// A position across the plot and an elapsed time in; a vertical offset and a
// brightness out. Also the curves of the hand-off into the data, further down.
//
// Three sines, not one. A single sine is too regular to read as anything but a
// test pattern — the eye finds the repeat immediately and the line stops
// looking like it's waiting for something. Summing three frequencies that
// aren't multiples of each other, each drifting at its own rate, gives a curve
// that keeps rearranging itself.
//
// The other half of the effect is restraint: a small amplitude and a faint,
// slowly breathing opacity. The line is a hint that the chart is alive, not a
// feature competing with the data about to replace it.
//
// Approach adapted from Liveline (github.com/benjitaylor/liveline, MIT), whose
// loading state solves the same problem well.
//
// Skia-free and header-only so the unit tests can cover it; see
// tests/test_loading_wave.cpp.

#pragma once

#include <cmath>

namespace vroom::loading_wave {

constexpr float kTwoPi = 6.283185307179586f;

// One component of the curve.
struct Harmonic {
    float freq;    // radians across the full plot width
    float weight;  // share of the amplitude
    float drift;   // multiple of the base phase speed
};

// Frequencies deliberately not integer multiples of one another: harmonics
// would lock into one repeating shape, which is the thing being avoided. The
// drifts are all multiples of a tenth only so the whole curve has an exact
// period to wrap the phase clock on — see kPeriodSeconds.
//
// Liveline's exact components, so the two charts' loading lines match.
constexpr Harmonic kHarmonics[] = {
    {9.4f, 0.55f, 1.0f},   // carrier — a crest and a half per screen
    {15.7f, 0.30f, 1.3f},  // ripple, running ahead
    {4.2f, 0.15f, 0.7f},   // a slow swell, running behind
};
constexpr int kHarmonicCount = 3;

// Base phase speed. Slow on purpose: this plays under a chart that has nothing
// to say yet, and anything quicker reads as activity.
constexpr float kDriftRadPerSecond = 1.0f;

// One full cycle of the *whole* curve. The drifts differ by tenths, so every
// component returns to its starting phase only after ten base cycles — which
// is also why the shape takes ~63s to come back around. Callers wrap elapsed
// time by this so a chart left loading doesn't lose float precision on the
// phase, and wrapping here is seamless because it is a true period.
constexpr float kPeriodSeconds = 10.f * kTwoPi / kDriftRadPerSecond;

// Peak displacement from the centreline, as a fraction of the pane height. The
// components rarely peak together, so the curve typically occupies well under
// this — it is a bound, not the height it looks.
constexpr float kAmplitudeFrac = 0.07f;

// Breathing opacity, a dimmer on the color: the line inherits the axis text
// tone by default, which would compete with the data at full strength.
constexpr float kBreathMin = 0.14f;
constexpr float kBreathMax = 0.30f;
// 26 breaths per curve cycle, so the breath wraps with the phase (~2.4s each)
// and never syncs with the drift into one combined pulse.
constexpr float kBreathCyclesPerPeriod = 26.f;

// Offset at `x_frac` (0 = left edge of the plot, 1 = right) and `elapsed_s`, in
// -1 .. 1. The weights sum to 1, so that range is tight. Phase runs as
// (k*x + w*t), which walks the crests leftward, the way a live series scrolls.
// Time outside one period is fine; sin wraps on its own.
inline float at(float elapsed_s, float x_frac) {
    const float base = kDriftRadPerSecond * elapsed_s;
    float sum = 0.f;
    for (int i = 0; i < kHarmonicCount; ++i) {
        const Harmonic& h = kHarmonics[i];
        sum += h.weight * std::sin(h.freq * x_frac + h.drift * base);
    }
    return sum;
}

// The curve's y as a fraction of the pane height (0 = pane top, 1 = bottom),
// centred on the pane. This is the form the line capture stores, so a resize
// mid-morph rescales instead of stranding the curve at old pixels.
inline float y_frac(float elapsed_s, float x_frac) {
    return 0.5f + kAmplitudeFrac * at(elapsed_s, x_frac);
}

// The line's opacity at `elapsed_s`, in kBreathMin .. kBreathMax.
inline float breath(float elapsed_s) {
    const float mid = (kBreathMin + kBreathMax) * 0.5f;
    const float half = (kBreathMax - kBreathMin) * 0.5f;
    return mid + half * std::sin(kTwoPi * kBreathCyclesPerPeriod * elapsed_s /
                                 kPeriodSeconds);
}

// Liveline's lerp: `speed` is the share of the remaining distance covered per
// 60fps frame, rescaled by `dt_s` so the curve is the same at any frame rate.
inline float approach(float current, float target, float speed, float dt_s) {
    const float factor = 1.f - std::pow(1.f - speed, dt_s * 60.f);
    return current + (target - current) * factor;
}

// What the line's clocks advance by for a frame `since_s` after the previous
// one. Real time, unlike the chart's shared dt, which counts any frame over
// 0.1s as a nominal 1/60s: a host thread busy mounting a screen can space
// frames well past that, and the line would crawl in for seconds. Capped so a
// resume from background lands the clocks rather than overflowing them.
constexpr float kMaxFrameSeconds = 1.f;
inline float frame_seconds(float since_s) {
    return since_s < 0.f ? 0.f
                         : (since_s > kMaxFrameSeconds ? kMaxFrameSeconds
                                                       : since_s);
}

// The line's entrance from nothing: Liveline's loading alpha, which snaps the
// last percent rather than creeping toward 1 forever.
constexpr float kFadeInSpeed = 0.14f;
inline float fade_in_step(float alpha, float dt_s) {
    const float a = approach(alpha, 1.f, kFadeInSpeed, dt_s);
    return a > 0.99f ? 1.f : a;
}

// The hand-off's single clock, Liveline's chartReveal: 0 when the data lands,
// 1 once the chart has fully taken over. A fast-out ease that settles in about
// 0.94s; every layer of the hand-off reads its progress off this one value.
constexpr float kRevealSpeed = 0.09f;
constexpr float kRevealSnap = 0.005f;
inline float reveal_step(float reveal, float dt_s) {
    const float r = approach(reveal, 1.f, kRevealSpeed, dt_s);
    return 1.f - r < kRevealSnap ? 1.f : r;
}

// Hermite ramp of `r` across [lo, hi].
inline float ramp(float r, float lo, float hi) {
    float t = (r - lo) / (hi - lo);
    t = t < 0.f ? 0.f : (t > 1.f ? 1.f : t);
    return t * t * (3.f - 2.f * t);
}

// How far the vertex at `x_frac` has travelled from the wave to the data. The
// centre resolves first and the edges last.
inline float resolve(float reveal, float x_frac) {
    const float edge = std::fabs(x_frac - 0.5f) * 2.f;
    const float t = (reveal - edge * 0.4f) / 0.6f;
    return t < 0.f ? 0.f : (t > 1.f ? 1.f : t);
}

// The line's share of the frame. In line mode (`line_mode` 1) it *is* the
// series and stays; over candles it gives way fast, cubed, so the bars take
// over early and the line never reads as a line chart.
inline float presence(float reveal, float line_mode) {
    const float out = (1.f - reveal) * (1.f - reveal) * (1.f - reveal);
    return line_mode > out ? line_mode : out;
}

// The line's opacity through the hand-off: up from the breath to full.
inline float reveal_alpha(float reveal, float breath_now) {
    return breath_now + (1.f - breath_now) * reveal;
}

// How far the line has tinted from `skeleton` toward the series color. Only a
// line-mode reveal tints, and it's done by a third of the way.
inline float tint(float reveal, float line_mode, float presence_now) {
    if (presence_now <= 0.001f) return 0.f;
    const float t = reveal * 3.f < 1.f ? reveal * 3.f : 1.f;
    return t * line_mode / presence_now;
}

// Liveline fades the plot's left edge out over this many points.
constexpr float kEdgeFadePx = 40.f;

// The tightest component in the table above.
constexpr float max_freq() {
    float m = 0.f;
    for (int i = 0; i < kHarmonicCount; ++i) {
        if (kHarmonics[i].freq > m) m = kHarmonics[i].freq;
    }
    return m;
}

// Vertices per cycle of that component needed to keep it from aliasing into a
// shape the curve doesn't have. Ten is comfortably past the point where the
// spline through the samples is indistinguishable from the real curve.
constexpr float kSamplesPerCycle = 10.f;

// How many vertices to sample the curve at across a plot `width_px` wide.
//
// The floor comes from the harmonic table rather than a literal, so retuning
// the curve can't silently undersample it — a narrow chart still gets enough
// vertices to resolve the finest component, it just spaces them more tightly.
//
// Both the idle curve and the morph capture size themselves through here, so
// the two are always sampled the same way and the hand-off has no shape
// discontinuity to hide.
inline int sample_count(float width_px) {
    const int floor_n =
        static_cast<int>(max_freq() / kTwoPi * kSamplesPerCycle) + 1;
    const int n = static_cast<int>(width_px / 8.f);
    const int ceil_n = 4 * floor_n;
    return n < floor_n ? floor_n : (n > ceil_n ? ceil_n : n);
}

}  // namespace vroom::loading_wave
