#include "fileSaver.hpp"
#include "videoWorker.hpp"
#include "deleteFile.hpp"
#include "docsWorker.hpp"
#include "photoWorker.hpp"
#include "txtWorker.hpp"

int fileSaver::processSave(const requestEntity &request,
                           const std::string &directoryPath,
                           int (*saveLong)(const requestEntity &, const std::string &),
                           int (*saveShort)(const requestEntity &, const std::string &)) {
    if (request.body.find(TEMP_FILE_PREFIX) != std::string::npos) {
        const int result = saveLong(request, directoryPath);
        deleteFile::delFile(request.body);
        return result;
    }
    return saveShort(request, directoryPath);
}


int fileSaver::saveVideo(const requestEntity &request, const std::string &directoryPath) {
    return processSave(request, directoryPath, videoWorker::saveLongVideo, videoWorker::saveShortVideo);
}

int fileSaver::saveDocs(const requestEntity &request, const std::string &directoryPath) {
    return processSave(request, directoryPath, docsWorker::saveLongDocs, docsWorker::saveShortDocs);
}

int fileSaver::savePhoto(const requestEntity &request, const std::string &directoryPath) {
    return processSave(request, directoryPath, photoWorker::saveLongPhoto, photoWorker::saveShortPhoto);
}

int fileSaver::saveTxt(const requestEntity &request, const std::string &directoryPath) {
    return processSave(request, directoryPath, txtWorker::saveLongTxt, txtWorker::saveShortTxt);
}
