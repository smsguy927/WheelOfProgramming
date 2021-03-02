#include "Wheel.h"
#include <array>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include <time.h>


// These two are shuffled before assigning them to wedges so each wheel is different.
std::array  <std::string, Wheel::NUM_COLORS>Wheel::wheelColors{"Red", "Orange", "Yellow", "Green", "Blue", "Purple", "Tan", "Gray", "Pink", "Sky Blue", "Indigo", "Magenta", "Lime", "Beige", "Silver", "Gold", };

std::array<int, Wheel::NUM_VALUES> wedgeValues{ 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950 };

// These are constant because these corespond to the WedgeID enum class.
const std::array  <std::string, Wheel::NUM_SPECIALS>Wheel::SPECIAL_COLORS{ "None", "White", "Yellow-Green", "Black", "Sparkle Red", "Sparkle Blue", "Sparkle Silver", "Blue on Dark Gray" };

const std::array  <std::string, Wheel::NUM_SPECIALS>Wheel::SPECIAL_WEDGES{"Normal", "Lose a Turn", "Free Spin", "Bankrupt", "Jackpot", "Prize", "Top Value", "Bit Shifter" };


const std::array<int, Wheel::NUM_TOP_VALUES> Wheel::TOP_VALUES{ 2500, 3500, 4000, 5000 };

Wheel::Wheel(int round)
{
	setTopValue(round);
	unsigned valueCounter = 0;
	unsigned wedgeCounter = 0;
	std::shuffle(wedgeValues.begin(), wedgeValues.end(), std::default_random_engine());
	std::shuffle(wheelColors.begin(), wheelColors.end(), std::default_random_engine());
	for (wedgeCounter = 0; wedgeCounter < NUM_WEDGES; wedgeCounter++)
	{
		if (wedgeCounter % (NUM_WEDGES / 2) == 0)
		{
			wheel[wedgeCounter].color = int(WedgeID::bankrupt);
			wheel[wedgeCounter].value = 0;
			wheel[wedgeCounter].special = int(WedgeID::bankrupt);
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
			wheel[wedgeCounter].color = 9;
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
	this->topValue = TOP_VALUES[num];
}



Wedge Wheel::getCurrentWedge()
{
	return currentWedge;
}

int Wheel::getTopValue()
{
	return topValue;
}

std::string Wheel::getColor(int num)
{
	return wheelColors[num];
}

void Wheel::spin()
{
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	std::rotate(wheel.begin(), wheel.begin() + rand() % NUM_WEDGES, wheel.end());
	currentWedge = wheel[0];
}
