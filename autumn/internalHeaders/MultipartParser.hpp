#ifndef CEPTEMBER_MULTIPARTPARSER_H
#define CEPTEMBER_MULTIPARTPARSER_H


#include <vector>
#include <string>
#include <string>
#include <map>
#include <string_view>

struct MultipartPart {
    std::string name;
    std::string filename;
    std::string contentType;
    std::string_view data;

    bool isFile() const { return !filename.empty(); }
};

class MultipartParser {
public:
    static std::vector<MultipartPart> parse(const std::string& body, const std::string& boundary);

private:
    static void parseHeaders(std::string_view headerChunk, MultipartPart& part);
};

#endif //CEPTEMBER_MULTIPARTPARSER_H
