#include "route_other.hpp"

self::RouteOther::RouteOther(crow::SimpleApp& app) : m_app{ app } {}
void self::RouteOther::favicon(void)
{
    // 图标
    CROW_ROUTE(this->m_app, "/favicon.ico").methods(crow::HTTPMethod::Get)([&]() {
        return self::OtherService::favicon();
        });
};