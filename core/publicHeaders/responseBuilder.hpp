#ifndef CEPTEMBER_RESPONSEBUILDER_H
#define CEPTEMBER_RESPONSEBUILDER_H

#include <string>

/* 1xx Informational */
#define HTTP_CONTINUE                        100
#define HTTP_SWITCHING_PROTOCOLS             101
#define HTTP_PROCESSING                      102
#define HTTP_EARLY_HINTS                     103

/* 2xx Success */
#define HTTP_OK                              200
#define HTTP_CREATED                         201
#define HTTP_ACCEPTED                        202
#define HTTP_NON_AUTHORITATIVE_INFORMATION   203
#define HTTP_NO_CONTENT                      204
#define HTTP_RESET_CONTENT                   205
#define HTTP_PARTIAL_CONTENT                 206
#define HTTP_MULTI_STATUS                    207
#define HTTP_ALREADY_REPORTED                208
#define HTTP_IM_USED                         226

/* 3xx Redirection */
#define HTTP_MULTIPLE_CHOICES                300
#define HTTP_MOVED_PERMANENTLY               301
#define HTTP_FOUND                           302
#define HTTP_SEE_OTHER                       303
#define HTTP_NOT_MODIFIED                    304
#define HTTP_USE_PROXY                       305
#define HTTP_TEMPORARY_REDIRECT              307
#define HTTP_PERMANENT_REDIRECT              308

/* 4xx Client Errors */
#define HTTP_BAD_REQUEST                     400
#define HTTP_UNAUTHORIZED                    401
#define HTTP_PAYMENT_REQUIRED                402
#define HTTP_FORBIDDEN                       403
#define HTTP_NOT_FOUND                       404
#define HTTP_METHOD_NOT_ALLOWED              405
#define HTTP_NOT_ACCEPTABLE                  406
#define HTTP_PROXY_AUTHENTICATION_REQUIRED   407
#define HTTP_REQUEST_TIMEOUT                 408
#define HTTP_CONFLICT                        409
#define HTTP_GONE                            410
#define HTTP_LENGTH_REQUIRED                 411
#define HTTP_PRECONDITION_FAILED             412
#define HTTP_PAYLOAD_TOO_LARGE               413
#define HTTP_URI_TOO_LONG                    414
#define HTTP_UNSUPPORTED_MEDIA_TYPE          415
#define HTTP_RANGE_NOT_SATISFIABLE           416
#define HTTP_EXPECTATION_FAILED              417
#define HTTP_IM_A_TEAPOT                     418
#define HTTP_MISDIRECTED_REQUEST             421
#define HTTP_UNPROCESSABLE_ENTITY            422
#define HTTP_LOCKED                          423
#define HTTP_FAILED_DEPENDENCY               424
#define HTTP_TOO_EARLY                       425
#define HTTP_UPGRADE_REQUIRED                426
#define HTTP_PRECONDITION_REQUIRED           428
#define HTTP_TOO_MANY_REQUESTS               429
#define HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE 431
#define HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   451

/* 5xx Server Errors */
#define HTTP_INTERNAL_SERVER_ERROR           500
#define HTTP_NOT_IMPLEMENTED                 501
#define HTTP_BAD_GATEWAY                     502
#define HTTP_SERVICE_UNAVAILABLE             503
#define HTTP_GATEWAY_TIMEOUT                 504
#define HTTP_VERSION_NOT_SUPPORTED           505
#define HTTP_VARIANT_ALSO_NEGOTIATES         506
#define HTTP_INSUFFICIENT_STORAGE            507
#define HTTP_LOOP_DETECTED                   508
#define HTTP_NOT_EXTENDED                    510
#define HTTP_NETWORK_AUTHENTICATION_REQUIRED 511

/* Text */
#define MIME_TEXT_PLAIN      "text/plain"
#define MIME_TEXT_HTML       "text/html"
#define MIME_TEXT_CSS        "text/css"
#define MIME_TEXT_JAVASCRIPT "text/javascript"
#define MIME_TEXT_XML        "text/xml"
#define MIME_TEXT_CSV        "text/csv"

/* Image */
#define MIME_IMG_PNG         "image/png"
#define MIME_IMG_JPG         "image/jpeg"
#define MIME_IMG_GIF         "image/gif"
#define MIME_IMG_SVG         "image/svg+xml"
#define MIME_IMG_WEBP        "image/webp"
#define MIME_IMG_ICO         "image/x-icon"

/* Binary and application */
#define MIME_APP_JSON        "application/json"
#define MIME_APP_XML         "application/xml"
#define MIME_APP_PDF         "application/pdf"
#define MIME_APP_ZIP         "application/zip"
#define MIME_APP_GZIP        "application/gzip"
#define MIME_APP_OCTET_STREAM "application/octet-stream"

/* Audio and video */
#define MIME_VIDEO_MP4       "video/mp4"
#define MIME_VIDEO_WEBM      "video/webm"
#define MIME_AUDIO_MPEG      "audio/mpeg"
#define MIME_AUDIO_WAV       "audio/wav"
#define MIME_AUDIO_OGG       "audio/ogg"

/* Font */
#define MIME_FONT_WOFF       "font/woff"
#define MIME_FONT_WOFF2      "font/woff2"
#define MIME_FONT_TTF        "font/ttf"

class responseBuilder {
    bool hasContent = false;
    std::string response = "";

public:
    responseBuilder &setStatusCode(int statusCode);

    responseBuilder &addHeader(const std::string &name, const std::string &value);

    responseBuilder &setContentLengthHeader(size_t contentLength);

    responseBuilder &setContentTypeHeader(const std::string &mimeType);

    responseBuilder &setConnectionHeader(bool keepAlive);

    responseBuilder &setLocationHeader(const std::string &url);

    responseBuilder &setAllowOriginHeader(const std::string &origin);

    responseBuilder &setDateHeader();

    responseBuilder &setContent(const std::string &content);

    void addBinaryContent(const std::string &path);

    std::string buildResponse();
};


#endif //CEPTEMBER_RESPONSEBUILDER_H
