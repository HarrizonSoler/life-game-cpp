#pragma once

#include <json/value.h>
#include <vector>
#include <cmath>
#include <iostream>

class Tick {
    std::vector<std::vector<bool>> matrix;

    // DD, DL, LD, LL
    std::array<int, 4> transitions = {0, 0, 0, 0};
    const int size_;

    public:
        Json::Value liveCells_;

        void calcTick(const Tick &lastTick);
        Tick(const int &size);
        void setCells(const Json::Value &cells);
        bool judgeCell(const int &x, const int &y, const Tick &lastTick);
        int getNearCount(const int &x, const int &y, const Tick &lastTick);
};
