#ifndef SIGNAL_H
#define SIGNAL_H

typedef struct {
  char* name;
  char symbol;
  char currentSignalValue;
  unsigned char enteredInIdle;
  unsigned int lastSignalChangeTimestamp;
  unsigned int shortestIdleDelay;
  unsigned int longestIdleDelay;
} Signal;

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char symbol);
Signal* findSignalBySymbol(Signal* signals, unsigned int nsignals, char symbol);
void assignSignalUpdate(Signal *signal, char signalValue, int timestamp);
void closeSignalCounters(Signal* signal, unsigned int timestamp);
void printSignal(Signal* signal);

#endif
