# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:275](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L275)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:279](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L279)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:277](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L277)

Window start (inclusive), Unix epoch milliseconds.
