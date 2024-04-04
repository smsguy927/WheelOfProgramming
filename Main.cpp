#include <iostream>

#include "Game.h"


//#include "GameShowHost.h"
char getSecretHostNameChoice();
std::string getSecretHostName();






int main() {

    char playAgain = YES;
    do {
        Game game;
        game.setDefaultPlayers();
        game.generateRegularPuzzles();
        game.generateBonusPuzzles();
        game.play();
        char secretHostNameChoice = getSecretHostNameChoice();
        //GameShowHost gsHost;
        if(secretHostNameChoice == SECRET_HOST) {
            std::string secretHostName = getSecretHostName();
            //gsHost = GameShowHost(secretHostName);
        } else {
            //gsHost = GameShowHost();
        }
        if(secretHostNameChoice != SECRET_SKIP_INTRO){
            //gsHost.sayIntroduction();
        }

        int gameLength = 5;//GameShowHost::generateGameLength();
        char explainRules = NO; //GameShowHost::askToExplainRules();
        if (explainRules == YES) {
            //GameShowHost::explainRules();
        }
        char gameMode = 'l'; //gsHost.generateGameMode();
        //gsHost.startGame(gameLength, gameMode);
        if(secretHostNameChoice != SECRET_SKIP_INTRO) {
            //gsHost.introducePlayers();
        }


        //gsHost.playGame();

        std::cout << "Do you want to play again?" << std::endl;
        std::cout << "Press " << YES << " for yes." << std::endl;
        std::cin >> playAgain;
    } while (playAgain == 'y');
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

char getSecretHostNameChoice() {
    std::cout << "Press any key to continue..." << std::endl;

    char choice = static_cast<char>(tolower(std::cin.get()));
    return choice;
}

std::string getSecretHostName() {
    std::string myName;
    std::cout << "Hello, game show host. What is your name?" << std::endl;
    std::getline(std::cin >> std::ws, myName);
    return myName;
}
