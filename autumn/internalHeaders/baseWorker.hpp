#ifndef CEPTEMBER_BASEWORKER_H
#define CEPTEMBER_BASEWORKER_H


#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "requestEntity.hpp"

namespace fs = std::filesystem;

class baseWorker {
protected:
    static std::string getBoundary(const requestEntity &request) {
        for (const auto& header : request.headers) {
            std::string key = header.first;
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            if (key == "content-type") {
                size_t pos = header.second.find("boundary=");
                if (pos != std::string::npos) return "--" + header.second.substr(pos + 9);
            }
        }
        return "";
    }

    static std::string sanitizeFilename(std::string name) {
        if (name.empty()) return "file";
        std::string forbidden = "/\\?%*:|\"<> ";
        for (char &ch : name) {
            if (forbidden.find(ch) != std::string::npos) ch = '_';
        }
        return name;
    }

    static bool finalizeSave(const std::string &title, const std::string &ext,
                            const char* data, size_t size, const std::string &path) {
        try {
            fs::create_directories(path);
            std::string fileName = sanitizeFilename(title) + ext;
            std::ofstream file(fs::path(path) / fileName, std::ios::binary);
            if (!file.is_open()) return false;
            file.write(data, size);
            return true;
        } catch (...) { return false; }
    }
};

#endif //CEPTEMBER_BASEWORKER_H
