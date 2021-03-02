#pragma once
#include <array>
#include <string>

// Constants for game operation.

const int NUM_ROUNDS = 4;
const int NUM_CATEGORIES = 0b111;







// Don't use a puzzle with too many l,n,r,s,t,e letters becuase 
// these are given to the player.



const std::array<std::string, NUM_CATEGORIES> CATEGORY{ "Thing", "Before & After", "Place", "What are you doing?", "Phrase", "Same Name", "Person" };