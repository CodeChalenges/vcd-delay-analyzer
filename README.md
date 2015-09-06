# vcd-delay-analyzer
A simple project that checks the signal with longer and shorter idle time in a VCD file

Compile
-------
```sh
$ make       # Compile
$ make clean # Cleanup intermediary files
```

Run
---
```sh
$ ./vcd-delay-analyzer [PATH TO VCD FILE]
```

Example
-------
```sh
$ ./vcd-delay-analyzer resources/sample.vcd

--- FINAL REPORT ---
[SIGNAL] Name: data            Symbol: #   LastSignalUpdate: 2296   ShortestSinalDelay: 0      LongestSinalDelay: 2296
[SIGNAL] Name: data_valid      Symbol: $   LastSignalUpdate: 2302   ShortestSinalDelay: 0      LongestSinalDelay: 2296
[SIGNAL] Name: en              Symbol: %   LastSignalUpdate: 0      ShortestSinalDelay: 0      LongestSinalDelay: 0
[SIGNAL] Name: rx_en           Symbol: &   LastSignalUpdate: 0      ShortestSinalDelay: 0      LongestSinalDelay: 0
[SIGNAL] Name: tx_en           Symbol: '   LastSignalUpdate: 2211   ShortestSinalDelay: 0      LongestSinalDelay: 2211
[SIGNAL] Name: empty           Symbol: (   LastSignalUpdate: 0      ShortestSinalDelay: 0      LongestSinalDelay: 0
[SIGNAL] Name: underrun        Symbol: )   LastSignalUpdate: 0      ShortestSinalDelay: 0      LongestSinalDelay: 0

Number of Signals: 7
Shortest delay: signal "data" with delay of 0
Longest  delay: signal "data" with delay of 2296
```
