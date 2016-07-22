#include <fstream>
#include "Utils.h"

bool Utils::fileExists(const std::string& filePath) {
    std::ifstream f(filePath);
    return f.good();
}
