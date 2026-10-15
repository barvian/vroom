# `Candle`

```ts
type Candle = {
  close: number;
  high: number;
  low: number;
  open: number;
  timeMs: number;
  volume: number;
};
```

Source: types/src/index.ts:8

A single OHLCV bar. `candles` is an array of these.

## Properties

### close

```ts
close: number;
```

Source: types/src/index.ts:18

Closing price.

---

### high

```ts
high: number;
```

Source: types/src/index.ts:14

Highest price during the bar.

---

### low

```ts
low: number;
```

Source: types/src/index.ts:16

Lowest price during the bar.

---

### open

```ts
open: number;
```

Source: types/src/index.ts:12

Opening price.

---

### timeMs

```ts
timeMs: number;
```

Source: types/src/index.ts:10

Bar open time as Unix epoch milliseconds.

---

### volume

```ts
volume: number;
```

Source: types/src/index.ts:20

Traded volume during the bar.
