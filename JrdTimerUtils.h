//
// Created by smsgu on 11/2/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_JRDTIMER_H
#define WHEELOFPROGRAMMINGCL_JRDTIMER_H
#include <chrono>
#include <ostream>
#include <iostream>

const int VOWEL_PRICE = 250;
const int MS_PER_SECOND = 1000;
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