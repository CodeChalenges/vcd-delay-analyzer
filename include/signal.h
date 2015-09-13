#ifndef SIGNAL_H
#define SIGNAL_H

typedef struct {
  char* name;
  char symbol;
  unsigned char currentSignalValue;
  unsigned char hasPassedInIdle;
  unsigned int lastSignalChangeTimestamp;
  unsigned int shortestIdleDelay;
  unsigned int longestIdleDelay;
} Signal;

/* Create a new signal */
void createSignal(Signal** signals, unsigned int* nsignals, char* name, char symbol);

/* Find a signal by its symbol in VCD */
Signal* findSignalBySymbol(Signal* signals, unsigned int nsignals, char symbol);

/* Assign a signal value change */
void assignSignalUpdate(Signal *signal, unsigned char signalValue, int timestamp);

/* Close all signal counters */
void closeSignalCounters(Signal* signal, unsigned int timestamp);

/* Print signal info */
void printSignal(Signal* signal);

#endif
