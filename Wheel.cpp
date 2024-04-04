//
// Created by smsgu on 10/31/2022.
//

#include "Wheel.h"
#include <array>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>


// These two are shuffled before assigning them to wedges so each wheel is different.
std::array  <std::string, Wheel::NUM_COLORS>Wheel::wheelColors{ "Red", "Orange", "Yellow", "Green", "Blue", "Purple", "Tan", "Gray", "Pink", "Sky Blue", "Indigo", "Magenta", "Lime", "Beige", "Silver", "Gold", };

std::array<int, Wheel::NUM_VALUES> wedgeValues{ 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1250, 1500 };



const std::array<int, Wheel::NUM_TOP_VALUES> Wheel::TOP_VALUES{ 2000, 2500, 3000, 5000, 7500 };

Wheel::Wheel(int round)
{
    setTopValue(round);
    unsigned valueCounter = 0;
    unsigned wedgeCounter;
    std::shuffle(wedgeValues.begin(), wedgeValues.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    for (wedgeCounter = 0; wedgeCounter < NUM_WEDGES; wedgeCounter++)
    {
        if (wedgeCounter % (NUM_WEDGES / 2) == 0)
        {
            wheel[wedgeCounter].color = int(WedgeID::bankrupt);
            wheel[wedgeCounter].value = 0;
            wheel[wedgeCounter].special = int(WedgeID::bankrupt);
        }

        else if(wedgeCounter == 0){
            wheel[wedgeCounter].color = int(WedgeID::express);
            wheel[wedgeCounter].value = SPECIAL_VALUE;
            wheel[wedgeCounter].special = int(WedgeID::express);
        }

        else if (wedgeCounter % NUM_WEDGES == 3)
        {
            wheel[wedgeCounter].color = int(WedgeID::loseATurn);
            wheel[wedgeCounter].value = 0;
            wheel[wedgeCounter].special = int(WedgeID::loseATurn);
        }
        else if (wedgeCounter % NUM_WEDGES == 6)
        {
            wheel[wedgeCounter].color = int(WedgeID::prize);
            wheel[wedgeCounter].value = SPECIAL_VALUE;
            wheel[wedgeCounter].special = int(WedgeID::prize);
        }
        else if (wedgeCounter % NUM_WEDGES == 9)
        {
            wheel[wedgeCounter].color = int(WedgeID::jackpot);
            wheel[wedgeCounter].value = SPECIAL_VALUE;
            wheel[wedgeCounter].special = int(WedgeID::jackpot);
        }
        else if (wedgeCounter % NUM_WEDGES == 15)
        {
            wheel[wedgeCounter].color = int(WedgeID::freeSpin);
            wheel[wedgeCounter].value = SPECIAL_VALUE;
            wheel[wedgeCounter].special = int(WedgeID::freeSpin);
        }
        else if (wedgeCounter % NUM_WEDGES == 18)
        {
            wheel[wedgeCounter].color = int(WedgeID::bitShifter);
            wheel[wedgeCounter].value = SPECIAL_VALUE;
            wheel[wedgeCounter].special = int(WedgeID::bitShifter);
        }
        else if (wedgeCounter % NUM_WEDGES == 21)
        {
            wheel[wedgeCounter].color = int(WedgeID::topValue);
            wheel[wedgeCounter].value = topValue;
            wheel[wedgeCounter].special = int(WedgeID::topValue);
        }
        else
        {
            wheel[wedgeCounter].color = valueCounter;
            wheel[wedgeCounter].value = wedgeValues[valueCounter];
            wheel[wedgeCounter].special = int(WedgeID::normal);
            valueCounter++;
        }
    }
}

void Wheel::setTopValue(int num)
{
    if(num < TOP_VALUES.size()) {
        this->topValue = TOP_VALUES[num];
    } else {
        this->topValue = TOP_VALUES[TOP_VALUES.size() - 1];
    }
}



Wedge Wheel::getCurrentWedge()
{
    return currentWedge;
}

int Wheel::getTopValue() const
{
    return topValue;
}

[[maybe_unused]] std::string Wheel::getColor(int num)
{
    return wheelColors[num];
}

void Wheel::spin()
{
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> intDistribution(MIN_SPIN, MAX_SPIN);
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    std::rotate(wheel.begin(), wheel.begin() + intDistribution(generator), wheel.end());
    currentWedge = wheel[0];
    this->jackpot += currentWedge.value;

}

[[maybe_unused]] void Wheel::setJackpot(int j) {
    this->jackpot = j;
}

int Wheel::getJackpot() const {
    return static_cast<int>(jackpot);
}
