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

    // Winsock 초기화
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
    std::cout << "아이디: ";
    std::getline(std::cin, username);
    std::cout << "비밀번호: ";
    std::getline(std::cin, password);

    // [6] 로그인 메시지 구성 및 전송
    std::string message = "LOGIN:" + username + ":" + password + ":";
    send(clientSocket, message.c_str(), static_cast<int>(message.length()), 0);

    // [7] 서버 응답 수신 (C++ 스타일로 처리)
    int bytesReceived = recv(clientSocket, buffer.data(), static_cast<int>(buffer.size()), 0);

    if (bytesReceived > 0) {
        std::string response(buffer.data(), bytesReceived);
        std::cout << "[서버 응답] " << response << std::endl;
    }
    else {
        std::cerr << "서버 응답 수신 실패\n";
    }

    // [8] 정리
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}