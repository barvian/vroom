# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:600](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L600)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:606](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L606)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:602](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L602)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:604](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L604)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:608](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L608)

Stroke width in px. Default 1.5.
