#pragma once

#include "crow.h"
#include <filesystem>
#include "string"
#include <configuration/config.hpp>
#include <common/utils.hpp>
#include <service/other/other_service.hpp>

namespace self {
	class RouteOther final {
	private:
		crow::SimpleApp& m_app;
	public:
		RouteOther() = delete;
		~RouteOther() = default;
		RouteOther(const RouteOther&) = delete;
		RouteOther(RouteOther&&) = delete;
		RouteOther& operator=(const RouteOther&) = delete;
		RouteOther& operator=(RouteOther&&) = delete;

		explicit RouteOther(crow::SimpleApp& app);

        void favicon(void);
	};
}