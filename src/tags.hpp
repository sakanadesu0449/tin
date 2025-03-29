#define TAGLIB_STATIC

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

#include <filesystem>

class Tag {
public:
    explicit Tag(const std::filesystem::path& filepath);

    std::string get_title();
    std::string get_artist();
    std::string get_album();
    int get_duration();
    int get_bitrate();

private:
    TagLib::FileRef file_r;
};