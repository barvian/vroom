---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Fix candles, volume bars and the line disappearing at the plot edges while still on screen. Every layer now draws each candle whose center is in view plus one past each edge, clipped to the plot, so they run all the way to both edges. The price auto-fit and the crosshair only read candles whose center is in view, so a candle the clip mostly hides never stretches the scale or catches the pointer.
