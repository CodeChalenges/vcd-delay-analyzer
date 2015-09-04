#include <stdlib.h>
#include <stdio.h>
#include "signal.h"
#include "main.h"

int main(int argc, char* argv[]) {
  Signal* signals = NULL;
  unsigned int nsignals = 0;

  char* name = (char*)malloc(100 * sizeof(char));
  char id;

  //Create first signal
  name = (char*)malloc(100 * sizeof(char));
  sprintf(name, "%s", "Signal A");
  id = 'A';
  createSignal(&signals, &nsignals, name, id);

  //Create second signal
  name = (char*)malloc(100 * sizeof(char));
  sprintf(name, "%s", "Signal $");
  id = '$';
  createSignal(&signals, &nsignals, name, id);

  int i;
  for(i = 0; i < nsignals; i++) {
    printf("Name: %s, Id: %c\n", signals[i].name, signals[i].identifier);
  }

  return 0;
}

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char identifier) {
  *signals = (Signal*)realloc(*signals, (++(*nsignals)) * sizeof(Signal));
  signals[*nsignals-1]->name = name;
  signals[*nsignals-1]->identifier = identifier;
  signals[*nsignals-1]->lastSignalUpdate   = 0;
  signals[*nsignals-1]->shortestSinalDelay = 0;
  signals[*nsignals-1]->longestSinalDelay  = 0;
}
