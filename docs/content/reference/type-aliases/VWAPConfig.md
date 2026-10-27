# `VWAPConfig`

```ts
type VWAPConfig = {
  color?: string | number;
  enabled?: boolean;
  resetMinutes?: number;
  width?: number;
};
```

Source: [types/src/index.ts:652](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L652)

VWAP overlay config (session anchor). Drawn as a single line on the price
pane, resetting each session.

## Properties

### color?

```ts
optional color?: string | number;
```

Source: [types/src/index.ts:658](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L658)

Line color (hex string or packed ARGB number).

---

### enabled?

```ts
optional enabled?: boolean;
```

Source: [types/src/index.ts:654](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L654)

Draw the line. Default false.

---

### resetMinutes?

```ts
optional resetMinutes?: number;
```

Source: [types/src/index.ts:656](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L656)

Session reset offset from UTC midnight, in minutes (default 0).

---

### width?

```ts
optional width?: number;
```

Source: [types/src/index.ts:660](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L660)

Stroke width in px. Default 1.5.
