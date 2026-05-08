#include "requestBodiesWorker.hpp"
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>
#include "raindrop.hpp"
#include "logger.hpp"

extern thread_local std::string CURRENT_TEMP_FILE_PATH;
extern logger LOGGER;

std::string requestBodiesWorker::getRandomString(size_t length) {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, charset.length() - 1);

    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result += charset[dis(gen)];
    }

    return result;
}

void requestBodiesWorker::writeBodyToDisk(const std::string& data, bool isFirstChunk) {

    if (isFirstChunk || CURRENT_TEMP_FILE_PATH.empty()) {
        CURRENT_TEMP_FILE_PATH = TEMP_FILE_PREFIX + getRandomString(20) + ".tmp";
    }

    std::ofstream out(CURRENT_TEMP_FILE_PATH, std::ios::binary | std::ios::app);

    if (out.is_open()) {
        out.write(data.data(), data.size());
        out.close();
    } else {
        LOGGER.log_server("Failed to open file: " + CURRENT_TEMP_FILE_PATH, SERVER_PORT, logger::ERROR);
    }

}