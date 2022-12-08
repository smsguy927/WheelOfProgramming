#ifndef WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H
#define WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H


#include <string>
#include <chrono>
#include <iostream>
#include <utility>
#include "Game.h"

#include "JrdTimerUtils.h"
#include "GameMode.h"

const std::string GS_HOST_DEFAULT_NAME = "Mr. Roboto";

class GameShowHost {
public:
    GameShowHost();

    void setName(std::string);
    void setGame(Game);

    std::string getName();
    Game getGame();

    explicit GameShowHost(std::string);
    void sayIntroduction();
    static int generateGameLength();
    static char askToExplainRules();
    static void explainRules();
    void startGame(int, char);
    void introducePlayers();
    void playGame();
    static char generateGameMode();
    static char validateGameMode();
    static void announceGameModeChoices();
private:
    std::string name;
    Game game;

};


#endif //WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H

