//
// Created by smsgu on 10/31/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_PUZZLE_H
#define WHEELOFPROGRAMMINGCL_PUZZLE_H
#include <iostream>
#include <array>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <stdexcept>
#include <chrono>
#include <random>
#include "JrdTimerUtils.h"

// Puzzle Record Structure
enum class PzFields
{
    puzzleID,
    typeID,
    solution,
    categoryID
};
const auto isMapValueZero = [](const auto& p) { return p.second == 0; };
const int NUM_ROUNDS = 36;
const int NUM_CATEGORIES = 7;
const int NUM_TYPES = 3;
const int NUM_FIELDS = 4;
const int REPEAT_GUESS = -1;
const int PZ_ERROR = -123;
const std::string PZ_CONSONANTS = "bcdfghjklmnpqrstvwxyz";
const std::string PZ_VOWELS = "aeiou";
const std::string PZ_RARE_LETTERS = "jqxz";
const char PZ_BLANK = '*';
const char PZ_SPACE = ' ';
const char PZ_FIELD_SEP = '%';
const std::array<std::string, NUM_CATEGORIES> CATEGORY{ "Thing", "Before & After", "Place", "What are you doing?", "Phrase", "Same Name", "Person" };
const std::array<std::string, NUM_TYPES> TYPE{"Normal", "Bonus Round", "Tiebreaker"};


class Puzzle
{
public:

    void setPuzzleID(int);
    void setCategoryID(int);
    void setTypeID(int);
    void setCategory(std::string);
    void setType(std::string);
    void setSolution(std::string);
    void setDisplay(std::string);
    void setIsSolved(bool);
    void setUsedConsonants(std::map<char,bool>);
    void setUsedVowels(std::map<char,bool>);
    void setFoundConsonants(std::map<char,int>);
    void setFoundVowels(std::map<char,int>);
    explicit Puzzle(std::string&);
    Puzzle();

    [[nodiscard]] int getPuzzleID() const;
    [[nodiscard]] int getCategoryID() const;
    [[nodiscard]] int getTypeID() const;
    std::string getCategory();
    std::string getType();
    std::string getSolution();
    std::string getDisplay();
    [[nodiscard]] bool getIsSolved() const;
    std::map<char,bool> getUsedConsonants();
    std::map<char,bool> getUsedVowels();
    std::map<char,int> getFoundConsonants();
    std::map<char,int> getFoundVowels();

    int evaluateGuess(char);
    [[nodiscard]] bool isCorrectSolution(const std::string&) const;
    [[nodiscard]] bool isGuessed(char) const;
    void revealDisplayLetters(char);
    bool areNoConsonantsLeft();
    bool areNoVowelsLeft();
    std::string getUsedConsonantStr();
    std::string getUsedVowelStr();

    static bool isPzVowel(char);
    static bool isPzConsonant(char);
    static bool isPzRareLetter(char);

    void applyGuessResult(char);
    char validateConsonant();
    char validateVowel();
    static void rareLetterResponse(char);
    [[nodiscard]] bool getIsPuzzleRevealed() const;


    void setUsedLetter(char);
    void setUsedLetters(const std::string&);

private:


    int puzzleID{};
    int typeID{};
    int categoryID{};
    bool isPuzzleRevealed{false};

    std::string category;
    std::string type;
    std::string solution;
    std::string display;
    bool isSolved{};
    std::map<char,bool> usedConsonants; // TODO: should this be an array instead?
    std::map<char,bool> usedVowels; // TODO: should this be an array instead?
    std::map<char,int> foundConsonants;
    std::map<char,int> foundVowels;

    static std::string toDisplay(std::string);
    void generateUsedConsonants();
    void generateUsedVowels();
    static std::vector<std::string> split(std::string record);


    void generateFoundConsonants();
    void generateFoundVowels();


    void displayUsedConsonants();
    void displayUsedVowels();
};


#endif //WHEELOFPROGRAMMINGCL_PUZZLE_H