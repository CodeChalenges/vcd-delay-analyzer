#include "signal.h"

void assignSignalUpdate(Signal *signal, int clockTick) {
  unsigned int delay = clockTick - signal->lastSignalUpdate;

  signal->lastSignalUpdate = clockTick;

  if (delay < signal->shortestSinalDelay) {
    signal->shortestSinalDelay = delay;
  }

  if (delay > signal->longestSinalDelay) {
    signal->longestSinalDelay = delay;
  }
}
