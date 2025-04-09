#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>
#include <mysql/jdbc.h>

#pragma comment(lib, "ws2_32.lib")

const std::string DB_HOST = "tcp://127.0.0.1:3306";
const std::string DB_USER = "root";
const std::string DB_PASS = "1234";
const std::string DB_NAME = "codingon_db";

void handleClient(SOCKET clientSocket) {
    std::vector<char> buffer(1024);
    int recvLen = recv(clientSocket, buffer.data(), buffer.size(), 0);

    if (recvLen <= 0) {
        closesocket(clientSocket);
        return;
    }

    std::string msg(buffer.data(), recvLen);
    std::cout << "[RECV] " << msg << std::endl;

    if (msg.rfind("LOGIN:", 0) == 0) {
        size_t pos1 = msg.find(":", 6);
        size_t pos2 = msg.find(":", pos1 + 1);

        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            std::string error = "Invalid Format";
            send(clientSocket, error.c_str(), error.length(), 0);
            closesocket(clientSocket);
            return;
        }

        std::string username = msg.substr(6, pos1 - 6);
        std::string password = msg.substr(pos1 + 1, pos2 - pos1 - 1);

        try {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            std::unique_ptr<sql::Connection> conn(
                driver->connect(DB_HOST, DB_USER, DB_PASS)
            );
            conn->setSchema(DB_NAME);

            std::unique_ptr<sql::PreparedStatement> pstmt(
                conn->prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")
            );
            pstmt->setString(1, username);
            pstmt->setString(2, password);

            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            std::string result = res->next() ? "Login Success" : "Login Failed";
            send(clientSocket, result.c_str(), result.length(), 0);
        }
        catch (sql::SQLException& e) {
            std::cerr << "MySQL Error: " << e.what() << std::endl;
            std::string err = "DB Error";
            send(clientSocket, err.c_str(), err.length(), 0);
        }
    }
    else {
        std::string error = "Unknown Command";
        send(clientSocket, error.c_str(), error.length(), 0);
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));


    listen(serverSocket, SOMAXCONN);
    std::cout << "Server Listen in 12345" << std::endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            handleClient(clientSocket);
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}