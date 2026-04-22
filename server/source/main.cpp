#include "crow.h"

#include "nrprotocol/nrprotocol.hpp"

#include "nrserver/routes/server_router.hpp"
#include "nrserver/db/database.hpp"


int main(int argc, char *argv[]) {
    Database::init();

    crow::SimpleApp app;

    CROW_WEBSOCKET_ROUTE(app, "/ws")
    .onopen([](crow::websocket::connection& conn) {
        std::cout << "client connected\n";
    })
    .onmessage([](crow::websocket::connection& conn,
                  const std::string& data,
                  bool is_binary) {

        if (!is_binary) return;

        ServerRouter::handle(conn, data);
    });

    app.bindaddr("0.0.0.0").port(0).multithreaded().run();

    std::cout << "RAW: " << data << std::endl;
};
