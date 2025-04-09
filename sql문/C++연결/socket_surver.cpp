# include <iostream>
# include <winsock2.h>
# include <vector>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main() {
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientSize = sizeof(clientAddr);
	vector<char> buffer(1024); // 버퍼 크기 설정
	// winsock 초기화
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	// socket()
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	// bind()
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	// listen()
	listen(serverSocket, SOMAXCONN);
	cout << "Server ready. Waiting for client..." << endl;
	// accept()
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientSize);
	cout << "Client connected." << endl;
	// send/recv()
	int recvLen = 0;
	while ((recvLen = recv(clientSocket, buffer.data(), buffer.size(), 0)) > 0) {
		cout << "Received: " << string(buffer.data(), recvLen) << endl;
		send(clientSocket, buffer.data(), recvLen, 0); // 그대로 다시 보냄
	}
	// close()
	closesocket(clientSocket); // 클라이언트 소켓을 닫고 서버 소켓을 사용합니다.
	closesocket(serverSocket); // 서버 소켓을 닫고 클라이언트 소켓을 사용합니다.
	WSACleanup();
	return 0;
}