#ifndef CEPTEMBER_FILESAVER_H
#define CEPTEMBER_FILESAVER_H

#include "requestEntity.hpp"
#include "raindrop.hpp"

class fileSaver {
    static int processSave(
        const requestEntity &request,
        const std::string &directoryPath,
        int (*saveLong)(const requestEntity &, const std::string &),
        int (*saveShort)(const requestEntity &, const std::string &)
    );

public:
    static int saveVideo(const requestEntity &request, const std::string &directoryPath);

    static int saveDocs(const requestEntity &request, const std::string &directoryPath);

    static int savePhoto(const requestEntity &request, const std::string &directoryPath);

    static int saveTxt(const requestEntity &request, const std::string &directoryPath);
};


#endif //CEPTEMBER_FILESAVER_H
