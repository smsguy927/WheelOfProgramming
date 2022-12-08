//
// Created by smsgu on 10/31/2022.
//

#ifndef WHEELOFPROGRAMMINGCL_ROUND_H
#define WHEELOFPROGRAMMINGCL_ROUND_H

#include <array>
#include <vector>
#include <string>
#include "Puzzle.h"
#include "Turn.h"
#include "PlayerScore.h"

enum class RoundType {
    normal,
    bonus,
    tiebreaker
};


const int NUM_ROUND_TYPES = 3;
const std::array<std::string, NUM_ROUND_TYPES> ROUND_TYPES {"Normal", "Bonus", "Tiebreaker"};


struct RoundInit
{
    std::vector<PlayerScore> playerScores;
    Puzzle puzzle;
    int maxTurns;
    int currentTurn;
    int currentTurnPlayerID;
    int currentRound;
    int currentRoundTurn;
    int currentRoundTypeID;
    int startingPlayerID;
};

class Round {
public:
    explicit Round(const RoundInit&);
    Round();
    void setPlayerScores(std::vector<PlayerScore>);
    void setPuzzle(Puzzle);
    void setMaxTurnsR(int);
    void setCurrentTurnR(int);
    void setCurrentTurnPlayerIDR(int);
    void setCurrentRoundR(int);
    void setCurrentRoundTurnR(int);
    void setCurrentRoundTypeIDR(int);
    void setStartingPlayerID(int);

    std::vector<PlayerScore> getPlayerScores();
    std::vector<PlayerScore>& getPlayerScoresRef();
    Puzzle getPuzzleR();
    [[nodiscard]] int getMaxTurnsR() const;
    [[nodiscard]] int getCurrentTurnR() const;
    [[nodiscard]] int getCurrentTurnPlayerIDR() const;
    [[nodiscard]] int getCurrentRoundR() const;
    [[nodiscard]] int getCurrentRoundTurnR() const;
    [[nodiscard]] int getCurrentRoundTypeIDR() const;

    void setPlayerScore(PlayerScore ps, int i);

    PlayerScore getPlayerScore(int i);
    PlayerScore& getPlayerScoreRef(int i);
    int getStartingPlayerID();

private:
    std::vector<PlayerScore> playerScores;
    std::vector<Turn> turns;
    Puzzle puzzleR;
    int maxTurnsR{};
    int currentTurnR{};
    int currentTurnPlayerIDR{};
    int currentRoundR{};
    int currentRoundTurnR{};
    int currentRoundTypeIDR{};
    int startingPlayerID{};


};


#endif //WHEELOFPROGRAMMINGCL_ROUND_H
