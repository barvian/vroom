---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

Rework the line chart's tip pulse to match a live-price knob: a single ring five sixths of the dot radius wide grows out from the dot's edge by twice its width while fading to nothing over 0.9s, then rests, once every 1.5s (was 2.6s) — the same rhythm as Liveline's live dot.

New theme key `lineTipPulseOpacity` sets the ring's starting opacity (default 0.4).
