import { afterEach, beforeEach, describe, expect, it, vi } from 'vitest';
import type { ChartFrame } from './jsi.d';
import { drawUiFrames, LOOP_IDLE, LOOP_RUNNING, LOOP_STOPPED } from './uiFrameLoop';

let queued: (() => void)[] = [];

function nextFrame() {
  const callbacks = queued;
  queued = [];
  callbacks.forEach((cb) => cb());
}

function chart(animatingFrames: number) {
  let left = animatingFrames;
  return {
    render: vi.fn(() => ({}) as ChartFrame),
    isAnimating: vi.fn(() => left-- > 0),
  };
}

beforeEach(() => {
  queued = [];
  vi.stubGlobal('requestAnimationFrame', (cb: () => void) => queued.push(cb));
});

afterEach(() => {
  vi.unstubAllGlobals();
});

describe('drawUiFrames', () => {
  it('draws once and goes idle when nothing is animating', () => {
    const handle = chart(0);
    const state = { value: LOOP_IDLE };
    const present = vi.fn();
    drawUiFrames(handle, state, present);
    expect(present).toHaveBeenCalledTimes(1);
    expect(queued).toHaveLength(0);
    expect(state.value).toBe(LOOP_IDLE);
  });

  it('keeps drawing a frame per display frame while the core animates', () => {
    const handle = chart(2);
    const state = { value: LOOP_IDLE };
    const present = vi.fn();
    drawUiFrames(handle, state, present);
    expect(state.value).toBe(LOOP_RUNNING);
    nextFrame();
    nextFrame();
    expect(present).toHaveBeenCalledTimes(3);
    expect(state.value).toBe(LOOP_IDLE);
    expect(queued).toHaveLength(0);
  });

  it('leaves a running loop to draw the next frame itself', () => {
    const handle = chart(5);
    const state = { value: LOOP_IDLE };
    drawUiFrames(handle, state, vi.fn());
    drawUiFrames(handle, state, vi.fn());
    expect(handle.render).toHaveBeenCalledTimes(1);
    expect(queued).toHaveLength(1);
  });

  it('draws nothing once its chart has unmounted', () => {
    const handle = chart(5);
    const state = { value: LOOP_IDLE };
    const present = vi.fn();
    drawUiFrames(handle, state, present);
    state.value = LOOP_STOPPED;
    nextFrame();
    drawUiFrames(handle, state, present);
    expect(present).toHaveBeenCalledTimes(1);
    expect(queued).toHaveLength(0);
  });
});
