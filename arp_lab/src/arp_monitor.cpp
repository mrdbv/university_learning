#include "arp_lab/arp_monitor.hpp"
#include <pcap.h>
#include <iostream>
#include <unordered_map>
#include <array>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <sys/time.h>

namespace arp_lab {

struct Context {
    std::unordered_map<uint32_t, std::array<uint8_t,6>> ip2mac;
    bool json;
};

static void packet_handler(u_char* user, const pcap_pkthdr* h, const u_char* bytes) {
    Context* ctx = reinterpret_cast<Context*>(user);
    if (h->len < 42) return;
    const u_char* eth = bytes;
    uint16_t ethertype = (eth[12] << 8) | eth[13];
    if (ethertype != 0x0806) return;
    const u_char* arp = bytes + 14;
    uint16_t op = (arp[6] << 8) | arp[7];
    std::array<uint8_t,6> sha;
    std::memcpy(sha.data(), arp + 8, 6);
    uint32_t spa;
    std::memcpy(&spa, arp + 14, 4);
    in_addr addr;
    addr.s_addr = spa;
    char ipbuf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr, ipbuf, sizeof(ipbuf));
    auto it = ctx->ip2mac.find(spa);
    if (it == ctx->ip2mac.end()) {
        ctx->ip2mac[spa] = sha;
        if (ctx->json) {
            std::cout << "{\"level\":\"info\",\"event\":\"new\",\"ip\":\"" << ipbuf << "\",\"mac\":\"";
            char macs[18];
            std::snprintf(macs, sizeof(macs), "%02x:%02x:%02x:%02x:%02x:%02x", sha[0],sha[1],sha[2],sha[3],sha[4],sha[5]);
            std::cout << macs << "\"}\n";
        } else {
            char macs[18];
            std::snprintf(macs, sizeof(macs), "%02x:%02x:%02x:%02x:%02x:%02x", sha[0],sha[1],sha[2],sha[3],sha[4],sha[5]);
            std::cout << "new mapping: " << ipbuf << " -> " << macs << std::endl;
        }
    } else {
        if (it->second != sha) {
            std::array<uint8_t,6> old = it->second;
            it->second = sha;
            if (ctx->json) {
                char oldm[18];
                std::snprintf(oldm, sizeof(oldm), "%02x:%02x:%02x:%02x:%02x:%02x", old[0],old[1],old[2],old[3],old[4],old[5]);
                char newm[18];
                std::snprintf(newm, sizeof(newm), "%02x:%02x:%02x:%02x:%02x:%02x", sha[0],sha[1],sha[2],sha[3],sha[4],sha[5]);
                std::cout << "{\"level\":\"alert\",\"event\":\"change\",\"ip\":\"" << ipbuf << "\",\"old\":\"" << oldm << "\",\"new\":\"" << newm << "\"}\n";
            } else {
                char oldm[18];
                std::snprintf(oldm, sizeof(oldm), "%02x:%02x:%02x:%02x:%02x:%02x", old[0],old[1],old[2],old[3],old[4],old[5]);
                char newm[18];
                std::snprintf(newm, sizeof(newm), "%02x:%02x:%02x:%02x:%02x:%02x", sha[0],sha[1],sha[2],sha[3],sha[4],sha[5]);
                std::cout << "ALERT: IP " << ipbuf << " changed MAC " << oldm << " -> " << newm << std::endl;
            }
        }
    }
}

int monitor_run(const std::string& iface, bool json) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* p = pcap_open_live(iface.c_str(), 65536, 1, 1000, errbuf);
    if (!p) {
        std::cerr << "pcap_open_live failed: " << errbuf << std::endl;
        return 1;
    }
    struct bpf_program fp;
    if (pcap_compile(p, &fp, "arp", 1, PCAP_NETMASK_UNKNOWN) != 0) {
        std::cerr << "pcap_compile failed" << std::endl;
        pcap_close(p);
        return 1;
    }
    if (pcap_setfilter(p, &fp) != 0) {
        std::cerr << "pcap_setfilter failed" << std::endl;
        pcap_freecode(&fp);
        pcap_close(p);
        return 1;
    }
    Context ctx;
    ctx.json = json;
    pcap_loop(p, 0, packet_handler, reinterpret_cast<u_char*>(&ctx));
    pcap_freecode(&fp);
    pcap_close(p);
    return 0;
}

}
