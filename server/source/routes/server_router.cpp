#include "nrserver/routes/server_router.hpp"

#include "nrprotocol/nrprotocol.hpp"

#include "nrserver/services/auth_service.hpp"
#include "nrserver/services/chat_service.hpp"
#include "nrserver/services/connection_manager.hpp"
#include "nrserver/services/session_manager.hpp"


void ServerRouter::handle(crow::websocket::connection& conn, const std::string& data) {

    Packet p = Deserializer::fromBytes(data);

    switch ((MessageType)p.header.type) {

        case MessageType::LOGIN: {
            auto msg = Deserializer::parseLogin(p);

            int user_id = AuthService::login(msg);

            if (user_id != -1) {
                SessionManager::bind(user_id, &conn);
            }
            break;
        }

        case MessageType::SEND_MESSAGE: {
            auto msg = Deserializer::parseChat(p);

            int user_id = SessionManager::getUserId(&conn);

            ChatService::sendMessage(msg.chat_id, user_id, msg.text);
            break;
        }
    }
}
