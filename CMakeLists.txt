cmake_minimum_required(VERSION 4.2)
project(Ceptember)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ceptember
        # Entry point
        src/main/main.cpp

        # Core
        core/engine/engine.cpp

        # Logger
        core/logger/logger.cpp

        # Parser
        core/parser/parser.cpp
        core/parser/picoHttpParser/picoHttpParser.c
        core/parser/MultipartParser/MultipartParser.cpp

        # HTTP controller
        core/httpController/httpController.cpp

        # Static handler
        core/staticHandler/staticHandler.cpp

        # File worker
        core/utils/workers/fileWorker/fileReader.cpp
        core/utils/workers/fileWorker/fileSearch.cpp

        # Video worker
        core/utils/workers/videoWorker/videoWorker.cpp

        # Photo worker
        core/utils/workers/photoWorker/photoWorker.cpp

        # Txt worker
        core/utils/workers/txtWorker/txtWorker.cpp

        # Docs worker
        core/utils/workers/docsWorker/docsWorker.cpp

        # File saver
        core/utils/fileSaver/fileSaver.cpp

        # Request processing
        core/utils/workers/requestBodiesWorker/requestBodiesWorker.cpp

        # Response builder
        core/utils/responseBuilder/responseBuilder.cpp

        # Delete file
        core/utils/deleteFile/deleteFile.cpp

        # Handlers
        src/main/handlers/GET.cpp
        src/main/handlers/POST.cpp
        src/main/handlers/DELETE.cpp
        src/main/handlers/PUT.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/core)
include_directories(${CMAKE_SOURCE_DIR}/core/publicHeaders)
include_directories(${CMAKE_SOURCE_DIR}/core/internalHeaders)