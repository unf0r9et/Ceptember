#include "engine.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include "string"
#include "logger.hpp"
#include "httpController.hpp"
#include <filesystem>
#include <unordered_set>
#include "fileSearch.hpp"
#include <fstream>

logger LOGGER(LoggerPath);
std::unordered_set<std::string> staticDirectories;
thread_local std::string httpBodyToSendPath;

extern thread_local mode MDtoReceive;
thread_local mode MDtoSend = RequestHTTP;
extern thread_local int content_size;
extern thread_local requestEntity rqEntity;
extern thread_local std::string CURRENT_TEMP_FILE_PATH;

void resetThreadState() {
    MDtoReceive = RequestHTTP;
    MDtoSend = RequestHTTP;
    content_size = 0;
    rqEntity = requestEntity();
    CURRENT_TEMP_FILE_PATH = "";
    httpBodyToSendPath = "";
}

void openSocket() {
    LOGGER.log_server("[ENGINE] SERVER STARTED", SERVER_PORT, logger::INFO);

    sockaddr_in socket_address = {AF_INET, htons(SERVER_PORT), INADDR_ANY, 0};
    const int socket_listener = socket(AF_INET, SOCK_STREAM, 0);

    constexpr int opt = 1;
    setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(socket_listener, reinterpret_cast<struct sockaddr *>(&socket_address), sizeof(socket_address)) < 0) {
        LOGGER.log_server("[ENGINE] Error while trying to BIND socket", SERVER_PORT, logger::ERROR);
        return;
    }

    if (listen(socket_listener, 5) < 0) {
        LOGGER.log_server("[ENGINE] Error while trying to LISTEN socket", SERVER_PORT, logger::ERROR);
        return;
    }

    LOGGER.log_server("[ENGINE] Waiting for client...", SERVER_PORT, logger::INFO);

    while (true) {
        sockaddr_in client_address = {};
        socklen_t client_len = sizeof(client_address);

        int socket_client;

        if ((socket_client = accept(socket_listener, reinterpret_cast<struct sockaddr *>(&client_address),
                                    &client_len)) <
            0) {
            LOGGER.log_server("[ENGINE] Error while trying to ACCEPT socket", SERVER_PORT, logger::ERROR);
            return;
        }

        LOGGER.log_server("[ENGINE] Client connected", SERVER_PORT, logger::INFO);

        LOGGER.log_server(
            "[ENGINE] Client " + std::string(inet_ntoa(client_address.sin_addr)) + ":" +
            std::to_string(ntohs(client_address.sin_port)) + " connected", SERVER_PORT, logger::INFO);

        std::thread client_thread([socket_client]() {
                resetThreadState();

                char buf[MaximumRequestSize];
                bool isWork = true;
                while (isWork) {
                    switch (MDtoSend) {
                        case RequestHTTP: {
                            int bytes = recv(socket_client, buf, sizeof(buf), 0);
                            if (bytes <= 0) {
                                isWork = false;
                                break;
                            }

                            LOGGER.log_server("[ENGINE] Request: " + std::string(buf, 40), SERVER_PORT,
                                              logger::INFO);

#ifdef debug
                            LOGGER.log_server("Received bytes: " + std::to_string(bytes), SERVER_PORT,
                                              logger::DEBUG);
#endif

                            std::string request_data(buf, bytes);

                            std::string response = httpController::startHttpController(request_data);
                            if (response == LOADING_PROCESS) {
                                continue;
                            }

                            send(socket_client, response.data(), response.size(), 0);
                        }
                        break;
                        case LoadingHTTP:
                            if (httpBodyToSendPath.empty()) {
                                std::string response = HTTP_RESPONSE_502;
                                send(socket_client, response.data(), response.size(), 0);
                                MDtoSend = RequestHTTP;
                            } else {
                                std::ifstream file(httpBodyToSendPath, std::ios::binary);
                                if (file.is_open()) {
                                    const size_t BUFFER_SIZE = 8192;
                                    std::vector<char> buffer(BUFFER_SIZE);
                                    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
                                        std::streamsize bytesRead = file.gcount();

                                        ssize_t bytesSent = send(socket_client, buffer.data(), bytesRead, 0);

                                        if (bytesSent == -1) {
                                            isWork = false;
                                            break;
                                        }
                                    }
                                    file.close();
                                }
                            }
                            MDtoSend = RequestHTTP;
                            break;
                        default:
                            std::string response = HTTP_RESPONSE_500;
                            send(socket_client, response.data(), response.size(), 0);
                            isWork = false;
                            break;
                    }
                }

                close(socket_client);
            }
        );
        client_thread.detach();
        LOGGER.log_server("[ENGINE] Client " + std::string(inet_ntoa(client_address.sin_addr)) + ":" +
                          std::to_string(ntohs(client_address.sin_port)) + " disconnected", SERVER_PORT,
                          logger::INFO);
    }
}

int engine::startTheRain() {
    staticDirectories = buildFolderSet(StaticRootPath);
    openSocket();
    return 0;
}
