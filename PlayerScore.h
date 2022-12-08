//
// Created by smsgu on 11/7/2022.
//

#ifndef WHEELOFPROGRAMMINGTEST_PLAYERSCORE_H
#define WHEELOFPROGRAMMINGTEST_PLAYERSCORE_H

#include <vector>

struct PlayerScoreInit {
    int playerID;
    int roundID;
    int freeSpins;
};



class PlayerScore {
public:
    explicit PlayerScore(PlayerScoreInit);
    PlayerScore();

    void setPlayerID(int);
    void setRoundID(int);
    void setCash(int);
    void setHasPrize(bool);
    void setHasJackpot(bool);
    void setFreeSpins(int);
    void setIsSolver(bool);

    int getPlayerID();
    int getRoundID();
    int getCash();
    bool getHasPrize();
    bool getHasJackpot();
    int getFreeSpins();
    bool getIsSolver();
private:
    int playerID{};
    int roundID{};
    int cash{0};
    bool hasPrize{false};
    bool hasJackpot{false};
    int freeSpins{}; // carries over to next round
    bool isSolver{false};
};


#endif //WHEELOFPROGRAMMINGTEST_PLAYERSCORE_H
