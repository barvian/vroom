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

Source: types/src/index.ts:615

A moving-average overlay line drawn on the price pane. Provide an array of
these via `movingAverages` to render a ribbon of SMA/EMA lines.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: types/src/index.ts:623

Line color (hex string or packed ARGB number).

---

### maType

```ts
maType: MAKind;
```

Source: types/src/index.ts:617

Averaging for this line ([MAKind](MAKind.md)).

---

### period

```ts
period: number;
```

Source: types/src/index.ts:619

Lookback in candles.

---

### source?

```ts
optional source?: MASource;
```

Source: types/src/index.ts:621

Price source ([MASource](MASource.md)). Default 'close'.

---

### width?

```ts
optional width?: number;
```

Source: types/src/index.ts:625

Stroke width in px. Default 1.5.
