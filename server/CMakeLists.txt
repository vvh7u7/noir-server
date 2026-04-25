add_executable(NoirServer
    source/main.cpp
    source/services/auth_service.cpp
    source/services/chat_service.cpp
    source/services/connection_manager.cpp
    source/services/session_manager.cpp

    source/routes/server_router.cpp

    source/db/database.cpp
)

target_include_directories(NoirServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(NoirServer PRIVATE
    NoirProtocol
    Crow::Crow
    sqlite3
)
