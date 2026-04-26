#ifndef CEPTEMBER_REQUEST_H
#define CEPTEMBER_REQUEST_H

#include "picoHttpParser.h"
#include <vector>
#include <string>
#include <utility>

class requestEntity {
public:
    std::string method;
    std::string path;
    std::vector<std::pair<std::string, std::string>> headers;
    std::string body;
};


#endif //CEPTEMBER_REQUEST_H
