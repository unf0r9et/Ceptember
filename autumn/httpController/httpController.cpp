#include "httpController.hpp"
#include "logger.hpp"
#include <parser.hpp>
#include <mutex>
#include "staticHandler.hpp"
#include "requestBodiesWorker.hpp"

#define debug

extern logger LOGGER;

thread_local int content_size;

thread_local mode MD = RequestHTTP;

thread_local requestEntity rqEntity;

std::string httpController::handleMethods() {
    switch (str_hash_for_switch(rqEntity.method)) {
        case "GET"_hash:    return methods_GET();
        case "POST"_hash:   return methods_POST();
        case "PUT"_hash:    return methods_PUT();
        case "DELETE"_hash: return methods_DELETE();
        default:            return HTTP_RESPONSE_405;
    }
}


std::string httpController::startHttpController(const std::string &request) {
    switch (MD) {
        case RequestHTTP:

            rqEntity = parser::parse(request);

            if (MD == LoadingHTTP) {
                return LOADING_PROCESS;
            }

            if (std::string response = isStaticFile(rqEntity.path); !response.empty()) {
                return response;
            }

#ifdef debug
            LOGGER.log_server("Method: " + rqEntity.method + " Endpoint: " + rqEntity.path, SERVER_PORT,
                                 logger::DEBUG);
#endif
            return handleMethods();
        case LoadingHTTP:
            requestBodiesWorker::writeBodyToDisk(request, false);
            content_size -= static_cast<int>(request.length());
            if (content_size <= 0) {
                MD = RequestHTTP;
                return handleMethods();
            }
            return LOADING_PROCESS;

    }
    return HTTP_RESPONSE_500;
}