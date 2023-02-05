cmake_minimum_required(VERSION 3.15)
project(PlainMan)

set(CMAKE_CXX_STANDARD 20) # Requires C11 standard
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")

SET (MY_HEADERS headers/combatstate.h
    headers/player.h 
    headers/ui.h 
    headers/attack.h 
    headers/enemy.h 
    headers/turtle.h 
    headers/bird.h 
    headers/cast-effect.h 
    headers/damage-bubble.h 
    headers/skilltree.h
    headers/skilltree-state.h
    headers/skilltree-node.h
    headers/mage-skilltree.h
    headers/bard-skilltree.h
    headers/necromancer-skilltree.h
    headers/combat-round.h
    headers/upgrade-state.h
)

SET (MY_SOURCE combatstate.cpp
    player.cpp 
    ui.cpp 
    attack.cpp 
    enemy.cpp 
    turtle.cpp 
    bird.cpp 
    cast-effect.cpp 
    damage-bubble.cpp 
    skilltree.cpp
    skilltree-state.cpp
    skilltree-node.cpp
    combat-round.cpp
    upgrade-state.cpp
)

find_library(RAYLIB_LIBRARY raylib HINTS /usr/local/include)

add_executable(${PROJECT_NAME} main.cpp ${MY_SOURCE} ${MY_HEADERS})

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
