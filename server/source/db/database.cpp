#include "nrserver/db/database.hpp"

#include <sqlite3.h>
#include <iostream>

static sqlite3* db;


static void logError(const std::string& msg) {
    std::cerr << "[DB ERROR] " << msg
              << " | " << sqlite3_errmsg(db)
              << std::endl;
}

void Database::init() {

    sqlite3_open("nrmsg.db", &db);

    sqlite3_exec(db,
                 "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password TEXT);",
                 nullptr, nullptr, nullptr);

    sqlite3_exec(db,
                 "CREATE TABLE IF NOT EXISTS chats (id INTEGER PRIMARY KEY, name TEXT);",
                 nullptr, nullptr, nullptr);

    sqlite3_exec(db,
                 "CREATE TABLE IF NOT EXISTS chat_users (chat_id INT, user_id INT);",
                 nullptr, nullptr, nullptr);

    sqlite3_exec(db,
                 "CREATE TABLE IF NOT EXISTS messages ("
                 "id INTEGER PRIMARY KEY, "
                 "chat_id INT, "
                 "user_id INT, "
                 "text TEXT, "
                 "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                 ");",
                 nullptr, nullptr, nullptr);
}

int Database::createUser(const std::string& username, const std::string& password) {

    sqlite3_stmt* stmt;

    const char* sql =
    "INSERT INTO users (username, password) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("prepare createUser");
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        logError("insert createUser");
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    int user_id = sqlite3_last_insert_rowid(db);

    return user_id;
}

int Database::getUserId(const std::string& username, const std::string& password) {

    sqlite3_stmt* stmt;

    const char* sql =
    "SELECT id, password FROM users WHERE username = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    int user_id = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        const unsigned char* stored_pass =
        sqlite3_column_text(stmt, 1);

        if (stored_pass == nullptr) {
            sqlite3_finalize(stmt);
            return -1;
        }

        std::string stored = (const char*)stored_pass;

        // пока без hash (для MVP)
        if (stored == password) {
            user_id = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);

    return user_id;
}

int Database::createChat(const std::string& name) {

    sqlite3_stmt* stmt;

    const char* sql =
    "INSERT INTO chats (name) VALUES (?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    int chat_id = sqlite3_last_insert_rowid(db);

    return chat_id;
}

void Database::addUserToChat(int user_id, int chat_id) {

    sqlite3_stmt* stmt;

    const char* sql =
    "INSERT INTO chat_users(chat_id, user_id) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }

    sqlite3_bind_int(stmt, 1, chat_id);
    sqlite3_bind_int(stmt, 2, user_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void Database::insertMessage(int chat_id, int user_id, const std::string& text) {

    sqlite3_stmt* stmt;

    const char* sql =
    "INSERT INTO messages (chat_id, user_id, text) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }

    sqlite3_bind_int(stmt, 1, chat_id);
    sqlite3_bind_int(stmt, 2, user_id);
    sqlite3_bind_text(stmt, 3, text.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);
}

std::vector<int> Database::getUsers(int chat_id) {

    std::vector<int> users;

    sqlite3_stmt* stmt;

    const char* sql =
    "SELECT user_id FROM chat_users WHERE chat_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return users;
    }

    sqlite3_bind_int(stmt, 1, chat_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int user_id = sqlite3_column_int(stmt, 0);
        users.push_back(user_id);
    }

    sqlite3_finalize(stmt);

    return users;
}
