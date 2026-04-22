#pragma once
#include <crow.h>
#include <cstdint>
#include <string>

class ServerRouter {
public:
    static void handle(crow::websocket::connection& conn, const std::string& data);
};
