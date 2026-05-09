#ifndef CEPTEMBER_BASICRESPONSE_H
#define CEPTEMBER_BASICRESPONSE_H

/**
 * @brief HTTP 100 Continue
 * Сервер удовлетворен начальной частью запроса и клиент может продолжать.
 */
#define HTTP_RESPONSE_100 \
"HTTP/1.1 100 Continue\r\n\r\n"

/**
 * @brief HTTP 101 Switching Protocols
 * Сервер согласен переключить протоколы (например, на WebSocket).
 */
#define HTTP_RESPONSE_101 \
"HTTP/1.1 101 Switching Protocols\r\n" \
"Upgrade: websocket\r\n" \
"Connection: Upgrade\r\n\r\n"

/**
 * @brief HTTP 200 OK
 */
#define HTTP_RESPONSE_200 \
"HTTP/1.1 200 OK\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 6\r\n" \
"\r\n" \
"200 OK"

/**
 * @brief HTTP 201 Created
 */
#define HTTP_RESPONSE_201 \
"HTTP/1.1 201 Created\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 11\r\n" \
"\r\n" \
"201 Created"

/**
 * @brief HTTP 202 Accepted
 * Запрос принят на обработку, но она ещё не завершена.
 */
#define HTTP_RESPONSE_202 \
"HTTP/1.1 202 Accepted\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 12\r\n" \
"\r\n" \
"202 Accepted"

/**
 * @brief HTTP 204 No Content
 * Запрос выполнен успешно, тело ответа отсутствует.
 */
#define HTTP_RESPONSE_204 \
"HTTP/1.1 204 No Content\r\n\r\n"

/**
 * @brief HTTP 301 Moved Permanently
 * Ресурс навсегда переехал.
 */
#define HTTP_RESPONSE_301 \
"HTTP/1.1 301 Moved Permanently\r\n" \
"Location: /\r\n" \
"Content-Length: 0\r\n" \
"\r\n"

/**
 * @brief HTTP 302 Found
 * Ресурс временно перемещен.
 */
#define HTTP_RESPONSE_302 \
"HTTP/1.1 302 Found\r\n" \
"Location: /\r\n" \
"Content-Length: 0\r\n" \
"\r\n"

/**
 * @brief HTTP 304 Not Modified
 * Ресурс не изменялся (используется для кеширования). Тело запрещено.
 */
#define HTTP_RESPONSE_304 \
"HTTP/1.1 304 Not Modified\r\n\r\n"

/**
 * @brief HTTP 400 Bad Request
 */
#define HTTP_RESPONSE_400 \
"HTTP/1.1 400 Bad Request\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 15\r\n" \
"\r\n" \
"400 Bad Request"

/**
 * @brief HTTP 401 Unauthorized
 */
#define HTTP_RESPONSE_401 \
"HTTP/1.1 401 Unauthorized\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 16\r\n" \
"\r\n" \
"401 Unauthorized"

/**
 * @brief HTTP 403 Forbidden
 */
#define HTTP_RESPONSE_403 \
"HTTP/1.1 403 Forbidden\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 13\r\n" \
"\r\n" \
"403 Forbidden"

/**
 * @brief HTTP 404 Not Found
 */
#define HTTP_RESPONSE_404 \
"HTTP/1.1 404 Not Found\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 13\r\n" \
"\r\n" \
"404 Not Found"

/**
 * @brief HTTP 405 Method Not Allowed
 */
#define HTTP_RESPONSE_405 \
"HTTP/1.1 405 Method Not Allowed\r\n" \
"Allow: GET, POST, OPTIONS\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 22\r\n" \
"\r\n" \
"405 Method Not Allowed"

/**
 * @brief HTTP 408 Request Timeout
 */
#define HTTP_RESPONSE_408 \
"HTTP/1.1 408 Request Timeout\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 19\r\n" \
"\r\n" \
"408 Request Timeout"

/**
 * @brief HTTP 409 Conflict
 * Конфликт с текущим состоянием ресурса.
 */
#define HTTP_RESPONSE_409 \
"HTTP/1.1 409 Conflict\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 12\r\n" \
"\r\n" \
"409 Conflict"

/**
 * @brief HTTP 410 Gone
 * Ресурс удалён навсегда.
 */
#define HTTP_RESPONSE_410 \
"HTTP/1.1 410 Gone\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 8\r\n" \
"\r\n" \
"410 Gone"

/**
 * @brief HTTP 413 Payload Too Large
 */
#define HTTP_RESPONSE_413 \
"HTTP/1.1 413 Payload Too Large\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 21\r\n" \
"\r\n" \
"413 Payload Too Large"

/**
 * @brief HTTP 415 Unsupported Media Type
 */
#define HTTP_RESPONSE_415 \
"HTTP/1.1 415 Unsupported Media Type\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 26\r\n" \
"\r\n" \
"415 Unsupported Media Type"

/**
 * @brief HTTP 429 Too Many Requests
 * Ограничение по количеству запросов (Rate Limiting).
 */
#define HTTP_RESPONSE_429 \
"HTTP/1.1 429 Too Many Requests\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 21\r\n" \
"\r\n" \
"429 Too Many Requests"

/**
 * @brief HTTP 500 Internal Server Error
 */
#define HTTP_RESPONSE_500 \
"HTTP/1.1 500 Internal Server Error\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 25\r\n" \
"\r\n" \
"500 Internal Server Error"

/**
 * @brief HTTP 501 Not Implemented
 */
#define HTTP_RESPONSE_501 \
"HTTP/1.1 501 Not Implemented\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 19\r\n" \
"\r\n" \
"501 Not Implemented"

/**
 * @brief HTTP 502 Bad Gateway
 * Сервер получил недопустимый ответ от вышестоящего сервера.
 */
#define HTTP_RESPONSE_502 \
"HTTP/1.1 502 Bad Gateway\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 15\r\n" \
"\r\n" \
"502 Bad Gateway"

/**
 * @brief HTTP 503 Service Unavailable
 */
#define HTTP_RESPONSE_503 \
"HTTP/1.1 503 Service Unavailable\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 23\r\n" \
"\r\n" \
"503 Service Unavailable"

/**
 * @brief HTTP 504 Gateway Timeout
 */
#define HTTP_RESPONSE_504 \
"HTTP/1.1 504 Gateway Timeout\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 19\r\n" \
"\r\n" \
"504 Gateway Timeout"

/**
 * @brief HTTP 418 I'm a teapot
 */
#define HTTP_RESPONSE_418 \
"HTTP/1.1 418 I'm a teapot\r\n" \
"Content-Type: text/plain\r\n" \
"Content-Length: 14\r\n" \
"\r\n" \
"418 I'm a teapot"

#endif //CEPTEMBER_BASICRESPONSE_H
