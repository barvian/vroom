---
'react-native-vroom-chart': patch
'@vroomchart/react': patch
'@vroomchart/core-wasm': patch
---

The current-price line's dashes now start at the price pill, so a whole dash always meets it, and the pattern holds still as the price moves: the pill is sized as if every digit were the widest one, so its edge no longer shifts with proportional figures.
