//
// Created by smsgu on 11/4/2022.
//

#include "Turn.h"

Turn::Turn(TurnInit ti) {
    this->playerID = ti.playerID;
    this->turnID = ti.turnID;
    this->isFinalSpin = ti.isFinalSpin;
    this->isAfterFinalSpin = ti.isAfterFinalSpin;
    this->isExpress = ti.isExpress;
    this->turnResult = TurnResult::null;
}

void Turn::setPlayerID(int pID) {
    this->playerID = pID;
}

void Turn::setTurnID(int tID) {
    this->turnID = tID;
}

void Turn::setActionID(int aID) {
    this->actionID = aID;
}

void Turn::setActionTimeUsedMs(int atums) {
    this->actionTimeUsedMs = atums;
}

void Turn::setLetterTimeUsedMs(int ltums) {
    this->letterTimeUsedMs = ltums;
}

void Turn::setSolveTimeUsedMs(int stums) {
    this->solveTimeUsedMs = stums;
}

void Turn::setIsFinalSpin(bool isfs) {
    this->isFinalSpin = isfs;
}

void Turn::setIsAfterFinalSpin(bool isafs) {
    this->isFinalSpin = isafs;
}

void Turn::setIsExpress(bool ie) {
    this->isExpress = ie;
}

void Turn::setGuess(char g) {
    this->guess = g;
}

void Turn::setIsRareLetter(bool irl) {
    this->isRareLetter = irl;
}

void Turn::setTnSpinResult(SpinResult tsr) {
    this->tnSpinResult = tsr;
}

void Turn::setSolveAttempt(std::string sa) {
    this->solveAttempt = sa;
}

int Turn::getPlayerID() const {
    return this->playerID;
}

int Turn::getTurnID() const {
    return this->turnID;
}

int Turn::getActionID() const {
    return this->actionID;
}

int Turn::getActionTimeUsedMs() const {
    return this->actionTimeUsedMs;
}

int Turn::getLetterTimeUsedMs() const {
    return this->letterTimeUsedMs;
}

int Turn::getSolveTimeUsedMs() const {
    return this->solveTimeUsedMs;
}

bool Turn::getIsFinalSpin() const {
    return this->isFinalSpin;
}

bool Turn::getIsAfterFinalSpin() const {
    return this->isAfterFinalSpin;
}

bool Turn::getIsExpress() const {
    return this->isExpress;
}

char Turn::getGuess() const {
    return this->guess;
}

bool Turn::getIsRareLetter() const {
    return this->isRareLetter;
}

SpinResult Turn::getTnSpinResult() {
    return this->tnSpinResult;
}

SpinResult& Turn::getTnSpinResultRef() {
    return this->tnSpinResult;
}

std::string Turn::getSolveAttempt() {
    return this->solveAttempt;
}

Turn::Turn() {
    this->playerID = -5;
    this->turnID = -5;
    this->isFinalSpin = false;
    this->isAfterFinalSpin = false;
    this->isExpress = false;
    this->turnResult = TurnResult::null;
}

void Turn::setTurnResult(TurnResult tr) {
    this->turnResult = tr;
}

TurnResult Turn::getTurnResult() {
    return turnResult;
}

void Turn::setConsonantsFound(int c) {
    this->consonantsFound = c;
}

int Turn::getConsonantsFound() const {
    return this->consonantsFound;
}

void Turn::setTurnAction(TnAction ta) {
    this->turnAction = ta;
}

TnAction Turn::getTurnAction() {
    return this->turnAction;
}

bool Turn::shouldEvaluateGuess() {
    if(tnSpinResult.getIsTurnEnding()){
        return false;
    }
    TnAction action = getTurnAction();
    return action == TnAction::spin || action == TnAction::vowel || action == TnAction::fsConsonant||
    action == TnAction::fsVowel || action == TnAction::express || action == TnAction::expressVowel;
}

void Turn::setSolveResult(SolveResult sr) {
    this->solveResult = sr;
}

SolveResult Turn::getSolveResult() {
    return solveResult;
}


