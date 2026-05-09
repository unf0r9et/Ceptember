#include "videoWorker.hpp"
#include "MultipartParser.hpp"

int videoWorker::saveShortVideo(const requestEntity &request, const std::string &directoryPath) {
    std::string boundary = getBoundary(request);
    auto parts = MultipartParser::parse(request.body, boundary);

    std::string title;
    const MultipartPart* filePart = nullptr;

    for (const auto& p : parts) {
        if (p.name == "videoTitle" || p.name == "title") title = std::string(p.data);
        if (p.isFile() || p.contentType.find("video/") != std::string::npos) filePart = &p;
    }

    if (!filePart) return -2;
    if (title.empty()) title = filePart->filename.empty() ? "video" : filePart->filename;

    std::string ext = ".mp4";
    size_t dot = filePart->filename.find_last_of(".");
    if (dot != std::string::npos) ext = filePart->filename.substr(dot);

    return finalizeSave(title, ext, filePart->data.data(), filePart->data.size(), directoryPath) ? 0 : -3;
}

int videoWorker::saveLongVideo(const requestEntity &request, const std::string &directoryPath) {
    std::string tempFilePath = request.body;
    if (!fs::exists(tempFilePath)) return -4;

    std::ifstream src(tempFilePath, std::ios::binary);
    if (!src.is_open()) return -4;

    const size_t previewSize = 10240;
    std::string headerPreview(previewSize, '\0');
    src.read(headerPreview.data(), previewSize);
    size_t bytesRead = src.gcount();
    headerPreview.resize(bytesRead);

    std::string boundary = getBoundary(request);

    headerPreview += "\r\n" + boundary + "--\r\n";

    auto parts = MultipartParser::parse(headerPreview, boundary);

    const MultipartPart* videoPart = nullptr;
    std::string title = "";

    for (const auto& p : parts) {
        if (p.name == "videoTitle" || p.name == "title") title = std::string(p.data);
        if (p.isFile() || p.contentType.find("video/") != std::string::npos) {
            videoPart = &p;
        }
    }

    if (!videoPart) return -2;
    size_t startOffsetInFile = videoPart->data.data() - headerPreview.data();

    src.seekg(0, std::ios::end);
    size_t fileSize = src.tellg();

    size_t footerSize = boundary.length() + 8;
    long long videoSize = (long long)fileSize - startOffsetInFile - footerSize;
    if (videoSize < 0) videoSize = fileSize - startOffsetInFile; 

    if (title.empty()) title = videoPart->filename.empty() ? "video" : videoPart->filename;
    std::string ext = ".mp4";
    if (size_t dot = videoPart->filename.find_last_of("."); dot != std::string::npos) {
        ext = videoPart->filename.substr(dot);
    }

    fs::create_directories(directoryPath);
    std::string finalName = sanitizeFilename(title) + ext;
    std::ofstream dest(fs::path(directoryPath) / finalName, std::ios::binary);
    if (!dest.is_open()) return -3;

    src.seekg(startOffsetInFile, std::ios::beg);

    std::vector<char> buffer(128 * 1024);
    size_t remaining = (size_t)videoSize;
    while (remaining > 0) {
        size_t toRead = std::min(remaining, buffer.size());
        src.read(buffer.data(), toRead);
        size_t readNow = src.gcount();
        if (readNow == 0) break;
        dest.write(buffer.data(), readNow);
        remaining -= readNow;
    }

    return 0;
}