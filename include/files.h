#ifndef FILES_H
#define FILES_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Files {
    static std::vector<std::string> getFiles(const std::string& path);
    static std::vector<std::string> getFolders(const std::string& path);
    static void newFile(const std::string& path, const std::string& name);
    static void newFolder(const std::string& path, const std::string& name);
    static void deleteFile(const std::string& path);
    static void deleteFolder(const std::string& path);
    static std::string readFile(const std::string& path);
    static void writeFile(const std::string& path, const std::string& value);
};

extern Files filesObject;

#endif // FILES_H
