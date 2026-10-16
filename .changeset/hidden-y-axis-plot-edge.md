---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

With `showYAxis: false`, the price pane now paints to the chart's right edge. A series panned past its newest candle used to stop at the right-hand gutter and leave a blank strip there. The newest candle and the line's tip dot keep the gutter's spacing when the view is at the latest bar.
