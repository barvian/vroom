---
'react-native-vroom-chart': minor
'@vroomchart/react': minor
'@vroomchart/core-wasm': minor
---

The simple crosshair's time badge can now be sized and shaped: `crosshair.simple` takes `badgeFontSize`, `badgeLineHeight`, `badgePaddingX`, `badgePaddingY` and `badgeRadius`. The radius is capped at half the badge's height, so `Infinity` draws a capsule. Unset, the badge looks as it did.

```tsx
<VroomChart
  crosshair={{
    mode: 'simple',
    simple: { badgeFontSize: 15, badgeLineHeight: 20, badgePaddingX: 10, badgeRadius: Infinity },
  }}
/>
```
