#include "httpController.hpp"
#include "fileSaver.hpp"

extern thread_local requestEntity rqEntity;

std::string httpController::methods_POST() {
    switch (str_hash_for_switch(rqEntity.path)) {
        //case "/"_hash:
        case "/upload-video"_hash: {

            fileSaver::saveVideo(rqEntity, "../fileStorage/");
            const std::string jsonBody = R"({"status": "success", "message": "Video saved"})";
            const std::string responseHeaders =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json; charset=utf-8\r\n"
                    "Content-Length: " + std::to_string(jsonBody.length()) + "\r\n"
                    "Connection: close\r\n"
                    "\r\n";
            std::string fullResponse = responseHeaders + jsonBody;
            return fullResponse;
        }

        case "/upload-docs"_hash: {
            int result = fileSaver::saveDocs(rqEntity, "../fileStorage/");

            std::string jsonBody;
            std::string statusLine;

            if (result == 0) {
                statusLine = "HTTP/1.1 200 OK\r\n";
                jsonBody = R"({"status": "success", "message": "Document saved"})";
            } else {
                statusLine = "HTTP/1.1 400 Bad Request\r\n";
                jsonBody = R"({"status": "error", "message": "Failed to save document", "error_code": )" + std::to_string(result) + "}";
            }

            const std::string responseHeaders =
                    statusLine +
                    "Content-Type: application/json; charset=utf-8\r\n" +
                    "Content-Length: " + std::to_string(jsonBody.length()) + "\r\n" +
                    "Connection: close\r\n" +
                    "\r\n";

            std::string fullResponse = responseHeaders + jsonBody;
            return fullResponse;
        }
        default:
            return HTTP_RESPONSE_404;
    }
}

