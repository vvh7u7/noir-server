add_executable(NoirServer
    source/main.cpp
    source/services/auth_service.cpp
    source/services/chat_service.cpp
    source/services/connection_manager.cpp
    source/services/session_manager.cpp

    source/routes/server_router.cpp

    source/db/database.cpp
)

include(FetchContent)

FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
)

FetchContent_MakeAvailable(crow)

target_include_directories(NoirServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(NoirServer PRIVATE
    NoirProtocol
    Crow::Crow
    sqlite3
)
