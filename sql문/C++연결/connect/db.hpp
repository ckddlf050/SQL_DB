#pragma once
#include <mysql/jdbc.h>
#include <memory>

extern std::unique_ptr<sql::Connection> con;
