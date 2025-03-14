#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <memory>

#ifdef _WIN32
const std::string _SYS_SEP = "\\";
#else
const std::string _SYS_SEP = "/";
#endif

const std::string DEFAULT_PROFILE_PATH = R"(config/user_profile.json)";
const std::string DEFAULT_USER_PROFILE_JSON_S = R"(
	{
		"media_repo":
		[
			"C:/Music"
		]
	}
)";
const nlohmann::json DEFAULT_USER_PROFILE_JSON = nlohmann::json::parse(DEFAULT_USER_PROFILE_JSON_S);

//Class Declaration
//
//abc
class ABCJsonHandler
{
public:
	virtual ~ABCJsonHandler() = default;

	bool FileIOInit(const std::string filepath);
	bool ReadFromJsonFile();
	bool WriteToJsonFile();

protected:
	std::unique_ptr<std::ifstream> file_stream;
	nlohmann::json user_profile;
	bool file_exist_checker(const std::string filepath);
};

class UserProfileR : public ABCJsonHandler
{
public:
	UserProfileR();
	~UserProfileR();
	
};

class UserProfileU : public ABCJsonHandler
{
	UserProfileU();
	~UserProfileU();

};

//Class Definition
//
bool ABCJsonHandler::file_exist_checker(const std::string filepath)
{
	std::filesystem::path _filepath(filepath);
	std::filesystem::path _parent = _filepath.parent_path();

	if(!std::filesystem::exists(_parent))
	{
		if(!std::filesystem::create_directories(_parent))
		{
			std::cerr << "Failed to create user profile directories: " << filepath << std::endl;
			return false;
		}
	}
	return true;
}
bool ABCJsonHandler::FileIOInit(const std::string filepath)
{
	if(!file_exist_checker(filepath))
	{
		std::cerr << "Unkknown error" << std::endl;
	}
	file_stream = std::make_unique<std::ifstream>(filepath);
	if (!file_stream->is_open())
	{
		std::cerr << "Failed open File" << filepath <<std::endl;
		return false;
	}

	return true;

}