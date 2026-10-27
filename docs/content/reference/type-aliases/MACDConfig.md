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

Source: [types/src/index.ts:1329](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1329)

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

Source: [types/src/index.ts:1331](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1331)

Draw the pane. Default false.

---

### fast?

```ts
optional fast?: number;
```

Source: [types/src/index.ts:1333](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1333)

Fast moving-average length. Default 12.

---

### histogramDownColor?

```ts
optional histogramDownColor?: string | number;
```

Source: [types/src/index.ts:1372](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1372)

Bars below zero still growing away from it. Defaults to `theme.accentBear`.

---

### histogramDownFadingColor?

```ts
optional histogramDownFadingColor?: string | number;
```

Source: [types/src/index.ts:1377](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1377)

Bars below zero rising back toward it. Defaults to `histogramDownColor` at
half opacity.

---

### histogramUpColor?

```ts
optional histogramUpColor?: string | number;
```

Source: [types/src/index.ts:1365](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1365)

Bars above zero that are still growing away from it. Defaults to
`theme.accentBull`. Set all four histogram colors alike for a flat,
single-color histogram.

---

### histogramUpFadingColor?

```ts
optional histogramUpFadingColor?: string | number;
```

Source: [types/src/index.ts:1370](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1370)

Bars above zero that are falling back toward it, i.e. momentum easing.
Defaults to `histogramUpColor` at half opacity.

---

### histogramVisible?

```ts
optional histogramVisible?: boolean;
```

Source: [types/src/index.ts:1359](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1359)

Draw the histogram bars. Default true.

---

### lineColor?

```ts
optional lineColor?: string | number;
```

Source: [types/src/index.ts:1346](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1346)

MACD line color (hex string or packed ARGB number). Default blue.

---

### lineVisible?

```ts
optional lineVisible?: boolean;
```

Source: [types/src/index.ts:1350](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1350)

Draw the MACD line. Default true.

---

### lineWidth?

```ts
optional lineWidth?: number;
```

Source: [types/src/index.ts:1348](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1348)

MACD line stroke width in px. Default 1.5.

---

### maType?

```ts
optional maType?: MAKind;
```

Source: [types/src/index.ts:1341](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1341)

Averaging used for the fast and slow legs ([MAKind](MAKind.md)). Default 'ema'.

---

### signal?

```ts
optional signal?: number;
```

Source: [types/src/index.ts:1337](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1337)

Signal-line length. Default 9.

---

### signalColor?

```ts
optional signalColor?: string | number;
```

Source: [types/src/index.ts:1352](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1352)

Signal line color. Default orange.

---

### signalMaType?

```ts
optional signalMaType?: MAKind;
```

Source: [types/src/index.ts:1343](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1343)

Averaging applied to the MACD series for the signal line. Default 'ema'.

---

### signalVisible?

```ts
optional signalVisible?: boolean;
```

Source: [types/src/index.ts:1356](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1356)

Draw the signal line. Default true.

---

### signalWidth?

```ts
optional signalWidth?: number;
```

Source: [types/src/index.ts:1354](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1354)

Signal line stroke width in px. Default 1.5.

---

### slow?

```ts
optional slow?: number;
```

Source: [types/src/index.ts:1335](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1335)

Slow moving-average length (forced > fast). Default 26.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:1339](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1339)

Price source for the fast/slow legs ([MASource](MASource.md)). Default 'close'.

---

### zeroLineColor?

```ts
optional zeroLineColor?: string | number;
```

Source: [types/src/index.ts:1380](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1380)

Zero-reference line color. Default gray.

---

### zeroLineVisible?

```ts
optional zeroLineVisible?: boolean;
```

Source: [types/src/index.ts:1382](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1382)

Draw the zero-reference line. Default true.
