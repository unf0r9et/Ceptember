#include "httpController.hpp"

extern thread_local requestEntity rqEntity;

std::string httpController::methods_DELETE() {
    switch (str_hash_for_switch(rqEntity.path)) {
        case "/"_hash:
        default:
            return HTTP_RESPONSE_404;
    }
}
