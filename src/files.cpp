#include "include/files.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> Files::getFiles(const std::string& path) {
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }

    return files;
}

std::vector<std::string> Files::getFolders(const std::string& path) {
    std::vector<std::string> folders;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            folders.push_back(entry.path().filename().string());
        }
    }

    return folders;
}

void Files::newFile(const std::string& path, const std::string& name) {

}

void Files::newFolder(const std::string& path, const std::string& name) {

}

std::string Files::readFile(const std::string& path) {

}

void Files::writeFile(const std::string& path, const std::string& value) {

}

Files filesObject;