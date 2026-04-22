#pragma once

#include "nrprotocol/nrprotocol.hpp"

class ChatService {
public:
    static void sendMessage(int chat_id, int user_id, const std::string& text);
};
