# `VolumeConfig`

```ts
type VolumeConfig = {
  downColor?: string | number;
  enabled?: boolean;
  height?: number;
  opacity?: number;
  radius?: number;
  upColor?: string | number;
};
```

Source: [types/src/index.ts:901](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L901)

Volume bar config. One bottom-anchored bar per candle on the price pane,
drawn under the candles and sharing their x position and body width.

Unlike the other indicator configs the bars are on by default, so omitting
this prop leaves the chart looking as it always has.

## Properties

### downColor?

```ts
optional downColor?: string | number;
```

Source: [types/src/index.ts:921](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L921)

Down-bar color (hex string or packed ARGB number). Defaults to `theme.accentBear`.

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:903](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L903)

Draw the bars. Default true.

---

### height?

```ts
optional height?: number;
```

Source: [types/src/index.ts:915](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L915)

Height of the tallest bar as a fraction of the price pane, 0..1.
Default 0.2.

This is a ceiling rather than a reserved strip: raising it lets the bars
reach further up over the candles rather than compressing them, matching
the conventional volume overlay. Heights always auto-fit the loudest volume
in view, so the tallest bar sits exactly at the ceiling.

---

### opacity?

```ts
optional opacity?: number;
```

Source: [types/src/index.ts:905](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L905)

Bar opacity 0..1 (1 = opaque). Default 0.5, so bars read quieter than the candles.

---

### radius?

```ts
optional radius?: number;
```

Source: [types/src/index.ts:917](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L917)

Corner radius (px) of the _top_ of each bar. Defaults to `theme.volumeRadius`, else 0 (square).

---

### upColor?

```ts
optional upColor?: string | number;
```

Source: [types/src/index.ts:919](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L919)

Up-bar color (hex string or packed ARGB number). Defaults to `theme.accentBull`.
