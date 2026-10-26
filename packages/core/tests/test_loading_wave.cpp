#include "doctest.h"

#include <cmath>
#include <initializer_list>

#include "loading_wave.h"

using namespace vroom::loading_wave;

namespace {

// Frames until `step` lands on 1 from 0, `dt` seconds apart.
template <typename Step>
int frames_to_land(Step step, float dt) {
    float v = 0.f;
    int frames = 0;
    while (v < 1.f && frames < 10000) {
        v = step(v, dt);
        ++frames;
    }
    return frames;
}

}  // namespace

TEST_CASE("the curve and breath hold their reference values") {
    // The wave scrolling leftward at 1 rad/s, and a breath of
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

TEST_CASE("a full period returns the curve and breath to where they started") {
    // This is what makes wrapping the phase clock seamless.
    for (int i = 0; i <= 24; ++i) {
        const float x = static_cast<float>(i) / 24.f;
        const float t = static_cast<float>(i) * 0.61f;
        CHECK(at(t + kPeriodSeconds, x) ==
              doctest::Approx(at(t, x)).epsilon(0.002));
        CHECK(breath(t + kPeriodSeconds) ==
              doctest::Approx(breath(t)).epsilon(0.002));
    }
}

TEST_CASE("sample_count resolves the sine at any width, within a bound") {
    for (float w : {-100.f, 0.f, 120.f, 1280.f, 100000.f}) {
        CHECK(static_cast<float>(sample_count(w)) >=
              kFreq / kTwoPi * kSamplesPerCycle);
    }
    CHECK(sample_count(320.f) > sample_count(160.f));
    CHECK(sample_count(100000.f) < 400);  // cheap enough to spline every frame
}

TEST_CASE("the reveal and fade-in step like Liveline's lerps") {
    // lerp(current, 1, speed) per 60fps frame, in Liveline's
    // src/useLivelineEngine.ts.
    float r = 0.f, a = 0.f, live_r = 0.f, live_a = 0.f;
    for (int i = 0; i < 20; ++i) {
        r = reveal_step(r, 1.f / 60.f);
        a = fade_in_step(a, 1.f / 60.f);
        live_r += (1.f - live_r) * 0.09f;
        live_a += (1.f - live_a) * 0.14f;
        CHECK(r == doctest::Approx(live_r).epsilon(0.001));
        CHECK(a == doctest::Approx(live_a).epsilon(0.001));
    }
}

TEST_CASE("the reveal lands in under a second at any frame rate") {
    const float at60 =
        static_cast<float>(frames_to_land(reveal_step, 1.f / 60.f)) / 60.f;
    CHECK(at60 > 0.8f);
    CHECK(at60 < 1.f);
    for (float fps : {30.f, 120.f}) {
        const float s =
            static_cast<float>(frames_to_land(reveal_step, 1.f / fps)) / fps;
        CHECK(s == doctest::Approx(at60).epsilon(0.05));
    }
}

TEST_CASE("a slow host thread neither cuts nor stretches the hand-off") {
    CHECK(frame_seconds(-0.01f) == 0.f);
    CHECK(frame_seconds(1.f / 60.f) == doctest::Approx(1.f / 60.f));
    CHECK(frame_seconds(30.f) == doctest::Approx(0.05f));
    // Frames 150ms apart, as on a screen still mounting around the chart.
    const int slow = frames_to_land(reveal_step, frame_seconds(0.15f));
    CHECK(slow >= 15);                              // motion, not a cut
    CHECK(static_cast<float>(slow) * 0.15f < 4.f);  // nor a crawl
}

TEST_CASE("the line resolves from the centre outward") {
    for (float x : {0.f, 0.5f, 1.f}) {
        CHECK(resolve(0.f, x) == 0.f);
        CHECK(resolve(1.f, x) == doctest::Approx(1.f));
    }
    CHECK(resolve(0.5f, 0.5f) > resolve(0.5f, 0.75f));
    CHECK(resolve(0.5f, 0.75f) > resolve(0.5f, 1.f));
    CHECK(resolve(0.5f, 0.25f) == doctest::Approx(resolve(0.5f, 0.75f)));
    CHECK(resolve(0.6f, 0.5f) == doctest::Approx(1.f));
}

// The bars grow out of wherever the line is this frame.
TEST_CASE("the reveal's line comes from the sine, or wherever a stage 2 left it") {
    const float elapsed = 3.f;
    const float frozen = 1.f;
    const float close = 0.2f;
    // No stage 2: the sine as it is now.
    CHECK(reveal_source_y_frac(elapsed, frozen, 0.25f, close, 0.f) ==
          doctest::Approx(y_frac(elapsed, 0.25f)));
    // A finished stage 2 already sits on the close.
    CHECK(reveal_source_y_frac(elapsed, frozen, 0.25f, close, 1.f) ==
          doctest::Approx(close));
    // Bars hanging off the plot read the curve at its edge.
    CHECK(reveal_source_y_frac(elapsed, frozen, 1.2f, close, 0.f) ==
          doctest::Approx(y_frac(elapsed, 1.f)));
}

TEST_CASE("a revealing bar grows about the line and lands with it") {
    const float source = 40.f;
    const float open = 100.f, high = 90.f, low = 130.f, close = 120.f;
    const float mid = 0.5f * (open + close);
    const auto lerp = [](float a, float b, float t) { return a + (b - a) * t; };

    for (const float p : {0.f, 0.1f, 0.25f, 0.5f, 0.8f, 1.f}) {
        CAPTURE(p);
        const float origin = reveal_bar_origin(source, close, mid, p);
        const float line = lerp(source, close, p);
        const float bar_open = lerp(origin, open, p);
        const float bar_close = lerp(origin, close, p);
        // Body and wick are their final sizes scaled by p...
        CHECK(bar_close - bar_open == doctest::Approx((close - open) * p));
        CHECK(lerp(origin, low, p) - lerp(origin, high, p) ==
              doctest::Approx((low - high) * p));
        // ...about a centre that leaves the line only as p² does.
        CHECK(0.5f * (bar_open + bar_close) - line ==
              doctest::Approx(p * p * (mid - close)));
    }
    // Out of nothing, on the line.
    CHECK(reveal_bar_origin(source, close, mid, 0.f) == source);
    // Landed: the line on the close, the bar on its prices.
    const float landed = reveal_bar_origin(source, close, mid, 1.f);
    CHECK(lerp(landed, high, 1.f) == doctest::Approx(high));
    CHECK(lerp(landed, close, 1.f) == doctest::Approx(close));
}

TEST_CASE("over candles the line gives way; as a line it becomes the series") {
    CHECK(presence(0.5f, 0.f) == doctest::Approx(0.125f));
    CHECK(presence(0.5f, 1.f) == doctest::Approx(1.f));
    CHECK(reveal_alpha(0.5f, 0.2f) == doctest::Approx(0.6f));
    CHECK(tint(0.4f, 0.f, presence(0.4f, 0.f)) == 0.f);
    CHECK(tint(1.f / 6.f, 1.f, 1.f) == doctest::Approx(0.5f));
    CHECK(tint(0.8f, 1.f, 1.f) == doctest::Approx(1.f));
}

TEST_CASE("the axes and price indicator come in on Liveline's ramps") {
    CHECK(ramp(0.6f, 0.4f, 0.8f) == doctest::Approx(0.5f));
    CHECK(ramp(1.f, 0.f, 1.f) == 1.f);
    CHECK(axis_alpha(0.25f) == 0.f);
    CHECK(axis_alpha(0.6f) == 1.f);
    // As a line: Liveline's badge, a quarter to halfway in.
    CHECK(price_alpha(0.25f, 1.f) == 0.f);
    CHECK(price_alpha(0.5f, 1.f) == 1.f);
    // Over candles: the close line's 0.4 to 0.8.
    CHECK(price_alpha(0.4f, 0.f) == 0.f);
    CHECK(price_alpha(0.8f, 0.f) == 1.f);
    // Only a line slides in, landing with the reveal.
    CHECK(price_slide(0.75f, 1.f) == doctest::Approx(0.25f));
    CHECK(price_slide(0.f, 0.f) == 0.f);
}
