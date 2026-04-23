#include "engine.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "string"
#include "logger.hpp"
#include "httpController.hpp"

logger LOGGER("../logs/frameworkLogs.txt");

void openSocket();

int engine::startTheRain() {
    openSocket();
    // std::thread t(openSocket);
    // t.join();
    return 0;
}

void openSocket() {
    LOGGER.log_server("SERVER STARTED", SERVER_PORT, logger::INFO);

    sockaddr_in socket_address = {AF_INET, htons(SERVER_PORT), INADDR_ANY, 0};
    const int socket_listener = socket(AF_INET, SOCK_STREAM, 0);

    constexpr int opt = 1;
    setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(socket_listener, reinterpret_cast<struct sockaddr *>(&socket_address), sizeof(socket_address)) < 0) {
        LOGGER.log_server("Error while trying to BIND socket", SERVER_PORT, logger::ERROR);
        return;
    }

    if (listen(socket_listener, 5) < 0) {
        LOGGER.log_server("Error while trying to LISTEN socket", SERVER_PORT, logger::ERROR);
        return;
    }

    LOGGER.log_server("Waiting for client...", SERVER_PORT, logger::INFO);

    while (true) {
        sockaddr_in client_address = {};
        socklen_t client_len = sizeof(client_address);

        int socket_client;

        if ((socket_client = accept(socket_listener, reinterpret_cast<struct sockaddr *>(&client_address),
                                    &client_len)) <
            0) {
            LOGGER.log_server("Error while trying to ACCEPT socket", SERVER_PORT, logger::ERROR);
            return;
        }

        LOGGER.log_server("Client connected", SERVER_PORT, logger::INFO);

        LOGGER.log_server(
            "Client " + std::string(inet_ntoa(client_address.sin_addr)) + ":" +
            std::to_string(ntohs(client_address.sin_port)) + " connected", SERVER_PORT, logger::INFO);

        std::thread client_thread([socket_client]() {
            char buf[65536];

            while (true) {
                int bytes = recv(socket_client, buf, sizeof(buf), 0);
                if (bytes <= 0) break;

                std::string request_data(buf, bytes);

                std::string response = httpController::startHttpController(request_data);
                if (response == "LOADING_PROCESS") {
                    continue;
                }

                send(socket_client, response.data(), response.size(), 0);
            }

            close(socket_client);
        });

        client_thread.detach();
    }
}
