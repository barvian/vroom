---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

Rework the line chart's tip pulse to match a live-price knob: a single ring five sixths of the dot radius wide grows out from the dot's edge by twice its width while fading to nothing over 0.9s, then rests, once every 2.2s (was 2.6s).

The ring's starting opacity is a new theme key, `lineTipPulseOpacity`, which defaults to 0.4.
