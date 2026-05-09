#include "photoWorker.hpp"
#include "MultipartParser.hpp"

int photoWorker::saveShortPhoto(const requestEntity &request, const std::string &directoryPath) {
    std::string boundary = getBoundary(request);
    auto parts = MultipartParser::parse(request.body, boundary);

    std::string title;
    const MultipartPart* filePart = nullptr;

    for (const auto& p : parts) {
        if (p.name == "photoTitle" || p.name == "title") title = std::string(p.data);
        if (p.isFile() || p.contentType.find("image/") != std::string::npos) filePart = &p;
    }

    if (!filePart) return -2;
    if (title.empty()) title = filePart->filename.empty() ? "photo" : filePart->filename;

    std::string ext = ".jpg";
    size_t dot = filePart->filename.find_last_of(".");
    if (dot != std::string::npos) ext = filePart->filename.substr(dot);

    return finalizeSave(title, ext, filePart->data.data(), filePart->data.size(), directoryPath) ? 0 : -3;
}

int photoWorker::saveLongPhoto(const requestEntity &request, const std::string &directoryPath) {
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
    const MultipartPart* photoPart = nullptr;
    std::string title = "";

    for (const auto& p : parts) {
        if (p.name == "photoTitle" || p.name == "title") title = std::string(p.data);
        if (p.isFile() || p.contentType.find("image/") != std::string::npos) photoPart = &p;
    }

    if (!photoPart) return -2;

    size_t startOffsetInFile = photoPart->data.data() - headerPreview.data();
    src.seekg(0, std::ios::end);
    size_t fileSize = src.tellg();

    size_t footerSize = boundary.length() + 8;
    long long photoSize = (long long)fileSize - startOffsetInFile - footerSize;
    if (photoSize < 0) photoSize = fileSize - startOffsetInFile;

    if (title.empty()) title = photoPart->filename.empty() ? "photo" : photoPart->filename;

    std::string ext = ".jpg";
    if (size_t dot = photoPart->filename.find_last_of("."); dot != std::string::npos) {
        ext = photoPart->filename.substr(dot);
    }

    fs::create_directories(directoryPath);
    std::string finalName = sanitizeFilename(title);
    if (title.find('.') == std::string::npos) finalName += ext;

    std::ofstream dest(fs::path(directoryPath) / finalName, std::ios::binary);
    if (!dest.is_open()) return -3;

    src.seekg(startOffsetInFile, std::ios::beg);
    std::vector<char> buffer(128 * 1024);
    size_t remaining = (size_t)photoSize;
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