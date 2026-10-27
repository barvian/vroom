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

Source: [types/src/index.ts:650](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L650)

A moving-average overlay line drawn on the price pane. Provide an array of
these via `movingAverages` to render a ribbon of SMA/EMA lines.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:658](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L658)

Line color (hex string or packed ARGB number).

---

### maType

```ts
maType: MAKind;
```

Source: [types/src/index.ts:652](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L652)

Averaging for this line ([MAKind](MAKind.md)).

---

### period

```ts
period: number;
```

Source: [types/src/index.ts:654](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L654)

Lookback in candles.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:656](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L656)

Price source ([MASource](MASource.md)). Default 'close'.

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:660](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L660)

Stroke width in px. Default 1.5.
