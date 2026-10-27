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

Source: [types/src/index.ts:640](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L640)

A moving-average overlay line drawn on the price pane. Provide an array of
these via `movingAverages` to render a ribbon of SMA/EMA lines.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:648](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L648)

Line color (hex string or packed ARGB number).

---

### maType

```ts
maType: MAKind;
```

Source: [types/src/index.ts:642](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L642)

Averaging for this line ([MAKind](MAKind.md)).

---

### period

```ts
period: number;
```

Source: [types/src/index.ts:644](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L644)

Lookback in candles.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:646](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L646)

Price source ([MASource](MASource.md)). Default 'close'.

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:650](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L650)

Stroke width in px. Default 1.5.
