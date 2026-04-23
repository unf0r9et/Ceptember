#include "fileSearch.hpp"

std::optional<fs::path> findFileRelative(const fs::path &root,
                                         std::string_view raw_name) {
    while (!raw_name.empty() && raw_name.front() == '/') {
        raw_name.remove_prefix(1);
    }

    for (const auto &entry: fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;

        if (entry.path().filename() == raw_name) {
            return fs::relative(entry.path(), root);
        }
    }
    return std::nullopt;
}


std::unordered_set<std::string>
buildFolderSet(const fs::path& root) {
    std::unordered_set<std::string> folders;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_directory()) continue;

        auto rel = fs::relative(entry.path(), root).string();

        if (!rel.empty() && rel[0] != '/')
            rel = "/" + rel;

        folders.insert(rel);
    }

    return folders;
}