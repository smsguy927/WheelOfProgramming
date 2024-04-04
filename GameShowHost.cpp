//
// Created by smsgu on 11/3/2022.
//


#include "GameShowHost.h"


#include <utility>


void GameShowHost::sayIntroduction() {

    std::cout << "Hello and welcome to the final program of Advanced C++" << std::endl;
    std::cout << "It's time for ..." << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Wheel" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Of" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Programming" << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "And here is the star of the show..." << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << this->getName() << '!' << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
}

GameShowHost::GameShowHost() {
    this->name = GS_HOST_DEFAULT_NAME;
}

[[maybe_unused]] GameShowHost::GameShowHost(std::string gsHostName) {
    this->name = std::move(gsHostName);
}

void GameShowHost::startGame(int gameSize, char gameMode) {
    this->game.setMaxTurns(MAX_TURNS[gameSize]);
    this->game.setMode(gameMode);
    int maxTurns = this->game.getMaxTurns();
    if(maxTurns == 0) {
        std::cout << "So you're a software tester, eh? " << std::endl;
    }
    std::cout << "Let's play for " << maxTurns <<" turns." << std::endl;
    this->game.setDefaultPlayers();
    this->game.generateRegularPuzzles();
    this->game.generateBonusPuzzles();

}
void GameShowHost::setName(std::string myName) {
    this->name = std::move(myName);
}
std::string GameShowHost::getName() {
    return this->name;
}

void GameShowHost::setGame(Game gm) {
    this->game = gm;
}

Game GameShowHost::getGame() {
    return this->game;
}

int GameShowHost::generateGameLength() {
    std::cout << "How long of a game do you want?" << std::endl;
    std::cout << "Press 1 for nano, 2 for micro, 3 for short," << std::endl;
    std::cout << "4 for regular, 5 for long, 6 for extreme," << std::endl;

    int gameLengthChoice = validate(0, 6);
    return gameLengthChoice;

}

char GameShowHost::askToExplainRules() {
    std::cout << "Do you want to explain the rules?" << std::endl;
    std::cout << "Press y for yes." << std::endl;
    char explain = static_cast<char>(tolower(std::cin.get()));
    return explain;
}

void GameShowHost::explainRules() {
    std::cout << "Here are the rules: There is a puzzle that is a string made up of dashes." << std::endl;
    std::cout << "Each dash represents a letter in the puzzle. You will fill in the letters" << std::endl;
    std::cout << "by spinning the wheel or buying a vowel, which is an a, e, i, o, or u." << std::endl;
    std::cout << "Vowels cost " << VOWEL_PRICE << ". There are 24" /* << Wheel::NUM_WEDGES << */" wedges on the wheel, each with a value," << std::endl;
    std::cout << "color, and special property. The special wedges include a jackpot, a special" << std::endl;
    std::cout << "prize, free spins, and even a wedge which shifts your score left one bit if" << std::endl;
    std::cout << "you can correctly guess a letter in the puzzle. Watch out for Bankrupt and" << std::endl;
    std::cout << "Lose a Turn. After you spin, you can guess a consonant. If it is in the puzzle," << std::endl;
    std::cout << "you get the value on the wedge multiplied by the number of the letter's" << std::endl;
    std::cout << "occurrence added to your score and your turn continues. If the letter is not in" << std::endl;
    std::cout << "the puzzle, your turn ends and control passes to the next player. Once enough" << std::endl;
    std::cout << "letters are filled in, you can try to solve the puzzle. Your answer must be an" << std::endl;
    std::cout << "exact match with no misplaced characters. If your answer is correct, you win" << std::endl;
    std::cout << "$500 and your score will be added to your final total and all other players" << std::endl;
    std::cout << "scores will be cleared. You should try to get a high score before solving," << std::endl;
    std::cout << "but don't get greedy. There are two Bankrupt wedges on the wheel. If you land" << std::endl;
    std::cout << "one of them, your current score will be set to 0 and your turn will end. " << std::endl;
    std::cout << "There is also a Lose a Turn wedge that will end your turn." << std::endl;
    std::cout << "At the end of the last round, the player with the highest final total will" << std::endl;
    std::cout << "advance to the bonus round. Are you ready? Let's play Wheel of Programming!" << std::endl;
    std::cout << std::endl << std::endl << std::endl;

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

void GameShowHost::introducePlayers() {

    std::cout << "Let's introduce our players." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Player 1, what's your name?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My name is " << this->game.getPlayer(P1_INDEX).getName() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "And what's your favorite Programming Language?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My favorite programming language is " << this->game.getPlayer(P1_INDEX).getFavoriteCodingLanguage() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Player 2, what's your name?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My name is " << this->game.getPlayer(P2_INDEX).getName() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "And what's your favorite Programming Language?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My favorite programming language is " << this->game.getPlayer(P2_INDEX).getFavoriteCodingLanguage() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "Player 3, what's your name?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My name is " << this->game.getPlayer(P3_INDEX).getName() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "And what's your favorite Programming Language?" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "My favorite programming language is " << this->game.getPlayer(P3_INDEX).getFavoriteCodingLanguage() << "." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
}

void GameShowHost::playGame() {

    std::cout << "Let's play!" << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    this->game.play();
}

char GameShowHost::generateGameMode() {
    announceGameModeChoices();
    char gameMode = validateGameMode();
    return gameMode;
}

char GameShowHost::validateGameMode() {
    char choice = NULL_CHAR;
    bool validChoice = false;
    std::cin >> choice;
    do {
        if (MODES.contains(choice)){
            validChoice = true;
        }
        else {
            std:: cout << "That's not a valid choice." << std::endl;
            announceGameModeChoices();
        }
    } while(!validChoice);
    return choice;
}

void GameShowHost::announceGameModeChoices() {
    std::cout << "What game mode do you want to play?" << std::endl;
    for (auto& [key, value]: MODES) {
        std::cout << "Press " << key << " for "  << value << std::endl;
    }
}


