# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:657](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L657)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:663](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L663)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:659](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L659)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:661](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L661)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:665](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L665)

Stroke width in px. Default 1.5.
