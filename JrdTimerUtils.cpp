//
// Created by smsgu on 11/5/2022.
//

#include "JrdTimerUtils.h"


void JrdTimer::Reset()
{
    _start = high_resolution_clock::now();
}

[[nodiscard]] std::chrono::milliseconds JrdTimer::Elapsed() const
{
    return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
}

template<typename T, typename Traits>
std::basic_ostream<T, Traits> &operator<<(std::basic_ostream<T, Traits> &out, const JrdTimer &timer) {
        return out << timer.Elapsed().count();
    }

JrdTimer::JrdTimer() {
    Reset();
}




int validate(int min, int max)
{
    /*
    /------------------------------------\
    |This function validates an int input|
    \------------------------------------/
    */

    // Sentinel Value Constant
    const double NO_MIN = -927;

    // function variables

    // This will be returned at the end
    int value;

    // These are flags for min and max values
    bool minBool = false;
    bool maxBool = false;

    // Part One
    // Determine whether there is a min and/or a max value to accept
    // The default arguments are 0,0 which means minimum of zero and
    // no maximum.
    if (min != 0 && min == max) {
        // No min or max
        std::cout << "Enter a number" << std::endl;
    }
    else if (min != NO_MIN && min < max) {
        // Yes min and Yes max
        minBool = true;
        maxBool = true;
        std::cout << "Enter a number " << min << " or higher and " << max << " or lower." << std::endl;
    }
    else if (min < max) {
        // No min Yes Max
        maxBool = true;
        std::cout << "Enter a number " << max << " or lower." << std::endl;
    }
    else {
        // Yes min No max
        minBool = true;
        std::cout << "Enter a number " << min << " or higher." << std::endl;
    }
    // Part Two
    // This is when the user actually enters the value and when it is
    // tested to make sure it is valid.

    // This controls the do while loop
    bool notReady = true;

    do {
        // Enter the value
        std::cin >> value;
        // Test the value to make sure it is valid

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter numbers only and try again." << std::endl;
        }
        else if ((minBool && maxBool) && (value < min || value > max)) {
            std::cout << "Please try again." << std::endl;
            std::cout << "Enter a number " << min << " or higher and " << max << " or lower." << std::endl;
        }
        else if ((minBool) && value < min) {
            std::cout << "Please try again." << std::endl;
            std::cout << "Enter a number " << min << " or higher." << std::endl;

        }
        else if ((maxBool) && value > max) {
            std::cout << "Please try again." << std::endl;
            std::cout << "Enter a number " << max << " or lower." << std::endl;

        }
        else {
            // Ignore any characters after the input is accepted
            // e.g decimal points, letters, etc.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            notReady = false;
        }
    } while (notReady);
    // Once the value is ready, return it.
    return value;
}

char toLower(char ch) {
    const int UPPERCASE_MIN = 65;
    const int UPPERCASE_MAX = 90;
    const int LOWERCASE_OFFSET = 32;
    if(!isalpha(ch) || ch < UPPERCASE_MIN || ch > UPPERCASE_MAX){
        return ch;
    };
    return static_cast<char>(ch + LOWERCASE_OFFSET);
}


