#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "main.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  Signal* signals = NULL;
  unsigned int nsignals = 0;

  const char* vcd_file = argv[1];
  char* name;
  char id;

  // Read VCD file
  FILE* fp;
  char* line = NULL;
  ssize_t len = 0;

  char* token = NULL;
  char* signalName = NULL;
  char signalId;

  if((fp = fopen(vcd_file, "r")) == NULL) {
    fprintf(stderr, "Failed to open VCD file: %s\n", vcd_file);
    exit(1);
  }

  while (getline(&line, &len, fp) != -1) {
    // Signal declaration line
    if (startsWith("$var", line) == 0) {
      // Ignore the first 3 parts of string.
      // Signal symbol is in the 4o part.
      // Signal name is in the 5o part.
      strtok(line, " ");
      strtok(NULL, " ");
      strtok(NULL, " ");
      token = strtok(NULL, " ");
      signalName = strtok(NULL, " ");
      signalId = token[0];
      printf ("[SIGNAL DECLARATION] -- Name: %s, Symbol: %c\n", signalName, signalId);
      createSignal(&signals, &nsignals, signalName, signalId);
    }
  }

  int i;
  for(i = 0; i < nsignals; i++) {
    printf(">>>>>> Name: %s, Id: %c\n", signals[i].name, signals[i].identifier);
  }

  return 0;
}

void createSignal(Signal** signals, unsigned int* nsignals, char* name, char identifier) {
  Signal* newSignal = (Signal*)malloc(sizeof(newSignal));
  newSignal->name = (char*)malloc(strlen(name) * sizeof(char));

  strcpy(newSignal->name, name);
  newSignal->identifier = identifier;
  newSignal->lastSignalUpdate   = 0;
  newSignal->shortestSinalDelay = 0;
  newSignal->longestSinalDelay  = 0;

  *signals = (Signal*)realloc(*signals, (++(*nsignals)) * sizeof(Signal));
  (*signals)[*nsignals-1] = *newSignal;
}
