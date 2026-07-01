#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <winhttp.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winhttp.lib")

#pragma pack(push, 1)
struct IPHeader {
	uint8_t  v_hl;
	uint8_t  tos;
	uint16_t total_len;
	uint16_t id;
	uint16_t frag_offset;
	uint8_t  ttl;
	uint8_t  protocol;
	uint16_t checksum;
	uint32_t src_addr;
	uint32_t dst_addr;
};

struct UDPHeader {
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t length;
	uint16_t checksum;
};
#pragma pack(pop)

class NetworkMonitor {
private:
	SOCKET _socket;
	bool _is_running;

	std::string get_timestamp() {
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		char buf[20];
		strftime(buf, sizeof(buf), "%H:%M:%S", &ltm);
		return std::string(buf);
	}

	void process_dns_query(const uint8_t* payload, int size) {
		const uint8_t* query_ptr = payload + 12;
		std::string domain = "";

		while (*query_ptr != 0 && (query_ptr - payload) < size) {
			int len = *query_ptr++;
			for (int i = 0; i < len; ++i) {
				domain += (char)*query_ptr++;
			}
			if (*query_ptr != 0) domain += ".";
		}

		if (!domain.empty()) {
			std::cout << "[" << get_timestamp() << "] DNS Request -> " << domain << std::endl;
		}
	}

public:
	NetworkMonitor() : _socket(INVALID_SOCKET), _is_running(false) {}

	bool initialize(const std::string& interface_ip) {
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;

		_socket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		if (_socket == INVALID_SOCKET) {
			std::cerr << "Error: Run as Admin! (WSAGetLastError: " << WSAGetLastError() << ")" << std::endl;
			return false;
		}

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		inet_pton(AF_INET, interface_ip.c_str(), &addr.sin_addr);
		addr.sin_port = htons(0);

		if (bind(_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) return false;

		unsigned long mode = RCVALL_ON;
		if (ioctlsocket(_socket, SIO_RCVALL, &mode) == SOCKET_ERROR) return false;

		_is_running = true;
		return true;
	}

	static std::string ip_to_str(uint32_t ip) {
		char buf[INET_ADDRSTRLEN];
		in_addr a;
		a.s_addr = ip;
		inet_ntop(AF_INET, &a, buf, INET_ADDRSTRLEN);
		return std::string(buf);
	}

	void run() {
		std::vector<uint8_t> buffer(65535);
		std::cout << "--- SNIFFER STARTED (CTRL+C to stop) ---" << std::endl;

		while (_is_running) {
			int bytes_read = recv(_socket, (char*)buffer.data(), buffer.size(), 0);
			if (bytes_read < sizeof(IPHeader)) continue;

			IPHeader* iph = reinterpret_cast<IPHeader*>(buffer.data());

			if (iph->protocol == 17) {
				int ip_hlen = (iph->v_hl & 0x0F) * 4;
				UDPHeader* udph = reinterpret_cast<UDPHeader*>(buffer.data() + ip_hlen);

				if (ntohs(udph->dst_port) == 53) {
					process_dns_query(buffer.data() + ip_hlen + sizeof(UDPHeader),
						bytes_read - ip_hlen - sizeof(UDPHeader));
				}
			}
		}
	}

	~NetworkMonitor() {
		if (_socket != INVALID_SOCKET) closesocket(_socket);
		WSACleanup();
	}

	static void inet_ptrack(int af, const char* src, in_addr* dst) {
		inet_pton(af, src, dst);
	}
};

int main() {
	NetworkMonitor sniffer;
	std::string my_ip = "192.168.0.12";

	if (sniffer.initialize(my_ip)) {
		sniffer.run();
	}

	return 0;
}
