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
	bool file_exist_checker(const std::string filepath) {
		std::filesystem::path _filepath(filepath);
		std::filesystem::path _parent = _filepath.parent_path();
	
		if(!std::filesystem::exists(_parent)) {
			if(!std::filesystem::create_directories(_parent)) {
				std::cerr << "Failed to create user profile directories: " << filepath << std::endl;
				return false;
			}
		}
		return true;
	}

    std::any json_to_any(const nlohmann::json& _j) {
		if (_j.is_number_integer()) {
			return _j.get<int>();
		} else if (_j.is_string()) {
			return _j.get<std::string>();
		} else if (_j.is_boolean()) {
			return _j.get<bool>();
		} else if (_j.is_number_unsigned()) {
			return _j.get<unsigned int>();
		} else if (_j.is_number_float()) {
			return _j.get<double>();
		} else if (_j.is_null()) {
			return nullptr;
		} else if (_j.is_array()) {
			std::vector<std::any> o_array;
			for (const auto& i : _j) {
				o_array.push_back(json_to_any(i));
			}
			return o_array;
		} else if (_j.is_object()) {
			std::map<std::string, std::any> o_map;
			for (const auto& [key, value] : _j.items()) {
				o_map[key] = json_to_any(value);
			}
			return o_map;
		} else {
			throw(std::runtime_error("err: unsuppost json type"));
		}
	}
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

