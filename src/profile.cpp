#include "profile.hpp"

//Class Definition
//
bool ABCJsonHandler::file_exist_checker(const std::string filepath) {
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
bool ABCJsonHandler::FileIOInit(const std::string& filepath, const bool rwtype) {
	if(!file_exist_checker(filepath)) {
		std::cerr << "Unkknown error" << std::endl;
	}
	if (rwtype) {
		auto file_stream = std::make_unique<std::ifstream>(filepath);
	} else {
		auto file_stream = std::make_unique<std::ofstream>(filepath);
	}
	if (!file_stream->is_open()) {
		std::cerr << "Failed open File: " << filepath << std::endl;
		return false;
	}
	return true;
}

std::any ABCJsonHandler::json_to_any(const nlohmann::json& _j) {
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
		throw std::runtime_error("Unsupported JSON type");
	}
}

UserProfile::UserProfile(const bool rwtype = true) {
	FileIOInit(DEFAULT_PROFILE_PATH, rwtype);
}

std::variant<int, std::string, bool, float> UserProfile::load_config(const std::string& conf_key) {
	*file_stream >> user_profile;
}
