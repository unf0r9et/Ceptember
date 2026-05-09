#ifndef SERVER_HTTP_CONTROLLER_H
#define SERVER_HTTP_CONTROLLER_H

#include <string>
#include <vector>

#include "str_switch.h"
#include "raindrop.hpp"
#include "requestEntity.hpp"
#include "basicResponse.h"

class httpController {
public:

    static std::string startHttpController(const std::string &);

    std::string static handleMethods();

    static std::string methods_GET();

    static std::string methods_POST();

    static std::string methods_PUT();

    static std::string methods_DELETE();
};


#endif //SERVER_HTTP_CONTROLLER_H
