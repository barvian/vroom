// How big the line chart's tip marker is, and how much gutter it needs.
//
// The dot marks the newest close, which on a view pinned to the latest bar sits
// half a slot from the right edge of the plot — a few pixels. The dot's own
// radius is larger than that, so it can only be drawn in full if it is allowed
// to spill into the gutter between the plot and the y-axis strip. That makes the
// marker's size a layout input, not just a paint detail, so the renderer
// (draw_close_tip in ma_overlay.cpp) and the layout (VroomChart::layout) read it
// from here rather than each carrying its own copy.
//
// The pulse ring is deliberately not part of this. At its widest it is 3.5x the
// dot radius, and reserving that much gutter would eat the plot; it is
// allowed to clip against the axis.
//
// Skia-free and header-only so the unit tests can cover it; see
// tests/test_tip_geometry.cpp.

#pragma once

#include <algorithm>

namespace vroom::tip_geometry {

// Gap left between the dot's outer edge and the y-axis strip. The dot touching
// the price labels reads as a rendering fault even when nothing is clipped.
constexpr float kClearPx = 4.f;

// Default for VROOM_FLOAT_LINE_TIP_DOT_SCALE: the dot's radius as a multiple of
// the line width.
constexpr float kDefaultDotScale = 2.f;

struct Geometry {
    float dot_r;  // the filled dot in the line's color
};

// The dot scales off the stroke, which keeps the marker proportionate at any
// line width; the floor stops a hairline chart from getting an invisible dot.
// A `dot_scale` <= 0 means unset.
inline Geometry of(float line_width, float dot_scale = kDefaultDotScale) {
    const float w = line_width > 0.f ? line_width : 1.5f;
    const float scale = dot_scale > 0.f ? dot_scale : kDefaultDotScale;
    return Geometry{std::max(2.f, w * scale)};
}

// Gutter width that lets the dot draw in full with `kClearPx` to spare.
//
// draw_close_tip drops the marker once its center passes the plot's right edge,
// so the center is at worst flush with that edge and the dot overhangs it by
// exactly `dot_r`. A gutter of that plus the clearance therefore makes "the
// dot never touches the axis strip" true by construction, whatever the window.
inline float gutter_px(float line_width, float dot_scale = kDefaultDotScale) {
    return of(line_width, dot_scale).dot_r + kClearPx;
}

}  // namespace vroom::tip_geometry
