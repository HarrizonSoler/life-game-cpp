#pragma once

#include <iostream>
#include <json/value.h>
#include <vector>
#include <array>

#include "Tick.h"

class Game {
    std::vector<Tick> ticks;

    const int size_;
    const Json::Value liveCells_;

    void setTick(const int &tick);

    public:
        Json::Value json;
        Game(const int &size, const int &ticksNumber, const Json::Value &liveCells);
};
