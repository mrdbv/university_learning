#!/bin/sh
set -e
if [ ! -d build ]; then
  mkdir build
fi
cd build
cmake ..
cmake --build .
./arp_lab --mode simulate --scenario spoof --out ../tests/spoof.pcap
printf "generated ../tests/spoof.pcap\n"
