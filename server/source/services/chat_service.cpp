#include "nrserver/services/chat_service.hpp"
#include "nrserver/services/connection_manager.hpp"
#include "nrserver/services/session_manager.hpp"
#include "nrserver/db/database.hpp"


void ChatService::sendMessage(int chat_id, int user_id, const std::string& text) {

    Database::insertMessage(chat_id, user_id, text);

    auto users = Database::getUsers(chat_id);

    for (int uid : users) {
        auto conn = SessionManager::get(uid);
        if (!conn) continue;

        conn->send_text(text); // позже заменишь на Packet
    }
}
