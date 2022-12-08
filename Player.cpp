//
// Created by smsgu on 11/3/2022.
//

#include "Player.h"

#include <utility>



Player::Player(const PlayerInit& playerVals) {
    this->positionID = playerVals.positionID;
    this->colorID = playerVals.colorID;
    this->playerID = playerVals.playerID;
    this->color = playerVals.color;
    this->name = playerVals.name;
    this->favoriteCodingLanguage = playerVals.favoriteCodingLanguage;
    this->totalWinnings = playerVals.totalWinnings;
    this->freeSpins = playerVals.freeSpins;
    this->isReturningChampion = playerVals.isReturningChampion;
    this->previousWinnings = playerVals.previousWinnings;
}

Player::Player() {
    this->positionID = DEFAULT_INIT_VALUES.positionID;
    this->colorID = DEFAULT_INIT_VALUES.colorID;
    this->playerID = DEFAULT_INIT_VALUES.playerID;
    this->color = DEFAULT_INIT_VALUES.color;
    this->name = DEFAULT_INIT_VALUES.name;
    this->favoriteCodingLanguage = DEFAULT_INIT_VALUES.favoriteCodingLanguage;
    this->totalWinnings = DEFAULT_INIT_VALUES.totalWinnings;
    this->freeSpins = DEFAULT_INIT_VALUES.freeSpins;
    this->isReturningChampion = DEFAULT_INIT_VALUES.isReturningChampion;
    this->previousWinnings = DEFAULT_INIT_VALUES.previousWinnings;

}

void Player::setPositionID(int psID) {
    this->positionID = psID;
}

void Player::setColorID(int cID) {
    this->colorID = cID;
}

void Player::setPlayerID(int plID) {
    this->playerID = plID;
}

void Player::setColor(std::string c) {
    this->color = std::move(c);
}

void Player::setName(std::string n) {
    this->name = std::move(n);
}

void Player::setFavoriteCodingLanguage(std::string fcl) {
    this->favoriteCodingLanguage = std::move(fcl);
}

void Player::setTotalWinnings(int tw) {
    this->totalWinnings = tw;
}

void Player::setFreeSpins(int fs) {
    this->freeSpins = fs;
}

void Player::setIsReturningChampion(bool irc) {
    this->isReturningChampion = irc;
}

void Player::setPreviousWinnings(int pw) {
    this->previousWinnings = pw;
}

int Player::getPositionID() const {
    return this->positionID;
}

int Player::getColorID() const {
    return this->colorID;
}

int Player::getPlayerID() const {
    return this->playerID;
}

std::string Player::getColor() {
    return this->color;
}

std::string Player::getName() {
    return this->name;
}

std::string Player::getFavoriteCodingLanguage() {
    return this->favoriteCodingLanguage;
}

int Player::getTotalWinnings() const {
    return this->totalWinnings;
}

int Player::getFreeSpins() const {
    return this->freeSpins;
}

bool Player::getIsReturningChampion() const {
    return this->isReturningChampion;
}

int Player::getPreviousWinnings() const {
    return this->previousWinnings;
}

bool Player::operator>(const Player& p2) const {
    return this->totalWinnings > p2.totalWinnings;
}

bool Player::operator<(const Player & p2) const {
    return this->totalWinnings < p2.totalWinnings;
}

bool Player::operator>=(const Player & p2) const {
    return this->totalWinnings >= p2.totalWinnings;
}

bool Player::operator<=(const Player & p2) const {
    return this->totalWinnings <= p2.totalWinnings;
}

int Player::operator<=>(const Player & p2) const {
    return this->totalWinnings - p2.totalWinnings;
}

void Player::setAwesomePoints(int ap) {
    this->awesomePoints = ap;
}

int Player::getAwesomePoints() const {
    return awesomePoints;
}
