cmake_minimum_required(VERSION 2.8.12)

project(todo-list LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)


set(SOURCE_FILES
    main.cpp
    qml.qrc
    todolist.h
    todolist.cpp
    todomodel.cpp
    todomodel.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)





