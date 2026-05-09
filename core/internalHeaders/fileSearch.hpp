#ifndef CEPTEMBER_FILESEARCH_H
#define CEPTEMBER_FILESEARCH_H
#include <filesystem>
#include <optional>
#include <unordered_set>

namespace fs = std::filesystem;

std::optional<fs::path> findFileRelative(const fs::path &root,
                                         std::string_view raw_name);

std::unordered_set<std::string> buildFolderSet(const fs::path& root);


#endif //CEPTEMBER_FILESEARCH_H
