//
// Created by smsgu on 11/3/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_PLAYER_H
#define WHEELOFPROGRAMMINGCL_PLAYER_H

#include <string>
#include <array>

enum class PlayerColor
{
    red,
    yellow,
    blue,
    green,
    purple,
    orange
};
const int NUM_PLAYER_COLORS = 6;
const std::array<std::string, NUM_PLAYER_COLORS> PLAYER_COLORS
        {"Red", "Yellow", "Blue", "Green", "Purple", "Orange"};

const int NUM_DEFAULT_PLAYERS = 3;
const int P1_INDEX = 0;
const int P2_INDEX = 1;
const int P3_INDEX = 2;

struct PlayerInit
{
    int positionID;
    int colorID;
    int playerID;
    std::string color;
    std::string name;
    std::string favoriteCodingLanguage;
    int totalWinnings;
    int freeSpins;
    bool isReturningChampion;
    int previousWinnings;
};

const PlayerInit DEFAULT_P1
        {0, 0, 0, "Red", "Sean", "C++", 0, 0,
         false, 0};

const PlayerInit DEFAULT_P2
        {1, 1, 1, "Yellow", "Barbara", "JavaScript", 0, 0,
         false, 0};

const PlayerInit DEFAULT_P3
        {2, 2, 2, "Blue", "Chris", "Python", 0, 0,
         false, 0};

const PlayerInit DEFAULT_INIT_VALUES
        {5, 5, 5, "Orange", "Null", "PHP", 0, 0,
         false, 0};

class Player {
public:
    explicit Player(const PlayerInit&);
    Player();

    void setPositionID(int);
    void setColorID(int);
    void setPlayerID(int);
    void setColor(std::string);
    void setName(std::string);
    void setFavoriteCodingLanguage(std::string);
    void setTotalWinnings(int);
    void setFreeSpins(int);
    void setIsReturningChampion(bool);
    void setPreviousWinnings(int);
    void setAwesomePoints(int);

    [[nodiscard]] int getPositionID() const;
    [[nodiscard]] int getColorID() const;
    [[nodiscard]] int getPlayerID() const;
    std::string getColor();
    std::string getName();
    std::string getFavoriteCodingLanguage();
    [[nodiscard]] int getTotalWinnings() const;
    [[nodiscard]] int getFreeSpins() const;
    [[nodiscard]] bool getIsReturningChampion() const;
    [[nodiscard]] int getPreviousWinnings() const;
    int getAwesomePoints() const;

    bool operator> (const Player&) const;
    bool operator< (const Player&) const;
    bool operator>= (const Player&) const;
    bool operator<= (const Player&) const;
    int operator<=> (const Player&) const;
private:
    int positionID;
    int colorID;
    int playerID;
    std::string color;
    std::string name;
    std::string favoriteCodingLanguage;
    int totalWinnings;
    int freeSpins;
    int awesomePoints{0}; // Not assigned yet, but used in generating a BonusRoundInit
    bool isReturningChampion;
    int previousWinnings;
};


#endif //WHEELOFPROGRAMMINGCL_PLAYER_H