#include "fileSaver.hpp"
#include "videoWorker.hpp"
#include "deleteFile.hpp"
#include "docsWorker.hpp"

int fileSaver::saveVideo(const requestEntity &request, const std::string &directoryPath) {
  if (request.body.find(TEMP_FILE_PREFIX) != std::string::npos) {
        const int result = videoWorker::saveLongVideo(request, directoryPath);
        deleteFile::delFile(request.body);
        return result;
  }
  return videoWorker::saveShortVideo(request, directoryPath);
}

int fileSaver::saveDocs(const requestEntity &request, const std::string &directoryPath) {
  if (request.body.find(TEMP_FILE_PREFIX) != std::string::npos) {
        const int result = docsWorker::saveLongDocs(request, directoryPath);
        deleteFile::delFile(request.body);
        return result;
  }
  return docsWorker::saveShortDocs(request, directoryPath);
}
