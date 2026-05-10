#include "parser.hpp"
#include "picoHttpParser.h"
#include <iostream>
#include <raindrop.hpp>
#include "requestBodiesWorker.hpp"
#include "logger.hpp"

thread_local std::string CURRENT_TEMP_FILE_PATH;
extern thread_local mode MDtoReceive;
extern thread_local int content_size;
extern logger LOGGER;

requestEntity parser::parse(const std::string &request) {

    requestEntity rqEntity;

    const char *buffer = request.c_str();
    size_t buf_len = request.length();

    std::vector<std::string> result;

    const char *method, *path;
    size_t method_len, path_len;
    int minor_version;

    phr_header headers[100];
    size_t num_headers = sizeof(headers) / sizeof(headers[0]);

    int bytes_consumed = phr_parse_request(
        buffer, buf_len,
        &method, &method_len,
        &path, &path_len,
        &minor_version,
        headers, &num_headers,
        0
    );

    if (bytes_consumed > 0) {
        rqEntity.method = std::string(method, method_len);
        rqEntity.path = std::string(path, path_len);

        int content_length = 0;

        for (size_t i = 0; i < num_headers; ++i) {
            std::string name(headers[i].name, headers[i].name_len);
            std::string value(headers[i].value, headers[i].value_len);
            rqEntity.headers.emplace_back(name, value);

            if (name == "Content-Length" || name == "content-length") {
                std::string val(headers[i].value, headers[i].value_len);
                content_length = std::stoi(val);
            }
        }

#ifdef debug
        LOGGER.log_server("[PARSER] Bytes consumed length: " + std::to_string(bytes_consumed), SERVER_PORT,
                          logger::DEBUG);
        LOGGER.log_server("[PARSER] Content length: " + std::to_string(content_length), SERVER_PORT,
                          logger::DEBUG);
#endif

        if (content_length > 0) {
            const char *body_start = buffer + bytes_consumed;
            size_t body_len = buf_len - bytes_consumed;

            if (content_length <= MaximumRequestSize - bytes_consumed) {
                std::string body_str(body_start, body_len);
                rqEntity.body = body_str;
                if (request.length() < content_length + bytes_consumed) {
                    content_size = content_length - body_len;
                    MDtoReceive = LoadingShortHTTP;
                }
            } else {
                requestBodiesWorker::writeBodyToDisk(std::string(body_start, body_len), true);
                rqEntity.body = CURRENT_TEMP_FILE_PATH;
                content_size = content_length - body_len;
                MDtoReceive = LoadingHTTP;
            }
        }

#ifdef debug
        LOGGER.log_server("[PARSER] Request body length: " + std::to_string(rqEntity.body.length()), SERVER_PORT,
                          logger::DEBUG);
#endif

    } else if (bytes_consumed == -1) {
        LOGGER.log_server("[PARSER] Parse error ", SERVER_PORT,
                        logger::ERROR);
        rqEntity.method = "ERROR";
    } else {
        LOGGER.log_server("[PARSER] Request incomplete, read more from socket ", SERVER_PORT,
                logger::ERROR);
        rqEntity.method = "ERROR";
    }

    return rqEntity;
}
