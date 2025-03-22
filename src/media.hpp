#pragma once

#include <filesystem>
#include <vector>

class MediaLib {
public:
    MediaLib();
private:
    std::vector<std::filesystem::path>* get_media_lib_paths();
};