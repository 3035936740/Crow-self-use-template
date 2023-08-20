/*
 * @File	  : config.hpp
 * @Coding	  : utf-8
 * @Author    : Bing
 * @Time      : 2023/03/05 21:14
 * @Introduce : 配置类(解析yaml)
*/

#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "yaml-cpp/yaml.h"
#include "fmt/format.h"
#include <limits>
#include <sqlite_modern_cpp.h>
#include <Poco/Net/MediaType.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include "configuration/define.hpp"

#ifndef CONFIG_HPP
#define CONFIG_HPP  

using namespace std::string_literals;
using namespace std::chrono_literals;

namespace std {
	using fmt::format;
	using fmt::format_error;
	using fmt::formatter;
}

namespace Config {
	static YAML::Node config_yaml{ YAML::LoadFile("./config.yaml") };
};

namespace Global {
	inline std::string resource_path{ Config::config_yaml["server"]["resource-path"].as<std::string>()};
	inline std::string authorization_code{ Config::config_yaml["server"]["authorization-code"].as<std::string>() };
};

namespace self::DB {
	static sqlite::database LocalDB{ sqlite::database(Config::config_yaml["db"]["sqlite"]["local"].as<std::string>()) };
};

namespace Config {
	inline void initialized(void) {
	}
}

#endif