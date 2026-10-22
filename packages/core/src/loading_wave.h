// The idle animation the loading line rides while a series is being fetched.
// A position across the plot and an elapsed time in; a vertical offset and a
// brightness out. Also the curves of the hand-off into the data, further down.
//
// A single sine travelling leftward, the way a live series scrolls, kept small
// and faint: a hint that the chart is alive, not competition for the data.
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

// Radians across the full plot width: about one crest per screen.
constexpr float kFreq = 6.3f;

constexpr float kDriftRadPerSecond = 1.0f;

// What callers wrap elapsed time by, so a chart left loading doesn't lose
// float precision on the phase. Ten of the sine's cycles, so the breath below
// also fits a whole number of times and the wrap is seamless.
constexpr float kPeriodSeconds = 10.f * kTwoPi / kDriftRadPerSecond;

// Peak displacement from the centreline, as a fraction of the pane height.
constexpr float kAmplitudeFrac = 0.07f;

// Breathing opacity, a dimmer on the color.
constexpr float kBreathMin = 0.14f;
constexpr float kBreathMax = 0.30f;
// Liveline breathes every 2.4s; 26 per wrap is the nearest whole count.
constexpr float kBreathCyclesPerPeriod = 26.f;

// Offset at `x_frac` (0 = left edge of the plot, 1 = right) and `elapsed_s`, in
// -1 .. 1. Phase runs as (k*x + w*t), which walks the crests leftward.
inline float at(float elapsed_s, float x_frac) {
    return std::sin(kFreq * x_frac + kDriftRadPerSecond * elapsed_s);
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
// one: real time up to Liveline's 50ms cap. Not the chart's shared dt, which
// counts a frame over 0.1s as 1/60s and crawls on a busy host thread; the cap
// keeps the hand-off a motion rather than a cut there.
constexpr float kMaxFrameSeconds = 0.05f;
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
// 1 once the chart has taken over, about 0.94s later.
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

// The line's share of the frame. In line mode it *is* the series and stays;
// over candles it gives way fast so it never reads as a line chart.
inline float presence(float reveal, float line_mode) {
    const float out = (1.f - reveal) * (1.f - reveal) * (1.f - reveal);
    return line_mode > out ? line_mode : out;
}

// The line's opacity through the hand-off: up from the breath to full.
inline float reveal_alpha(float reveal, float breath_now) {
    return breath_now + (1.f - breath_now) * reveal;
}

// How far the line has tinted from `skeleton` toward the series color.
inline float tint(float reveal, float line_mode, float presence_now) {
    if (presence_now <= 0.001f) return 0.f;
    const float t = reveal * 3.f < 1.f ? reveal * 3.f : 1.f;
    return t * line_mode / presence_now;
}

// The gridlines and axis labels through the hand-off.
inline float axis_alpha(float reveal) { return ramp(reveal, 0.25f, 0.6f); }

// The current-price indicator's opacity through the hand-off: Liveline's badge
// as a line, its close-price line over candles.
inline float price_alpha(float reveal, float line_mode) {
    float badge = (reveal - 0.25f) / 0.25f;
    badge = badge < 0.f ? 0.f : (badge > 1.f ? 1.f : badge);
    return badge * line_mode + ramp(reveal, 0.4f, 0.8f) * (1.f - line_mode);
}

// How much of the way from the pane's centre to the price the indicator has
// still to travel. Only a line slides in.
inline float price_slide(float reveal, float line_mode) {
    return (1.f - reveal) * line_mode;
}

// Liveline starts the live dot's pulse once the reveal passes this.
constexpr float kPulseFrom = 0.6f;

// Vertices per cycle of the sine needed to keep it from aliasing into a
// shape the curve doesn't have. Ten is comfortably past the point where the
// spline through the samples is indistinguishable from the real curve.
constexpr float kSamplesPerCycle = 10.f;

// How many vertices to sample the curve at across a plot `width_px` wide.
//
// The floor comes from kFreq rather than a literal, so retuning the curve can't
// silently undersample it.
//
// Both the idle curve and the morph capture size themselves through here, so
// the two are always sampled the same way and the hand-off has no shape
// discontinuity to hide.
inline int sample_count(float width_px) {
    const int floor_n =
        static_cast<int>(kFreq / kTwoPi * kSamplesPerCycle) + 1;
    const int n = static_cast<int>(width_px / 8.f);
    const int ceil_n = 4 * floor_n;
    return n < floor_n ? floor_n : (n > ceil_n ? ceil_n : n);
}

}  // namespace vroom::loading_wave
