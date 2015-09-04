#ifndef SIGNAL_H
#define SIGNAL_H

typedef struct {
  char* name;
  char identifier;
  unsigned int lastSignalUpdate;
  unsigned int shortestSinalDelay;
  unsigned int longestSinalDelay;
} Signal;

void assignSignalUpdate(Signal *signal, int clockTick);

#endif
