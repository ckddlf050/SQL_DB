#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    vector<char> buffer(1024);

    // Winsock �ʱ�ȭ
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // socket()
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // connect()
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    cout << "Connected to server." << endl;

    // send()/recv()
    std::string username, password;
    std::cout << "���̵�: ";
    std::getline(std::cin, username);
    std::cout << "��й�ȣ: ";
    std::getline(std::cin, password);

    // [6] �α��� �޽��� ���� �� ����
    std::string message = "LOGIN:" + username + ":" + password + ":";
    send(clientSocket, message.c_str(), static_cast<int>(message.length()), 0);

    // [7] ���� ���� ���� (C++ ��Ÿ�Ϸ� ó��)
    int bytesReceived = recv(clientSocket, buffer.data(), static_cast<int>(buffer.size()), 0);

    if (bytesReceived > 0) {
        std::string response(buffer.data(), bytesReceived);
        std::cout << "[���� ����] " << response << std::endl;
    }
    else {
        std::cerr << "���� ���� ���� ����\n";
    }

    // [8] ����
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}