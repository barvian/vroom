---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

Add an `edgeCulling` prop. `'strict'` (default) keeps today's behavior. `'overscan'` keeps drawing candles, volume bars and line segments at the left and right edges until they are fully out of view, clipped to the plot, instead of dropping a candle as soon as its period starts outside the window.
