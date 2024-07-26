#include "TCP.h"
#include "TCPServer.h"
#include <iostream>
#include <thread>
#include <chrono>

void runServer() {
    TCPServer server("127.0.0.1", 12345);
    server.start();
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Server'ı 10 saniye çalıştır
    server.stop();
}

void runClient() {
    TCP& tcpClient = TCP::getInstance();
    tcpClient.start("127.0.0.1", 12345);

    // Test verilerini gönder
    for (int i = 0; i < 5; ++i) {
        tcpClient.insert("Message " + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    tcpClient.stop();
}

int main() {
    std::thread serverThread(runServer);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Server'ın başlatılmasını bekle

    runClient();

    serverThread.join();
    return 0;
}
