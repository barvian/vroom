# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:271](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L271)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:275](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L275)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:273](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L273)

Window start (inclusive), Unix epoch milliseconds.
