#include "httpController.hpp"
#include "logger.hpp"
#include <parser.hpp>
#include <mutex>

#define debug

extern logger LOGGER;

thread_local size_t content_size;

thread_local static bool IS_FIRST_CHUNK = true;

thread_local static std::string REQUEST;

thread_local httpController::mode MD = httpController::Request;
thread_local std::vector<std::string> vector_request;


std::string httpController::startHttpController(const std::string &request) {
    REQUEST = request;
    switch (MD) {
        case Request:
            vector_request = parser::parse(request);

#ifdef debug
            LOGGER.log_server("Method: " + vector_request[0] + " Endpoint: " + vector_request[1], SERVER_PORT,
                                 logger::DEBUG);
#endif

            switch (str_hash_for_switch(vector_request[0])) {
                case "GET"_hash:
                    return methods_GET();
                case "POST"_hash:
                    return methods_POST();
                case "PUT"_hash:
                    return methods_PUT();
                case "DELETE"_hash:
                    return methods_DELETE();
                default:
                    return ERROR_METHOD;
            }
        // case Loading:
        //     std::string answer = endpoints::upload_video_endpoint(REQUEST, IS_FIRST_CHUNK);
        //     if (answer != "LOADING_PROCESS") MD = Request;
        //     return answer;
    }
    return ERROR_MODE;
}