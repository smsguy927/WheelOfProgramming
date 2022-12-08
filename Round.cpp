//
// Created by smsgu on 11/4/2022.
//

#include "Round.h"

#include <utility>

std::vector<Round> allRounds;

Round::Round(const RoundInit& ri) {
    this->playerScores = ri.playerScores;
    this->puzzleR = ri.puzzle;
    this->maxTurnsR = ri.maxTurns;
    this->currentTurnR = ri.currentTurn;
    this->currentTurnPlayerIDR = ri.currentTurnPlayerID;
    this->currentRoundR = ri.currentRound;
    this->currentRoundTurnR = ri.currentRoundTurn;
    this->currentRoundTypeIDR = ri.currentRoundTypeID;
    this->startingPlayerID = ri.startingPlayerID;
    allRounds.push_back(*this);
}

Round::Round() = default;

void Round::setPlayerScores(std::vector<PlayerScore> ps) {
    this->playerScores = std::move(ps);
}

void Round::setPlayerScore(PlayerScore ps, int i) {
    this->playerScores[i] = ps;
}

void Round::setPuzzle(Puzzle pz) {
    this->puzzleR = std::move(pz);
}

void Round::setMaxTurnsR(int mt) {
    this->maxTurnsR = mt;
}

void Round::setCurrentTurnR(int ct) {
    this->currentRoundTurnR = ct;
}

void Round::setCurrentTurnPlayerIDR(int ctpID) {
    this->currentTurnPlayerIDR = ctpID;
}

void Round::setCurrentRoundR(int cr) {
    this->currentRoundR = cr;
}

void Round::setCurrentRoundTurnR(int crt) {
    this->currentRoundTurnR = crt;
}

void Round::setCurrentRoundTypeIDR(int crtID) {
    this->currentRoundTypeIDR = crtID;
}

std::vector<PlayerScore> Round::getPlayerScores() {
    return this->playerScores;
}

std::vector<PlayerScore>& Round::getPlayerScoresRef() {
    return this->playerScores;
}

PlayerScore Round::getPlayerScore(int i) {
    return this->playerScores[i];
}

PlayerScore& Round::getPlayerScoreRef(int i) {
    return this->playerScores[i];
}

int Round::getMaxTurnsR() const {
    return this->maxTurnsR;
}

int Round::getCurrentTurnR() const {
    return this->currentTurnR;
}

int Round::getCurrentTurnPlayerIDR() const {
    return this->currentTurnPlayerIDR;
}

int Round::getCurrentRoundR() const {
    return this->currentRoundR;
}

int Round::getCurrentRoundTurnR() const {
    return this->currentRoundTurnR;
}

int Round::getCurrentRoundTypeIDR() const {
    return this->currentRoundTypeIDR;
}

Puzzle Round::getPuzzleR() {
    return this->puzzleR;
}

void Round::setStartingPlayerID(int spID) {
    this->startingPlayerID = spID;
}

int Round::getStartingPlayerID() {
    return startingPlayerID;
}







