clang++ \
    src/main.cpp \
    src/player.cpp \
    src/combatstate.cpp \
    src/ui.cpp \
    src/attack.cpp \
    src/enemy.cpp \
    src/turtle.cpp \
    src/bird.cpp \
    -std=c++20 \
    -o pm \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
