#pragma once

// 设置1为开启跨域访问(想要性能问题的话建议关闭,使用反向代理)
#include <chrono> 
#include <filesystem>
#include <functional>
#include "crow.h"

#include "spdlog/spdlog.h"
#include "fmt/format.h"

#if ENABLED_ASYNCIO
#include <asyncio/task.h>
#include <asyncio/runner.h>
#include <asyncio/sleep.h>
#include <asyncio/schedule_task.h>
#include <asyncio/callstack.h>
#endif

#include <sw/redis++/redis++.h>
#include "bcrypt.h"

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
#include "self/reusable.hpp"
#include "route/route_other.hpp"

#ifndef MAIN_H
#define MAIN_H

// O3优化
#pragma GCC optimize(3)
#pragma G++ optimize(3)

using namespace std::literals::string_view_literals;
using namespace std::chrono_literals;

//初始化
void init(void) {
    Config::initialized();
    LogSystem::initialized();
}

// 启动项
inline void start(void) {
    init();

    uint16_t port{ Config::config_yaml["server"]["port"].as<uint16_t>() };

    crow::SimpleApp app;

    // 关于其他的配置相关
    self::RouteOther other(app);
    other.favicon();

    app.port(port).multithreaded().run_async();

    return;
}

#endif