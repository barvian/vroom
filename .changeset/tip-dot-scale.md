---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

The line chart's tip dot is bigger by default: its radius is now 2× `lineWidth` (was 1.5×), still at least 2px. The new theme key `lineTipDotScale` sets that ratio. The pulse ring and the line-mode right gutter scale with the dot, so the gutter grows with it.
