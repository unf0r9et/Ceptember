#include "fileReader.hpp"
#include <logger.hpp>

extern logger LOGGER;

std::string fileReader::send(const std::string &u_file_path, const std::string& type, const int u_port) {
    FILE *file = fopen(u_file_path.c_str(), "r");
    if (file == nullptr) {
        LOGGER.log_server(("Error while trying to open " + type + " file"), u_port, logger::ERROR);
    }

    std::string file_content;
    char buffer[4096] = {0};

    while (fgets(buffer, 4096, file)) {
        file_content += std::string(buffer);
    }
    return file_content;
}
