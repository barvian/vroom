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

Source: [types/src/index.ts:1334](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1334)

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

Source: [types/src/index.ts:1336](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1336)

Draw the pane. Default false.

---

### fast?

```ts
optional fast?: number;
```

Source: [types/src/index.ts:1338](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1338)

Fast moving-average length. Default 12.

---

### histogramDownColor?

```ts
optional histogramDownColor?: string | number;
```

Source: [types/src/index.ts:1377](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1377)

Bars below zero still growing away from it. Defaults to `theme.accentBear`.

---

### histogramDownFadingColor?

```ts
optional histogramDownFadingColor?: string | number;
```

Source: [types/src/index.ts:1382](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1382)

Bars below zero rising back toward it. Defaults to `histogramDownColor` at
half opacity.

---

### histogramUpColor?

```ts
optional histogramUpColor?: string | number;
```

Source: [types/src/index.ts:1370](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1370)

Bars above zero that are still growing away from it. Defaults to
`theme.accentBull`. Set all four histogram colors alike for a flat,
single-color histogram.

---

### histogramUpFadingColor?

```ts
optional histogramUpFadingColor?: string | number;
```

Source: [types/src/index.ts:1375](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1375)

Bars above zero that are falling back toward it, i.e. momentum easing.
Defaults to `histogramUpColor` at half opacity.

---

### histogramVisible?

```ts
optional histogramVisible?: boolean;
```

Source: [types/src/index.ts:1364](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1364)

Draw the histogram bars. Default true.

---

### lineColor?

```ts
optional lineColor?: string | number;
```

Source: [types/src/index.ts:1351](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1351)

MACD line color (hex string or packed ARGB number). Default blue.

---

### lineVisible?

```ts
optional lineVisible?: boolean;
```

Source: [types/src/index.ts:1355](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1355)

Draw the MACD line. Default true.

---

### lineWidth?

```ts
optional lineWidth?: number;
```

Source: [types/src/index.ts:1353](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1353)

MACD line stroke width in px. Default 1.5.

---

### maType?

```ts
optional maType?: MAKind;
```

Source: [types/src/index.ts:1346](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1346)

Averaging used for the fast and slow legs ([MAKind](MAKind.md)). Default 'ema'.

---

### signal?

```ts
optional signal?: number;
```

Source: [types/src/index.ts:1342](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1342)

Signal-line length. Default 9.

---

### signalColor?

```ts
optional signalColor?: string | number;
```

Source: [types/src/index.ts:1357](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1357)

Signal line color. Default orange.

---

### signalMaType?

```ts
optional signalMaType?: MAKind;
```

Source: [types/src/index.ts:1348](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1348)

Averaging applied to the MACD series for the signal line. Default 'ema'.

---

### signalVisible?

```ts
optional signalVisible?: boolean;
```

Source: [types/src/index.ts:1361](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1361)

Draw the signal line. Default true.

---

### signalWidth?

```ts
optional signalWidth?: number;
```

Source: [types/src/index.ts:1359](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1359)

Signal line stroke width in px. Default 1.5.

---

### slow?

```ts
optional slow?: number;
```

Source: [types/src/index.ts:1340](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1340)

Slow moving-average length (forced > fast). Default 26.

---

### source?

```ts
optional source?: MASource;
```

Source: [types/src/index.ts:1344](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1344)

Price source for the fast/slow legs ([MASource](MASource.md)). Default 'close'.

---

### zeroLineColor?

```ts
optional zeroLineColor?: string | number;
```

Source: [types/src/index.ts:1385](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1385)

Zero-reference line color. Default gray.

---

### zeroLineVisible?

```ts
optional zeroLineVisible?: boolean;
```

Source: [types/src/index.ts:1387](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1387)

Draw the zero-reference line. Default true.
