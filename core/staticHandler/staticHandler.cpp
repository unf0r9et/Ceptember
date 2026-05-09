#include <string>
#include "str_switch.h"
#include "fileReader.hpp"
#include "raindrop.hpp"
#include "fileSearch.hpp"
#include <filesystem>
#include <fstream>
#include <iterator>

extern std::unordered_set<std::string> staticDirectories;

std::string FAVICON() {
    std::ifstream file("../src/static/favicon.ico", std::ios::binary);

    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: image/x-icon\r\n";
        response += "Content-Length: " + std::to_string(content.size()) + "\r\n";
        response += "\r\n";

        response += content;
        return response;
    }
    return "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
}


std::string CSS(const std::string &path) {
    const std::string file_content = fileReader::send(path, "CSS", SERVER_PORT);

    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/css\r\n"
           "Content-Length: " + std::to_string(file_content.length()) + "\r\n"
           "\r\n"
           + file_content;
}

std::string HTML(const std::string &path) {
    const std::string file_content = fileReader::send(path, "HTML", SERVER_PORT);

    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/html\r\n"
           "Content-Length: " + std::to_string(file_content.length()) + "\r\n"
           "\r\n"
           + file_content;
}

std::string JS(const std::string &path) {
    const std::string file_content = fileReader::send(path, "JS", SERVER_PORT);

    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/js\r\n"
           "Content-Length: " + std::to_string(file_content.length()) + "\r\n"
           "\r\n"
           + file_content;
}

std::string makeResponse(const std::string &path, const std::string &contentType) {
    switch (str_hash_for_switch(contentType)) {
        case "js"_hash: {
            auto filePath = findFileRelative(StaticRootPath, path);
            if (!filePath) {
                return "HTTP/1.1 404 Not Found\r\n\r\n";
            }
            return JS((fs::path(StaticRootPath) / *filePath).string());
        }
        case "css"_hash: {
            auto filePath = findFileRelative(StaticRootPath, path);
            if (!filePath) {
                return "HTTP/1.1 404 Not Found\r\n\r\n";
            }
            return CSS((fs::path(StaticRootPath) / *filePath).string());
        }
        default:
            const std::string middle = path.length() > 1 ? path + "/" : path;
            return HTML(StaticRootPath + middle + "index.html");
    }
}

std::string isStaticFile(const std::string &path) {
    if (staticDirectories.contains(path) || path == "/") {
        return makeResponse(path, "html");
    }
    if (path.find(".js") != std::string::npos) {
        return makeResponse(path, "js");
    }
    if (path.find(".css") != std::string::npos) {
        return makeResponse(path, "css");
    }
    if (path == "/favicon.ico") {
        return FAVICON();
    }
    return "";
}
