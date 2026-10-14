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

Source: [types/src/index.ts:1192](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1192)

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

Source: [types/src/index.ts:1194](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1194)

Draw the pane. Default false.

---

### fast?

```ts
optional fast?: number;
```

Source: [types/src/index.ts:1196](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1196)

Fast moving-average length. Default 12.

---

### histogramDownColor?

```ts
optional histogramDownColor?: string | number;
```

Source: [types/src/index.ts:1235](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1235)

Bars below zero still growing away from it. Defaults to `theme.accentBear`.

---

### histogramDownFadingColor?

```ts
optional histogramDownFadingColor?: string | number;
```

Source: [types/src/index.ts:1240](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1240)

Bars below zero rising back toward it. Defaults to `histogramDownColor` at
half opacity.

---

### histogramUpColor?

```ts
optional histogramUpColor?: string | number;
```

Source: [types/src/index.ts:1228](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1228)

Bars above zero that are still growing away from it. Defaults to
`theme.accentBull`. Set all four histogram colors alike for a flat,
single-color histogram.

---

### histogramUpFadingColor?

```ts
optional histogramUpFadingColor?: string | number;
```

Source: [types/src/index.ts:1233](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1233)

Bars above zero that are falling back toward it, i.e. momentum easing.
Defaults to `histogramUpColor` at half opacity.

---

### histogramVisible?

```ts
optional histogramVisible?: boolean;
```

Source: [types/src/index.ts:1222](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1222)

Draw the histogram bars. Default true.

---

### lineColor?

```ts
optional lineColor?: string | number;
```

Source: [types/src/index.ts:1209](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1209)

MACD line color (hex string or packed ARGB number). Default blue.

---

### lineVisible?

```ts
optional lineVisible?: boolean;
```

Source: [types/src/index.ts:1213](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1213)

Draw the MACD line. Default true.

---

### lineWidth?

```ts
optional lineWidth?: number;
```

Source: [types/src/index.ts:1211](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1211)

MACD line stroke width in px. Default 1.5.

---

### maType?

```ts
optional maType?: MAKind;
```

Source: [types/src/index.ts:1204](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1204)

Averaging used for the fast and slow legs ([MAKind](MAKind.md)). Default 'ema'.

---

### signal?

```ts
optional signal?: number;
```

Source: [types/src/index.ts:1200](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1200)

Signal-line length. Default 9.

---

### signalColor?

```ts
optional signalColor?: string | number;
```

Source: [types/src/index.ts:1215](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1215)

Signal line color. Default orange.

---

### signalMaType?

```ts
optional signalMaType?: MAKind;
```

Source: [types/src/index.ts:1206](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1206)

Averaging applied to the MACD series for the signal line. Default 'ema'.

---

### signalVisible?

```ts
optional signalVisible?: boolean;
```

Source: [types/src/index.ts:1219](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1219)

Draw the signal line. Default true.

---

### signalWidth?

```ts
optional signalWidth?: number;
```

Source: [types/src/index.ts:1217](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1217)

Signal line stroke width in px. Default 1.5.

---

### slow?

```ts
optional slow?: number;
```

Source: [types/src/index.ts:1198](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1198)

Slow moving-average length (forced > fast). Default 26.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:1202](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1202)

Price source for the fast/slow legs ([MASource](MASource.md)). Default 'close'.

---

### zeroLineColor?

```ts
optional zeroLineColor?: string | number;
```

Source: [types/src/index.ts:1243](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1243)

Zero-reference line color. Default gray.

---

### zeroLineVisible?

```ts
optional zeroLineVisible?: boolean;
```

Source: [types/src/index.ts:1245](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1245)

Draw the zero-reference line. Default true.
