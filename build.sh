clang++ \
    src/main.cpp \
    src/player.cpp \
    src/combatstate.cpp \
    src/ui.cpp \
    src/attack.cpp \
    src/enemy.cpp \
    src/turtle.cpp \
    -o pm \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
