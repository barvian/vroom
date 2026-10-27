# `VisibleRange`

```ts
type VisibleRange = {
  endMs: number;
  startMs: number;
};
```

Source: [types/src/index.ts:270](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L270)

A time window over the candle data, as Unix epoch milliseconds.

## Properties

### endMs

```ts
endMs: number;
```

Source: [types/src/index.ts:274](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L274)

Window end (inclusive), Unix epoch milliseconds.

---

### startMs

```ts
startMs: number;
```

Source: [types/src/index.ts:272](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L272)

Window start (inclusive), Unix epoch milliseconds.
