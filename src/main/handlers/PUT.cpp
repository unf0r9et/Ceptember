#include "httpController.hpp"

extern thread_local std::vector<std::string> vector_request;

std::string httpController::methods_PUT() {
    switch (str_hash_for_switch(vector_request[1])) {
        case "/"_hash:
        default:
            return ERROR_ENDPOINT;
    }
}
