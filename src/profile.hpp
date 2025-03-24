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
		"media_lib":
		[
			"C:/Music"
		]
	}
)";
const nlohmann::json DEFAULT_USER_PROFILE_JSON = nlohmann::json::parse(DEFAULT_USER_PROFILE_JSON_S);

//Class Declaration
//i
//abc
class ABCJsonHandler {
public:
	//~ABCJsonHandler();

	//retype: True to read, False to write, default read
	bool FileIOInit(const std::string& filepath, const bool rwtype);

	bool ReadFromJsonFile();
	bool WriteToJsonFile(const nlohmann::json _updates);

protected:
	std::unique_ptr<std::ifstream> file_stream_r;
	std::unique_ptr<std::ofstream> file_stream_w;
	nlohmann::json user_profile;
	bool file_exist_checker(const std::string filepath);
    std::any json_to_any(const nlohmann::json& _j);
};

class UserProfile : public ABCJsonHandler {
public:
	UserProfile(const bool rwtype = true);
	//~UserProfile();
    //bool set_config();

	template <typename T>
	T load_config(const std::string& conf_key) {
		if (!file_stream_r) {
			throw std::runtime_error("err: file-stream doesn't open");
		}

		*file_stream_r >> user_profile;
		auto _conf = json_to_any(user_profile[conf_key]);
		try {
			return std::any_cast<T>(_conf);
		} catch (const std::bad_any_cast& err) {
			throw std::invalid_argument(std::string("err: value type doesn't match the expected") + err.what());
		}
	}
};

