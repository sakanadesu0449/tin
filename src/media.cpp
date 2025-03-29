#include "media.hpp"
#include "profile.hpp"

GetMediaLibPath::GetMediaLibPath() {
    get_media_lib_paths();
}

std::vector<std::filesystem::path>& GetMediaLibPath::paths() {
    return filepaths;
}

void GetMediaLibPath::get_media_lib_paths() {
    ReadUserProfile _user_profile;
    std::vector<std::any> _filepaths = _user_profile.load_config<std::vector<std::any>>("media_lib");

    for (const std::any& _a_path : _filepaths) {
        try {
            std::string _path = std::any_cast<std::string>(_a_path);
            std::cout << "loading: " << _path << std::endl;
            filepaths.emplace_back(_path);
        } catch (const std::exception& err) {
            throw(std::runtime_error(std::string("err: failed to load media library: ") + err.what()));
        }
    }
}

TinPlaylist& BaseFileEnumerator::get_playlist_from_paths(const std::vector<std::filesystem::path>& root_paths) {
    
}

