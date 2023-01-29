#!/bin/bash

#clang++ \
    #src/main.cpp \
    #src/player.cpp \
    #src/combatstate.cpp \
    #src/ui.cpp \
    #src/attack.cpp \
    #src/enemy.cpp \
    #src/turtle.cpp \
    #src/damage-bubble.cpp \
    #src/cast-effect.cpp \
    #src/necromancer-skilltree.cpp \
    #-std=c++20 \
    #-o pm \
    #-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    #

cd build && cmake ../src && make && cp plainman .. && cd .. && ./plainman
