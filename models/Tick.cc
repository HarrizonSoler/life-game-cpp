#include "Tick.h"
#include <cstring>
#include <iostream>
#include <json/value.h>
#include <vector>

Tick::Tick(const int &size) : size_(size), matrix(size, std::vector<bool>(size, false)) {
    liveCells_["matrixCells"] = Json::arrayValue;
}

void Tick::setCells(const Json::Value &cells) {
    int x, y = 0;

    for (int index = 0; index < cells.size(); ++index ) {
        matrix[std::floor((cells[index].asInt() - 1) / size_)][(cells[index].asInt() - 1) % size_] = true;
        liveCells_["matrixCells"].append(cells[index]);
    }
}

void Tick::calcTick(const Tick &lastTick) {
    for (int y = 0; y < size_; ++y) {
        for (int x = 0; x < size_; ++x) {
            matrix[y][x] = judgeCell(x, y, lastTick);
        }
    }
}

bool Tick::judgeCell(const int &x, const int &y, const Tick &lastTick) {
    int neighborsCount = getNearCount(x, y, lastTick);

    if (!lastTick.matrix[y][x]) {
        if (neighborsCount != 3) {
            ++transitions[0]; // DD
            return false;
        } else {
            ++transitions[1]; // DL
            liveCells_["matrixCells"].append(y * size_ + x);
            return true;
        }
    } 

    if (neighborsCount < 2 || neighborsCount > 3) {
        ++transitions[2]; // LD
        return false;
    } else {
        ++transitions[3]; // LL
        liveCells_["matrixCells"].append(y * size_ + x);
        return true;
    }
}

int Tick::getNearCount(const int &x, const int &y, const Tick &lastTick) {
    const std::vector<std::vector<int>> bakedPos {{{1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}}};

    int count = 0;

    for (auto &pos : bakedPos) {

        if (x + pos[0] < 0 || x + pos[0] > size_ - 1) {
            continue;
        }

        if (y + pos[1] < 0 || y + pos[1] > size_ - 1) {
            continue;
        }

        if (lastTick.matrix[y + pos[1]][x + pos[0]]) {
            ++count;
        }
    }

    return count;
}
