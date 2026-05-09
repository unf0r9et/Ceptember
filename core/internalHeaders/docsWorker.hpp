#ifndef CEPTEMBER_DOCSWORKER_H
#define CEPTEMBER_DOCSWORKER_H

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "requestEntity.hpp"
#include "baseWorker.hpp"

namespace fs = std::filesystem;

class docsWorker : public baseWorker{
public:
    static int saveShortDocs(const requestEntity &request, const std::string &directoryPath);

    static int saveLongDocs(const requestEntity &request, const std::string &directoryPath);

};
#endif //CEPTEMBER_DOCSWORKER_H
