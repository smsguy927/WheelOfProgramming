//
// Created by smsgu on 12/7/2022.
//

#ifndef WHEELOFPROGRAMMINGTEST_GAMEMODE_H
#define WHEELOFPROGRAMMINGTEST_GAMEMODE_H


#include <map>
#include <string>


enum class GameModeID {
    light = 'l',
    normal = 'n',
    strict = 's'
};
const std::map<char, std::string> MODES{
        {'l', "Light"},
        {'n', "Normal"},
        {'s', "Strict"}};
class GameMode {

public:
    explicit GameMode(char);
    GameMode();

    [[nodiscard]] char getSymbol() const;
    std::string getName();

private:
    char symbol;
    std::string name;

};


#endif //WHEELOFPROGRAMMINGTEST_GAMEMODE_H
