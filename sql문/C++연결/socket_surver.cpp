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
	vector<char> buffer(1024); // ���� ũ�� ����
	// winsock �ʱ�ȭ
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
		send(clientSocket, buffer.data(), recvLen, 0); // �״�� �ٽ� ����
	}
	// close()
	closesocket(clientSocket); // Ŭ���̾�Ʈ ������ �ݰ� ���� ������ ����մϴ�.
	closesocket(serverSocket); // ���� ������ �ݰ� Ŭ���̾�Ʈ ������ ����մϴ�.
	WSACleanup();
	return 0;
}