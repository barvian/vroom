# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:662](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L662)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:668](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L668)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:664](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L664)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:666](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L666)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:670](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L670)

Stroke width in px. Default 1.5.
