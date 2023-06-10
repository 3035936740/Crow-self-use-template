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

#ifndef CONFIG_HPP
#define CONFIG_HPP  

using namespace std::string_literals;
using namespace std::chrono_literals;

namespace std {
	using fmt::format;
	using fmt::format_error;
	using fmt::formatter;
}

#define Json nlohmann::json

class Config final{
private:
	Config() = delete;
	~Config() = delete;
	Config(const Config&) = delete;
	Config(Config&&) = delete;
	Config& operator=(const Config&) = delete;
	Config& operator=(Config&&) = delete;
public:
	inline static YAML::Node config_yaml{ YAML::LoadFile("./config.yaml")};
	static void initialized(){

	}
};

class Global final {
	friend class Config;
private:
	Global() = delete;
	~Global() = delete;
	Global(const Global&) = delete;
	Global(Global&&) = delete;
	Global& operator=(const Global&) = delete;
	Global& operator=(Global&&) = delete;
public:
	inline static std::string resource_path{ Config::config_yaml["server"]["resource-path"].as<std::string>()};
};


#endif