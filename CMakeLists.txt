cmake_minimum_required(VERSION 3.19)
project(WheelOfProgrammingTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(WheelOfProgrammingTest main.cpp GameShowHost.cpp GameShowHost.h Game.cpp Game.h Player.cpp Player.h Puzzle.cpp Puzzle.h Round.cpp Round.h Turn.cpp Turn.h BonusRound.cpp BonusRound.h Wheel.cpp Wheel.h SpinResult.cpp SpinResult.h JrdTimerUtils.cpp JrdTimerUtils.h PlayerScore.cpp PlayerScore.h GameMode.cpp GameMode.h)