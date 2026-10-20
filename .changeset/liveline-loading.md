---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Match the `loading` line to Liveline's: its three-sine wave drifting leftward at 7% of the pane, breathing between 14% and 30% of `skeleton`, which now inherits `axisText` instead of `grid`, and fading out over its left 40px. On hand-off the moving line resolves centre-first onto the candle closes over about 0.9s on Liveline's ease, while the candles grow out of it; in line mode it becomes the series line.
