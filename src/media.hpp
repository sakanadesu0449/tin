#pragma once

#include <filesystem>
#include <vector>
#include <iostream>

#include "tintypes.hpp"

class BaseFileEnumerator {
protected:
    TinPlaylist& get_playlist_from_paths(const std::vector<std::filesystem::path>& root_paths);
//protected:
//  std::filesystem::directory_entry& root_entry;
};

class GetMediaLibPath {
public:
    GetMediaLibPath();
    std::vector<std::filesystem::path>& paths();
private:
    std::vector<std::filesystem::path> filepaths;
    void get_media_lib_paths();
};

class MediaLib : public BaseFileEnumerator {
public:
    MediaLib();

};


