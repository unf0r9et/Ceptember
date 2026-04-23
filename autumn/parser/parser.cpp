#include <vector>
#include "parser.hpp"
#include <string>
#include "picoHttpParser.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

std::vector<std::string> parser::parse(const std::string &request) {

    const char* buffer = request.c_str();
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

        result.emplace_back(method, method_len);
        result.emplace_back(path, path_len);

        int content_length = 0;
        for (size_t i = 0; i < num_headers; ++i) {
            std::string name(headers[i].name, headers[i].name_len);
            result.emplace_back(headers[i].name, headers[i].name_len);
            if (name == "Content-Length" || name == "content-length") {
                std::string val(headers[i].value, headers[i].value_len);
                content_length = std::stoi(val);
                result.emplace_back(headers[i].value, headers[i].value_len);
            }
        }


        if (content_length > 0) {

            const char* body_start = buffer + bytes_consumed;

            if (buf_len >= bytes_consumed + content_length) {
                std::string body_str(body_start, content_length);
                std::cout << "Body Raw: " << body_str << "\n";

                try {
                    auto j = json::parse(body_str);
                    std::cout << "Parsed JSON key 'foo': " << j["foo"] << "\n";
                } catch(...) {
                    std::cout << "Not a JSON body\n";
                }
            }
        }
    } else if (bytes_consumed == -1) {
        std::cerr << "Parse error\n";
    } else {
        std::cout << "Request incomplete, read more from socket...\n";
    }

    return result;
}
