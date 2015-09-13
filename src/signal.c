#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "signal.h"

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char symbol) {
  Signal* newSignal = (Signal*)malloc(sizeof(newSignal));
  newSignal->name = (char*)malloc(strlen(name) * sizeof(char));

  strcpy(newSignal->name, name);
  newSignal->symbol = symbol;
  newSignal->currentSignalValue = 'X';
  newSignal->hasPassedInIdle = 0;
  newSignal->lastSignalChangeTimestamp = 0;
  newSignal->shortestIdleDelay  = UINT_MAX;
  newSignal->longestIdleDelay   = 0;

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

void assignSignalUpdate(Signal *signal, unsigned char signalValue, int timestamp) {
  if (signalValue == 0) {
    signal->hasPassedInIdle = 1;
  }
  else if (signal->currentSignalValue == 0) {
    // Signal leaving idle state:
    // Calculate delay and and check shortest and longest boundaries
    unsigned int delay = timestamp - signal->lastSignalChangeTimestamp;

    if (delay < signal->shortestIdleDelay) {
      signal->shortestIdleDelay = delay;
    }

    if (delay > signal->longestIdleDelay) {
      signal->longestIdleDelay = delay;
    }
  }

  signal->currentSignalValue = signalValue;
  signal->lastSignalChangeTimestamp = timestamp;
}

void closeSignalCounters(Signal* signal, unsigned int timestamp) {
  if (signal->currentSignalValue == 0) {
    unsigned int delay = timestamp - signal->lastSignalChangeTimestamp;

    if (delay < signal->shortestIdleDelay) {
      signal->shortestIdleDelay = delay;
    }

    if (delay > signal->longestIdleDelay) {
      signal->longestIdleDelay = delay;
    }
  }
}

void printSignal(Signal* signal) {
  printf("[SIGNAL] Name: %-15s Symbol: %-3c lastSignalChangeTimestamp: %-6d ShortestIdleDelay: %-6d LongestIdleDelay: %d\n",
           signal->name,
           signal->symbol,
           signal->lastSignalChangeTimestamp,
          (signal->hasPassedInIdle) ? signal->shortestIdleDelay : -1,
          (signal->hasPassedInIdle) ? signal->longestIdleDelay  : -1);
}
