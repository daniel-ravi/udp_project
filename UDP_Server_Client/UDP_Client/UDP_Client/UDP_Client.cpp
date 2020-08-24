#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class udp {

protected:
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version, &data);
	unsigned short portnumber = 50003;

	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in server;


public:
	void checkudp()
	{
		if (wsOk != 0)
		{
			cout << "Can't start Winsock! " << wsOk;
			return;
		}
	}

};

class udp_client : public udp {

public:
	udp_client() {

		for(int i=0;i<256;i++)
			clientIp[i] = '0';

	}

private:
	char clientIp[256];


public:
	void udpworking(int argc, char* argv[])
	{
		server.sin_family = AF_INET;
		server.sin_port = htons(portnumber);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		string s(argv[1]);
		int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR)
		{
			cout << "That didn't work! " << WSAGetLastError() << endl;
		}
		closesocket(out);
		WSACleanup();
	}
};

int main(int argc, char** argv) {
	udp_client obj;
	obj.checkudp();
	obj.udpworking(argc, argv);
	return 0;
}
