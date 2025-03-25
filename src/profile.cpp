#include "profile.hpp"

//Class Definition


//template <>
//ABCJsonHandler<std::fstream>::~ABCJsonHandler() {
//	if (file_stream && file_stream->is_open()) {
//		file_stream->close();
//	}
//}

ReadUserProfile::ReadUserProfile() {
	FileIOInit(DEFAULT_PROFILE_PATH);
}


//std::any UserProfile::load_config(const std::string& conf_key) {
//	*file_stream >> user_profile;
//	const auto& _conf = json_to_any(user_profile[conf_key]);
//	return _conf;
//}
