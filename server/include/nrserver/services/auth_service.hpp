#pragma once

#include "nrprotocol/nrprotocol.hpp"


class AuthService {
public:
    static int login(const LoginMessage& msg);
    static int registerUser(const LoginMessage& msg);
};
