#pragma once

// 设置1为开启跨域访问(想要性能问题的话建议关闭,使用反向代理)
#include "httplib.h"
#include <iostream>
#include <thread>
#include <chrono> 
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <array>
#include <vector>
#include "crow.h"

#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace std {
    using fmt::format;
    using fmt::format_error;
    using fmt::formatter;
}
#include "configuration/config.hpp"
#include "common/utils.hpp"
#include "common/self_exception.hpp"
#include "common/http_util.hpp"
#include "common/log_system.hpp"

#include <restbed>
#include <ctime>
#include <cpprest/http_client.h>

#ifndef MAIN_H
#define MAIN_H

// O3优化
#pragma GCC optimize(3)
#pragma G++ optimize(3)

using namespace std::chrono_literals;


//初始化
inline void init(void) {
    Config::initialized();
    LogSystem::initialized();
}

// 启动项
inline void start(void) {
    uint16_t port{ Config::config_yaml["server"]["port"].as<uint16_t>() };

    crow::SimpleApp app;

    // 图标
    CROW_ROUTE(app, "/favicon.ico").methods(crow::HTTPMethod::Get)([&]() {
        crow::response response;

        std::string path{ Global::resource_path + "favicon.ico"s};

        if (!std::filesystem::exists(path)) {
            response.set_header("Content-Type", "application/json");
            response.code = 404;
            response.write(HTTPUtil::StatusCodeHandle::getSimpleJsonResult(404).dump(2));
            return response;
        }

        // 获取当前时间
        auto now{ std::chrono::system_clock::now() };

        // 计算七天后的时间
        auto seven_days_later{ now + std::chrono::hours(24 * 7) };

        // 将时间转换为时间戳（秒数）
        auto timestamp{ std::chrono::system_clock::to_time_t(seven_days_later) };

        // 将时间戳转换为 Crow 框架中的 Expires 数值
        std::stringstream ss;
        ss << std::put_time(std::gmtime(&timestamp), "%a, %d %b %Y %H:%M:%S GMT");
        std::string expires{ ss.str() };
        response.set_static_file_info(path);
        response.set_header("Cache-Control", "public");
        response.set_header("Expires", expires);
        return response;
    });

    app.port(port).multithreaded().run_async();
}

#endif