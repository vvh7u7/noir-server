#pragma once

#include <unordered_map>
#include <string>
#include <crow/websocket.h>


class SessionManager {
public:
    static void bind(int user_id, crow::websocket::connection* conn);
    static void unbind(int user_id);

    static crow::websocket::connection* get(int user_id);

    static int getUserId(crow::websocket::connection* conn);

private:
    static std::unordered_map<int, crow::websocket::connection*> sessions;
};
