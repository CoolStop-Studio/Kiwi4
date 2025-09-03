#include "include/utils.h"
#include "include/globals.h"

std::string formatPath(std::string path) {
    if (!path.empty() && path.front() == '/') {
        path.erase(0, 1);
    }

    if (path.rfind(PROJECT_PATH, 0) == 0) {
        return path;
    }

    return PROJECT_PATH + path;
}