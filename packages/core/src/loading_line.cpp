#include "loading_line.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkPoint.h"
#include "include/core/SkRect.h"
#pragma clang diagnostic pop

#include <algorithm>
#include <cstddef>
#include <vector>

#include "chart.h"
#include "color_lerp.h"
#include "curve.h"
#include "gradient.h"
#include "loading_wave.h"
#include "theme.h"
#include "tip_geometry.h"
#include "tip_pulse.h"
#include "viewport.h"

namespace vroom::loading_line {

namespace {

// The series line's width, so the placeholder has the weight of the line that
// replaces it.
float stroke_width(const VroomChart& chart) {
    return chart.theme.floats[VROOM_FLOAT_LINE_WIDTH_PX];
}

float lerp(float a, float b, float t) { return a + (b - a) * t; }

// Multiplies into whatever alpha the resolved color already carries.
SkColor faded(SkColor c, float a) {
    const float scaled = static_cast<float>(SkColorGetA(c)) *
                         std::clamp(a, 0.f, 1.f);
    return SkColorSetA(c, static_cast<U8CPU>(scaled + 0.5f));
}

// The loading line's color. A transparent `skeleton` inherits the axis text
// color, the same sentinel convention the candle border and wick colors use,
// and the tone Liveline draws its loading line in. The breath keeps it faint.
SkColor stroke_color(const VroomChart& chart) {
    const SkColor c = chart.theme.colors[VROOM_COLOR_SKELETON];
    return SkColorGetA(c) == 0 ? chart.theme.colors[VROOM_COLOR_AXIS_TEXT] : c;
}

// Emits `pts` as a monotone cubic — the same curve the line chart draws (see
// curve.h), so the loading line and the series it hands off to are shaped by
// the same math and the transition has no renderer seam to hide.
//
// Monotone rather than a plain spline matters even here: by the end of the
// morph these vertices *are* real price data, and an unconstrained curve would
// overshoot a sharp reversal and bow outside the candle it is supposed to pass
// through.
SkPath spline(const std::vector<SkPoint>& pts, float tension = 1.f) {
    SkPathBuilder path;
    if (pts.empty()) return path.detach();
    path.moveTo(pts[0]);
    // Below three points there is no interior vertex to fit a tangent to.
    if (pts.size() < 3) {
        for (std::size_t i = 1; i < pts.size(); ++i) path.lineTo(pts[i]);
        return path.detach();
    }

    const auto secant_at = [&](std::size_t i) {
        return curve::secant(pts[i].fX, pts[i].fY,
                             pts[i + 1].fX, pts[i + 1].fY);
    };
    const auto tangent_at = [&](std::size_t i) {
        if (i == 0) return secant_at(0);
        if (i + 1 == pts.size()) return secant_at(pts.size() - 2);
        return curve::monotone_tangent(secant_at(i - 1), secant_at(i));
    };

    for (std::size_t i = 0; i + 1 < pts.size(); ++i) {
        // Flat or backwards spacing has no meaningful tangent, and curving
        // through it would fold the line back on itself.
        if (!(pts[i + 1].fX > pts[i].fX)) {
            path.lineTo(pts[i + 1]);
            continue;
        }
        const curve::Controls c = curve::segment_controls(
            pts[i].fX, pts[i].fY, pts[i + 1].fX, pts[i + 1].fY,
            tangent_at(i), tangent_at(i + 1), tension);
        path.cubicTo(c.c1x, c.c1y, c.c2x, c.c2y, pts[i + 1].fX, pts[i + 1].fY);
    }
    return path.detach();
}

void stroke_path(SkCanvas* canvas,
                 const SkPath& path,
                 SkColor color,
                 float width,
                 float alpha) {
    SkPaint p;
    p.setStyle(SkPaint::kStroke_Style);
    p.setStrokeWidth(width);
    p.setStrokeCap(SkPaint::kRound_Cap);
    p.setStrokeJoin(SkPaint::kRound_Join);
    p.setAntiAlias(true);
    p.setColor(faded(color, alpha));
    canvas->drawPath(path, p);
}

void stroke_path(SkCanvas* canvas,
                 const VroomChart& chart,
                 const SkPath& path,
                 float alpha) {
    stroke_path(canvas, path, stroke_color(chart), stroke_width(chart), alpha);
}

// Pinned to phase 0 under reduced motion, which leaves a still curve at
// mid-breath rather than nothing — the placeholder is still worth showing.
float phase(const VroomChart& chart) {
    return chart.loading_animate ? chart.loading_elapsed_s : 0.f;
}

// Stage 1: the curve alone, sampled across the whole plot.
SkPath idle_path(const VroomChart& chart, float area_w, float pane_h) {
    const int samples = loading_wave::sample_count(area_w);
    const float elapsed = phase(chart);
    std::vector<SkPoint> pts;
    pts.reserve(static_cast<std::size_t>(samples) + 1);
    for (int i = 0; i <= samples; ++i) {
        const float xf = static_cast<float>(i) / static_cast<float>(samples);
        pts.push_back(SkPoint{xf * area_w,
                              loading_wave::y_frac(elapsed, xf) * pane_h});
    }
    return spline(pts);
}

// Stage 2: the captured vertices, eased from the frozen curve toward the
// candle closes. `t` of 1 is the shape the candles grow out of. The centre
// resolves first and the edges last, as Liveline's does.
SkPath morph_path(const VroomChart& chart,
                  const Layout& lay,
                  float area_w,
                  float pane_h,
                  float t) {
    std::vector<SkPoint> pts;
    pts.reserve(chart.loading_line.size());
    for (const LinePoint& pt : chart.loading_line) {
        const float from_y = pt.from_y * pane_h;
        const float to_y = y_at_fraction(lay, pt.to_y);
        const float local = loading_wave::resolve(t, pt.x);
        pts.push_back(SkPoint{pt.x * area_w, from_y + (to_y - from_y) * local});
    }
    return spline(pts);
}

// Stage 3's vertices at `reveal`. Unlike stage 2 the source keeps moving: each
// vertex leaves the sine as it is *now*, so the wave carries on until the data
// has the line. The padding outside the data slides in onto the end candles,
// so at 1 the line spans exactly the series. `from_t` is how far a host-driven
// stage 2 already took the line, if one ran.
//
// Aimed afresh each frame, as Liveline morphs toward its live data: the
// framing, the eased y-range and the bars can all move under a reveal, and a
// line still heading for where they were would land off them.
std::vector<SkPoint> reveal_points(const VroomChart& chart,
                                   const Layout& lay,
                                   float area_w,
                                   float pane_h,
                                   float reveal,
                                   float from_t) {
    const float elapsed = phase(chart);
    const auto aimed = chart.aim_loading_line(chart.loading_frozen_s);
    std::vector<SkPoint> pts;
    pts.reserve(aimed.size());
    for (const LinePoint& pt : aimed) {
        const float xf = lerp(pt.x, pt.to_x, reveal);
        const float to_y = y_at_fraction(lay, pt.to_y);
        const float live_y =
            loading_wave::y_frac(elapsed, std::clamp(xf, 0.f, 1.f)) * pane_h;
        const float frozen_y = pt.from_y * pane_h;
        const float stage2_y =
            lerp(frozen_y, to_y, loading_wave::resolve(from_t, pt.x));
        const float source_y = lerp(live_y, stage2_y, from_t);
        pts.push_back(SkPoint{
            xf * area_w,
            lerp(source_y, to_y, loading_wave::resolve(reveal, xf))});
    }
    return pts;
}

// Stage 3's line this frame, plus what tints it toward the series line.
struct RevealFrame {
    std::vector<SkPoint> pts;
    float line_mode = 0.f;
    float presence = 0.f;
    float tint = 0.f;
    float tension = 1.f;
};

RevealFrame reveal_frame(const VroomChart& chart, const Layout& lay) {
    RevealFrame f{};
    if (chart.loading_line.empty()) return f;
    const float area_w = candle_area_width(lay);
    const float pane_h = price_pane_bottom(lay);
    if (area_w <= 0.f || pane_h <= 0.f) return f;

    const float r = chart.loading_reveal;
    f.line_mode = std::clamp(chart.morph_fade, 0.f, 1.f);
    f.presence = loading_wave::presence(r, f.line_mode);
    if (f.presence <= 0.01f) return f;
    // Tinting toward the series is also what carries the stroke's width and
    // curve over to the series line's, so the line it lands as is the one
    // that replaces it.
    f.tint = loading_wave::tint(r, f.line_mode, f.presence);
    f.tension = lerp(1.f, chart.theme.floats[VROOM_FLOAT_LINE_TENSION], f.tint);
    f.pts = reveal_points(chart, lay, area_w, pane_h, r, chart.loading_line_t);
    return f;
}

}  // namespace

void draw(SkCanvas* canvas, const VroomChart& chart, const Layout& lay) {
    if (!canvas) return;
    const float area_w = candle_area_width(lay);
    const float pane_h = price_pane_bottom(lay);
    if (area_w <= 0.f || pane_h <= 0.f) return;

    const float b = loading_wave::breath(phase(chart));

    // A capture present means the data has landed and the line is on its way to
    // the candle closes; absent means nothing has arrived yet. The breath is
    // frozen with the phase, so the morph holds the line's last brightness.
    if (chart.loading_line.empty()) {
        stroke_path(canvas, chart, idle_path(chart, area_w, pane_h), b);
        return;
    }
    stroke_path(canvas, chart,
                morph_path(chart, lay, area_w, pane_h, chart.loading_line_t),
                b);
}

void draw_reveal(SkCanvas* canvas, const VroomChart& chart, const Layout& lay) {
    if (!canvas) return;
    const RevealFrame frame = reveal_frame(chart, lay);
    const auto& pts = frame.pts;
    if (pts.empty()) return;

    const float r = chart.loading_reveal;
    const float line_mode = frame.line_mode;
    const float lp = frame.presence;
    const auto& f = chart.theme.floats;
    const float series_w = f[VROOM_FLOAT_LINE_WIDTH_PX];
    const SkColor color = static_cast<SkColor>(
        lerp_argb(stroke_color(chart), chart.theme.colors[VROOM_COLOR_LINE],
                  frame.tint));
    const float alpha =
        lp * loading_wave::reveal_alpha(r, loading_wave::breath(phase(chart)));

    // The line and its tip draw opaque into one layer that takes the alpha, so
    // the dot doesn't stack its own over the line's end into a seam.
    SkAutoCanvasRestore restore(canvas, false);
    if (alpha < 1.f) canvas->saveLayerAlphaf(nullptr, alpha);
    stroke_path(canvas, spline(pts, frame.tension), color, series_w, 1.f);

    // The series line's tip dot, standing in for it with the rest of the
    // series line: in the line's color, fading only with the layer.
    if (line_mode <= 0.f || f[VROOM_FLOAT_LINE_TIP_DOT] <= 0.5f) return;
    const float dot_r =
        tip_geometry::of(series_w, f[VROOM_FLOAT_LINE_TIP_DOT_RADIUS_PX]).dot_r;
    // The ring joins partway, as Liveline's does, on the phase the series
    // tip's will carry on from.
    if (r > loading_wave::kPulseFrom && f[VROOM_FLOAT_LINE_TIP_PULSE] > 0.5f) {
        const tip_pulse::Frame ring_f = tip_pulse::at(
            chart.tip_pulse_elapsed_s / tip_pulse::kPeriodSeconds,
            f[VROOM_FLOAT_LINE_TIP_PULSE_OPACITY]);
        if (ring_f.alpha > 0.f) {
            SkPaint ring;
            ring.setAntiAlias(true);
            ring.setStyle(SkPaint::kStroke_Style);
            ring.setColor(color);
            ring.setAlphaf(ring.getAlphaf() * ring_f.alpha);
            ring.setStrokeWidth(dot_r * tip_pulse::kWidthMul);
            canvas->drawCircle(pts.back(), dot_r * ring_f.radius_mul, ring);
        }
    }
    SkPaint dot;
    dot.setAntiAlias(true);
    dot.setColor(color);
    canvas->drawCircle(pts.back(), dot_r, dot);
}

void draw_reveal_fill(SkCanvas* canvas,
                      const VroomChart& chart,
                      const Layout& lay) {
    if (!canvas) return;
    const RevealFrame frame = reveal_frame(chart, lay);
    if (frame.pts.size() < 2) return;
    // Liveline's: the wash comes up with the reveal, in line mode only.
    const float alpha =
        std::clamp(chart.theme.floats[VROOM_FLOAT_LINE_GRADIENT_OPACITY], 0.f,
                   1.f) *
        frame.line_mode * chart.loading_reveal;
    if (alpha <= 0.f) return;

    const float area_w = candle_area_width(lay);
    const float pane_h = price_pane_bottom(lay);
    const SkPath line = spline(frame.pts, frame.tension);
    const SkRect b = line.getBounds();
    const float top = std::max(b.top(), 0.f);
    if (top >= pane_h) return;

    // The same closed region and ramp the series fill draws (see
    // ma_overlay::draw_close_gradient), so the swap at the end is invisible.
    SkPathBuilder area(line);
    area.lineTo(b.right(), pane_h);
    area.lineTo(b.left(), pane_h);
    area.close();
    const SkPoint ends[2] = {SkPoint::Make(0.f, top),
                             SkPoint::Make(0.f, pane_h)};
    SkPaint fill;
    fill.setAntiAlias(true);
    fill.setStyle(SkPaint::kFill_Style);
    fill.setShader(linear_alpha_ramp(
        ends, static_cast<SkColor>(chart.theme.colors[VROOM_COLOR_LINE]), alpha,
        0.f));
    canvas->save();
    canvas->clipRect(SkRect::MakeLTRB(0.f, 0.f, area_w, pane_h));
    canvas->drawPath(area.detach(), fill);
    canvas->restore();
}

}  // namespace vroom::loading_line
