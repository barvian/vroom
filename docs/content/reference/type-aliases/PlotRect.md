# `PlotRect`

```ts
type PlotRect = {
  bottom: number;
  left: number;
  right: number;
  top: number;
};
```

Source: [types/src/index.ts:1122](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1122)

The chart's plot area in logical px relative to the chart element's top-left:
the candles and everything drawn over them, with the price and time axis
strips excluded.

This is the rect to test a floating UI against, and it is deliberately _not_
the element's own box — the element includes the axis strips, so measuring it
overstates the room beside anything near an edge.

## Properties

### bottom

```ts
bottom: number;
```

Source: [types/src/index.ts:1126](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1126)

---

### left

```ts
left: number;
```

Source: [types/src/index.ts:1123](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1123)

---

### right

```ts
right: number;
```

Source: [types/src/index.ts:1125](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1125)

---

### top

```ts
top: number;
```

Source: [types/src/index.ts:1124](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1124)
