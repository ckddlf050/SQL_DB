#include <iostream>
#include <winsock2.h>
#include<WS2tcpip.h>
#include<vector>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() 
{
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN  serverAddr;
	vector<char> buffer(1024);
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//sorcket()
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// connect()
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

	connect(clientSocket, (SOCKADDR*)&serverAddr,sizeof(serverAddr));
	cout << "connected to server." << endl;

	//send()/recv() ±¸Çö
	while (true)
	{
		cout << "message: ";
		cin.getline(buffer.data(), sizeof(buffer));

		if (strcmp(buffer.data(), "exit") == 0)break;

		send(clientSocket, buffer.data(), strlen(buffer.data()), 0);
		int recvLen = recv(clientSocket, buffer.data(), sizeof(buffer), 0);
		cout << "server recieve : " << buffer.data() << endl;
	
	}

	//close()
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}