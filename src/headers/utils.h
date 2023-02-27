#pragma once

#include <random>

int randomRange(int min, int max) {
    // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

int randomChoice(int numChoices) {
    if (numChoices < 1) {
        return 0;
    }

    return randomRange(0, numChoices - 1);
}
