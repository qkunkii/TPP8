cmake_minimum_required(VERSION 3.21)
project(SupermarketORM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(SupermarketORM
    src/main.cpp
    src/Repo.cpp
    src/RawApi.cpp
    src/Demos.cpp
)

target_include_directories(SupermarketORM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(SupermarketORM PRIVATE sqlite_orm::sqlite_orm unofficial::sqlite3::sqlite3)