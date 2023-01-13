clang++ \
    src/main.cpp \
    src/player.cpp \
    src/gamestate.cpp \
    src/ui.cpp \
    src/attack.cpp \
    src/enemy.cpp \
    -o pm \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
