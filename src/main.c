#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "signal.h"
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

  unsigned char dumpVarsStarted = 0,
                dumpVarsEnded = 0;
  unsigned int timestamp = 0;
  while (getline(&line, &len, fp) != -1) {
    // Removing trailing line break
    if (line[strlen(line)-1] == '\n') {
      line[strlen(line)-1] = '\0';
    }

    printf("Line: %s\n", line);

    // Signal declaration line
    if (startsWith("$var", line)) {
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
    else if (startsWith("$dumpvars", line)) {
      dumpVarsStarted = 1;
    }
    else if (startsWith("$end", line) && dumpVarsStarted) {
      dumpVarsEnded = 1;
    }
    else if (dumpVarsEnded) {
      // Timestamp update
      if (line[0] == '#') {
        char timestampStr[16];
        strcpy(timestampStr, line+1);
        timestamp = atoi(timestampStr);
      }
      else {
        char symbol = line[strlen(line)-1];
        Signal* signal = findSignalBySymbol(signals, nsignals, symbol);
        assignSignalUpdate(signal, timestamp);
      }
    }
  }

  printf("--- FINAL REPORT ---\n");
  int i;
  for(i = 0; i < nsignals; i++) {
    printf("Name: %s, Id: %c, LastSignalUpdate: %d, ShortestSinalDelay: %d, LongestSinalDelay: %d\n\n",
            signals[i].name, signals[i].identifier, signals[i].lastSignalUpdate, signals[i].shortestSinalDelay, signals[i].longestSinalDelay);
  }

  return 0;
}
