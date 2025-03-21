#include <iostream>
#include <filesystem>
#include <chrono>
#include <vector>
#include <unordered_map>


struct TinTrack
{
    const std::filesystem::path filepath;
    const std::string trackname;
    const std::string artist;
    const std::chrono::seconds duration;
    const std::string album;
};

class TinPlaylist
{
public:
    TinTrack* get_track(const std::string& trackname);
    void add_track(const TinTrack& track);
    bool del_track(const std::string& trackname);
    size_t get_playlist_size() const;

private:
    std::unordered_map<std::string, TinTrack> tracklist;
};

TinTrack* TinPlaylist::get_track(const std::string& trackname)
{
    auto track = tracklist.find(trackname);
    if (track != tracklist.end())
    {
        return &(track->second);
    }
    return nullptr;
}

void TinPlaylist::add_track(const TinTrack& track)
{
    tracklist.emplace(track.trackname, track);
}
bool TinPlaylist::del_track(const std::string& trackname)
{
    return tracklist.erase(trackname) > 0;
}

size_t TinPlaylist::get_playlist_size() const
{
    return tracklist.size();
}


