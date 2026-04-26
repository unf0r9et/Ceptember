#include "parser.hpp"
#include "picoHttpParser.h"
#include <iostream>
#include <raindrop.hpp>
#include "requestBodiesWorker.hpp"

thread_local std::string CURRENT_TEMP_FILE_PATH;
extern thread_local mode MD;
extern thread_local int content_size;

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


        if (content_length > 0) {
            const char *body_start = buffer + bytes_consumed;

            if (content_length <= MaximumRequestSize - bytes_consumed) {
                std::string body_str(body_start, content_length);
                rqEntity.body = body_str;
            } else {
                size_t body_len = buf_len - bytes_consumed;
                requestBodiesWorker::writeBodyToDisk(std::string(body_start, body_len), true);
                rqEntity.body = CURRENT_TEMP_FILE_PATH;
                content_size = content_length - body_len;
                MD = LoadingHTTP;
            }

        }
    } else if (bytes_consumed == -1) {
        std::cerr << "Parse error\n";
    } else {
        std::cout << "Request incomplete, read more from socket...\n";
    }

    return rqEntity;
}
