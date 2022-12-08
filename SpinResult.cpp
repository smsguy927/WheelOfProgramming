//
// Created by smsgu on 11/4/2022.
//

#include "SpinResult.h"
#include <utility>
#include <vector>

std::vector<SpinResult> allSpinResults;

SpinResult::SpinResult(Wedge wedge) {
    this->value = static_cast<int>(wedge.value);
    this->colorID = static_cast<int>(wedge.color);
    this->specialID = static_cast<int>(wedge.special);
    if(this->specialID == static_cast<int>(SpecialType::normal)){
        this->color = SR_COLORS[this->colorID];
    } else {
        this->color = SR_SPECIAL_COLORS[this->colorID];
    }

    this->special = SPECIAL_NAMES[this->specialID];
    this->isTurnEnding = this->specialID < static_cast<int>(SpecialType::normal);
    this->specialType = static_cast<SpecialType>(specialID);
    allSpinResults.push_back(*this);
}


SpinResult::SpinResult() = default;

void SpinResult::setValue(int v) {
    this->value = v;
}

void SpinResult::setColorID(int cID) {
    this->colorID = cID;
}

void SpinResult::setColor(std::string c) {
    this->color = std::move(c);
}

void SpinResult::setSpecialID(int sID) {
    this->specialID = sID;
}

void SpinResult::setSpecial(std::string s) {
    this->special = std::move(s);
}

void SpinResult::setIsTurnEnding(bool ite) {
    this->isTurnEnding = ite;
}

int SpinResult::getValue() const {
    return value;
}

int SpinResult::getColorID() const {
    return colorID;
}

std::string SpinResult::getColor() {
    return color;
}

int SpinResult::getSpecialID() const {
    return this->specialID;
}

std::string SpinResult::getSpecial() {
    return special;
}

bool SpinResult::getIsTurnEnding() const {
    return this->isTurnEnding;
}

void SpinResult::display() {
    if(static_cast<SpecialType>(specialID) == SpecialType::normal) {
        std::cout << "You landed on $" << value << std::endl;
        std::cout << "Its color is " << color << std::endl;
    } else {
        std::cout << "You landed on " << special << std::endl;
        std::cout << "Its color is " << color << std::endl;
        if(value) {
            std::cout << "It is also worth $" << value << " per letter." << std::endl;
        }

    }
}

void SpinResult::setSpecialType(SpecialType st) {
    this->specialType = st;
}

SpecialType SpinResult::getSpecialType() {
    return this->specialType;
}

