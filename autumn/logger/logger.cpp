#include "logger.hpp"
#include <iostream>

std::string getCurrentTime() {
    const auto now = std::chrono::system_clock::now();

    const std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    std::tm tm{};
    localtime_r(&in_time_t, &tm);
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

std::string what_type(const logger::TYPE type) {
    switch (type) {
        case logger::DEBUG:
            return "DEBUG";
        case logger::INFO:
            return "INFO";
        case logger::WARNING:
            return "WARNING";
        case logger::ERROR:
            return "ERROR";
        case logger::FATAL:
            return "FATAL";
        default:
            return "undefined";
    }
}

void print_log_in_terminal(const std::string &server_message, const logger::TYPE type) {
    switch (type) {
        case logger::DEBUG:
            std::cout << "\033[32m" << server_message << "\033[0m";
            break;
        case logger::INFO:
            std::cout << server_message;
            break;
        case logger::WARNING:
            std::cout << "\033[1;33m" << server_message << "\033[0m";
            break;
        case logger::ERROR:
        case logger::FATAL:
            std::cerr << server_message;
            break;
    }
}

void logger::logger_thread() {
    while (true) {
        std::unique_lock lock(mtx);

        cv.wait(lock, [this] {
            return !messages.empty() || stop_work;
        });

        if (stop_work && messages.empty()) {
            break;
        }

        std::string task = messages.front();
        messages.pop();

        lock.unlock();

        fputs(task.c_str(), file);
        fflush(file);
    }
}

logger::logger(const std::string &u_file_path) {
    if (FILE *u_file = fopen(u_file_path.c_str(), "a"); u_file != nullptr) {
        this->file = u_file;
    } else {
        std::cerr << "Error opening file \"" << u_file_path << "\"" << std::endl;
        abort();
    }
    log_thread = std::thread(&logger::logger_thread, this);
}

logger::~logger() {
    {
        std::lock_guard lock(mtx);
        stop_work = true;
    }
    cv.notify_one();

    if (log_thread.joinable()) {
        log_thread.join();
    }

    if (file != nullptr) {
        fclose(file);
    }
}

void logger::set_file(FILE *u_file) {
    this->file = u_file;
}

FILE *logger::get_file() const {
    return file;
}

void logger::log_server(const std::string &message, const int port, const TYPE type) {
    {
        const std::string server_message = "[" + getCurrentTime() + "] " + "[" + what_type(type) + "] [PORT:" +
                                           std::to_string(port) + "] " + message + "\n";
        std::lock_guard lock(mtx);
        messages.push(server_message);
        print_log_in_terminal(server_message, type);
    }
    cv.notify_one();
}

