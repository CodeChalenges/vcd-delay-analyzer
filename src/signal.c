#include <stdlib.h>
#include <string.h>
#include "signal.h"

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char symbol) {
  Signal* newSignal = (Signal*)malloc(sizeof(newSignal));
  newSignal->name = (char*)malloc(strlen(name) * sizeof(char));

  strcpy(newSignal->name, name);
  newSignal->symbol = symbol;
  newSignal->lastSignalUpdate   = 0;
  newSignal->shortestSinalDelay = 0;
  newSignal->longestSinalDelay  = 0;

  *signals = (Signal*)realloc(*signals, (++(*nsignals)) * sizeof(Signal));
  (*signals)[*nsignals-1] = *newSignal;
}

Signal* findSignalBySymbol(Signal* signals, unsigned int nsignals, char symbol) {
  unsigned int i;
  for (i = 0; i < nsignals; i++) {
    if (signals[i].symbol == symbol) {
      return &signals[i];
    }
  }

  return NULL;
}

void assignSignalUpdate(Signal *signal, int timestamp) {
  unsigned int delay = timestamp - signal->lastSignalUpdate;

  signal->lastSignalUpdate = timestamp;

  if (delay < signal->shortestSinalDelay) {
    signal->shortestSinalDelay = delay;
  }

  if (delay > signal->longestSinalDelay) {
    signal->longestSinalDelay = delay;
  }
}
