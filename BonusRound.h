//
// Created by smsgu on 11/4/2022.
//

#ifndef WHEELOFPROGRAMMINGTEST_BONUSROUND_H
#define WHEELOFPROGRAMMINGTEST_BONUSROUND_H

#include <string>

#include "Puzzle.h"
#include "Player.h"
#include "JrdTimerUtils.h"
#include "GameMode.h"

const std::string BONUS_GIVEN_LETTERS{"rstlne"}; // Do not change this order
const int BASE_BONUS_CONSONANTS = 3;
const int BASE_BONUS_VOWELS = 1;
const int BASE_TIME_LIMIT_MS = 30000;
const int BASE_MAX_GUESS = 5;

// These may change in the future
const std::string BONUS_PRIZE_NAME{"Cash"};
const int BONUS_PRIZE_VALUE = 32768;

struct BonusRoundInit {
    int playerID{};
    Player player;
    int bonusConsonants{};
    int bonusVowels{};
    Puzzle puzzle;
    GameMode gameMode;
};

class BonusRound {
public:
    explicit BonusRound(const BonusRoundInit&);
    BonusRound();

    void play();
    void introducePuzzle();
    void giveDefaultLetters();
    void revealLetters(const std::string&);
    void chooseLetters();
    void revealChosenLetters();
    void displayPuzzle();
    void solveWithMaxGuesses();
    void addPrizeToWinnings();
    void displayBonusRoundResults();
    void solveWithTimeLimit();
    void solvePuzzle();
    [[nodiscard]] bool hasTimeLeft() const;
    [[nodiscard]] int calcTimeLimitSeconds() const;
    [[nodiscard]] long long calcTimeRemainingMs() const;
    [[nodiscard]] int calcTimeRemainingSecondsRounded() const;
    [[nodiscard]] int calcTimeRemainingSecondsFloored() const;
    [[nodiscard]] double calcTimeRemainingSecondsExact() const;
    [[nodiscard]] long long calcTimeOverLimitMs() const;
    [[nodiscard]] double calcTimeOverLimitSecondsExact() const;
private:
    int playerID{0};
    Player player;
    std::string prizeName; // Not used, always BONUS_PRIZE_NAME now.
    int prizeValue{0}; // Not used, always BONUS_PRIZE_VALUE now.
    std::string chosenLetters;
    int bonusConsonants{0};
    int bonusVowels{0};
    long long timeUsedMs{0};
    long long timeLimitMs{BASE_TIME_LIMIT_MS};
    bool isWon{false};
    std::vector<std::string> attempts;
    Puzzle puzzle;
    GameMode gameMode;
};


#endif //WHEELOFPROGRAMMINGTEST_BONUSROUND_H
