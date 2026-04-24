cmake_minimum_required(VERSION 4.2)
project(Ceptember)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ceptember src/main/main.cpp
        autumn/raindrop.hpp
        autumn/engine/engine.cpp
        autumn/logger/logger.cpp
        autumn/parser/parser.cpp
        autumn/parser/picoHttpParser/picoHttpParser.c
        autumn/internalHeaders/fileReader.hpp
        autumn/fileWorker/fileReader.cpp
        autumn/publicHeaders/httpController.hpp
        autumn/httpController/httpController.cpp
        src/main/handlers/GET.cpp
        src/main/handlers/POST.cpp
        src/main/handlers/DELETE.cpp
        src/main/handlers/PUT.cpp
        autumn/staticHandler/staticHandler.cpp
        autumn/internalHeaders/staticHandler.hpp
        autumn/fileWorker/fileSearch.cpp
        autumn/internalHeaders/fileSearch.hpp
        autumn/publicHeaders/request.hpp)

include_directories(${CMAKE_SOURCE_DIR}/autumn)
include_directories(${CMAKE_SOURCE_DIR}/autumn/publicHeaders)
include_directories(${CMAKE_SOURCE_DIR}/autumn/internalHeaders)