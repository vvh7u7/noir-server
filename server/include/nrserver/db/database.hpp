#pragma once

#include <string>
#include <vector>

class Database {
public:
    static void init();

    static int createUser(const std::string& username, const std::string& password);
    static int getUserId(const std::string& username, const std::string& password);

    static int createChat(const std::string& name);
    static void addUserToChat(int user_id, int chat_id);

    static void insertMessage(int chat_id, int user_id, const std::string& text);

    static std::vector<int> getUsers(int chat_id);
};
