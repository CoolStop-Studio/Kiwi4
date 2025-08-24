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
    std::ofstream file(path + "/" + name);
    
    file.close();
}

void Files::newFolder(const std::string& path, const std::string& name) {
    std::filesystem::path folderPath = path + "/" + name;
    std::filesystem::create_directories(folderPath);
}

void Files::deleteFile(const std::string& path) {
    if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
        std::filesystem::remove(path);
    }
}

void Files::deleteFolder(const std::string& path) {
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        std::filesystem::remove_all(path);
    }
}

std::string Files::readFile(const std::string& path) {
    std::ifstream inputFileStream(path);

    if (!inputFileStream.is_open()) {
        printf("Error: Could not open file %s", path.c_str());
        return "";
    }

    std::stringstream buffer;
    buffer << inputFileStream.rdbuf();

    inputFileStream.close();

    return buffer.str();
}

void Files::writeFile(const std::string& path, const std::string& value) {
    std::ofstream outputFile(path);
    
    outputFile << value;
    outputFile.close();
}

Files filesObject;