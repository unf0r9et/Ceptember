#ifndef SERVER_FILE_READER_H

#define SERVER_FILE_READER_H

#include <string>

class fileReader {
public:
    static std::string send(const std::string &u_file_path, const std::string& type, int u_port);
};


#endif //SERVER_FILE_READER_H
