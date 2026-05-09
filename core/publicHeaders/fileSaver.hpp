#ifndef CEPTEMBER_FILESAVER_H
#define CEPTEMBER_FILESAVER_H

#include "requestEntity.hpp"
#include "raindrop.hpp"

class fileSaver {
public:
    static int saveVideo(const requestEntity &request, const std::string &directoryPath);

    static int saveDocs(const requestEntity &request, const std::string &directoryPath);
};


#endif //CEPTEMBER_FILESAVER_H
