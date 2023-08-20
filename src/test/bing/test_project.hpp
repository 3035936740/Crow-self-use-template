#pragma once

#include <iostream>
#include <fmt/core.h>
#include <fstream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <utility>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <string>
#include <span>
#include <jwt-cpp/jwt.h>
#include <sqlite_modern_cpp.h>
#include "crow.h"
#include "tl/generator.hpp"

#if ENABLED_ASYNCIO
#include <asyncio/task.h>
#include <asyncio/runner.h>
#include <asyncio/sleep.h>
#include <asyncio/schedule_task.h>
#include <asyncio/callstack.h>
#endif

#include <Poco/Net/MediaType.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <snowflake.hpp>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DigestEngine.h"
#include "Poco/SHA2Engine.h"
#include "Poco/SHA1Engine.h"

#ifndef TEST_PROJECT_HPP
#define TEST_PROJECT_HPP  
//#define WARNING_CONTENT  
using _uint64 = unsigned long long int;

tl::generator<int> generateInts()
{
	for (int i = 0; i < 10; ++i)
	{
		co_yield i;
	}
};

#if ENABLED_ASYNCIO
asyncio::Task<std::string_view> hello() {
	co_return "hello";
}

asyncio::Task<std::string_view> world() {
	co_return "world";
}

asyncio::Task<std::string> hello_world() {
	co_return fmt::format("{} {}", co_await hello(), co_await world());
	fmt::print("{}", asyncio::run(world()));
}
#endif

class TestProject final {
public:
#if ENABLED_ASYNCIO
	inline static void coroutine_test() {
		StartWatch();
		auto completes_synchronously = [](int args) -> asyncio::Task<int> {
			co_return args;
		};

		auto main = [&](const int N) ->  asyncio::Task<int> {
			int sum = 0;
			for (int i = 0; i < N; ++i) {
				sum += co_await completes_synchronously(3);
			}
			co_return sum;
		};

		fmt::print("{}\n", asyncio::run(main(10)));
		StopWatch();
	};
#endif

	inline static void uuid_test() {
		using snowflake_t = snowflake<-1L, std::mutex>;
		snowflake_t::twepoch = 1690029136L * 1000L;
		snowflake_t snowflake_uuid;
		snowflake_uuid.init(1, 1);
		auto id = snowflake_uuid.nextid();

		Poco::UUIDGenerator uuid_generator{};

		std::cout << Poco::UUID("00000000-0000-0000-0000-000000000000").toString() << std::endl;

		//Poco::DigestEngine* engine{ new Poco::MD5Engine() };
		std::unique_ptr<Poco::DigestEngine> engine{ new Poco::SHA1Engine() };
		Poco::UUID uuid{ uuid_generator.createFromName(Poco::UUID("00000000-0000-0000-0000-000000000000"), std::to_string(id), *engine, Poco::UUID::UUID_NAME_BASED_SHA1) };

		engine.reset();

		std::cout << uuid.toString() << std::endl;
		std::cout << id << "\n";
	}

	inline static void test(void) {
	};
private:
	inline static std::chrono::system_clock::time_point start, end;

	inline static void StartWatch(void) {
		std::cout << "\033[42mstart watch\033[0m\n";
		start = std::chrono::high_resolution_clock::now();
	};

	inline static void StopWatch(void) {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		std::cout << "\033[42mtime consumed " << elapsed.count() << " ms\033[0m\n";
		std::cout.flush();
	};
};

#endif