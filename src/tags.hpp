#pragma once

#define TAGLIB_STATIC

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

#include <filesystem>
#include <format>

class AudioTag
{
public:
    explicit AudioTag(const std::filesystem::path &filepath, const bool read_lrc = false);

    ~AudioTag() = default;

    std::string get_title() const;
    std::string get_artist() const;
    std::string get_album() const;
    int get_duration() const;
    int get_bitrate() const;

private:
    TagLib::FileRef file_r;

    int duration;
    int bitrate;
    std::string title;
    std::string artist;
    std::string album;
};