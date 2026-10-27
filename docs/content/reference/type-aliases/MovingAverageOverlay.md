# `MovingAverageOverlay`

```ts
type MovingAverageOverlay = {
  color?: string | number;
  maType: MAKind;
  period: number;
  source?: MASource;
  width?: number;
};
```

Source: [types/src/index.ts:635](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L635)

A moving-average overlay line drawn on the price pane. Provide an array of
these via `movingAverages` to render a ribbon of SMA/EMA lines.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:643](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L643)

Line color (hex string or packed ARGB number).

---

### maType

```ts
maType: MAKind;
```

Source: [types/src/index.ts:637](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L637)

Averaging for this line ([MAKind](MAKind.md)).

---

### period

```ts
period: number;
```

Source: [types/src/index.ts:639](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L639)

Lookback in candles.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:641](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L641)

Price source ([MASource](MASource.md)). Default 'close'.

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:645](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L645)

Stroke width in px. Default 1.5.
