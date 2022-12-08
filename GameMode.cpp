//
// Created by smsgu on 12/7/2022.
//

#include "GameMode.h"

GameMode::GameMode(char gm) {

    if(MODES.contains(gm)) {
        symbol = gm;
        name = MODES.at(gm);
    }
}

GameMode::GameMode() {
    symbol = '!';
    name = "";
}

char GameMode::getSymbol() const {
    return symbol;
}

std::string GameMode::getName() {
    return name;
}
