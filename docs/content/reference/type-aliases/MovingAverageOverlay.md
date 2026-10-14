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

Source: [types/src/index.ts:583](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L583)

A moving-average overlay line drawn on the price pane. Provide an array of
these via `movingAverages` to render a ribbon of SMA/EMA lines.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:591](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L591)

Line color (hex string or packed ARGB number).

---

### maType

```ts
maType: MAKind;
```

Source: [types/src/index.ts:585](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L585)

Averaging for this line ([MAKind](MAKind.md)).

---

### period

```ts
period: number;
```

Source: [types/src/index.ts:587](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L587)

Lookback in candles.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:589](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L589)

Price source ([MASource](MASource.md)). Default 'close'.

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:593](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L593)

Stroke width in px. Default 1.5.
