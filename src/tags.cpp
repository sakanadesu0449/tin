#pragma once

#include "tags.hpp"

AudioTag::AudioTag(const std::filesystem::path& filepath, const bool read_lrc) {
    #ifdef _WIN32
    const std::u8string _u8_filepath = filepath.u8string();
    const auto _filepath = std::string(_u8_filepath.begin(), _u8_filepath.end());
    #else
    const std::string _filepath = filepath.string();
    #endif

    file_r = TagLib::FileRef(_filepath.c_str());
    if (file_r.isNull()) {
        throw std::runtime_error(
            std::format("cannot initialize file: {}", _filepath)
        );
    }


} 