cmake_minimum_required(VERSION 3.15)
project(PlainMan)

set(CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

SET (MY_HEADERS
    src/headers/enums.h
    src/headers/utils.h
    src/headers/attack.h
    src/headers/combat-entity.h
)

SET (MY_SOURCE 
    src/main.cpp
    src/attack.cpp
    src/combat-entity.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#TODO remove 
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_library(RAYLIB_LIBRARY raylib HINTS /usr/local/include)

add_executable(${PROJECT_NAME} ${MY_SOURCE} ${MY_HEADERS})

target_link_directories(${PROJECT_NAME} PRIVATE headers)
target_link_libraries(${PROJECT_NAME} PUBLIC ${RAYLIB_LIBRARY})

target_include_directories(${PROJECT_NAME} PRIVATE headers src/headers)



# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "plainman")

