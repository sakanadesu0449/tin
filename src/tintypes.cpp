#include "tintypes.hpp"


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


