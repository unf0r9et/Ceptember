#include <vector>
#include "parser.hpp"
#include "handleRequest.hpp"

std::vector<std::string> parser::parse(const std::string &request) {
    return handle_request(request.c_str(), request.length());
}
