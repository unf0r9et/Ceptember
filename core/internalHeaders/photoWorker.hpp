#ifndef CEPTEMBER_PHOTOWORKER_H
#define CEPTEMBER_PHOTOWORKER_H

#include <baseWorker.hpp>

class photoWorker : public baseWorker {
public:
    static int saveShortPhoto(const requestEntity &request, const std::string &directoryPath);

    static int saveLongPhoto(const requestEntity &request, const std::string &directoryPath);
};


#endif //CEPTEMBER_PHOTOWORKER_H
