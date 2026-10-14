---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Panning the line chart's newest point off an edge no longer pops its tip dot and pulse out of view the moment their center crosses it: they keep drawing until none of them is left inside the plot. The dot still stops at the y-axis strip.
