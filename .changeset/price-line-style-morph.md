---
'react-native-vroom-chart': minor
---

The current-price line's style now blends across a candle↔line switch. When `priceIndicator*` theme keys change in the same render as `chartType`, the dash, gap, width and opacity ease in step with the chart's morph and the caps switch halfway, instead of snapping while the chart morphs around them. The dashes stay anchored to the price pill throughout. A fresh mount, `transitionMs: 0` and reduced motion still snap.
