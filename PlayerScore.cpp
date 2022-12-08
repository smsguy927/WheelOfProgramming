//
// Created by smsgu on 11/7/2022.
//

#include "PlayerScore.h"

std::vector<PlayerScore> allScores;

PlayerScore::PlayerScore(PlayerScoreInit psi) {
    this->playerID = psi.playerID;
    this->roundID = psi.roundID;
    this->freeSpins = psi.freeSpins;
    allScores.push_back(*this);
}

PlayerScore::PlayerScore() = default;

void PlayerScore::setPlayerID(int pID) {
    this->playerID = pID;
}

void PlayerScore::setRoundID(int rID) {
    this->roundID = rID;
}

void PlayerScore::setCash(int c) {
    this->cash = c;
}

void PlayerScore::setHasPrize(bool hp) {
    this->hasPrize = hp;
}

void PlayerScore::setHasJackpot(bool hj) {
    this->hasJackpot = hj;
}

void PlayerScore::setFreeSpins(int fs) {
    this->freeSpins = fs;
}

void PlayerScore::setIsSolver(bool s) {
    this->isSolver = s;
}

int PlayerScore::getPlayerID() {
    return this->playerID;
}

int PlayerScore::getRoundID() {
    return this->roundID;
}

int PlayerScore::getCash() {
    return this->cash;
}

bool PlayerScore::getHasPrize() {
    return this->hasPrize;
}

bool PlayerScore::getHasJackpot() {
    return this->hasJackpot;
}

int PlayerScore::getFreeSpins() {
    return this->freeSpins;
}

bool PlayerScore::getIsSolver() {
    return this->isSolver;
}




