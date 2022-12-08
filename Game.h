//
// Created by smsgu on 10/31/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_GAME_H
#define WHEELOFPROGRAMMINGCL_GAME_H

#pragma once
#include <array>
#include <vector>
#include <utility>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <thread>
#include "Player.h"
#include "Puzzle.h"
#include "Round.h"
#include "Turn.h"
#include "BonusRound.h"
#include "Wheel.h"
#include "JrdTimerUtils.h"
#include "BonusRound.h"
#include "GameMode.h"

enum class GameSize
{
    testing,
    nano,
    micro,
    shorts, // short is a reserved word
    medium,
    longs, // long is a reserved word
    extreme
};



const std::chrono::duration<int, std::milli> oneSecInMs(1000);

const char YES = 'y';
const char NO = 'n';
const char NULL_CHAR = '!';


const int GAME_SIZES = 7;
const int NUM_PLAYERS = 3;

const int SOLVE_BONUS = 500;
const int FINAL_SPIN_BONUS = 1000;

const int PRIZE_VALUE = 8192;
const int GAME_NULL_INT = -555;

const int BIT_SHIFTER_RIGHT = 1;
const int BIT_SHIFTER_WRONG = 2;

const std::pair<int, int> EXPRESS_TURN_FRACTION{2,3};

const std::string PUZZLES_FILENAME = "Puzzles.txt";
const std::string BONUS_FILENAME = "BonusPuzzles.txt";


const std::array<int, int(GameSize::extreme) + 1>MAX_TURNS{0, 10, 20, 30,50,70,100};


class Game {
public:
    Game();
    void setMaxTurns(int);
    void setCurrentTurn(int);
    void setCurrentTurnPlayerID(int);
    void setCurrentRound(int);
    void setCurrentRoundTurn(int);
    void setCurrentRoundTypeID(int);

    void setIsAfterFinalSpin(bool);
    void setIsExpress(bool);
    void setPlayers(std::array<Player, NUM_PLAYERS>);
    void setPlayer(Player, int);
    void setDefaultPlayers();
    void setPuzzles(std::vector<Puzzle>);
    void setPuzzle(Puzzle, int);
    void setRounds(std::vector<Round>);
    void setRound(Round, int);
    void setTurns(std::vector<Turn>);
    void setTurn(Turn, int);
    void setWheels(std::vector<Wheel>);
    void setWheel(Wheel, int);
    void play();
    void playRound();
    void incrementTurn();
    void passTurn();
    [[nodiscard]] int calcStartPlayer() const;
    [[nodiscard]] TurnInit generateTurnInit() const;


    [[nodiscard]] int getMaxTurns() const;
    [[nodiscard]] int getCurrentTurn() const;
    [[nodiscard]] int getCurrentTurnPlayerID() const;
    [[nodiscard]] int getCurrentRound() const;
    [[nodiscard]] int getCurrentRoundTurn() const;
    [[nodiscard]] int getCurrentRoundTypeID() const;

    [[nodiscard]] bool getIsAfterFinalSpin() const;
    [[nodiscard]] bool getIsExpress() const;
    std::array<Player, NUM_PLAYERS> getPlayers();
    Player getPlayer(int);
    Player& getPlayerRef(int);
    std::vector<Puzzle> getPuzzles();
    std::vector<Puzzle>& getPuzzlesRef();
    Puzzle getPuzzle(int);
    Puzzle& getPuzzleRef(int);
    std::vector<Round> getRounds();
    std::vector<Round>& getRoundsRef();
    Round getRound(int);
    Round& getRoundRef(int);
    std::vector<Turn> getTurns();
    std::vector<Turn>& getTurnsRef();
    Turn getTurn(int);
    Turn& getTurnRef(int);
    std::vector<Wheel> getWheels();
    std::vector<Wheel>& getWheelsRef();
    Wheel getWheel(int);
    Wheel& getWheelRef(int);

    void generateRegularPuzzles();
    void generateBonusPuzzles();
    Round generateNewRound();
    Puzzle selectPuzzle();
    Puzzle& getPuzzleRef();
    void displayActionChoices();
    bool noMoreConsonantsInCurrentRound();
    bool noMoreVowelsInCurrentRound();
    bool cannotSpin();
    bool cannotBuyAVowel();
    bool cannotAffordAVowel();
    int getCurrentPlayerCash();
    std::pair<int, int>generateActionChoice();
    void handleSpin();
    void handleBuyAVowel();
    void handleSolve();

    void bankrupt();
    char generateFreeSpinChoice();
    static bool isUsingFreeSpin(char);
    bool hasFreeSpins();
    void useFreeSpin();

    void setCurrentPlayerFreeSpins(int);
    int getCurrentPlayerFreeSpins();

    void displayUsedConsonants();
    void displayUsedVowels();
    void displayPuzzle();

    std::string getUsedConsonants();
    std::string getUsedVowels();
    std::string getPuzzleView();

    PlayerScore getCurrentPlayerScore();
    PlayerScore& getCurrentPlayerScoreRef();

    char generateGuess();


    char validateConsonantOrVowel();

    void evaluateGuess();


    char getGuess();

    void respondToGuessResult(int);
    void applySpinSpecialEffects();
    void applySpinEffects();
    Turn& getCurrentTurnRef();
    SpinResult& getCurrentSpinResultRef();
    void addFreeSpin();
    void positiveBitShift();
    void negativeBitShift();
    void subtractVowelPrice();
    void checkAndSetIsPuzzleSolved();
    static bool isPuzzleSolved(Puzzle&);
    void handleRoundEnd();
    void handleMainGameEnd();
    static std::string generateSolveAttempt();
    static bool isWrong(Turn& );
    void evaluateAction(TnAction);
    void displayFinalSpinAction();
    void setFinalSpinValue(int);
    [[nodiscard]] int getFinalSpinValue() const;
    void handleFinalSpin();
    [[nodiscard]] bool isTimeForFinalSpin() const;
    void handleFinalSpinLetter();
    void applyFinalSpinEffects();
    int determineWinner();
    void generateBonusRound();
    BonusRoundInit generateBonusRoundInit();
    void setWinningPlayerID(int);
    [[nodiscard]] int getWinningPlayerID() const;
    void setBonusRound(BonusRound);
    BonusRound getBonusRound();
    BonusRound& getBonusRoundRef();
    void handleExpress();
    static char generateStartExpressChoice();
    void handleExpressLetter();
    void displayExpressAction();
    char validatePuzzleCharacter();
    void handleExpressEnd();
    static int calcExpressMaxTurnsAdjustment(int);
    bool isOutOfPuzzles();
    void handleOutOfPuzzles();
    void handleTurnEnd(Turn &);
    std::pair<int, int>assignActionChoice();
    bool isValidActionChoice(int);
    bool canSpin();
    bool canBuyAVowel();
    void setMode(char);
    GameMode& getGameModeRef();
    static bool isOutOfTime(Turn &);
    bool isInTime();


private:
    int maxTurns{};
    int currentTurn{};
    int currentTurnPlayerID{};
    int currentRound{};
    int currentRoundTurn{};
    int currentRoundTypeID{};
    int expressTurnLength{GAME_NULL_INT};
    bool isAfterFinalSpin{};
    bool isExpress{};
    int finalSpinValue{};
    int firstPlayer{0};
    GameMode mode;
    std::array<Player, NUM_PLAYERS> players;
    std::vector<Puzzle> puzzles;
    std::vector<Puzzle> bonusPuzzles;
    std::vector<Round> rounds;
    std::vector<Turn> turns;
    std::vector<Wheel> wheels;
    int winningPlayerID{GAME_NULL_INT};
    BonusRound bonusRound;

    static void introducePuzzle(Puzzle &currentPuzzle) ;


    void playTurn();
};


#endif //WHEELOFPROGRAMMINGCL_GAME_H
