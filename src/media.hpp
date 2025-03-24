#pragma once

#include <filesystem>
#include <vector>
#include <iostream>

class MediaLib {
public:
    MediaLib();
private:
    std::vector<std::filesystem::path> filepaths;
    void get_media_lib_paths();
};