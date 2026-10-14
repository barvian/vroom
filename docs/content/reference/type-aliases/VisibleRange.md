# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:218](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L218)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:222](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L222)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:220](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L220)

Window start (inclusive), Unix epoch milliseconds.
