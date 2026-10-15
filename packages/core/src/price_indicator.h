// Current-price indicator — a dotted horizontal line at the latest candle's
// close, spanning the candle area and ending in a rounded price tag in the
// y-axis strip. Red/green by whether the latest period closed up or down. Kept
// in its own module alongside candles / labels / crosshair so the chart
// orchestrator stays thin.

#pragma once

#include <algorithm>

class SkCanvas;
struct VroomChart;

namespace vroom {
struct CandleSnapshot;
struct Layout;
struct PriceBounds;
}  // namespace vroom

namespace vroom::price_indicator {

// Draws the line at the latest close's y, from the left edge to the price
// badge when that badge is drawn, otherwise to `candle_right`. `candle_area_h`
// is the y of the x-axis separator; the indicator is skipped if the close maps
// outside [0, candle_area_h].
//
// `morph_from` is the newest candle's outgoing capture (slot 0 of
// VroomChart::morph_from), or null to draw the settled close. When present the
// level eases across `morph_t` on the same clock as the candle it marks, so the
// badge tracks the bar instead of jumping ahead of it — see
// price_indicator_anim.h. Callers must only pass a capture that pairs with the
// newest candle (tip_anchor.h).
void draw(SkCanvas* canvas,
          const VroomChart& chart,
          const Layout& lay,
          const PriceBounds& bounds,
          float candle_right,
          float candle_area_h,
          const CandleSnapshot* morph_from = nullptr,
          float morph_t = 1.f);

}  // namespace vroom::price_indicator

// Layout for that line's dash. The stroke is a SkDashPathEffect, the same
// effect the crosshair, price lines, fair-value gaps and RSI bands use; those
// pass a fixed pattern, and this is the visible-length adjustment they don't
// need. The theme's dash and gap are the lengths you see. A round cap adds
// half the stroke width to each end, so that much comes out of the on interval
// and goes into the off one, keeping the period at dash + gap. A dash shorter
// than the width bottoms out at a dot. Skia-free so the unit tests can cover
// it; see tests/test_price_indicator_anim.cpp.
namespace vroom::price_indicator_dash {

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
