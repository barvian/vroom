#include "doctest.h"

#include <cmath>

#include "loading_wave.h"

using vroom::loading_wave::at;
using vroom::loading_wave::breath;
using vroom::loading_wave::kAmplitudeFrac;
using vroom::loading_wave::kBreathMax;
using vroom::loading_wave::kBreathMin;
using vroom::loading_wave::kDriftRadPerSecond;
using vroom::loading_wave::kFreq;
using vroom::loading_wave::kPeriodSeconds;
using vroom::loading_wave::kTwoPi;
using vroom::loading_wave::sample_count;
using vroom::loading_wave::y_frac;

TEST_CASE("the offset stays in -1..1") {
    for (int xi = 0; xi <= 60; ++xi) {
        for (int ti = 0; ti <= 60; ++ti) {
            const float v = at(static_cast<float>(ti) * 0.43f,
                               static_cast<float>(xi) / 60.f);
            CHECK(v >= -1.f);
            CHECK(v <= 1.f);
        }
    }
}

TEST_CASE("the curve travels toward the left") {
    // The phase is (k*x + w*t), so a feature at x after dt sits further left.
    const float dt = 0.5f;
    const float x0 = (kTwoPi * 0.25f) / kFreq;
    const float x1 = (kTwoPi * 0.25f - kDriftRadPerSecond * dt) / kFreq;
    CHECK(x1 < x0);
}

TEST_CASE("the curve and breath hold their reference values") {
    // The wave at a scroll of 1 rad/s, and a breath of
    // 0.22 + 0.08 * sin(t / 1.2s * pi).
    for (float t : {0.f, 0.7f, 3.1f, 11.f}) {
        for (int xi = 0; xi <= 20; ++xi) {
            const float x = static_cast<float>(xi) / 20.f;
            const float ref = std::sin(x * 6.3f + t);
            CHECK(at(t, x) == doctest::Approx(ref).epsilon(0.001));
            CHECK(y_frac(t, x) ==
                  doctest::Approx(0.5f + 0.07f * ref).epsilon(0.001));
        }
    }
    CHECK(breath(0.f) == doctest::Approx(0.22f));
    CHECK(breath(0.6f) == doctest::Approx(0.30f).epsilon(0.01));
    CHECK(breath(1.8f) == doctest::Approx(0.14f).epsilon(0.01));
}

TEST_CASE("a full period returns the whole curve to where it started") {
    // This is what makes wrapping the phase clock seamless.
    for (int xi = 0; xi <= 24; ++xi) {
        const float x = static_cast<float>(xi) / 24.f;
        const float ref = at(0.31f, x);
        for (float k : {1.f, 3.f, 12.f}) {
            CHECK(at(0.31f + kPeriodSeconds * k, x) ==
                  doctest::Approx(ref).epsilon(0.002));
        }
    }
}

TEST_CASE("the curve undulates gently, not as a lone swell or noise") {
    // Count local extremes across the plot: a crest and a trough or so, never
    // a flat arc and never jitter.
    const auto extremes = [](float t) {
        int n = 0;
        float prev = 0.f;
        bool have_prev = false;
        for (int i = 1; i <= 600; ++i) {
            const float d = at(t, static_cast<float>(i) / 600.f) -
                            at(t, static_cast<float>(i - 1) / 600.f);
            if (have_prev && ((d > 0.f) != (prev > 0.f))) ++n;
            prev = d;
            have_prev = true;
        }
        return n;
    };
    for (int i = 0; i <= 10; ++i) {
        const int n = extremes(kPeriodSeconds * static_cast<float>(i) / 11.f);
        CHECK(n >= 2);
        CHECK(n <= 3);
    }
}

TEST_CASE("y_frac centres the curve on the pane and stays well inside it") {
    for (int xi = 0; xi <= 40; ++xi) {
        for (int ti = 0; ti <= 30; ++ti) {
            const float y = y_frac(static_cast<float>(ti) * 0.83f,
                                   static_cast<float>(xi) / 40.f);
            CHECK(y >= 0.5f - kAmplitudeFrac);
            CHECK(y <= 0.5f + kAmplitudeFrac);
        }
    }
    // Restraint is the point: a crest should stay nowhere near the pane edges.
    CHECK(kAmplitudeFrac > 0.02f);
    CHECK(kAmplitudeFrac < 0.15f);
}

TEST_CASE("y_frac tracks the offset it is built from") {
    for (int xi = 0; xi <= 10; ++xi) {
        const float x = static_cast<float>(xi) / 10.f;
        CHECK(y_frac(1.7f, x) ==
              doctest::Approx(0.5f + kAmplitudeFrac * at(1.7f, x)));
    }
}

TEST_CASE("the breath stays faint and within its bounds") {
    // A dimmer on the axis text tone the line inherits, but never down to
    // nothing.
    CHECK(kBreathMin > 0.f);
    CHECK(kBreathMax < 0.5f);
    CHECK(kBreathMax > kBreathMin);
    for (int ti = 0; ti <= 200; ++ti) {
        const float b = breath(static_cast<float>(ti) * 0.17f);
        CHECK(b >= kBreathMin - 1e-5f);
        CHECK(b <= kBreathMax + 1e-5f);
    }
}

TEST_CASE("the breath wraps with the phase clock") {
    for (int ti = 0; ti <= 20; ++ti) {
        const float t = static_cast<float>(ti) * 0.61f;
        CHECK(breath(t + kPeriodSeconds) ==
              doctest::Approx(breath(t)).epsilon(0.002));
    }
}

TEST_CASE("the breath and the drift do not pulse together") {
    // Sharing a period would collapse the two into one visible beat.
    const float breath_period =
        kPeriodSeconds / vroom::loading_wave::kBreathCyclesPerPeriod;
    const float drift_period = kTwoPi / kDriftRadPerSecond;
    CHECK(std::fabs(breath_period - drift_period) > 0.5f);
}

TEST_CASE("a still curve sits mid-breath") {
    // Reduced motion pins elapsed time at 0, and the result has to be a
    // visible line rather than one caught at the bottom of its fade.
    CHECK(breath(0.f) == doctest::Approx((kBreathMin + kBreathMax) * 0.5f));
}

TEST_CASE("the drift is slow enough to read as waiting") {
    // Regression guard on feel: two earlier revisions ran several times this
    // fast and read as frantic.
    const float cross_seconds = kFreq / kDriftRadPerSecond;
    CHECK(cross_seconds > 4.f);
    CHECK(cross_seconds < 20.f);
}

TEST_CASE("sample_count resolves the sine at any width") {
    // The floor is the point of this function: even a narrow chart has to
    // carry enough vertices that the sine isn't aliased away.
    const float crests = kFreq / kTwoPi;
    for (float w : {-100.f, 0.f, 120.f, 480.f, 1280.f, 4000.f, 100000.f}) {
        CHECK(static_cast<float>(sample_count(w)) >=
              crests * vroom::loading_wave::kSamplesPerCycle);
    }
}

TEST_CASE("sample_count grows with width but stays bounded") {
    CHECK(sample_count(320.f) > sample_count(160.f));
    CHECK(sample_count(100000.f) == sample_count(200000.f));
    CHECK(sample_count(100000.f) < 400);  // cheap enough to spline every frame
}

namespace {

// Frames until `step` lands on 1, at `fps`.
template <typename Step>
int frames_to_land(Step step, float from, float fps) {
    float v = from;
    int frames = 0;
    while (v < 1.f && frames < 10000) {
        v = step(v, 1.f / fps);
        ++frames;
    }
    return frames;
}

}  // namespace

TEST_CASE("the reveal steps like Liveline's chartReveal lerp") {
    // lerp(current, 1, CHART_REVEAL_SPEED_FWD) per 60fps frame, in Liveline's
    // src/useLivelineEngine.ts, snapping within 0.005 of the target.
    float r = 0.f;
    float liveline = 0.f;
    for (int i = 0; i < 40; ++i) {
        r = vroom::loading_wave::reveal_step(r, 1.f / 60.f);
        liveline += (1.f - liveline) * 0.09f;
        if (1.f - liveline < 0.005f) liveline = 1.f;
        CHECK(r == doctest::Approx(liveline).epsilon(0.001));
    }
}

TEST_CASE("the reveal lands in under a second at any frame rate") {
    const auto step = [](float v, float dt) {
        return vroom::loading_wave::reveal_step(v, dt);
    };
    const float at60 = static_cast<float>(frames_to_land(step, 0.f, 60.f)) / 60.f;
    CHECK(at60 > 0.8f);
    CHECK(at60 < 1.f);
    for (float fps : {30.f, 120.f}) {
        const float s = static_cast<float>(frames_to_land(step, 0.f, fps)) / fps;
        CHECK(s == doctest::Approx(at60).epsilon(0.05));
    }
}

TEST_CASE("the line fades in like Liveline's loading alpha") {
    const auto step = [](float v, float dt) {
        return vroom::loading_wave::fade_in_step(v, dt);
    };
    float a = 0.f;
    float liveline = 0.f;
    for (int i = 0; i < 20; ++i) {
        a = step(a, 1.f / 60.f);
        liveline += (1.f - liveline) * 0.14f;
        CHECK(a == doctest::Approx(liveline).epsilon(0.001));
    }
    // Quick enough that a cached response doesn't flash a placeholder.
    const float s = static_cast<float>(frames_to_land(step, 0.f, 60.f)) / 60.f;
    CHECK(s < 0.6f);
}

TEST_CASE("a slow host thread neither cuts nor stretches the hand-off") {
    using vroom::loading_wave::frame_seconds;
    using vroom::loading_wave::reveal_step;
    const auto frames_to_land_at = [](float dt) {
        float v = 0.f;
        int frames = 0;
        while (v < 1.f && frames < 10000) {
            v = reveal_step(v, dt);
            ++frames;
        }
        return frames;
    };
    // Frames 150ms apart, as on a screen still mounting around the chart.
    const float gap = 0.15f;
    const int slow = frames_to_land_at(frame_seconds(gap));
    // Enough drawn frames to read as motion rather than a cut...
    CHECK(slow >= 15);
    // ...without the crawl of counting each one as a nominal 1/60s.
    CHECK(static_cast<float>(slow) * gap < 4.f);
    CHECK(static_cast<float>(frames_to_land_at(1.f / 60.f)) * gap > 8.f);
    // At a steady 60fps the cap never engages.
    CHECK(frames_to_land_at(frame_seconds(1.f / 60.f)) ==
          frames_to_land_at(1.f / 60.f));
}

TEST_CASE("the line's frame clock keeps real time within bounds") {
    using vroom::loading_wave::frame_seconds;
    using vroom::loading_wave::kMaxFrameSeconds;
    CHECK(frame_seconds(0.f) == 0.f);
    CHECK(frame_seconds(-0.01f) == 0.f);
    CHECK(frame_seconds(1.f / 60.f) == doctest::Approx(1.f / 60.f));
    CHECK(frame_seconds(0.04f) == doctest::Approx(0.04f));
    CHECK(frame_seconds(0.25f) == kMaxFrameSeconds);
    CHECK(frame_seconds(30.f) == kMaxFrameSeconds);
    CHECK(kMaxFrameSeconds == doctest::Approx(0.05f));
}

TEST_CASE("the line resolves from the centre outward") {
    using vroom::loading_wave::resolve;
    for (float x : {0.f, 0.2f, 0.5f, 0.8f, 1.f}) {
        CHECK(resolve(0.f, x) == 0.f);
        CHECK(resolve(1.f, x) == doctest::Approx(1.f));
    }
    for (float r : {0.2f, 0.5f, 0.8f}) {
        CHECK(resolve(r, 0.5f) >= resolve(r, 0.75f));
        CHECK(resolve(r, 0.75f) >= resolve(r, 1.f));
        CHECK(resolve(r, 0.25f) == doctest::Approx(resolve(r, 0.75f)));
    }
    CHECK(resolve(0.5f, 0.5f) > resolve(0.5f, 0.75f));
    CHECK(resolve(0.5f, 0.75f) > resolve(0.5f, 1.f));
    // The centre lands well before the edges do.
    CHECK(resolve(0.6f, 0.5f) == doctest::Approx(1.f));
    CHECK(resolve(0.6f, 0.f) < 0.5f);
}

TEST_CASE("over candles the line gives way fast; in line mode it stays") {
    using vroom::loading_wave::presence;
    for (float r : {0.f, 0.3f, 0.7f, 1.f}) {
        CHECK(presence(r, 1.f) == doctest::Approx(1.f));
        CHECK(presence(r, 0.f) ==
              doctest::Approx((1.f - r) * (1.f - r) * (1.f - r)));
    }
    CHECK(presence(0.5f, 0.f) < 0.15f);
}

TEST_CASE("the line brightens from its breath to full through the reveal") {
    using vroom::loading_wave::reveal_alpha;
    CHECK(reveal_alpha(0.f, 0.22f) == doctest::Approx(0.22f));
    CHECK(reveal_alpha(1.f, 0.22f) == doctest::Approx(1.f));
    CHECK(reveal_alpha(0.5f, 0.2f) == doctest::Approx(0.6f));
}

TEST_CASE("only a line-mode reveal tints the line, by a third of the way") {
    using vroom::loading_wave::presence;
    using vroom::loading_wave::tint;
    for (float r : {0.f, 0.4f, 0.9f}) {
        CHECK(tint(r, 0.f, presence(r, 0.f)) == 0.f);
    }
    CHECK(tint(0.f, 1.f, 1.f) == 0.f);
    CHECK(tint(1.f / 6.f, 1.f, 1.f) == doctest::Approx(0.5f));
    CHECK(tint(1.f / 3.f, 1.f, 1.f) == doctest::Approx(1.f));
    CHECK(tint(0.8f, 1.f, 1.f) == doctest::Approx(1.f));
}

TEST_CASE("ramp is a clamped smoothstep") {
    using vroom::loading_wave::ramp;
    CHECK(ramp(0.3f, 0.4f, 0.8f) == 0.f);
    CHECK(ramp(0.6f, 0.4f, 0.8f) == doctest::Approx(0.5f));
    CHECK(ramp(0.9f, 0.4f, 0.8f) == 1.f);
    CHECK(ramp(0.25f, 0.f, 1.f) == doctest::Approx(0.15625f));
}

TEST_CASE("the axes come up on Liveline's grid ramp through the reveal") {
    using vroom::loading_wave::axis_alpha;
    CHECK(axis_alpha(0.25f) == 0.f);
    CHECK(axis_alpha(0.425f) == doctest::Approx(0.5f));
    CHECK(axis_alpha(0.6f) == 1.f);
}

TEST_CASE("the price indicator follows Liveline's badge as a line, its close line over candles") {
    using vroom::loading_wave::price_alpha;
    using vroom::loading_wave::price_slide;
    // As a line: nothing until a quarter in, fully up by halfway.
    CHECK(price_alpha(0.25f, 1.f) == 0.f);
    CHECK(price_alpha(0.375f, 1.f) == doctest::Approx(0.5f));
    CHECK(price_alpha(0.5f, 1.f) == 1.f);
    // Over candles: the close line's 0.4 to 0.8.
    CHECK(price_alpha(0.4f, 0.f) == 0.f);
    CHECK(price_alpha(0.6f, 0.f) == doctest::Approx(0.5f));
    CHECK(price_alpha(0.8f, 0.f) == 1.f);
    // Only a line slides in from the centre, and it lands with the reveal.
    CHECK(price_slide(0.f, 1.f) == 1.f);
    CHECK(price_slide(0.75f, 1.f) == doctest::Approx(0.25f));
    CHECK(price_slide(1.f, 1.f) == 0.f);
    CHECK(price_slide(0.f, 0.f) == 0.f);
}
