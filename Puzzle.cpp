//
// Created by smsgu on 10/31/2022.
//

#include "Puzzle.h"



std::vector<Puzzle>allPuzzles;

void Puzzle::setPuzzleID(int num) {
    this->puzzleID = num;
}

void Puzzle::setCategoryID(int num) {
    this->categoryID = num;
}

void Puzzle::setTypeID(int num) {
    this->typeID = num;
}

void Puzzle::setCategory(std::string str) {
    this->category = std::move(str);
}

void Puzzle::setType(std::string str) {
    this->type = std::move(str);
}

void Puzzle::setSolution(std::string str) {
    this->solution = std::move(str);
}

void Puzzle::setDisplay(std::string str) {
    this->display = std::move(str);
}

int Puzzle::getPuzzleID() const {
    return this->puzzleID;
}

int Puzzle::getTypeID() const {
    return this->typeID;
}

int Puzzle::getCategoryID() const {
    return this->categoryID;
}

std::string Puzzle::getCategory() {
    return this->category;
}

std::string Puzzle::getType() {
    return this->type;
}

std::string Puzzle::getSolution() {
    return this->solution;
}

std::string Puzzle::getDisplay() {
    return this->display;
}

Puzzle::Puzzle(std::string& record) {
    std::vector<std::string> puzzleFields = split(record);
    this->puzzleID = stoi(puzzleFields[0]);
    this->typeID = stoi(puzzleFields[1]);
    this->solution = puzzleFields[2].substr(0);
    this->display = toDisplay(this->solution);
    this->isSolved = false;
    this->categoryID = stoi(puzzleFields[3]);
    this->category = CATEGORY[this->categoryID];
    this->type = TYPE[this->typeID];
    generateUsedConsonants();
    generateUsedVowels();
    generateFoundConsonants();
    generateFoundVowels();

}

std::vector<std::string> Puzzle::split(std::string record) {
    std::vector<std::string> result;
    int  i = 0;
    int startIndex = 0;
    while (i <= record.length())
    {
        if (record[i] == PZ_FIELD_SEP || i == record.length())
        {
            std::string field = record.substr(startIndex, i - startIndex);
            result.push_back(field);
            startIndex = i + 1;
        }
        i++;
    }
    return result;
}

std::string Puzzle::toDisplay(std::string text) {
    std::string resultText = std::move(text);
    for (char & i : resultText) {
        if(isalpha(i)) {
            i = PZ_BLANK;
        }
    }
    return resultText;
}

void Puzzle::generateUsedConsonants() {

    for (char i : PZ_CONSONANTS) {
        this->usedConsonants[i] = false;
    }

}

void Puzzle::generateUsedVowels() {
    for (char i : PZ_VOWELS) {
        this->usedVowels[i] = false;
    }
}

void Puzzle::generateFoundConsonants() {
    for(char letter : this->solution) {
        if(isPzConsonant(letter)) {
            if(foundConsonants.find(letter) == foundConsonants.end()) {
                foundConsonants[letter] = 1;
            } else {
                foundConsonants[letter]++;
            }
        }
    }
}

void Puzzle::generateFoundVowels() {
    for(char letter : this->solution) {
        if(isPzVowel(letter)) {
            if(foundVowels.find(letter) == foundVowels.end()) {
                foundVowels[letter] = 1;
            } else {
                foundVowels[letter]++;
            }
        }
    }
}

bool Puzzle::isPzVowel(char letter) {
    auto it = std::find(PZ_VOWELS.begin(), PZ_VOWELS.end(), letter);
    return it != PZ_VOWELS.end();
}

bool Puzzle::isPzConsonant(char letter) {
    auto it = std::find(PZ_CONSONANTS.begin(), PZ_CONSONANTS.end(), letter);
    return it != PZ_CONSONANTS.end();
}

bool Puzzle::isPzRareLetter(char letter) {
    auto it = std::find(PZ_RARE_LETTERS.begin(), PZ_RARE_LETTERS.end(), letter);
    return it != PZ_RARE_LETTERS.end();;
}

std::map<char, bool> Puzzle::getUsedConsonants() {
    return this->usedConsonants;
}

std::map<char, bool> Puzzle::getUsedVowels() {
    return this->usedVowels;
}

std::map<char, int> Puzzle::getFoundConsonants() {
    return this->foundConsonants;
}

std::map<char, int> Puzzle::getFoundVowels() {
    return this->foundVowels;
}

void Puzzle::setUsedConsonants(std::map<char, bool> charMap) {
    this->usedConsonants = std::move(charMap);
}

void Puzzle::setUsedVowels(std::map<char, bool> charMap) {
    this->usedVowels = std::move(charMap);
}

void Puzzle::setFoundConsonants(std::map<char, int> charMap) {
    this->foundConsonants = std::move(charMap);
}

void Puzzle::setFoundVowels(std::map<char, int> charMap) {
    this->foundVowels = std::move(charMap);
}

int Puzzle::evaluateGuess(char guess) {
    if (isGuessed(guess)) {
        return REPEAT_GUESS;
    }
    if (isPzVowel(guess))
    {
        return this->foundVowels[guess];
    }
    else if (isPzConsonant(guess))
    {
        return this->foundConsonants[guess];
    }
    else {
        return PZ_ERROR;
    }

}

bool Puzzle::isCorrectSolution(const std::string& attempt) const {
    return attempt == this->solution;
}

bool Puzzle::isGuessed(char guess) const {
    return isPzConsonant(guess) && usedConsonants.at(guess) || isPzVowel(guess) && usedVowels.at(guess);
}

void Puzzle::revealDisplayLetters(char guess) {
    for(int i = 0; i < this->solution.length(); i++) {
        if (this->solution[i] == guess) {
            this->display[i] = guess;
        }
    }
    if (solution == display) {
        isPuzzleRevealed = true;
    }
}

void Puzzle::setIsSolved(bool s) {
    this->isSolved = s;
}

bool Puzzle::getIsSolved() const {
    return this->isSolved;
}

bool Puzzle::areNoConsonantsLeft() {
    return std::all_of(this->foundConsonants.begin(), this->foundConsonants.end(), isMapValueZero);
}

bool Puzzle::areNoVowelsLeft() {
    return std::all_of(this->foundVowels.begin(), this->foundVowels.end(), isMapValueZero);
}

std::string Puzzle::getUsedConsonantStr() {
    std::string result;
    for (auto& [key, val]: this->usedConsonants) {
        if(val) {
            result.push_back(key);
        }
    }
    return result;
}

std::string Puzzle::getUsedVowelStr() {
    std::string result;
    for (auto& [key, val]: this->usedVowels) {
        if(val) {
            result.push_back(key);
        }
    }
    return result;
}

void Puzzle::applyGuessResult(char guess) {
    setUsedLetter(guess);
    revealDisplayLetters(guess);
}

char Puzzle::validateConsonant() {
    char guess = ' ';
    bool validGuess = false;
    do
    {
        std::cout << "Enter a consonant" << std::endl;
        std::cin >> guess;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        guess = toLower(guess);
        if (!isalpha(guess))
        {
            std::cout << "That is not a letter. Please try again." << std::endl;
        }
        else if (Puzzle::isPzVowel(guess))
        {
            std::cout << "You cannot guess a vowel. Please try again" << std::endl;
        }
        else if (isGuessed(guess))
        {
            std::cout << "That letter has already been guessed." << std::endl;
            std::cout << "Pick another letter." << std::endl;
            displayUsedConsonants();
        }
        else
        {
            validGuess = true;

            if (Puzzle::isPzRareLetter(guess))
            {
                // Give a random sarcastic response to a rare letter
                // j, q, x, z
                rareLetterResponse(guess);
            }
        }

    } while (!validGuess);
    return guess;
}

char Puzzle::validateVowel() {
    char guess = ' ';
    bool validGuess = false;
    do
    {
        std::cout << "Enter a vowel" << std::endl;
        std::cin >> guess;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        guess = toLower(guess);
        if (!isalpha(guess))
        {
            std::cout << "That is not a letter. Please try again." << std::endl;
        }
        else if (Puzzle::isPzConsonant(guess))
        {
            std::cout << "You cannot guess a consonant. Please try again" << std::endl;
        }
        else if (isGuessed(guess))
        {
            std::cout << "That letter has already been guessed." << std::endl;
            std::cout << "Pick another letter." << std::endl;
            displayUsedVowels();
        }
        else
        {
            validGuess = true;
        }
    } while (!validGuess);
    return guess;
}

void Puzzle::rareLetterResponse(char guess) {
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> intDistribution(0, 8);
    int num = intDistribution(generator);
    switch (num)
    {
        case 0:
            std::cout << guess << " ? Really?" << std::endl;
            break;

        case 1:
            std::cout << "A what?! " << std::endl;
            break;

        case 2:
            std::cout << "Hmm... Interesting." << std::endl;
            break;

        case 3:
            std::cout << "Are you sure you want to guess " << guess << "?" << std::endl;
            break;

        case 4:
            std::cout << "That's an odd choice..." << std::endl;
            break;

        case 5:
            std::cout << "You must know something I don't." << std::endl;
            break;

        case 6:
            std::cout << "Yep, that would be my first choice." << std::endl;
            break;

        case 7:
            std::cout << "I think someone threw a tomato at you." << std::endl;
            break;

        default:
            std::cout << "How did we end up here?" << std::endl;
            break;
    }
}

void Puzzle::displayUsedConsonants() {
    std::cout << "Used Consonants: " << getUsedConsonantStr() << std::endl;
}

void Puzzle::displayUsedVowels() {
    std::cout << "Used Vowels: " << getUsedConsonantStr() << std::endl;
}

bool Puzzle::getIsPuzzleRevealed() const {
    return isPuzzleRevealed;
}

void Puzzle::setUsedLetter(char letter) {
if(isPzConsonant(letter)) {
    usedConsonants[letter] = true;
    } else if (isPzVowel(letter)) {
    usedVowels[letter] = true;
    } else {
        std::cout <<  letter << " That's not a letter!" << std::endl;
    }
}

void Puzzle::setUsedLetters(const std::string& letters) {
    for(char letter : letters) {
        setUsedLetter(letter);
    }
}


Puzzle::Puzzle() = default;