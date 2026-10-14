---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

Rework the line chart's tip pulse to match a live-price knob: a single ring five sixths of the dot radius wide grows out from the dot's edge by twice its width while fading from 35% (as Liveline's does) to nothing over 0.9s, then rests, once every 2.2s (was 2.6s).
