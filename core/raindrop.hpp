#ifndef CEPTEMBER_CEPTEMBER_H
#define CEPTEMBER_CEPTEMBER_H

#define Raindrop

#define GET(endpoint)
#define PUT(endpoint)
#define DELETE(endpoint)
#define SET(endpoint)

#define SERVER_PORT 8080
#define MaximumRequestSize 131072
#define StaticRootPath "../src/static"
#define LoggerPath "../core/files/logs/frameworkLogs.txt"
#define TEMP_FILE_PREFIX "../core/files/requestBodies/unf0r9etpref_"
#define LOADING_PROCESS "LOADING_PROCESS"
#define TIMEOUT 30

enum mode { RequestHTTP, LoadingHTTP, LoadingShortHTTP };

#endif //CEPTEMBER_CEPTEMBER_H
