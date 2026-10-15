---
'react-native-vroom-chart': patch
---

Snap a fresh chart handle to the `chartType` prop before the first picture, so a line chart does not flash candlesticks. Candles stay the default when the prop is candles or omitted.
