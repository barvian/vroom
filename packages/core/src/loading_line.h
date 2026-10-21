// The loading line: a single stroke across the plot standing in for a series
// that hasn't arrived yet, and the bridge the real candles grow out of.
//
// Three stages, all drawn by the one function here:
//
//   1. idle    — a travelling sine across the full width (see loading_wave.h)
//   2. morph   — that sine, frozen, easing into a polyline through the
//                close of every candle about to be drawn
//   3. reveal  — the still-moving sine resolving onto those closes, centre
//                first, while the candles grow out of it and the line gives
//                way to them (or, in line mode, becomes the series line)
//
// Stage 2 is the host-driven version of stage 3's line, kept for hosts that
// still drive it; the bundled ones go straight from 1 to 3.
//
// Stages 1 and 2 run instead of the chart, so the axis text, price badge,
// crosshair and indicator panes stay suppressed until the data is really
// there. Stage 3 runs over the top of the normal scene.

#pragma once

class SkCanvas;
struct VroomChart;

namespace vroom {
struct Layout;
}

namespace vroom::loading_line {

// Stages 1 and 2, in place of the chart. Which one it draws depends on whether
// the chart holds a capture (see VroomChart::begin_loading_morph).
void draw(SkCanvas* canvas, const VroomChart& chart, const Layout& lay);

// Stage 3, over the scene, at `chart.loading_reveal`. In line mode this line
// stands in for the series line, tip dot included, until the reveal lands.
void draw_reveal(SkCanvas* canvas, const VroomChart& chart, const Layout& lay);

// The line-mode wash under stage 3's line, standing in for the series' own so
// the fill sits under the line as it is rather than where it's heading.
// Drawn where the series fill would be, beneath the candles and the line.
void draw_reveal_fill(SkCanvas* canvas,
                      const VroomChart& chart,
                      const Layout& lay);

}  // namespace vroom::loading_line
