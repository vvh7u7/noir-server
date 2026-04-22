#include "nrserver/services/auth_service.hpp"
#include "nrserver/db/database.hpp"


int AuthService::login(const LoginMessage& msg) {
    return Database::getUserId(msg.username, msg.password);
}

int AuthService::registerUser(const LoginMessage& msg) {
    return Database::createUser(msg.username, msg.password);
}
