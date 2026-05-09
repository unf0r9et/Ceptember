#ifndef CEPTEMBER_REQUESTBODIESWORKER_H
#define CEPTEMBER_REQUESTBODIESWORKER_H

#include <string>

class requestBodiesWorker {
public:
    std::string static getRandomString(size_t length = 20);
    void static writeBodyToDisk(const std::string& data, bool isFirstChunk);
};


#endif //CEPTEMBER_REQUESTBODIESWORKER_H
