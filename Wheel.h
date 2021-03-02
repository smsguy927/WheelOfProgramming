#pragma once
#include <array>
#include <string>
enum class WedgeID
{
	normal,
	loseATurn,
	freeSpin,
	bankrupt,
	jackpot,
	prize,
	topValue,
	bitShifter
};
struct Wedge
{
	unsigned value : 13;
	unsigned color : 4;
	unsigned special : 4;
};

class Wheel
{
public:
	
	const static int NUM_SPECIALS{ 8 };
	const static int SPECIAL_VALUE{ 1000 };
	const static int NUM_COLORS{ 16 };
	const static int NUM_WEDGES{ 24 };
	const static int NUM_VALUES{ 16 };
	const static int NUM_TOP_VALUES{ 4 };
	const static std::array<std::string, NUM_SPECIALS > SPECIAL_WEDGES;
	const static std::array<std::string, NUM_SPECIALS > SPECIAL_COLORS;
	const static std::array<int, NUM_TOP_VALUES>TOP_VALUES;
	Wheel(int round);
	void setTopValue(int);
	
	Wedge getCurrentWedge();
	int getTopValue();
	std::string getColor(int num);
	void spin(); 
private:
	std::array<Wedge, NUM_WEDGES> wheel;
	static std::array<std::string, NUM_COLORS > wheelColors;
	
	static std::array<int, NUM_COLORS > wheelValues;
	
	int topValue;
	Wedge currentWedge;
};