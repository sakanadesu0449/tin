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
template <typename StreamType>
class ABCJsonHandler {
public:
	virtual ~ABCJsonHandler() = default;

	void FileIOInit(const std::string& filepath) {
		file_exist_checker(filepath);
		file_stream = std::make_unique<StreamType>(filepath);
		if (!file_stream->is_open()) {
			throw(std::string("err: failed open ") + filepath);
		}
	}
	//bool ReadFromJsonFile();
	//bool WriteToJsonFile(const nlohmann::json _updates);
protected:
	std::unique_ptr<StreamType> file_stream;
	nlohmann::json user_profile;
	bool file_exist_checker(const std::string filepath);
    std::any json_to_any(const nlohmann::json& _j);
};

class ReadUserProfile : public ABCJsonHandler<std::ifstream> {
public:
	ReadUserProfile();
	//~UserProfile();
    //bool set_config();

	template <typename T>
	T load_config(const std::string& conf_key) {
		if (!file_stream) {
			throw std::runtime_error("err: file-stream doesn't open");
		}

		*file_stream >> user_profile;
		auto _conf = json_to_any(user_profile[conf_key]);
		try {
			return std::any_cast<T>(_conf);
		} catch (const std::bad_any_cast& err) {
			throw std::invalid_argument(std::string("err: value type doesn't match the expected") + err.what());
		}
	}
};

