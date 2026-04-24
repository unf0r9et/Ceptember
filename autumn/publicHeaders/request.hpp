#ifndef CEPTEMBER_REQUEST_H
#define CEPTEMBER_REQUEST_H

#include "picoHttpParser.h"
#include <vector>
#include <string>

class request {
public:
    std::string method;
    std::string path;
    std::vector<phr_header> headers;
    std::string body;
};


#endif //CEPTEMBER_REQUEST_H
