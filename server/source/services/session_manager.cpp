#include "nrserver/services/session_manager.hpp"

std::unordered_map<int, crow::websocket::connection*> SessionManager::sessions;

void SessionManager::bind(int user_id, crow::websocket::connection* conn) {
    sessions[user_id] = conn;
}

void SessionManager::unbind(int user_id) {
    sessions.erase(user_id);
}

crow::websocket::connection* SessionManager::get(int user_id) {
    return sessions.count(user_id) ? sessions[user_id] : nullptr;
}

int SessionManager::getUserId(crow::websocket::connection* conn) {
    for (auto& [uid, c] : sessions) {
        if (c == conn) return uid;
    }
    return -1;
}
