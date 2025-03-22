#pragma once
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <memory>
#include <variant>
#include <any>

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
class ABCJsonHandler {
public:
	virtual ~ABCJsonHandler() = default;

	bool FileIOInit(const std::string& filepath, const bool rwtype);
	bool ReadFromJsonFile();
	bool WriteToJsonFile(const nlohmann::json _updates);

protected:
	std::unique_ptr<std::ifstream> file_stream;
	nlohmann::json user_profile;
	bool file_exist_checker(const std::string filepath);
    std::any json_to_any(const nlohmann::json& _j);
};

class UserProfile : public ABCJsonHandler {
public:
	UserProfile(const bool rwtype = true);
	~UserProfile();
    std::variant<int, std::string, bool, float> load_config(const std::string& conf_key);
    bool set_config();
	
};

