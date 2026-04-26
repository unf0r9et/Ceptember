//
// Created by unf0r9et on 09.02.2026.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <string>
#include <vector>
#include <requestEntity.hpp>

class parser {
public:
    static requestEntity parse(const std::string &);
};


#endif //SERVER_PARSER_H
