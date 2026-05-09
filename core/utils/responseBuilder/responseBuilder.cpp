#include <ctime>
#include <iomanip>
#include <sstream>
#include "responseBuilder.hpp"
#include "raindrop.hpp"

extern thread_local mode MDtoSend;
extern thread_local std::string httpBodyToSendPath;

responseBuilder &responseBuilder::setStatusCode(const int statusCode) {
    this->response += "HTTP/1.1 " + std::to_string(statusCode) + " \r\n";
    return *this;
}

responseBuilder &responseBuilder::addHeader(const std::string &name, const std::string &value) {
    this->response += name + ": " + value + "\r\n";
    return *this;
}

responseBuilder &responseBuilder::setContentLengthHeader(const size_t contentLength) {
    this->response += "Content-Length: " + std::to_string(contentLength) + "\r\n";
    return *this;
}

responseBuilder &responseBuilder::setContentTypeHeader(const std::string &mimeType) {
    addHeader("Content-Type", mimeType);
    return *this;
}

responseBuilder &responseBuilder::setConnectionHeader(const bool keepAlive) {
    addHeader("Connection", keepAlive ? "keep-alive" : "close");
    return *this;
}

responseBuilder &responseBuilder::setLocationHeader(const std::string &url) {
    addHeader("Location", url);
    return *this;
}

responseBuilder &responseBuilder::setAllowOriginHeader(const std::string &origin = "*") {
    addHeader("Access-Control-Allow-Origin", origin);
    return *this;
}

responseBuilder & responseBuilder::setDateHeader() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::gmtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%a, %d %b %Y %H:%M:%S GMT");
    addHeader("Date", ss.str());
    return *this;
}

responseBuilder &responseBuilder::setContent(const std::string &content) {
    hasContent = true;
    this->response += "\r\n" + content;
    return *this;
}

void responseBuilder::addBinaryContent(const std::string &path) {
    MDtoSend = LoadingHTTP;
    httpBodyToSendPath = path;
}

std::string responseBuilder::buildResponse() {
    if (!hasContent) this->response += "\r\n";
    return this->response;
}
