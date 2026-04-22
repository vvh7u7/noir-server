#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <crow.h>

class ConnectionManager {
public:
    static void add(int user_id, crow::websocket::connection* conn);
    static void remove(int user_id);
    static crow::websocket::connection* get(int user_id);

    static std::vector<crow::websocket::connection*> getChatUsers(int chat_id);

private:
    static std::unordered_map<int, crow::websocket::connection*> users;
};
