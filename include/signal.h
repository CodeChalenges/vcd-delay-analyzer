#ifndef SIGNAL_H
#define SIGNAL_H

typedef struct {
  char* name;
  char identifier;
  unsigned int lastSignalUpdate;
  unsigned int shortestSinalDelay;
  unsigned int longestSinalDelay;
} Signal;

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char identifier);
Signal* findSignalBySymbol(Signal* signals, unsigned int nsignals, char symbol);
void assignSignalUpdate(Signal *signal, int timestamp);

#endif
