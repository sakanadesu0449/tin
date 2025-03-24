#include "media.hpp"
#include "profile.hpp"

MediaLib::MediaLib() {
    get_media_lib_paths();
}

void MediaLib::get_media_lib_paths() {
    UserProfile _user_profile;
    std::vector<std::any> _filepaths = _user_profile.load_config<std::vector<std::any>>("media_lib");

    for (const std::any& _path : _filepaths) {
        try {
            std::cout << std::any_cast<std::string>(_path) << std::endl;
            filepaths.emplace_back(std::any_cast<std::string>(_path));
        } catch (const std::exception& err) {
            throw(std::runtime_error(std::string("err: failed to load media library: ") + std::any_cast<std::string>(_path)));
        }
    }
}

