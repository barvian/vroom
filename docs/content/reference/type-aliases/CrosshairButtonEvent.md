# `CrosshairButtonEvent`

```ts
type CrosshairButtonEvent = {
  button: {
    bottom: number;
    left: number;
    right: number;
    top: number;
  } | null;
  close: () => void;
  open: boolean;
  pane: PlotRect | null;
  price: number | null;
  reason: "open" | "move" | "close";
  timeMs: number | null;
};
```

Source: [types/src/index.ts:1225](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1225)

Fired when the crosshair plus button is activated and the crosshair locks
(`'open'`), when the locked button moves on screen (`'move'`), and when it
unlocks (`'close'`).

The chart draws no menu of its own — this event is the hook for yours. While
open, the crosshair stays where it was clicked, so the pointer can travel onto
your UI. Position it off `button`, in the same coordinate space as
[FootprintEvent](FootprintEvent.md) (logical px from the chart element's top-left). To sit
it directly left of the button:

```ts
const right = button.left - 6; // your UI's right edge
const centerY = (button.top + button.bottom) / 2; // vertical center
```

It closes on another click of the button, a click or tap elsewhere on the
chart, Escape, any pan or zoom, a series reset, `enabled` turning false, or
your own call to `close()` (e.g. once the user has picked an order).

## Properties

### button

```ts
button:
  | {
  bottom: number;
  left: number;
  right: number;
  top: number;
}
  | null;
```

Source: [types/src/index.ts:1244](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1244)

The price badge's rect, plus included — the whole clickable area. Null on close.

---

### close

```ts
close: () => void;
```

Source: [types/src/index.ts:1248](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1248)

Close the button and unlock the crosshair. Safe to call more than once.

#### Returns

`void`

---

### open

```ts
open: boolean;
```

Source: [types/src/index.ts:1227](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1227)

True while the button is open (crosshair locked); false once it closes.

---

### pane

```ts
pane: PlotRect | null;
```

Source: [types/src/index.ts:1246](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1246)

The plot area, for checking your UI fits. Null on close.

---

### price

```ts
price: number | null;
```

Source: [types/src/index.ts:1237](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1237)

Price at the crosshair's horizontal line, unformatted. Null on close.

---

### reason

```ts
reason: "open" | "move" | "close";
```

Source: [types/src/index.ts:1235](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1235)

Why this event fired:
'open' — the button was activated
'move' — the open button moved on screen without a gesture (a live tick
re-fit the price axis, or the chart resized); re-anchor to it
'close' — it was dismissed (see above)

---

### timeMs

```ts
timeMs: number | null;
```

Source: [types/src/index.ts:1242](https://github.com/keepitreal/vroom/blob/main/packages/types/src/index.ts#L1242)

Bar-open time (epoch ms) of the slot under the vertical line — a real
candle, or an empty future slot. Null on close.
