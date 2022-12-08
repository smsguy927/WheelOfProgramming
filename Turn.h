//
// Created by smsgu on 11/3/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_TURN_H
#define WHEELOFPROGRAMMINGCL_TURN_H

#include <string>
#include "SpinResult.h"

enum class TnAction
{
    null = -1,
    outOfTime,
    spin,
    vowel,
    solve,
    fsConsonant,
    fsVowel,
    express,
    expressConsonant,
    expressVowel
};

enum class SolveResult
{
    wrong,
    right,
    outOfTime,
    null
};

enum class TurnResult
{
    null = 0,
    wrong,
    right,
    loseATurn,
    bankrupt,
    actionTimeUp,
    guessTimeUp,
    repeatGuess,
    error
};

struct TurnInit
{
    int playerID;
    int turnID;
    bool isFinalSpin;
    bool isAfterFinalSpin;
    bool isExpress;
};

const int ACTION_TIME_LIMIT_MS = 6000;
const int LETTER_TIME_LIMIT_MS = 8000;
const int SOLVE_TIME_LIMIT_MS = 30000;
const int EXPRESS_TIME_LIMIT_MS = 5000;
const int EXPRESS_SOLVE_TIME_LIMIT_MS = 20000;

class Turn {
public:

    explicit Turn(TurnInit);
    Turn();

    void setPlayerID(int);
    void setTurnID(int);
    void setActionID(int);
    void setActionTimeUsedMs(int);
    void setLetterTimeUsedMs(int);
    void setSolveTimeUsedMs(int);
    void setIsFinalSpin(bool);
    void setIsAfterFinalSpin(bool);
    void setIsExpress(bool);
    void setGuess(char);
    void setIsRareLetter(bool);
    void setTnSpinResult(SpinResult);
    void setSolveAttempt(std::string);
    void setTurnResult(TurnResult);
    void setConsonantsFound(int);
    void setTurnAction(TnAction);
    void setSolveResult(SolveResult);

    [[nodiscard]] int getPlayerID() const;
    [[nodiscard]] int getTurnID() const;
    [[nodiscard]] int getActionID() const;
    [[nodiscard]] int getActionTimeUsedMs() const;
    [[nodiscard]] int getLetterTimeUsedMs() const;
    [[nodiscard]] int getSolveTimeUsedMs() const;
    [[nodiscard]] bool getIsFinalSpin() const;
    [[nodiscard]] bool getIsAfterFinalSpin() const;
    [[nodiscard]] bool getIsExpress() const;
    [[nodiscard]] char getGuess() const;
    [[nodiscard]] bool getIsRareLetter() const;
    SpinResult getTnSpinResult();
    SpinResult& getTnSpinResultRef();
    std::string getSolveAttempt();
    TurnResult getTurnResult();
    [[nodiscard]] int getConsonantsFound() const;
    TnAction getTurnAction();
    bool shouldEvaluateGuess();
    SolveResult getSolveResult();


private:
    int playerID{};
    int turnID{};
    int actionID{};
    int actionTimeUsedMs{0};
    int letterTimeUsedMs{0};
    int solveTimeUsedMs{0};
    bool isFinalSpin{};
    bool isAfterFinalSpin{};
    bool isExpress{};
    char guess{};
    int consonantsFound{};
    bool isRareLetter{};
    SpinResult tnSpinResult;
    std::string solveAttempt;
    TurnResult turnResult;
    TnAction turnAction{TnAction::null};
    SolveResult solveResult{SolveResult::null};
};


#endif //WHEELOFPROGRAMMINGCL_TURN_H
