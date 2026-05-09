#include "deleteFile.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/**
 * Удаляет конкретный файл по указанному пути.
 * @param filePath Полный путь к файлу
 * @return true если файл успешно удален, false если возникла ошибка или файла нет
 */
bool deleteFile::delFile(const std::string &filePath) {
    try {
        fs::path path(filePath);
        if (fs::exists(path) && fs::is_regular_file(path)) {
            return fs::remove(path);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
    return false;
}