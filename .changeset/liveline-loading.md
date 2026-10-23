---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

Redraw the `loading` line as a single sine wave, 7% of the pane in amplitude, drifting leftward, stroked at `lineWidth`, breathing between 14% and 30% of `skeleton`, which now inherits `axisText` instead of `grid`. On hand-off the moving line resolves centre-first onto the candle closes over about 0.9s on Liveline's ease, while the candles grow out of it; in line mode it becomes the series line.

The hand-off now runs on its own clock: `transitionMs` and `transitionEasing` no longer set its duration or easing, though `transitionMs={0}` still snaps it. If you drive the `@vroomchart/core-wasm` handle directly, call `beginLoadingMorph()` then `beginLoadingReveal()` and keep rendering while `isAnimating()` is true; you no longer drive `setIntervalMorph` to finish it.
