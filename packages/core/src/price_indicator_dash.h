// Dash layout for the current-price indicator's line (see
// price_indicator.cpp).
//
// The theme's dash and gap are the lengths you see. A round cap adds half the
// stroke width to each end of a dash, so that much comes out of the on interval
// and goes into the off one, keeping the period at dash + gap. A dash shorter
// than the width bottoms out at a dot.
//
// Skia-free and header-only so the unit tests can cover it; see
// tests/test_price_indicator_anim.cpp.

#pragma once

#include <algorithm>

namespace vroom::price_indicator_dash {

// SkDashPathEffect intervals.
struct Intervals {
    float on;
    float off;  // 0 = draw solid, with no dash effect
};

inline Intervals intervals(float dash, float gap, float width, bool round_cap) {
    dash = std::max(dash, 0.f);
    if (gap <= 0.f) return {dash, 0.f};
    if (!round_cap) return {dash, gap};
    const float on = std::max(dash - width, 0.f);
    return {on, dash + gap - on};
}

// Where the stroke starts so the pattern hangs off `right`, the price pill's
// edge or wherever the line ends. The line draws from here to the left at phase
// 0, so a whole dash always ends flush with `right` however long the line is,
// and the pattern only moves when `right` does. A round cap reaches half the
// width past its stroke, so the stroke starts that much short of `right`.
inline float stroke_start(float right, float width, bool round_cap) {
    return round_cap ? right - width * 0.5f : right;
}

}  // namespace vroom::price_indicator_dash
