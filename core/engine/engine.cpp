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

    engine::printLogo();

    LOGGER.log_server("[ENGINE] SERVER STARTED", SERVER_PORT, logger::INFO);

    sockaddr_in socket_address = {AF_INET, htons(SERVER_PORT), INADDR_ANY, 0};
    const int socket_listener = socket(AF_INET, SOCK_STREAM, 0);

    constexpr int opt = 1;
    setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(socket_listener, reinterpret_cast<sockaddr *>(&socket_address), sizeof(socket_address)) < 0) {
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

        if ((socket_client = accept(socket_listener, reinterpret_cast<sockaddr *>(&client_address),
                                    &client_len)) <
            0) {
            LOGGER.log_server("[ENGINE] Error while trying to ACCEPT socket", SERVER_PORT, logger::ERROR);
            continue;
        }

        timeval tv{};
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;
        setsockopt(socket_client, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
        setsockopt(socket_client, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);

        LOGGER.log_server("[ENGINE] Client connected", SERVER_PORT, logger::INFO);

        std::thread client_thread([socket_client, client_address]() {
                std::string client_info = std::string(inet_ntoa(client_address.sin_addr)) + ":" +
                                          std::to_string(ntohs(client_address.sin_port));

                LOGGER.log_server("[ENGINE] Client " + client_info + " connected", SERVER_PORT, logger::INFO);

                resetThreadState();

                char buf[MaximumRequestSize];
                bool isWork = true;
                while (isWork) {
                    switch (MDtoSend) {
                        case RequestHTTP: {
                            int bytes = recv(socket_client, buf, sizeof(buf), 0);
                            if (bytes <= 0) {
                                if (bytes < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                                    LOGGER.log_server("[ENGINE] Connection closed by timeout", SERVER_PORT,
                                                      logger::INFO);
                                } else if (bytes == 0) {
                                    LOGGER.log_server("[ENGINE] Client disconnected gracefully", SERVER_PORT,
                                                      logger::INFO);
                                } else {
                                    LOGGER.log_server("[ENGINE] Recv error: " + std::to_string(errno), SERVER_PORT,
                                                      logger::ERROR);
                                }
                                isWork = false;
                                break;
                            } {
#ifdef debug
                                LOGGER.log_server("Received bytes: " + std::to_string(bytes), SERVER_PORT,
                                                  logger::DEBUG);
#endif
                                std::string preview(buf, std::min(bytes, 40));
                                std::replace(preview.begin(), preview.end(), '\r', ' ');
                                std::replace(preview.begin(), preview.end(), '\n', ' ');

                                LOGGER.log_server("[ENGINE] Request: " + preview, SERVER_PORT, logger::INFO);
                            }

                            std::string request_data(buf, bytes);

                            std::string response = httpController::startHttpController(request_data);
                            if (response == LOADING_PROCESS) {
                                continue;
                            }

                            ssize_t sent_bytes = send(socket_client, response.data(), response.size(), MSG_NOSIGNAL);
                            if (sent_bytes == -1) {
                                isWork = false;
                            }
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
                                    constexpr size_t BUFFER_SIZE = 8192;
                                    std::vector<char> buffer(BUFFER_SIZE);
                                    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
                                        std::streamsize bytesRead = file.gcount();

                                        ssize_t bytesSent = send(socket_client, buffer.data(), bytesRead, MSG_NOSIGNAL);

                                        if (bytesSent == -1) {
                                            isWork = false;
                                        }
                                    }
                                    file.close();
                                }
                            }
                            MDtoSend = RequestHTTP;
                            break;
                        default:
                            std::string response = HTTP_RESPONSE_500;
                            send(socket_client, response.data(), response.size(), MSG_NOSIGNAL);
                            isWork = false;
                            break;
                    }
                }

                close(socket_client);
                LOGGER.log_server("[ENGINE] Client " + std::string(inet_ntoa(client_address.sin_addr)) + ":" +
                                  std::to_string(ntohs(client_address.sin_port)) + " disconnected", SERVER_PORT,
                                  logger::INFO);
            }
        );
        client_thread.detach();
    }
}

int engine::startTheRain() {
    staticDirectories = buildFolderSet(StaticRootPath);
    openSocket();
    return 0;
}
