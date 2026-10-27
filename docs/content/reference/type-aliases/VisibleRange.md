# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:266](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L266)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:270](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L270)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:268](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L268)

Window start (inclusive), Unix epoch milliseconds.
