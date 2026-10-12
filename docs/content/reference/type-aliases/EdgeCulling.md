# `EdgeCulling`

```ts
type EdgeCulling = "strict" | "overscan";
```

Source: [types/src/index.ts:255](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L255)

Which candles are drawn at the left and right edges of the plot.
'strict' — default: only candles whose period starts inside the visible
window. A candle panning off the left edge disappears while
most of its body is still on screen, and the line stops short
of both edges.
'overscan' — every candle whose center is in view, plus one more past each
edge, trimmed by the plot area. Candles, volume bars and the
line run all the way to both edges until they are fully out of
view.
