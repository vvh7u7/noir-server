#include "nrserver/services/connection_manager.hpp"

void ConnectionManager::add(int user_id, crow::websocket::connection* conn) {
    users[user_id] = conn;
}

void ConnectionManager::remove(int user_id) {
    users.erase(user_id);
}

crow::websocket::connection* ConnectionManager::get(int user_id) {
    return users[user_id];
}

std::vector<crow::websocket::connection*> ConnectionManager::getChatUsers(int chat_id) {
    std::vector<crow::websocket::connection*> result;
    for (auto& [id, conn] : users) {
        result.push_back(conn);
    }
    return result;
}

std::unordered_map<int, crow::websocket::connection*> ConnectionManager::users;
