#ifndef CEPTEMBER_VIDEOWORKER_H
#define CEPTEMBER_VIDEOWORKER_H

#include "baseWorker.hpp"

class videoWorker : public baseWorker {
public:
    static int saveShortVideo(const requestEntity &request, const std::string &directoryPath);

    static int saveLongVideo(const requestEntity &request, const std::string &directoryPath);
};

#endif //CEPTEMBER_VIDEOWORKER_H
