# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:607](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L607)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:613](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L613)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:609](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L609)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:611](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L611)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:615](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L615)

Stroke width in px. Default 1.5.
