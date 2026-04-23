cmake_minimum_required(VERSION 4.2)
project(Ceptember)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ceptember src/main/main.cpp
        autumn/raindrop.hpp
        autumn/engine/engine.cpp
        autumn/logger/logger.cpp
        autumn/parser/parser.cpp
        autumn/parser/handleRequest.cpp
        autumn/parser/picohttpparser/picoHttpParser.c
        autumn/internalHeaders/fileReader.hpp
        autumn/fileReader/fileReader.cpp
        autumn/publicHeaders/httpController.hpp
        autumn/httpController/httpController.cpp
        src/main/handlers/GET.cpp
        src/main/handlers/POST.cpp
        src/main/handlers/DELETE.cpp
        src/main/handlers/PUT.cpp)

target_precompile_headers(Ceptember PRIVATE "autumn/raindrop.hpp")

include_directories(${CMAKE_SOURCE_DIR}/autumn)
include_directories(${CMAKE_SOURCE_DIR}/autumn/publicHeaders)
include_directories(${CMAKE_SOURCE_DIR}/autumn/internalHeaders)