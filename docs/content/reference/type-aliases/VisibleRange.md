# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:225](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L225)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:229](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L229)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:227](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L227)

Window start (inclusive), Unix epoch milliseconds.
