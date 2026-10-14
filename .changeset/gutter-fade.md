---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Panned back from the latest bar, the line chart now fades out across the gutter instead of being cut off at the y-axis strip. The fade eases in over the first few pixels of panning, so a chart following the latest bar looks the same as before.
