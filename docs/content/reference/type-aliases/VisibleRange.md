# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:280](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L280)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:284](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L284)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:282](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L282)

Window start (inclusive), Unix epoch milliseconds.
