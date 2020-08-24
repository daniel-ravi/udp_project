#include <iostream>
#include <WS2tcpip.h>

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")
using namespace std;

class udp {

protected:
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	unsigned short portnumber = 50003;
	int wsOk = WSAStartup(version, &data);

	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	sockaddr_in client;
	int clientLength = sizeof(client);

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

class udp_server : public udp {

public:
	udp_server() {

		for (int i = 0; i < 1024; i++)
			buf[i] = '0';
		
		bytesIn = 0;
		count = 0;

		for (int i = 0; i < 256; i++)
			clientIp[i] = '0';
	}

private:

	char buf[1024];
	int bytesIn;
	int count;
	char clientIp[256];


public:
	void udpworking() {

			serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
			serverHint.sin_family = AF_INET;
			serverHint.sin_port = htons(portnumber);

			if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
			{
				cout << "Can't bind socket! " << WSAGetLastError() << endl;
				return;
			}

			while (count < 5)
			{
				ZeroMemory(&client, clientLength);
				ZeroMemory(buf, 1024);

				bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
				if (bytesIn == SOCKET_ERROR)
				{
					cout << "Error receiving from client " << WSAGetLastError() << endl;
					continue;
				}
				ZeroMemory(clientIp, 256);
				inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
				cout << "Message recv from " << clientIp << " : " << buf << endl;
				count++;
			}
			closesocket(in);
			WSACleanup();


	}
};
void main()
{
	udp_server obj;
	obj.checkudp();
	obj.udpworking();
}