//
// Created by smsgu on 11/2/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_JRDTIMER_H
#define WHEELOFPROGRAMMINGCL_JRDTIMER_H
#include <chrono>
#include <ostream>
#include <iostream>
#include <array>

enum class GameSize
{
    testing,
    nano,
    micro,
    shorts, // short is a reserved word
    medium,
    longs, // long is a reserved word
    extreme
};



const int VOWEL_PRICE = 250;
const int MS_PER_SECOND = 1000;

const std::chrono::duration<int, std::milli> oneSecInMs(1000);

const char YES = 'y';
const char NO = 'n';
const char NULL_CHAR = '!';


const char SECRET_HOST = 'z';
const char SECRET_SKIP_INTRO = 'x';


const int GAME_SIZES = 7;
const int NUM_PLAYERS = 3;

const int SOLVE_BONUS = 500;
const int FINAL_SPIN_BONUS = 1000;

const int PRIZE_VALUE = 8192;
const int GAME_NULL_INT = -555;

const int BIT_SHIFTER_RIGHT = 1;
const int BIT_SHIFTER_WRONG = 2;

const std::pair<int, int> EXPRESS_TURN_FRACTION{2,3};

const std::string PUZZLES_FILENAME = "Puzzles.txt";
const std::string BONUS_FILENAME = "BonusPuzzles.txt";


const std::array<int, int(GameSize::extreme) + 1>MAX_TURNS{0, 10, 20, 30,50,70,100};

int validate(int = 0, int = 0);
char toLower(char);

class JrdTimer {
    typedef std::chrono::high_resolution_clock high_resolution_clock;
    typedef std::chrono::milliseconds milliseconds;
public:

    explicit JrdTimer();
    void Reset();

    [[nodiscard]] milliseconds Elapsed() const;

    template <typename T, typename Traits>
    friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, const JrdTimer& timer);
private:
    high_resolution_clock::time_point _start;
};


#endif //WHEELOFPROGRAMMINGCL_JRDTIMER_H