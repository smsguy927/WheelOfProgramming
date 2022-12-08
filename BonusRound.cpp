//
// Created by smsgu on 11/4/2022.
//

#include <iostream>
#include <ratio>
#include <chrono>
#include "BonusRound.h"
#include "Game.h"

BonusRound::BonusRound(const BonusRoundInit& bri) {
    this->playerID = bri.playerID;
    this->player = bri.player;
    this->prizeName = BONUS_PRIZE_NAME;
    this->prizeValue = BONUS_PRIZE_VALUE;
    this->bonusConsonants = bri.bonusConsonants;
    this->bonusVowels = bri.bonusVowels;
    this->puzzle = bri.puzzle;
    this->gameMode = bri.gameMode;
}

void BonusRound::play() {

    introducePuzzle();
    giveDefaultLetters();
    chooseLetters();
    revealChosenLetters();
    displayPuzzle();
    solvePuzzle();
    displayBonusRoundResults();

}

void BonusRound::introducePuzzle() {
    //std::chrono::duration<int, std::milli> oneSecInMs(1000);
    std::cout << "Each " << PZ_BLANK  << " represents one letter in the puzzle" << std::endl;
    std::cout << "The category is: " << puzzle.getCategory() << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);

    std::cout << "\t" << puzzle.getDisplay() << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
}

void BonusRound::giveDefaultLetters() {
    std::cout << "You will be given the following letters: " << std::endl;
    std::cout << BONUS_GIVEN_LETTERS << std::endl;
    std::cout << "Let's display them in the puzzle." << std::endl;
    revealLetters(BONUS_GIVEN_LETTERS);
    puzzle.setUsedLetters(BONUS_GIVEN_LETTERS);
    std::cout << std::endl << std::endl;
    std::cout << puzzle.getDisplay();
    std::cout << std::endl << std::endl;
}

void BonusRound::revealLetters(const std::string& letters) {
    for(char letter : letters){
        puzzle.revealDisplayLetters(letter);
    }
}

void BonusRound::chooseLetters() {
    std::cout << "You also get " << bonusConsonants << " consonants and " << bonusVowels << " vowel." << std::endl;
    for(int i = 0; i < bonusConsonants; i++) {
        char letter = puzzle.validateConsonant();
        puzzle.setUsedLetter(letter);
        chosenLetters.push_back(letter);
    }
    for(int i = 0; i < bonusVowels; i++) {
        char letter = puzzle.validateVowel();
        puzzle.setUsedLetter(letter);
        chosenLetters.push_back(letter);
    }

}

void BonusRound::revealChosenLetters() {
    revealLetters(chosenLetters);
}

void BonusRound::displayPuzzle() {
    std::cout << puzzle.getDisplay();
}

void BonusRound::solveWithMaxGuesses() {
    std::cout << "You have " << BASE_MAX_GUESS << " chances." << std::endl;
    std::cout << "There is no time limit. Good Luck!" << std::endl;
    int chancesLeft = BASE_MAX_GUESS;
    for(int i = 0; i < BASE_MAX_GUESS; i++) {
        displayPuzzle();
        std::cout << std::endl;
        std::string attempt = Game::generateSolveAttempt();
        attempts.push_back(attempt);
        chancesLeft--;
        if(puzzle.isCorrectSolution(attempt)){
            puzzle.setDisplay(attempt);

            std::cout << "That's right!" << std::endl;
            isWon = true;
            return;
        } else if(chancesLeft > 1) {
            std::cout << "Wrong. Try again, you have " << chancesLeft <<" more chances." << std::endl;

        } else if(chancesLeft) {
            std::cout << "Wrong. Try again, you have 1 more chance" << std::endl;

        } else {
            std::cout << "Wrong." << std::endl;
            std::cout << "The correct answer is " << puzzle.getSolution() << std::endl;
        }
    }

}

void BonusRound::addPrizeToWinnings() {
    player.setTotalWinnings(player.getTotalWinnings() + prizeValue);
}

void BonusRound::displayBonusRoundResults() {
    if(isWon) {
        std::cout <<"Congratulations! You won the bonus prize, " << prizeName << " worth $" << prizeValue << std::endl;
        addPrizeToWinnings();
    } else {
        std::cout <<"You did not win the bonus prize, " << prizeName << " worth $" << prizeValue << std::endl;
    }
    std::cout << "Your grand total is $" << player.getTotalWinnings() << std::endl;
    std::cout << "Thanks for playing." << std::endl;
}

void BonusRound::solveWithTimeLimit() {
    std::cout << std::endl;
    if(puzzle.getIsPuzzleRevealed()) {
        std::cout << "All the letters in the puzzle have been revealed!" << std::endl;
        displayPuzzle();
        isWon = true;
        return;
    }
    std::cout << "You have " << calcTimeLimitSeconds() << " seconds." << std::endl;
    std::cout << "Good Luck!" << std::endl;
    auto jrdTimer = JrdTimer();
    while(timeUsedMs < timeLimitMs) {
        displayPuzzle();
        std::cout << std::endl;
        std::string attempt = Game::generateSolveAttempt();
        attempts.push_back(attempt);
        timeUsedMs = jrdTimer.Elapsed().count();

        if(puzzle.isCorrectSolution(attempt) && hasTimeLeft()){
            puzzle.setDisplay(attempt);

            double timeLeft = calcTimeRemainingSecondsExact();
            std::cout << "That's right!" << std::endl;
            std::cout << "You did it with " << timeLeft <<" seconds to spare." << std::endl;
            isWon = true;
            return;
        } else if(hasTimeLeft()) {
            int timeLeft = calcTimeRemainingSecondsRounded();
            std::cout << "Wrong. Try again, you have about " << timeLeft <<" seconds left." << std::endl;

        } else if(puzzle.isCorrectSolution(attempt)) {
            double timeOverLimit = calcTimeOverLimitSecondsExact();
            std::cout << "That's right but it is " << timeOverLimit <<  " seconds too late." << std::endl;

        } else {
            std::cout << "Wrong." << std::endl;
            std::cout << "The correct answer is " << puzzle.getSolution() << std::endl;
        }
    }

}

int BonusRound::calcTimeLimitSeconds() const {
    return static_cast<int>(timeLimitMs) / MS_PER_SECOND;
}

bool BonusRound::hasTimeLeft() const {
    return timeUsedMs < timeLimitMs;
}

long long BonusRound::calcTimeRemainingMs() const {
    return timeLimitMs - timeUsedMs;
}

int BonusRound::calcTimeRemainingSecondsRounded() const {
    return static_cast<int>(std::round(static_cast<double>(timeLimitMs - timeUsedMs) / MS_PER_SECOND * 1.0));
}

int BonusRound::calcTimeRemainingSecondsFloored() const {
    return static_cast<int>(timeLimitMs - timeUsedMs / MS_PER_SECOND);
}

long long BonusRound::calcTimeOverLimitMs() const {
    return timeUsedMs - timeLimitMs;
}

double BonusRound::calcTimeOverLimitSecondsExact() const {
    return static_cast<double>(calcTimeOverLimitMs()) / MS_PER_SECOND;
}

double BonusRound::calcTimeRemainingSecondsExact() const {
    return static_cast<double>(calcTimeRemainingMs()) / MS_PER_SECOND;
}

void BonusRound::solvePuzzle() {
    if(gameMode.getName() == "Light"){
        solveWithMaxGuesses();
    } else {
        solveWithTimeLimit();
    }
}

BonusRound::BonusRound() = default;
