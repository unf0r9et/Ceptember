cmake_minimum_required(VERSION 4.2)
project(Ceptember)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ceptember
        # Entry point
        src/main/main.cpp

        # Core
        autumn/engine/engine.cpp

        # Logger
        autumn/logger/logger.cpp

        # Parser
        autumn/parser/parser.cpp
        autumn/parser/picoHttpParser/picoHttpParser.c

        # HTTP controller
        autumn/httpController/httpController.cpp

        # Static handler
        autumn/staticHandler/staticHandler.cpp

        # File worker
        autumn/utils/fileWorker/fileReader.cpp
        autumn/utils/fileWorker/fileSearch.cpp

        # Request processing
        autumn/utils/requestBodiesWorker/requestBodiesWorker.cpp

        # Handlers
        src/main/handlers/GET.cpp
        src/main/handlers/POST.cpp
        src/main/handlers/DELETE.cpp
        src/main/handlers/PUT.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/autumn)
include_directories(${CMAKE_SOURCE_DIR}/autumn/publicHeaders)
include_directories(${CMAKE_SOURCE_DIR}/autumn/internalHeaders)