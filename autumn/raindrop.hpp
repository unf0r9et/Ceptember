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
#define LoggerPath "../autumn/files/logs/frameworkLogs.txt"
#define TEMP_FILE_PREFIX "../autumn/files/requestBodies/unf0r9etpref_"
#define LOADING_PROCESS "LOADING_PROCESS"

enum mode { RequestHTTP, LoadingHTTP };


/**
 * @brief HTTP 404 Not Found
 *
 * Используется, когда запрашиваемый endpoint не существует.
 * Сервер не нашёл ресурс по указанному URL.
 */
#define HTTP_RESPONSE_404 \
"HTTP/1.1 404 Not Found\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 13\r\n" \
"\r\n" \
"404 Not Found"


/**
 * @brief HTTP 405 Method Not Allowed
 *
 * Используется, когда endpoint существует, но HTTP-метод не поддерживается.
 * Обязательно указывается заголовок Allow со списком допустимых методов.
 */
#define HTTP_RESPONSE_405 \
"HTTP/1.1 405 Method Not Allowed\r\n" \
"Content-Type: text/plain\r\n" \
"Allow: GET, POST\r\n" \
"\r\n" \
"405 Method Not Allowed"


/**
 * @brief HTTP 500 Internal Server Error
 *
 * Используется при внутренней ошибке сервера.
 * Например: исключение, сбой логики, ошибка БД или неожиданное состояние.
 */
#define HTTP_RESPONSE_500 \
"HTTP/1.1 500 Internal Server Error\r\n" \
"Content-Type: text/plain\r\n" \
"\r\n" \
"500 Internal Server Error"


#endif //CEPTEMBER_CEPTEMBER_H
