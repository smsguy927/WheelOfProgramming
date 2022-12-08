//
// Created by smsgu on 11/4/2022.
//

#ifndef WHEELOFPROGRAMMINGTEST_SPINRESULT_H
#define WHEELOFPROGRAMMINGTEST_SPINRESULT_H


#include <string>
#include <array>
#include <iostream>
#include "Wheel.h"

enum class SpecialType
{
    bankrupt,
    loseATurn,
    normal,
    topValue,
    bitShifter,
    freeSpin,
    jackpot,
    prize,
    express
};

const int NUM_SPECIAL_TYPES = 9;
const int NUM_SR_COLORS = 16;
const int NUM_SR_SPECIAL_COLORS = 9;

const std::array<std::string, NUM_SPECIAL_TYPES> SPECIAL_NAMES{
    "Bankrupt", "Lose a Turn",  "Normal","Top Value","Bit Shifter",
    "Free Spin","Jackpot", "Prize","Express"
};

const std::array<std::string, NUM_SR_COLORS>SR_COLORS{
    "Red", "Orange", "Yellow", "Green","Blue", "Purple",
    "Tan", "Gray", "Pink", "Sky Blue", "Indigo","Magenta",
    "Lime", "Beige", "Silver", "Gold", };

const std::array<std::string, NUM_SR_SPECIAL_COLORS>SR_SPECIAL_COLORS{
    "Black", "White","None","Sparkle Silver","Green on Black",
    "Yellow-Green", "Sparkle Red","Sparkle Blue", "Blue on Dark Gray" };



class SpinResult {
public:

    explicit SpinResult(Wedge wedge);
    SpinResult();

    void setValue(int);
    void setColorID(int);
    void setColor(std::string);
    void setSpecialID(int);
    void setSpecial(std::string);
    void setIsTurnEnding(bool);

    [[nodiscard]] int getValue() const;
    [[nodiscard]] int getColorID() const;
    std::string getColor();
    [[nodiscard]] int getSpecialID() const;
    std::string getSpecial();
    [[nodiscard]] bool getIsTurnEnding() const;
    void display();
    void setSpecialType(SpecialType);
    SpecialType getSpecialType();

private:
    int value{};
    int colorID{};
    std::string color;
    int specialID{};
    std::string special;
    bool isTurnEnding{};
    SpecialType specialType{SpecialType::normal};
};


#endif //WHEELOFPROGRAMMINGTEST_SPINRESULT_H
