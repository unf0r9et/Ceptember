//
// Created by unf0r9et on 02.02.2026.
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H
#include <string>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class logger {
public:
    enum TYPE { DEBUG, INFO, WARNING, ERROR, FATAL };

    explicit logger(const std::string&);
    ~logger();

    void set_file(FILE *u_file);
    [[nodiscard]] FILE *get_file() const;

    void log_server(const std::string&, int port, TYPE type = INFO);

protected:
    FILE *file = nullptr;
    std::queue<std::string> messages;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread log_thread;
    bool stop_work = false;

    void logger_thread();
};


#endif //SERVER_LOGGER_H
