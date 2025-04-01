#pragma once

#include <iostream>
#include <filesystem>
#include <chrono>
#include <vector>
#include <unordered_map>

#include "tags.hpp"


struct TinTrack {
    const std::filesystem::path filepath;
    const std::u8string filename;
    const std::string trackname;
    const std::string artist;
    const int duration;
    const std::string album;
    const int bitrate;
    const uintmax_t filesize;
    const std::chrono::system_clock::time_point last_change;

    explicit TinTrack(const std::filesystem::directory_entry& _entry, const AudioTag& _tags) :
        filepath(_entry.path()),
        filename(filepath.filename().u8string()),
        trackname(_tags.get_title()),
        artist(_tags.get_artist()),
        duration(_tags.get_duration()),
        album(_tags.get_album()),
        filesize(get_filesize(_entry)),
        last_change(
            std::chrono::clock_cast<std::chrono::system_clock>(
                std::filesystem::last_write_time(_entry)
            )
        ),
        bitrate(_tags.get_bitrate()) {}

private:
        static uintmax_t get_filesize(const auto& _entry) {
            try {
                return _entry.is_regular_file() ? _entry.file_size() : 0;
            } catch(...) {
                return 0;
            }
        }
};

class TinPlaylist {
public:
    TinTrack* get_track(const std::string& trackname);
    void add_track(const TinTrack& track);
    bool del_track(const std::string& trackname);
    size_t get_playlist_size() const;

private:
    std::unordered_map<std::string, TinTrack> tracklist;
};