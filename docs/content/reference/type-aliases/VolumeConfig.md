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

Source: [types/src/index.ts:906](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L906)

Volume bar config. One bottom-anchored bar per candle on the price pane,
drawn under the candles and sharing their x position and body width.

Unlike the other indicator configs the bars are on by default, so omitting
this prop leaves the chart looking as it always has.

## Properties

### downColor?

```ts
optional downColor?: string | number;
```

Source: [types/src/index.ts:926](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L926)

Down-bar color (hex string or packed ARGB number). Defaults to `theme.accentBear`.

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:908](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L908)

Draw the bars. Default true.

---

### height?

```ts
optional height?: number;
```

Source: [types/src/index.ts:920](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L920)

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

Source: [types/src/index.ts:910](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L910)

Bar opacity 0..1 (1 = opaque). Default 0.5, so bars read quieter than the candles.

---

### radius?

```ts
optional radius?: number;
```

Source: [types/src/index.ts:922](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L922)

Corner radius (px) of the _top_ of each bar. Defaults to `theme.volumeRadius`, else 0 (square).

---

### upColor?

```ts
optional upColor?: string | number;
```

Source: [types/src/index.ts:924](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L924)

Up-bar color (hex string or packed ARGB number). Defaults to `theme.accentBull`.
