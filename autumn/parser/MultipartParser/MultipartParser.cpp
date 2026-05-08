#include "MultipartParser.hpp"
#include <algorithm>

std::vector<MultipartPart> MultipartParser::parse(const std::string& body, const std::string& boundary) {
    std::vector<MultipartPart> parts;
    if (boundary.empty()) return parts;

    std::string_view data(body);
    std::string fullBoundary = boundary;

    size_t pos = data.find(fullBoundary);
    while (pos != std::string_view::npos) {
        pos += fullBoundary.length();
        if (pos + 2 >= data.size() || data.substr(pos, 2) == "--") break;
        pos += 2;

        size_t nextBoundary = data.find(fullBoundary, pos);
        if (nextBoundary == std::string_view::npos) break;

        std::string_view partView = data.substr(pos, nextBoundary - pos);

        size_t headerEnd = partView.find("\r\n\r\n");
        if (headerEnd != std::string_view::npos) {
            MultipartPart part;
            parseHeaders(partView.substr(0, headerEnd), part);

            std::string_view content = partView.substr(headerEnd + 4);
            if (content.ends_with("\r\n")) content.remove_suffix(2);

            part.data = content;
            parts.push_back(part);
        }

        pos = nextBoundary;
    }
    return parts;
}

void MultipartParser::parseHeaders(std::string_view headerChunk, MultipartPart& part) {
    if (size_t pos = headerChunk.find("name=\""); pos != std::string_view::npos) {
        size_t start = pos + 6;
        size_t end = headerChunk.find("\"", start);
        part.name = std::string(headerChunk.substr(start, end - start));
    }

    if (size_t pos = headerChunk.find("filename=\""); pos != std::string_view::npos) {
        size_t start = pos + 10;
        size_t end = headerChunk.find("\"", start);
        part.filename = std::string(headerChunk.substr(start, end - start));
    }

    if (size_t pos = headerChunk.find("Content-Type: "); pos != std::string_view::npos) {
        size_t start = pos + 14;
        size_t end = headerChunk.find("\r\n", start);
        part.contentType = std::string(headerChunk.substr(start, end - start));
    }
}