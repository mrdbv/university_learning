# ARP lab

This project provides two tools: a passive ARP monitor and a pcap-based ARP scenario generator.

The monitor listens for ARP traffic on a network interface and tracks mappings from IP addresses to MAC addresses. It reports when a mapping changes or when suspicious patterns appear.

The simulator produces synthetic ARP traffic and writes it into a pcap file for offline analysis or replay in an isolated lab environment.

Building

mkdir build
cd build
cmake ..
cmake --build .

Usage

./arp_lab --mode monitor --iface <interface> [--json]
./arp_lab --mode simulate --scenario <normal|spoof|flood> --out <file.pcap>

Security and safe use

Only run the monitor on networks where you have permission. The simulator writes pcap files and does not send traffic to the network. If you use the generated pcap files with tools such as tcpreplay, do so only in isolated lab environments.
