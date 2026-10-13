---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Fix candles, volume bars and the line disappearing at the plot edges while still on screen. Every layer now draws each candle whose center is in view plus one past each edge, clipped to the plot, so they run all the way to both edges. The price auto-fit and the crosshair only read candles whose center is in view, so a candle the clip mostly hides never stretches the scale or catches the pointer. `getCrosshairCandle` now returns null on an empty slot (ahead of the newest candle or over a gap in the data), matching `getCrosshairInfo`.
