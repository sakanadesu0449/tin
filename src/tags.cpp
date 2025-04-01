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
    const TagLib::Tag *_tag = file_r.tag();
    const TagLib::AudioProperties *_properties = file_r.audioProperties();
    if (read_lrc) {
        const TagLib::PropertyMap& _lrcs_props = file_r.properties();
    }
    duration = _properties->lengthInSeconds();
    bitrate = _properties->bitrate();
    title = _tag->title().toCString();
    album = _tag->album().toCString();
    artist = _tag->artist().toCString();
}

std::string AudioTag::get_title() const {
    return title;
}

std::string AudioTag::get_album() const {
    return album;
}

std::string AudioTag::get_artist() const {
    return artist;
}

int AudioTag::get_bitrate() const {
    return bitrate;
}

int AudioTag::get_duration() const {
    return duration;
}