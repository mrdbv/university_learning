#include "arp_lab/arp_monitor.hpp"
#include "arp_lab/arp_simulator.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string mode;
    std::string iface;
    std::string scenario;
    std::string out;
    bool json = false;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--mode" && i + 1 < argc) {
            mode = argv[++i];
        } else if (a == "--iface" && i + 1 < argc) {
            iface = argv[++i];
        } else if (a == "--scenario" && i + 1 < argc) {
            scenario = argv[++i];
        } else if (a == "--out" && i + 1 < argc) {
            out = argv[++i];
        } else if (a == "--json") {
            json = true;
        }
    }

    if (mode == "monitor") {
        if (iface.empty()) {
            std::cerr << "interface required for monitor mode\n";
            return 1;
        }
        return arp_lab::monitor_run(iface, json);
    }

    if (mode == "simulate") {
        if (scenario.empty() || out.empty()) {
            std::cerr << "scenario and out file required for simulate mode\n";
            return 1;
        }
        return arp_lab::simulator_run(scenario, out);
    }

    std::cerr << "usage:\n  --mode monitor --iface <interface> [--json]\n  --mode simulate --scenario <normal|spoof|flood> --out <file.pcap>\n";
    return 1;
}
