# `IchimokuConfig`

```ts
type IchimokuConfig = {
  bearishCloudColor?: string | number;
  bullishCloudColor?: string | number;
  chikouColor?: string | number;
  chikouVisible?: boolean;
  chikouWidth?: number;
  cloudOpacity?: number;
  cloudVisible?: boolean;
  displacement?: number;
  enabled?: boolean;
  kijunColor?: string | number;
  kijunPeriod?: number;
  kijunVisible?: boolean;
  kijunWidth?: number;
  senkouAColor?: string | number;
  senkouAVisible?: boolean;
  senkouAWidth?: number;
  senkouBColor?: string | number;
  senkouBPeriod?: number;
  senkouBVisible?: boolean;
  senkouBWidth?: number;
  tenkanColor?: string | number;
  tenkanPeriod?: number;
  tenkanVisible?: boolean;
  tenkanWidth?: number;
};
```

Source: [types/src/index.ts:726](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L726)

Ichimoku Kinko Hyo overlay config. Five lines on the price pane plus the
cloud (kumo) shaded between the two leading spans. No pane is reserved.

Unlike the other overlays, three of the lines are drawn away from the bar
they were computed on:

- Senkou A and B lead by `displacement` bars, so the cloud extends past the
  newest candle into empty time. The chart reserves that space when it frames
  itself, so the forward cloud is on screen without panning.
- Chikou lags by `displacement` bars.

Ichimoku is built on highs and lows rather than a single price series, so it
takes no [MASource](MASource.md) or [MAKind](MAKind.md).

Like the other price-pane overlays, its values don't feed the automatic
y-axis fit — the cloud can run off the top or bottom of the pane on a chart
scaled to the candles alone.

## Properties

### bearishCloudColor?

```ts
optional bearishCloudColor?: string | number;
```

Source: [types/src/index.ts:778](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L778)

Cloud fill where Senkou A is below Senkou B. Default red.

---

### bullishCloudColor?

```ts
optional bullishCloudColor?: string | number;
```

Source: [types/src/index.ts:776](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L776)

Cloud fill where Senkou A is above Senkou B. Default green.

---

### chikouColor?

```ts
optional chikouColor?: string | number;
```

Source: [types/src/index.ts:767](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L767)

Chikou span color. Default teal.

---

### chikouVisible?

```ts
optional chikouVisible?: boolean;
```

Source: [types/src/index.ts:771](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L771)

Draw the Chikou span. Default true.

---

### chikouWidth?

```ts
optional chikouWidth?: number;
```

Source: [types/src/index.ts:769](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L769)

Chikou span stroke width in px. Default 1.

---

### cloudOpacity?

```ts
optional cloudOpacity?: number;
```

Source: [types/src/index.ts:780](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L780)

Cloud opacity 0..1, applied to whichever cloud color is in play. Default 0.15.

---

### cloudVisible?

```ts
optional cloudVisible?: boolean;
```

Source: [types/src/index.ts:774](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L774)

Draw the cloud between the two leading spans. Default true.

---

### displacement?

```ts
optional displacement?: number;
```

Source: [types/src/index.ts:740](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L740)

Bars the cloud leads by and Chikou lags by. Default 26, clamped to >= 0.
Changing it only moves what's already drawn — the lines themselves don't
recompute.

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:728](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L728)

Draw the indicator. Default false.

---

### kijunColor?

```ts
optional kijunColor?: string | number;
```

Source: [types/src/index.ts:749](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L749)

Kijun-sen color. Default red.

---

### kijunPeriod?

```ts
optional kijunPeriod?: number;
```

Source: [types/src/index.ts:732](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L732)

Kijun-sen (base) lookback. Default 26, clamped to >= 1.

---

### kijunVisible?

```ts
optional kijunVisible?: boolean;
```

Source: [types/src/index.ts:753](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L753)

Draw the Kijun-sen. Default true.

---

### kijunWidth?

```ts
optional kijunWidth?: number;
```

Source: [types/src/index.ts:751](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L751)

Kijun-sen stroke width in px. Default 1.

---

### senkouAColor?

```ts
optional senkouAColor?: string | number;
```

Source: [types/src/index.ts:755](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L755)

Senkou Span A color. Default green.

---

### senkouAVisible?

```ts
optional senkouAVisible?: boolean;
```

Source: [types/src/index.ts:759](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L759)

Draw the Senkou Span A edge. Default true.

---

### senkouAWidth?

```ts
optional senkouAWidth?: number;
```

Source: [types/src/index.ts:757](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L757)

Senkou Span A stroke width in px. Default 1.

---

### senkouBColor?

```ts
optional senkouBColor?: string | number;
```

Source: [types/src/index.ts:761](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L761)

Senkou Span B color. Default orange.

---

### senkouBPeriod?

```ts
optional senkouBPeriod?: number;
```

Source: [types/src/index.ts:734](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L734)

Senkou Span B lookback. Default 52, clamped to >= 1.

---

### senkouBVisible?

```ts
optional senkouBVisible?: boolean;
```

Source: [types/src/index.ts:765](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L765)

Draw the Senkou Span B edge. Default true.

---

### senkouBWidth?

```ts
optional senkouBWidth?: number;
```

Source: [types/src/index.ts:763](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L763)

Senkou Span B stroke width in px. Default 1.

---

### tenkanColor?

```ts
optional tenkanColor?: string | number;
```

Source: [types/src/index.ts:743](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L743)

Tenkan-sen color (hex string or packed ARGB number). Default blue.

---

### tenkanPeriod?

```ts
optional tenkanPeriod?: number;
```

Source: [types/src/index.ts:730](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L730)

Tenkan-sen (conversion) lookback. Default 9, clamped to >= 1.

---

### tenkanVisible?

```ts
optional tenkanVisible?: boolean;
```

Source: [types/src/index.ts:747](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L747)

Draw the Tenkan-sen. Default true.

---

### tenkanWidth?

```ts
optional tenkanWidth?: number;
```

Source: [types/src/index.ts:745](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L745)

Tenkan-sen stroke width in px. Default 1.
