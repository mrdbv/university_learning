#include "arp_lab/arp_simulator.hpp"
#include <pcap.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <sys/time.h>

namespace arp_lab {

static void write_packet(pcap_dumper_t* dumper, const std::vector<uint8_t>& pkt) {
    pcap_pkthdr hdr;
    timeval tv;
    gettimeofday(&tv, nullptr);
    hdr.ts = tv;
    hdr.caplen = pkt.size();
    hdr.len = pkt.size();
    pcap_dump((u_char*)dumper, &hdr, pkt.data());
}

static std::vector<uint8_t> make_arp_packet(const uint8_t dst_mac[6], const uint8_t src_mac[6], uint16_t op, uint32_t spa, uint8_t sha[6], uint32_t tpa, uint8_t tha[6]) {
    std::vector<uint8_t> pkt(14 + 28);
    std::memcpy(pkt.data(), dst_mac, 6);
    std::memcpy(pkt.data() + 6, src_mac, 6);
    pkt[12] = 0x08;
    pkt[13] = 0x06;
    uint8_t* arp = pkt.data() + 14;
    arp[0] = 0x00;
    arp[1] = 0x01;
    arp[2] = 0x08;
    arp[3] = 0x00;
    arp[4] = 6;
    arp[5] = 4;
    arp[6] = (op >> 8) & 0xff;
    arp[7] = op & 0xff;
    std::memcpy(arp + 8, sha, 6);
    std::memcpy(arp + 14, &spa, 4);
    std::memcpy(arp + 18, tha, 6);
    std::memcpy(arp + 24, &tpa, 4);
    return pkt;
}

int simulator_run(const std::string& scenario, const std::string& out) {
    pcap_t* dead = pcap_open_dead(DLT_EN10MB, 65535);
    if (!dead) return 1;
    pcap_dumper_t* dumper = pcap_dump_open(dead, out.c_str());
    if (!dumper) {
        pcap_close(dead);
        return 1;
    }

    uint8_t mac1[6] = {0x02,0x42,0xac,0x11,0x00,0x02};
    uint8_t mac2[6] = {0x02,0x42,0xac,0x11,0x00,0x03};
    uint8_t mac3[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
    uint32_t ip1; inet_pton(AF_INET, "192.168.56.101", &ip1);
    uint32_t ip2; inet_pton(AF_INET, "192.168.56.102", &ip2);
    if (scenario == "normal") {
        std::vector<uint8_t> req = make_arp_packet(mac3, mac1, 1, ip1, mac1, ip2, (uint8_t*)"\0\0\0\0\0\0");
        write_packet(dumper, req);
        std::vector<uint8_t> rep = make_arp_packet(mac1, mac2, 2, ip2, mac2, ip1, mac1);
        write_packet(dumper, rep);
    } else if (scenario == "spoof") {
        std::vector<uint8_t> rep = make_arp_packet(mac1, mac2, 2, ip1, mac2, ip2, mac2);
        write_packet(dumper, rep);
    } else if (scenario == "flood") {
        for (int i = 0; i < 1000; ++i) {
            std::vector<uint8_t> pkt = make_arp_packet(mac3, mac1, 1, ip1, mac1, ip2, (uint8_t*)"\0\0\0\0\0\0");
            write_packet(dumper, pkt);
        }
    } else {
        pcap_dump_close(dumper);
        pcap_close(dead);
        return 1;
    }

    pcap_dump_close(dumper);
    pcap_close(dead);
    return 0;
}

}
