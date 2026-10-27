// Global typeface for axis/label text rendering.
//
// Loaded once at startup by the bridge layer (which constructs a platform
// SkFontMgr and grabs the system default). Held as a process-global so all
// charts share it unless they set their own.

#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include "include/core/SkRefCnt.h"
#pragma clang diagnostic pop

class SkTypeface;
struct VroomChart;

namespace vroom {

// Returns the currently-installed axis typeface, or nullptr if none has been
// set yet. Drawing code should null-check.
sk_sp<SkTypeface> axis_typeface();

// Replaces the axis typeface. Charts pick it up on their next draw.
void set_axis_typeface(sk_sp<SkTypeface> typeface);

// The chart's own typeface, else the axis typeface.
sk_sp<SkTypeface> typeface(const VroomChart& chart);

}  // namespace vroom
