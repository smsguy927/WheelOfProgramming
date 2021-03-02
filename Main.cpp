#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <array>
#include <vector>
#include <thread>
#include <chrono>


//#include <Windows.h>
#include "Wheel.h"
#include "Puzzle.h"
enum class Action
{
	spin = 1,
	vowel,
	solve
};
using namespace std;

const string PUZZLES_FILENAME = "Puzzles.txt";
const string BONUS_FILENAME = "BonusPuzzles.txt";
const char SYMBOL = '%';

const int NUM_PLAYERS = 3;
const int NUM_CHANCES = 5;
const int BONUS_CONSONANTS = 3;

const int VOWEL_PRICE = 0b1111'1010;
const int SOLVE_BONUS = 0b1'1111'0100;
const int JACKPOT_START = 0b1'0011'1000'1000;
const int PRIZE_VALUE = 0b10'0000'0000'0000;
const int BONUS_PRIZE = 0b1000'0000'0000'0000;

// These are for building the display board
const char BLANK[]{ '-', '\0' };
const char SPACE[]{ ' ', '\0' };

const char VOWELS[]{ 'a', 'e', 'i', 'o', 'u', '\0'};
const char RARE_LETTERS[]{ 'j', 'q', 'x', 'z', '\0' };
const char BONUS_GIVEN_LETTERS[]{ 'r', 's', 't', 'l', 'n', 'e', '\0' };

void setSolutions(array<string, NUM_ROUNDS>&, array<int, NUM_ROUNDS>&);
void explainRules();
void playRound(array<int, NUM_PLAYERS> &, array<int, NUM_PLAYERS> &, int &, array<string, NUM_ROUNDS>&, array<int, NUM_ROUNDS>&);

void displayActionchoices(int, int, int);
void describeBitShifter(Wedge &, int);
char validateConsonant(char, char[]);
char validateVowel(char, char[]);

bool isVowel(char);
bool isRareLetter(char);
void rareLetterResponse(char guess);
bool isGuessed(char, char[]);

// These affect players scores and current turn
void bankrupt(Wedge &, array<int, NUM_PLAYERS> &, int &, array<bool, NUM_PLAYERS> &, array<bool, NUM_PLAYERS> &, array<int, NUM_PLAYERS> & freeSpins);

void applyGuessResult(int, char, int &, int &, array<int, NUM_PLAYERS> &, int &, int, int, Wedge &, array<int, NUM_PLAYERS> &);

void ApplyWedgeEffects(Wedge &, array<bool, NUM_PLAYERS > &, int, array<bool, NUM_PLAYERS> &, array<int, NUM_PLAYERS> &, array<int, NUM_PLAYERS> &);

void passTurn(int &, array<int, NUM_PLAYERS> &);

void updateTotals(int, int, array<int, NUM_PLAYERS> &, array<int, NUM_PLAYERS> &, array<bool, NUM_PLAYERS> &, array<bool, NUM_PLAYERS> &);

// Bonus Round only
void bonusRound(int&, array<int, NUM_PLAYERS> &, array<int, NUM_PLAYERS> &);
void setBonusSolution(string&, int&);
bool isBonusGivenLetter(char);
bool isBonusChosen(char, char[]);

// Used for menu choice
int validate(int = 0, int = 0);

int main()
{
	// Arrays for puzzles and categories
	std::array<std::string, NUM_ROUNDS>solutions;
	std::array<int, NUM_ROUNDS>puzzleCategories;
	setSolutions(solutions, puzzleCategories);
	// variable for sleep function
	std::chrono::duration<int, std::milli> timespan(1000);
	cout << "Hello and welcome to the final program of Advanced C++" << endl;
	cout << "It's time for ..." << endl << endl;
	std::this_thread::sleep_for(timespan);
	cout << "Wheel" << endl;
	std::this_thread::sleep_for(timespan);
	cout << "Of" << endl;
	std::this_thread::sleep_for(timespan);
	cout << "Programming" << endl << endl;
	std::this_thread::sleep_for(timespan);
	
	cout << "Do you want to explain the rules?" << endl;
	cout << "Press y for yes." << endl;
	char explain = tolower(cin.get());
	if (explain == 'y')
	{
		explainRules();
	}
	
	// Final Totals and Free Spins that carry over through rach round.
	array<int, NUM_PLAYERS> totals{ 0 };
	array<int, NUM_PLAYERS> freeSpins{ 0 };
	
	
	int currentRound = 0;
	do 
	{ 
		int num = 0;
		//bonusRound(num, totals, freeSpins);
		playRound(totals, freeSpins, currentRound, solutions, puzzleCategories);
		cout << "At the end of round " << currentRound << ":" << endl;

		for (unsigned i = 0; i < NUM_PLAYERS; i++)
		{
			cout << "Player " << i + 1 << ", your total is $" << totals[i] << endl;
		}

	} while (currentRound < NUM_ROUNDS);

	auto result = max_element(totals.begin(), totals.end());
	int winningPlayer = result-totals.begin();
	cout << "Player " << winningPlayer + 1 << ", you are going to the bonus round!" << endl;
	bonusRound(winningPlayer, totals, freeSpins);
	cout << "That's the end of our show." << endl;
	cout << "Wheel of Programming is based on Wheel of Fortune, a game show" << endl;
	cout << "by Merv Griffin. Copyright by Califon Productions, Inc." << endl;
	cout << "Wheel of Fortune is distributed by CBS Television Distribution." << endl;
	cout << "Press any key to exit." << endl;
	cin.get();
	cin.get();
	return 0;
}

void setSolutions(array<string, NUM_ROUNDS>& solutions, array<int, NUM_ROUNDS>& puzzleCategories )
{
	default_random_engine engine;
	engine.seed(std::chrono::system_clock::now().time_since_epoch().count());

	ifstream puzzlesFile{ PUZZLES_FILENAME, ios::in };
	if (!puzzlesFile)
	{
		cerr << PUZZLES_FILENAME << " not found. Please make sure " << PUZZLES_FILENAME << " and" << endl;
		cerr << "this program's .exe file are in the same folder." << endl;
		cerr << "If " << PUZZLES_FILENAME << "does not exist, " << endl;
		cerr << "create one." << endl;
		exit(1);
	}
	else
	{
		vector<string>puzzleIDs;
		int puzzlesCount = 0;
		string puzzleIDStr, puzzleText, categoryIDStr;
		while (puzzlesFile)
		{
			getline(puzzlesFile, puzzleIDStr, SYMBOL);
			puzzleIDs.push_back(puzzleIDStr);
			getline(puzzlesFile, puzzleText, SYMBOL);
			getline(puzzlesFile, categoryIDStr, '\n');
			puzzlesCount++;
		}

		puzzlesFile.close();
		
		
		shuffle(puzzleIDs.begin(), puzzleIDs.end(), engine);
		
		

		for (unsigned int i = 0; i < NUM_ROUNDS; i++)
		{
			puzzlesFile.open(PUZZLES_FILENAME, ios::in);
			while (puzzlesFile)
			{
				getline(puzzlesFile, puzzleIDStr, SYMBOL);
				getline(puzzlesFile, puzzleText, SYMBOL);
				getline(puzzlesFile, categoryIDStr, '\n');

				if (puzzleIDs[i] == puzzleIDStr)
				{
					solutions[i] = puzzleText;
					puzzleCategories[i] = stoi(categoryIDStr);
					puzzlesFile.close();
				}
			}
		}
	}
	return;
}

void explainRules()
{
	cout << "Here are the rules: There is a puzzle that is a c-string made up of dashes." << endl;
	cout << "Each dash represents a letter in the puzzle. You will fill in the letters" << endl;
	cout << "by spinning the wheel or buying a vowel, which is an a, e, i, o, or u." << endl;
	cout << "Vowels cost " << VOWEL_PRICE << ". There are " << Wheel::NUM_WEDGES << " wedge structs on the wheel, each with a value," << endl;
	cout << "color, and special property. The special wedges include a jackpot, a special" << endl;
	cout << "prize, free spins, and even a wedge which shfts your score left one bit if" << endl;
	cout << "you can correctly guess a letter in the puzzle. Watch out for Bankrupt and" << endl;
	cout << "Lose a Turn. After you spin, you can guess a consonant. If it is in the puzzle," << endl;
	cout << "you get the value on the wedge multiplied by the number of the letter's" << endl;
	cout << "occurrence added to your score and your turn continues. If the letter is not in" << endl;
	cout << "the puzzle, your turn ends and control passes to the next player. Once enough" << endl;
	cout << "letters are filled in, you can try to solve the puzzle. Your answer must be an" << endl;
	cout << "exact match with no misplaced characters. If your answer is correct, you win" << endl;
	cout << "$500 and your score will be added to your final total and all other players" << endl; 
	cout << "scores will be cleared. You should try to get a high score before solving," << endl;
	cout << "but don't get greedy. There are two Bankrupt wedges on the wheel. If you land" << endl;
	cout << "one of them, your current score will be set to 0 and your turn will end. " << endl;
	cout << "There is also a Lose a Turn wedge that will end your turn. There are " << NUM_ROUNDS << " rounds. " << endl;
	cout <<  "At the end of the last round, the player with the highest final total will" << endl;
	cout << "advance to the bonus round. Are you ready? Let's play Wheel of Programming!" << endl;
	cout << endl << endl << endl;

	cout << "Press any key to continue." << endl;
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void playRound(array<int, NUM_PLAYERS>& totals, array<int, NUM_PLAYERS>& freeSpins, int & currentRound, array<string, NUM_ROUNDS> & solutions, array<int, NUM_ROUNDS> & puzzleCategories)
{
	// Time variable to sleep for spinning the wheel
	std::chrono::duration<int, std::milli> timespan(1000);

	// A new wheel is created for each round.
	// Also seed the RNG
	Wheel mainWheel(currentRound);
	srand(std::chrono::system_clock::now().time_since_epoch().count());

	// Players scores and prizes are reset to 0.
	// They must solve the puzzle to win these.
	array<int, NUM_PLAYERS> scores{ 0 };
	array<bool, NUM_PLAYERS> hasPrize{ false };
	array<bool, NUM_PLAYERS> hasJackpot{ false };

	// Increment and display the round
	currentRound++;
	cout << "\nRound " << currentRound << endl;
	int currentPlayer;
	if (currentRound > NUM_PLAYERS)
	{
		currentPlayer = currentRound % NUM_PLAYERS - 1;
	}
	else
	{
		currentPlayer = currentRound - 1;
	}
	char solution[100];
	int consonantsRemaining = 0;
	int vowelsRemaining = 0;

	// Copy the solution from the solutions array in Puzzle.h
	strcpy_s(solution, solutions[currentRound - 1].c_str());

	// Determine how many vowels and consonants are in the puzzle
	for (unsigned i = 0; i < strlen(solution); i++)
	{
		if (isVowel(solution[i]))
		{
			vowelsRemaining++;
		}
		else if (isalpha(solution[i]))
		{
			consonantsRemaining++;
		}
	}
	cout << "The category is: " << CATEGORY[puzzleCategories[currentRound - 1]] << endl;
	
	// C-string that is visible to the players
	char display[100]{ '\0' };

	// Build the display
	for (unsigned i = 0; i < strlen(solution); i++)
	{
		if (isalpha(solution[i]))
		{
			strcat_s(display, BLANK);
		}
		else if (isspace(solution[i]))
		{
			strcat_s(display, SPACE);
		}
		else
		{
			strcat_s(display, BLANK);
			// Displays symbols / numbers in puzzle.
			display[i] = solution[i];
		}
	}

	char usedConsonants[22]{ '\0' };
	char usedVowels[6]{ '\0' };
	bool solved = false;

	cout << "Each dash represents one letter in the puzzle" << endl << endl;
	cout << "\t" << display << endl << endl;

	int actionChoice;
	char guess;
	int wheelValue = 0;
	int jackpot = JACKPOT_START;
	Wedge spinResult;
	do { // This Do while controls the round's puzzle

		bool validChoice = false; // for spin / vowel / solve choice
		do { // This Do while controls the player's actionChoice

			displayActionchoices(currentPlayer, consonantsRemaining, vowelsRemaining);
			actionChoice = validate(0);
			if (actionChoice == int(Action::spin) && consonantsRemaining)
			{
				validChoice = true;
				cout << "Spinning wheel ..." << endl;
				std::this_thread::sleep_for(timespan);
				// Spin wheel multiple times for randomness
				for (unsigned i = 0; i < rand() % 10 + 1; i++)
				{
					mainWheel.spin();
				}
				spinResult = mainWheel.getCurrentWedge();
				wheelValue = spinResult.value;
				jackpot += wheelValue;
				if (spinResult.value > 0)
				{
					if (spinResult.special == int(WedgeID::bitShifter))
					{
						describeBitShifter(spinResult, wheelValue);
					}
					else if (spinResult.special > int(WedgeID::normal))
					{
						cout << "You landed on " << Wheel::SPECIAL_WEDGES[spinResult.special] << endl;
						cout << "It is also worth $" << wheelValue << " per letter." << endl;
						cout << "Its wedge color is " << Wheel::SPECIAL_COLORS[spinResult.special] << endl;
					}
					else
					{
						cout << "You spun $" << wheelValue << endl;
						cout << "The wedge color is " << mainWheel.getColor(spinResult.color) << endl;
					}

					guess = validateConsonant(guess, usedConsonants);
					char guessed[]{ guess, '\0' };
					strcat_s(usedConsonants, guessed);
					cout << "Used consonants: " << usedConsonants << endl;
				} // End if for guessing a consonant
				else if (spinResult.special == int(WedgeID::loseATurn))
				{
					cout << "You landed on " << Wheel::SPECIAL_WEDGES[spinResult.special] << endl;
					cout << "Its color is " << Wheel::SPECIAL_COLORS[spinResult.special] << endl;
					cout << "Lose a turn. Too bad." << endl;
					passTurn(currentPlayer, freeSpins);

				}
				else if (spinResult.special == int(WedgeID::bankrupt))
				{
					bankrupt(spinResult, scores, currentPlayer, hasPrize, hasJackpot, freeSpins);
				}
				else
				{
					// This should not happen
					cout << "Spin again." << endl;
				}
			} // End if for choice spin
			else if (actionChoice == int(Action::vowel) && scores[currentPlayer] >= VOWEL_PRICE && vowelsRemaining)
			{
				validChoice = true;
				scores[currentPlayer] -= VOWEL_PRICE;
				wheelValue = 0;
				guess = validateVowel(guess, usedVowels);
				char guessed[]{ guess, '\0' };
				strcat_s(usedVowels, guessed);
				cout << "Used vowels: " << usedVowels << endl;
			}
			else if (actionChoice == int(Action::vowel))
			{
				cout << "You do not have enough money to buy a vowel." << endl;
				cout << "You need $" << VOWEL_PRICE << " to buy a vowel." << endl;
				cout << "Please spin or solve." << endl;
				actionChoice = 0;
			}
			else if (actionChoice == int(Action::solve))
			{
				validChoice = true;
				cout << "Solve the puzzle!" << endl;
				char answer[100];
				cout << "Enter the solution." << endl;
				cin.getline(answer, 100);
				if (strcmp(answer, solution) == 0)
				{
					cout << "Yes, that's right." << endl;
					solved = true;
					updateTotals(currentPlayer, jackpot, totals, scores, hasPrize, hasJackpot);
				}
				else
				{
					cout << "No, " << answer << " is wrong." << endl;
					passTurn(currentPlayer, freeSpins);
				}
			}
			else
			{
				cout << "That's not a valid choice." << endl;
			}
		} while (validChoice == false);

		// Evaluate the player's action

		// Did the player guess a letter through buying a vowel or spinning and not hitting
		// bankrupt or lose a turn?
		if (actionChoice == int(Action::vowel) || (actionChoice == int(Action::spin) && spinResult.special != int(WedgeID::bankrupt) && spinResult.special != int(WedgeID::loseATurn)))
		{

			int found = 0;
			for (unsigned i = 0; i < strlen(solution); i++)
			{
				if (solution[i] == guess)
				{
					display[i] = guess;
					found++;
				}
			}

			// Displays how many letters were found and adusts score accordingly
			applyGuessResult(found, guess, vowelsRemaining, consonantsRemaining, scores, currentPlayer, wheelValue, actionChoice, spinResult, freeSpins);

			// If a player landed on a special wedge and guessed a correct letter,
			// They receive a special effect.
			if (found && actionChoice == int(Action::spin) && spinResult.special != int(WedgeID::normal))
			{
				ApplyWedgeEffects(spinResult, hasPrize, currentPlayer, hasJackpot, freeSpins, scores);
			}

			// Display the updated display puzzle
			cout << display << endl;

			// If all the letters are revealed in the display,
			// the puzzle is solved.
			if (strcmp(solution, display) == 0)
			{
				cout << "All the letters have been revealed." << endl;
				solved = true;
				updateTotals(currentPlayer, jackpot, totals, scores, hasPrize, hasJackpot);
			}
		}
		
	} while (solved == false);
	cout << "You solved the puzzle!" << endl;
	cout << "You current total is $" << totals[currentPlayer] << endl;
	return;
}

void displayActionchoices(int currentPlayer, int consonantsRemaining, int vowelsRemaining)
{
	cout << "Player " << currentPlayer + 1 << ", what would you like to do?" << endl;
	// Vowels remaining and consonants remaining cannot be 0 at the same time.
	// If they were, the puzzle would be solved!
	if (vowelsRemaining == 0)
	{
		cout << "There are no more vowels left." << endl;
		cout << "Enter 1 to spin or 3 to solve." << endl;
	}
	else if (consonantsRemaining == 0)
	{
		cout << "There are no more consonants left." << endl;
		cout << "Enter 2 to buy a vowel or 3 to solve." << endl;
	}
	else
	{
		cout << "Enter 1 to spin, 2 to buy a vowel," << endl;
		cout << "or 3 to solve." << endl;
	}
	return;
}

void describeBitShifter(Wedge & spinResult, int wheelValue)
{
	cout << "You landed on " << Wheel::SPECIAL_WEDGES[spinResult.special] << endl;
	cout << "Its color is " << Wheel::SPECIAL_COLORS[spinResult.special] << endl;
	cout << "If you guess a correct letter, you earn $" << wheelValue << endl;
	cout << "per correct letter and then your score is shifted left" << endl;
	cout << "one bit, effectively doubling it. Be careful, if the" << endl;
	cout << "letter you guess is not in the puzzle, your score will" << endl;
	cout << "be shifted right two bits, which means you will lose" << endl;
	cout << "3/4ths of your current score. Good luck!" << endl;
	return;
}

char validateConsonant(char guess, char usedConsonants[])
{
	bool validGuess = false;
	do
	{
		cout << "Enter a consonant" << endl;
		cin >> guess;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		guess = tolower(guess);
		if (!isalpha(guess))
		{
			cout << "That is not a letter. Please try again." << endl;
		}
		else if (isVowel(guess))
		{
			cout << "You cannot guess a vowel. Please try again" << endl;
		}
		else if (isGuessed(guess, usedConsonants))
		{
			cout << "That letter has already been guessed." << endl;
			cout << "Pick another letter." << endl;
			cout << "Used consonants: " << usedConsonants << endl;
		}
		else
		{
			validGuess = true;

			if (isRareLetter(guess))
			{
				// Give a random sarcastic response to a rare letter
				// j, q, x, z
				rareLetterResponse(guess);
			}
		}
		
	} while (!validGuess);
	return guess;
}

char validateVowel(char guess, char usedVowels[])
{
	bool validGuess = false;
	do
	{
		cout << "Enter a vowel" << endl;
		cin >> guess;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!isalpha(guess))
		{
			cout << "That is not a letter. Please try again." << endl;
		}
		if (!isVowel(guess))
		{
			cout << "You cannot guess a consonant. Please try again." << endl;
		}
		else if (isGuessed(guess, usedVowels))
		{
			cout << "That letter has already been guessed" << endl;
			cout << "Pick another vowel." << endl;
			cout << "Used vowels: " << usedVowels << endl;
		}
		else
		{
			validGuess = true;
		}
	} while (!validGuess);
	return guess;
}

bool isVowel(char guess)
{
	if (strchr(VOWELS, guess) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isGuessed(char guess, char guessed[])
{
	if (strchr(guessed, guess) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isRareLetter(char guess)
{
	if (strchr(RARE_LETTERS, guess) != nullptr)
	{

		return true;
	}
	else
	{
		return false;
	}
}

void rareLetterResponse(char guess)
{
	int num = rand() % 7;
	switch (num)
	{
	case 0:
		cout << guess << " ? Really?" << endl;
		break;

	case 1:
		cout << "A what?! " << endl;
		break;

	case 2:
		cout << "Hmm... Interesting." << endl;
		break;

	case 3:
		cout << "Are you sure you want to guess " << guess << "?" << endl;
		break;

	case 4:
		cout << "That's an odd choice..." << endl;
		break;

	case 5:
		cout << "You must know something I don't." << endl;
		break;

	case 6:
		cout << "Yep, that would be my first choice." << endl;
		break;
	}
	return;
}

void bankrupt(Wedge &spinResult, array<int, NUM_PLAYERS> &scores, int &currentPlayer, array<bool, NUM_PLAYERS> &hasPrize, array<bool, NUM_PLAYERS> &hasJackpot, array<int, NUM_PLAYERS> & freeSpins)
{
	// Bankrupt means they lose everything except their final total
	cout << "You landed on " << Wheel::SPECIAL_WEDGES[spinResult.special] << endl;
	cout << "Its color is " << Wheel::SPECIAL_COLORS[spinResult.special] << endl;
	cout << "You've gone bankrupt! You lose your score and prizes!" << endl;
	scores[currentPlayer] = 0;

	hasPrize[currentPlayer] = false;
	hasJackpot[currentPlayer] = false;
	passTurn(currentPlayer, freeSpins);
	return;
}

void applyGuessResult(int found, char guess, int &vowelsRemaining, int &consonantsRemaining, array<int, NUM_PLAYERS> &scores, int &currentPlayer, int wheelValue, int actionChoice, Wedge &spinResult, array<int, NUM_PLAYERS> & freeSpins)
{
	if (found > 1)
	{
		if (isVowel(guess))
		{
			vowelsRemaining -= found;
		}
		else
		{
			consonantsRemaining -= found;
			scores[currentPlayer] += wheelValue * found;
		}
		cout << "There are " << found << " " << guess << "'s." << endl;
		cout << "Your score is $" << scores[currentPlayer] << endl;
	}
	else if (found)
	{
		if (isVowel(guess))
		{
			vowelsRemaining--;
		}
		else
		{
			consonantsRemaining--;
			scores[currentPlayer] += wheelValue;
		}
		cout << "There is " << found << " " << guess << endl;

		cout << "Your score is $" << scores[currentPlayer] << endl;
	}
	else
	{
		cout << "Buzz! Sorry, there are no " << guess << "'s." << endl;
		if (actionChoice == int(Action::spin) && spinResult.special == int(WedgeID::bitShifter))
		{
			scores[currentPlayer] >>= 2;
			cout << "Your score's bits were shifted right by 2." << endl;
			cout << "because " << guess << " was not in the puzzle." << endl;
			cout << "Your score is $" << scores[currentPlayer] << endl;
		}
		passTurn(currentPlayer, freeSpins);
	}
	return;
}

void ApplyWedgeEffects(Wedge &spinResult, array<bool, NUM_PLAYERS> &hasPrize, int currentPlayer, array<bool, NUM_PLAYERS> &hasJackpot, array<int, NUM_PLAYERS> & freeSpins, array<int, NUM_PLAYERS> &scores)
{
	if (spinResult.special == int(WedgeID::prize))
	{
		hasPrize[currentPlayer] = true;
	}
	else if (spinResult.special == int(WedgeID::jackpot))
	{
		hasJackpot[currentPlayer] = true;
	}
	else if (spinResult.special == int(WedgeID::freeSpin))
	{
		freeSpins[currentPlayer]++;
	}
	else if (spinResult.special == int(WedgeID::bitShifter))
	{
		scores[currentPlayer] <<= 1;
		cout << "Your score has been shifted left by 1 bit." << endl;
		cout << "Your score is $" << scores[currentPlayer] << endl;
	}
	return;
}

void passTurn(int & currentPlayer, array<int, NUM_PLAYERS> & freeSpins)
{
	char useFreeSpin = ' ';
	if (freeSpins[currentPlayer])
	{
		cout << "Would you like to use a free spin?" << endl;
		cout << "Enter y for yes." << endl;
		cin >> useFreeSpin;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		useFreeSpin = tolower(useFreeSpin);
	}

	if (useFreeSpin == 'y')
	{
		freeSpins[currentPlayer]--;
	}
	else if (currentPlayer == NUM_PLAYERS - 1)
	{
		currentPlayer = 0;
	}
	else
	{
		currentPlayer++;
	}
	return;
}

void updateTotals(int currentPlayer, int jackpot, array<int, NUM_PLAYERS>& totals, array<int, NUM_PLAYERS>& scores, array<bool, NUM_PLAYERS>& hasPrize, array<bool, NUM_PLAYERS> &hasJackpot)
{
	totals[currentPlayer] += SOLVE_BONUS;
	totals[currentPlayer] += scores[currentPlayer];
	if (hasJackpot[currentPlayer])
	{
		totals[currentPlayer] += jackpot;
		cout << "You won the jackpot!" << endl;
	}
	if (hasPrize[currentPlayer])
	{
		totals[currentPlayer] += PRIZE_VALUE;
		cout << "You won a high-end gaming pc worth $" << PRIZE_VALUE << endl;
	}
	return;
}

void bonusRound(int & winningPlayer, array<int, NUM_PLAYERS> & totals, array<int, NUM_PLAYERS> & freeSpins)
{
	std::string bonusRoundSolution;
	int bonusCategory = 0;
	setBonusSolution(bonusRoundSolution, bonusCategory);
	char chosenLetters[22]{ '\0' };
	cout << "Welcome to the bonus round!" << endl;
	char solution[100];
	strcpy_s(solution, bonusRoundSolution.c_str());
	char display[100]{ '\0' };



	// Build the puzzle
	for (unsigned i = 0; i < strlen(solution); i++)
	{
		if (isalpha(solution[i]))
		{
			strcat_s(display, BLANK);
		}
		else if (isspace(solution[i]))
		{
			strcat_s(display, SPACE);
		}
		else
		{
			strcat_s(display, BLANK);
			// Displays symbols / numbers in puzzle.
			display[i] = solution[i];
		}
	}
	cout << "Here is the bonus puzzle." << endl;
	cout << "The category is: " << CATEGORY[bonusCategory] << endl;
	cout << "Each dash represents one letter in the puzzle" << endl << endl;
	cout << "\t" << display << endl << endl;

	cout << "You will be given the following letters: " << endl;
	cout << BONUS_GIVEN_LETTERS << endl;
	cout << "Let's display them in the puzzle." << endl;
	for (unsigned i = 0; i < strlen(solution); i++)
	{
		if (isBonusGivenLetter(solution[i]))
		{
			display[i] = solution[i];
		}
	}

	cout << "\t" << display << endl << endl;

	cout << "You also get " << BONUS_CONSONANTS << " consonants plus one more for " << endl;
	cout << "each unused free spin and one vowel." << endl;

	int totalConsonants = BONUS_CONSONANTS + freeSpins[winningPlayer];
	char bonusChosen[22]{ '\0' };

	char chosen = ' ';
	bool validGuess = false;
	cout << "Please enter " << totalConsonants << " consonants." << endl;
	for (unsigned i = 0; i < totalConsonants; i++)
	{
		validGuess = false;
		do
		{
			cout << "Enter a consonant" << endl;
			cin >> chosen;
			chosen = tolower(chosen);
			if (!isalpha(chosen))
			{
				cout << "That is not a letter. Please try again." << endl;
			}
			else if (isVowel(chosen))
			{
				cout << "You cannot guess a vowel" << endl;
			}
			else if (isBonusGivenLetter(chosen))
			{
				cout << "That letter is already revealed." << endl;
				cout << "Pick another letter." << endl;
			}
			else if (isBonusChosen(chosen, bonusChosen))
			{
				cout << "That letter has already been guessed." << endl;
				cout << "Pick another letter." << endl;
				cout << "Chosen letters: " << bonusChosen << endl;
			}
			else
			{
				validGuess = true;
			}
			if (isRareLetter(chosen))
			{
				rareLetterResponse(chosen);
			}
		} while (!validGuess);
		char guessed[]{ chosen, '\0' };
		strcat_s(bonusChosen, guessed);

	}

	chosen = ' ';
	validGuess = false;

	do
	{
		cout << "Enter a vowel" << endl;
		cin >> chosen;
		if (!isalpha(chosen))
		{
			cout << "That is not a letter. Please try again." << endl;
		}
		if (!isVowel(chosen))
		{
			cout << "You cannot guess a consonant." << endl;
		}
		else if (isBonusGivenLetter(chosen))
		{
			cout << "That letter is already revealed." << endl;
			cout << "Pick another letter." << endl;
		}
		else
		{
			validGuess = true;
		}
	} while (!validGuess);
	char guessed[]{ chosen, '\0' };
	strcat_s(bonusChosen, guessed);

	cout << "Let's see if your chosen letters are in the puzzle." << endl;

	for (unsigned i = 0; i < strlen(solution); i++)
	{
		if (isBonusChosen(solution[i], bonusChosen))
		{
			display[i] = solution[i];
		}
	}
	cout << "\t" << display << endl << endl;

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int chances = NUM_CHANCES;
	bool solved = false;

	if (strcmp(display, solution) == 0)
	{
		cout << "All the letters in the puzzle are revealed." << endl;
		solved = true;
	}
	else
	{
		cout << "You have " << chances << " chances to solve the puzzle." << endl;
		cout << "There is no time limit." << endl;
		while (chances && solved == false)
		{
			cout << "Solve the puzzle!" << endl;
			cout << "You have " << chances << " chances left." << endl;
			char answer[100];
			cout << "Enter the solution." << endl;
			cin.getline(answer, 100);
			if (strcmp(answer, solution) == 0)
			{
				cout << "Yes, that's right." << endl;
				solved = true;
			}
			else
			{
				chances--;
			}
		}
	}

	if (solved == true)
	{
		cout << "You solved the puzzle! Congratulations!" << endl;
		cout << "You win $" << BONUS_PRIZE << endl;
		totals[winningPlayer] += BONUS_PRIZE;
	}
	else
	{
		cout << "You ran out of chances." << endl;
		cout << "The correct puzzle solution is " << solution << endl;
	}
	cout << "Your grand total is $" << totals[winningPlayer] << endl;

}

void setBonusSolution(string & bonusRoundSolution, int & bonusCategory)
{
	default_random_engine engine;
	
	engine.seed(std::chrono::system_clock::now().time_since_epoch().count());

	ifstream bonusFile{ BONUS_FILENAME, ios::in };
	if (!bonusFile)
	{
		cerr << BONUS_FILENAME << " not found. Please make sure " << BONUS_FILENAME << " and" << endl;
		cerr << "this program's .exe file are in the same folder." << endl;
		cerr << "If " << BONUS_FILENAME << "does not exist, " << endl;
		cerr << "create one." << endl;
		exit(1);
	}
	else
	{
		vector<string>puzzleIDs;
		int puzzlesCount = 0;
		string puzzleIDStr, puzzleText, categoryIDStr;
		while (bonusFile)
		{
			getline(bonusFile, puzzleIDStr, SYMBOL);
			puzzleIDs.push_back(puzzleIDStr);
			getline(bonusFile, puzzleText, SYMBOL);
			getline(bonusFile, categoryIDStr, '\n');
			puzzlesCount++;
		}

		bonusFile.close();


		shuffle(puzzleIDs.begin(), puzzleIDs.end(), engine);

		bonusFile.open(BONUS_FILENAME, ios::in);
		while (bonusFile)
		{
			getline(bonusFile, puzzleIDStr, SYMBOL);
			getline(bonusFile, puzzleText, SYMBOL);
			getline(bonusFile, categoryIDStr, '\n');

			if (puzzleIDs[0] == puzzleIDStr)
			{
				bonusRoundSolution = puzzleText;
				bonusCategory = stoi(categoryIDStr);
				bonusFile.close();
			}
		}
		
	}
	return;
}

bool isBonusGivenLetter(char letter)
{
	if (strchr(BONUS_GIVEN_LETTERS, letter) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool isBonusChosen(char letter, char chosenLetters[])
{
	if(strchr(chosenLetters, letter) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
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
		cout << "Enter a number" << endl;
	}
	else if (min != NO_MIN && min < max) {
		// Yes min and Yes max
		minBool = true;
		maxBool = true;
		cout << "Enter a number " << min << " or higher and " << max << " or lower." << endl;
	}
	else if (min < max) {
		// No min Yes Max
		maxBool = true;
		cout << "Enter a number " << max << " or lower." << endl;
	}
	else {
		// Yes min No max
		minBool = true;
		cout << "Enter a number " << min << " or higher." << endl;
	}
	// Part Two
	// This is when the user actually enters the value and when it is 
	// tested to make sure it is valid.

	// This controls the do while loop
	bool notReady = true;

	do {
		// Enter the value
		cin >> value;
		// Test the value to make sure it is valid

		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please enter numbers only and try again." << endl;
		}
		else if ((minBool && maxBool) && (value < min || value > max)) {
			cout << "Please try again." << endl;
			cout << "Enter a number " << min << " or higher and " << max << " or lower." << endl;
		}
		else if ((minBool) && value < min) {
			cout << "Please try again." << endl;
			cout << "Enter a number " << min << " or higher." << endl;

		}
		else if ((maxBool) && value > max) {
			cout << "Please try again." << endl;
			cout << "Enter a number " << max << " or lower." << endl;

		}
		else {
			// Ignore any characters after the input is accepted
			// e.g decimal points, letters, etc.
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			notReady = false;
		}
	} while (notReady);
	// Once the value is ready, return it.
	return value;
}