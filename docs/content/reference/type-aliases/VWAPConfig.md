# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:646](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L646)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:652](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L652)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:648](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L648)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:650](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L650)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:654](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L654)

Stroke width in px. Default 1.5.
