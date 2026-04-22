#include "crow.h"

#include "nrprotocol/nrprotocol.hpp"

#include "nrserver/routes/server_router.hpp"
#include "nrserver/db/database.hpp"


int main(int argc, char *argv[]) {
    const char* port = std::getenv("PORT");

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

    app.port(std::stoi(port ? port : "8080"))
    .bindaddr("0.0.0.0")
    .multithreaded()
    .run();
};
