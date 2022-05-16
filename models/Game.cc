#include "Game.h"

void Game::setTick(const int &tick) {
    if (tick == 0) {
        ticks.push_back(Tick(size_));
        ticks.back().setCells(liveCells_);
    } else {
        ticks.push_back(Tick(size_));
        ticks.back().calcTick(ticks[tick - 1]);
    }

    ticks.back().liveCells_["tickNumber"] = tick;
}

Game::Game (const int &size, const int &ticksNumber, const Json::Value &liveCells) : 
    size_(size), liveCells_(liveCells) {
    json["ticks"] = Json::arrayValue;

    for (int tick = 0 ; tick < ticksNumber ; ++tick) {
        setTick(tick);
        json["ticks"].append(ticks[tick].liveCells_);
    }
}
