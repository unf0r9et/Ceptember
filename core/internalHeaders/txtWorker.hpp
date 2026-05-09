#ifndef CEPTEMBER_TXTWORKER_H
#define CEPTEMBER_TXTWORKER_H
#include "baseWorker.hpp"


class txtWorker : public baseWorker {
public:
    static int saveShortTxt(const requestEntity &request, const std::string &directoryPath);

    static int saveLongTxt(const requestEntity &request, const std::string &directoryPath);
};


#endif //CEPTEMBER_TXTWORKER_H
