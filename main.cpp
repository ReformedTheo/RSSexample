#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <Winsock2.h>
#include <regex>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return -1;
    }

    // Setup socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2189);
    serv_addr.sin_addr.s_addr = inet_addr("10.0.0.132");

    // Connect to the RFID reader
    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection Failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Setup camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    std::string command = "R\r\n";
    char buffer[1024] = {0};

    while (true) {
        // Send command
        send(sock, command.c_str(), static_cast<int>(command.size()), 0);

        // Read response
        int valread = recv(sock, buffer, 1024, 0);
        std::string response(buffer, valread);

        // Regex to find HEX code
        std::regex hex_pattern("H[0-9A-Fa-f]+");
        std::smatch matches;
        if (std::regex_search(response, matches, hex_pattern)) {
            for (const auto& match : matches) {
                std::string hex_code = match.str();

                // Capture and save image
                cv::Mat frame;
                if (cap.read(frame)) {
                    std::string imagePath = hex_code + ".jpg";
                    cv::imwrite(imagePath, frame);
                    std::cout << "Image saved as: " << imagePath << std::endl;
                } else {
                    std::cerr << "Failed to capture image" << std::endl;
                }
            }
        }

        Sleep(1000); // Wait for 1 second
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
