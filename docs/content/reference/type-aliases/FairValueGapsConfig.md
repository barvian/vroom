# `FairValueGapsConfig`

```ts
type FairValueGapsConfig = {
  bearishBorderColor?: VroomColor;
  bearishColor?: VroomColor;
  borderStyle?: "solid" | "dotted" | "dashed";
  borderVisible?: boolean;
  borderWidth?: number;
  boxLength?: number;
  bullishBorderColor?: VroomColor;
  bullishColor?: VroomColor;
  deleteAfterFill?: boolean;
  enabled?: boolean;
  extendBoxes?: boolean;
  fillType?: "close" | "wick";
  inverseBearishColor?: VroomColor;
  inverseBullishColor?: VroomColor;
  inverseLabel?: string;
  label?: string;
  labelColor?: VroomColor;
  labelDistance?: number;
  labelFontSize?: number;
  maxBarsBack?: number;
  opacity?: number;
  showInverse?: boolean;
  showLabels?: boolean;
  waitForClose?: boolean;
};
```

Source: [types/src/index.ts:795](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L795)

Fair Value Gap overlay config. Shaded boxes on the price pane marking
three-candle imbalances — a run so fast the first and third candles' wicks
never overlap, leaving a band of price that was skipped.

A gap is bullish when `candles[i - 1].high < candles[i + 1].low` and bearish
when `candles[i - 1].low > candles[i + 1].high`, and spans the untouched
range between those two wicks. Each box is anchored to the middle bar's open
and runs `boxLength` bars to the right, or to the pane's edge under
`extendBoxes`.

Gaps are tracked until price trades back through them — see `fillType` for
which price settles that, and `deleteAfterFill` for what happens once it
does. With `showInverse`, a filled gap carries on as a zone of the opposite
polarity. Unlike the line overlays, the boxes are pure geometry: they don't
feed the automatic y-axis fit.

## Properties

### bearishBorderColor?

```ts
optional bearishBorderColor?: VroomColor;
```

Source: [types/src/index.ts:841](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L841)

Outline color for bearish gaps. Defaults to `bearishColor` at full alpha.

---

### bearishColor?

```ts
optional bearishColor?: VroomColor;
```

Source: [types/src/index.ts:828](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L828)

Fill color for bearish gaps. Default red.

---

### borderStyle?

```ts
optional borderStyle?: "solid" | "dotted" | "dashed";
```

Source: [types/src/index.ts:835](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L835)

Outline style. Default `'solid'`.

---

### borderVisible?

```ts
optional borderVisible?: boolean;
```

Source: [types/src/index.ts:833](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L833)

Draw the box outline. Default true.

---

### borderWidth?

```ts
optional borderWidth?: number;
```

Source: [types/src/index.ts:837](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L837)

Outline stroke width in px. Default 1.

---

### boxLength?

```ts
optional boxLength?: number;
```

Source: [types/src/index.ts:823](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L823)

Box width in bars when `extendBoxes` is off. Default 20, clamped to >= 1.

---

### bullishBorderColor?

```ts
optional bullishBorderColor?: VroomColor;
```

Source: [types/src/index.ts:839](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L839)

Outline color for bullish gaps. Defaults to `bullishColor` at full alpha.

---

### bullishColor?

```ts
optional bullishColor?: VroomColor;
```

Source: [types/src/index.ts:826](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L826)

Fill color for bullish gaps (hex string or packed ARGB). Default green.

---

### deleteAfterFill?

```ts
optional deleteAfterFill?: boolean;
```

Source: [types/src/index.ts:816](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L816)

Hide a gap once it's been filled. Default true. When false the box stays
but stops at the bar that filled it, leaving a record of the rebalance.

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:797](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L797)

Draw the indicator. Default false.

---

### extendBoxes?

```ts
optional extendBoxes?: boolean;
```

Source: [types/src/index.ts:821](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L821)

Run every box to the right edge of the pane instead of ending it after
`boxLength` bars. Default false. A filled box still stops at its fill bar.

---

### fillType?

```ts
optional fillType?: "close" | "wick";
```

Source: [types/src/index.ts:811](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L811)

Which price counts as trading back through the gap. `'close'` (default)
needs a candle to close past the far edge; `'wick'` settles it the moment
a high or low reaches through.

---

### inverseBearishColor?

```ts
optional inverseBearishColor?: VroomColor;
```

Source: [types/src/index.ts:879](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L879)

Fill color for inverted zones that are bearish — that is, for _bullish_
gaps price has broken below. Defaults to `bearishColor`.

---

### inverseBullishColor?

```ts
optional inverseBullishColor?: VroomColor;
```

Source: [types/src/index.ts:874](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L874)

Fill color for inverted zones that are bullish — that is, for _bearish_
gaps price has broken above. Defaults to `bullishColor`.

---

### inverseLabel?

```ts
optional inverseLabel?: string;
```

Source: [types/src/index.ts:881](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L881)

Label text on inverted boxes. Default `'iFVG'`.

---

### label?

```ts
optional label?: string;
```

Source: [types/src/index.ts:846](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L846)

Label text. Default `'FVG'`.

---

### labelColor?

```ts
optional labelColor?: VroomColor;
```

Source: [types/src/index.ts:854](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L854)

Label color. Defaults to the box's border color.

---

### labelDistance?

```ts
optional labelDistance?: number;
```

Source: [types/src/index.ts:852](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L852)

Bars of clearance between the box and its label, used only under
`extendBoxes` — a fixed-length box places the label inside its right end.
Default 10, clamped to >= 0.

---

### labelFontSize?

```ts
optional labelFontSize?: number;
```

Source: [types/src/index.ts:856](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L856)

Label font size in px. Defaults to the axis font size.

---

### maxBarsBack?

```ts
optional maxBarsBack?: number;
```

Source: [types/src/index.ts:799](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L799)

How many bars back to scan for gaps. Default 300, clamped to >= 0.

---

### opacity?

```ts
optional opacity?: number;
```

Source: [types/src/index.ts:830](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L830)

Fill opacity 0..1, applied to whichever fill color is in play. Default 0.15.

---

### showInverse?

```ts
optional showInverse?: boolean;
```

Source: [types/src/index.ts:869](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L869)

Keep drawing a gap after it's been filled, with its polarity flipped — the
band price rejected on the way through becomes a zone of the opposite
kind. Default false.

The inverse box starts where the original one stops, at the close of the
bar that filled the gap, and lasts until price reclaims the band the other
way (by the same rule `fillType` sets). This pairs with the default
`deleteAfterFill: true`: the original box vanishes at the fill and the
inverse takes over from there.

---

### showLabels?

```ts
optional showLabels?: boolean;
```

Source: [types/src/index.ts:844](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L844)

Draw a text label on each box. Default true.

---

### waitForClose?

```ts
optional waitForClose?: boolean;
```

Source: [types/src/index.ts:805](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L805)

Withhold a gap until its third candle closes. Default false, so a gap
formed by the still-forming bar appears immediately and disappears again
if that bar fills back in.
