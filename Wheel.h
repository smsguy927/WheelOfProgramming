//
// Created by Sean on 10/31/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_WHEEL_H
#define WHEELOFPROGRAMMINGCL_WHEEL_H

#include <array>
#include <string>

enum class WedgeID
{   bankrupt,
    loseATurn,
    normal,
    topValue,
    bitShifter,
    freeSpin,
    jackpot,
    prize,
    express
};
struct Wedge
{
    unsigned value;
    unsigned color ;
    unsigned special;
};



class Wheel {
public:

    const static int NUM_SPECIALS{ 9 };
    const static int SPECIAL_VALUE{ 1000 };
    const static int JACKPOT_START = 2500;
    const static int NUM_COLORS{ 16 };
    const static int NUM_WEDGES{ 24 };
    const static int NUM_VALUES{ 20 };
    const static int NUM_TOP_VALUES{ 5 };
    const static int MIN_SPIN{ 3 };
    const static int MAX_SPIN{ NUM_WEDGES };
    const static std::array<std::string, NUM_SPECIALS > SPECIAL_WEDGES;
    const static std::array<std::string, NUM_SPECIALS > SPECIAL_COLORS;
    const static std::array<int, NUM_TOP_VALUES>TOP_VALUES;
    explicit Wheel(int round);
    void setTopValue(int);

    [[maybe_unused]] void setJackpot(int);
    int getJackpot() const;

    Wedge getCurrentWedge();
    [[nodiscard]] int getTopValue() const;

    [[maybe_unused]] static std::string getColor(int num);
    void spin();
private:
    std::array<Wedge, NUM_WEDGES> wheel{};
    static std::array<std::string, NUM_COLORS > wheelColors;

    static std::array<int, NUM_COLORS > wheelValues;

    int topValue{};
    unsigned jackpot{JACKPOT_START};
    Wedge currentWedge{};

};


#endif //WHEELOFPROGRAMMINGCL_WHEEL_H