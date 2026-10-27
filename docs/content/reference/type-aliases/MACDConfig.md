# `MACDConfig`

```ts
type MACDConfig = {
  enabled?: boolean;
  fast?: number;
  histogramDownColor?: string | number;
  histogramDownFadingColor?: string | number;
  histogramUpColor?: string | number;
  histogramUpFadingColor?: string | number;
  histogramVisible?: boolean;
  lineColor?: string | number;
  lineVisible?: boolean;
  lineWidth?: number;
  maType?: MAKind;
  signal?: number;
  signalColor?: string | number;
  signalMaType?: MAKind;
  signalVisible?: boolean;
  signalWidth?: number;
  slow?: number;
  source?: MASource;
  zeroLineColor?: string | number;
  zeroLineVisible?: boolean;
};
```

Source: [types/src/index.ts:1325](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1325)

MACD indicator config. Rendered in its own pane below the candles: the gap
between a fast and a slow moving average, a signal line smoothing that gap,
and a histogram of the distance between the two.

Every style field is optional and falls back to the stock look, so an
untouched config renders exactly as it always has.

## Properties

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:1327](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1327)

Draw the pane. Default false.

---

### fast?

```ts
optional fast?: number;
```

Source: [types/src/index.ts:1329](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1329)

Fast moving-average length. Default 12.

---

### histogramDownColor?

```ts
optional histogramDownColor?: string | number;
```

Source: [types/src/index.ts:1368](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1368)

Bars below zero still growing away from it. Defaults to `theme.accentBear`.

---

### histogramDownFadingColor?

```ts
optional histogramDownFadingColor?: string | number;
```

Source: [types/src/index.ts:1373](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1373)

Bars below zero rising back toward it. Defaults to `histogramDownColor` at
half opacity.

---

### histogramUpColor?

```ts
optional histogramUpColor?: string | number;
```

Source: [types/src/index.ts:1361](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1361)

Bars above zero that are still growing away from it. Defaults to
`theme.accentBull`. Set all four histogram colors alike for a flat,
single-color histogram.

---

### histogramUpFadingColor?

```ts
optional histogramUpFadingColor?: string | number;
```

Source: [types/src/index.ts:1366](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1366)

Bars above zero that are falling back toward it, i.e. momentum easing.
Defaults to `histogramUpColor` at half opacity.

---

### histogramVisible?

```ts
optional histogramVisible?: boolean;
```

Source: [types/src/index.ts:1355](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1355)

Draw the histogram bars. Default true.

---

### lineColor?

```ts
optional lineColor?: string | number;
```

Source: [types/src/index.ts:1342](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1342)

MACD line color (hex string or packed ARGB number). Default blue.

---

### lineVisible?

```ts
optional lineVisible?: boolean;
```

Source: [types/src/index.ts:1346](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1346)

Draw the MACD line. Default true.

---

### lineWidth?

```ts
optional lineWidth?: number;
```

Source: [types/src/index.ts:1344](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1344)

MACD line stroke width in px. Default 1.5.

---

### maType?

```ts
optional maType?: MAKind;
```

Source: [types/src/index.ts:1337](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1337)

Averaging used for the fast and slow legs ([MAKind](MAKind.md)). Default 'ema'.

---

### signal?

```ts
optional signal?: number;
```

Source: [types/src/index.ts:1333](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1333)

Signal-line length. Default 9.

---

### signalColor?

```ts
optional signalColor?: string | number;
```

Source: [types/src/index.ts:1348](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1348)

Signal line color. Default orange.

---

### signalMaType?

```ts
optional signalMaType?: MAKind;
```

Source: [types/src/index.ts:1339](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1339)

Averaging applied to the MACD series for the signal line. Default 'ema'.

---

### signalVisible?

```ts
optional signalVisible?: boolean;
```

Source: [types/src/index.ts:1352](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1352)

Draw the signal line. Default true.

---

### signalWidth?

```ts
optional signalWidth?: number;
```

Source: [types/src/index.ts:1350](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1350)

Signal line stroke width in px. Default 1.5.

---

### slow?

```ts
optional slow?: number;
```

Source: [types/src/index.ts:1331](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1331)

Slow moving-average length (forced > fast). Default 26.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:1335](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1335)

Price source for the fast/slow legs ([MASource](MASource.md)). Default 'close'.

---

### zeroLineColor?

```ts
optional zeroLineColor?: string | number;
```

Source: [types/src/index.ts:1376](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1376)

Zero-reference line color. Default gray.

---

### zeroLineVisible?

```ts
optional zeroLineVisible?: boolean;
```

Source: [types/src/index.ts:1378](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1378)

Draw the zero-reference line. Default true.
