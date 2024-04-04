#ifndef WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H
#define WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H


#include <string>
#include <chrono>
#include <iostream>
#include <utility>


#include "JrdTimerUtils.h"
#include "Player.h"
//

const std::string GS_HOST_DEFAULT_NAME = "Mr. Roboto";

class GameShowHost {
public:
    GameShowHost();

    void setName(std::string);


    std::string getName();


    explicit GameShowHost(std::string);
    void sayIntroduction();
    static int generateGameLength();
    static char askToExplainRules();
    static void explainRules();
    //void startGame(int, char);
    static void introducePlayers(std::array<Player, NUM_PLAYERS>);
    static void announcePlay();
    static char generateGameMode();
    static char validateGameMode();
    static void announceGameModeChoices();
private:
    std::string name;


};


#endif //WHEELOFPROGRAMMINGCL_GAMESHOWHOST_H

