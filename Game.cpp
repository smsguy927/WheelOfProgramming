//
// Created by smsgu on 10/31/2022.
//

#include "Game.h"

#include <utility>



Game::Game() {
    this->maxTurns = 10;
    this->currentTurn = 0;
    this->currentTurnPlayerID = 0;
    this->currentRound = 0;
    this->currentRoundTurn = 0;
    this->currentRoundTypeID = 0;

    this->isAfterFinalSpin = false;

}

void Game::setMaxTurns(int mt) {
    this->maxTurns = mt;
}

void Game::setCurrentTurn(int ct) {
    this->currentTurn = ct;
}

void Game::setCurrentTurnPlayerID(int ctpID) {
    this->currentTurnPlayerID = ctpID;
}

void Game::setCurrentRound(int cr) {
    this->currentRound = cr;
}

void Game::setCurrentRoundTurn(int crt) {
    this->currentRoundTurn = crt;
}

void Game::setCurrentRoundTypeID(int crtID) {
    this->currentRoundTurn = crtID;
}

int Game::getMaxTurns() const {
    return this->maxTurns;
}

int Game::getCurrentTurn() const {
    return this->currentTurn;
}

int Game::getCurrentTurnPlayerID() const {
    return this->currentTurnPlayerID;
}

int Game::getCurrentRound() const {
    return this->currentRound;
}

int Game::getCurrentRoundTurn() const {
    return this->currentRoundTurn;
}

int Game::getCurrentRoundTypeID() const {
    return this->currentRoundTurn;
}

void Game::setPlayers(std::array<Player, NUM_PLAYERS> playersArr) {
    this->players = std::move(playersArr);
}

void Game::setPlayer(Player pl, int index) {
    this->players[index] = std::move(pl);
}

std::array<Player, NUM_PLAYERS> Game::getPlayers() {
    return this->players;
}

Player Game::getPlayer(int index) {
    return players[index];
}

Player &Game::getPlayerRef(int index) {
    return players[index];
}

void Game::setDefaultPlayers() {
    Player p1 = Player(DEFAULT_P1);
    this->setPlayer(p1,P1_INDEX);
    Player p2 = Player(DEFAULT_P2);
    this->setPlayer(p2,P2_INDEX);
    Player p3 = Player(DEFAULT_P3);
    this->setPlayer(p3,P3_INDEX);
}

void Game::setPuzzles(std::vector<Puzzle> pzs) {
    this->puzzles = std::move(pzs);
}

void Game::setPuzzle(Puzzle pz, int index) {
    this->puzzles[index] = std::move(pz);
}

std::vector<Puzzle> Game::getPuzzles() {
    return this->puzzles;
}

std::vector<Puzzle>& Game::getPuzzlesRef() {
    return this->puzzles;
}

Puzzle Game::getPuzzle(int index) {
    return this->puzzles[index];
}

Puzzle& Game::getPuzzleRef(int index) {
    return this->puzzles[index];
}

void Game::generateRegularPuzzles() {
    auto randomEngine = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    std::ifstream puzzlesFile{ PUZZLES_FILENAME, std::ios::in };
    if (!puzzlesFile)
    {
        std::cerr << PUZZLES_FILENAME << " not found. Please make sure " << PUZZLES_FILENAME << " and" << std::endl;
        std::cerr << "this program's .exe file are in the same folder." << std::endl;
        std::cerr << "If " << PUZZLES_FILENAME << "does not exist, " << std::endl;
        std::cerr << "create one." << std::endl;
        exit(1);
    }
    else
    {
        std::vector<Puzzle> puzzles2;
        std::vector<std::string>puzzleIDs;
        int puzzlesCount = 0;
        while (puzzlesFile)
        {
            std::string record;
            getline(puzzlesFile, record, '\n');
            if(!record.empty())
            {
                Puzzle pz = Puzzle(record);
                this->puzzles.push_back(pz);
            }


        }

        shuffle(this->puzzles.begin(), this->puzzles.end(), randomEngine);

    }
}

void Game::generateBonusPuzzles() {
    auto randomEngine = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    std::ifstream bonusPuzzlesFile{ BONUS_FILENAME, std::ios::in };
    if (!bonusPuzzlesFile)
    {
        std::cerr << BONUS_FILENAME << " not found. Please make sure " << BONUS_FILENAME << " and" << std::endl;
        std::cerr << "this program's .exe file are in the same folder." << std::endl;
        std::cerr << "If " << BONUS_FILENAME << "does not exist, " << std::endl;
        std::cerr << "create one." << std::endl;
        exit(1);
    }
    else
    {
        std::vector<Puzzle> puzzles2;
        std::vector<std::string>puzzleIDs;
        int puzzlesCount = 0;
        while (bonusPuzzlesFile)
        {
            std::string record;
            getline(bonusPuzzlesFile, record, '\n');
            if(!record.empty())
            {
                Puzzle pz = Puzzle(record);
                this->bonusPuzzles.push_back(pz);
            }


        }

        shuffle(this->bonusPuzzles.begin(), this->bonusPuzzles.end(), randomEngine);

    }
}

void Game::play() {

    do {
        Round currentRoundPlaying;

            currentRoundPlaying = generateNewRound();
            setCurrentTurnPlayerID(calcStartPlayer());
            std::cout << "Round " << currentRoundPlaying.getCurrentRoundR() + 1 << std::endl;
            std::this_thread::sleep_for(oneSecInMs);

        this->rounds.push_back(currentRoundPlaying);
        // Simulate Game Playing

        playRound();
        setCurrentRound(getCurrentRound() + 1);
    } while(!this->isAfterFinalSpin);
    handleMainGameEnd();
    std::cout << "It's time for the Bonus Round" << std::endl;
}

Round Game::generateNewRound() {
    std::vector<PlayerScore> playerScores;
    for(auto & player : players) {
        int playerID = player.getPlayerID();
        int roundID = this->getCurrentRound();
        int freeSpins = player.getFreeSpins();
        PlayerScoreInit playerScoreInit{playerID, roundID, freeSpins};
        auto playerScore = PlayerScore(playerScoreInit);
        playerScores.push_back(playerScore);
    }
    int currentRound1 = this->getCurrentRound();
    if(currentRound1 >= this->puzzles.size())
    {
       std::cout << "We are out of puzzles!" << std::endl;
       return Round();
    }
    Puzzle pz = this->puzzles[currentRound1];
    int maxTurns2 = this->getMaxTurns();
    int currentTurn2 = this->getCurrentTurn();
    int ctPlayerId2 = this->getCurrentTurnPlayerID();
    int currentRound2 = this->getCurrentRound();
    int crt2 = this->getCurrentRoundTurn();
    int crtID2 = this->getCurrentRoundTypeID();
    RoundInit ri{playerScores, pz, maxTurns2, currentTurn2, ctPlayerId2, currentRound2, crt2, crtID2};
    Round newRound = Round(ri);
    return newRound;
}

void Game::playRound() {
    if(isOutOfPuzzles())
    {
        return;
    }
    Puzzle& currentPuzzle = getPuzzleRef(currentRound);

    introducePuzzle(currentPuzzle);
    // Time variable to sleep for spinning the wheel
    std::chrono::duration<int, std::milli> timespan(1000);

    // A new wheel is created for each round.
    Wheel mainWheel(this->getCurrentRound());
    this->wheels.push_back(mainWheel);


    std::cout << "The top value is: $" << mainWheel.getTopValue() << std::endl;

    do {
        playTurn();
    } while(!currentPuzzle.getIsSolved());
    handleRoundEnd();
    std::cout << std::endl << std::endl;
}

void Game::playTurn() {
    std::cout << "Player " << getCurrentTurnPlayerID() + 1 << ", it's your turn." << std::endl;
    if (isTimeForFinalSpin()) {
        handleFinalSpin();
    }
    TurnInit ti = generateTurnInit();
    Turn newTurn = Turn(ti);
    turns.push_back(newTurn);
    Turn& turnRef = getTurnRef(currentTurn);
    std::cout << "Turn " << newTurn.getTurnID() << std::endl;
    if(isExpress){
        displayExpressAction();
    }
    else if (isAfterFinalSpin) {
        displayFinalSpinAction();
    } else {
        displayActionChoices();
    }

    std::pair<int, int> actionChoice = assignActionChoice();
    turnRef.setActionTimeUsedMs(actionChoice.second);
    auto action = static_cast<TnAction>(actionChoice.first);
    turnRef.setActionID(actionChoice.first);
    turnRef.setTurnAction(static_cast<TnAction>(actionChoice.first));
    char symbol = mode.getSymbol();
    char light = static_cast<char>(GameModeID::light);
    char normal = static_cast<char>(GameModeID::normal);
    char strict = static_cast<char>(GameModeID::strict);
    if(symbol != light ) {
        if(turnRef.getActionTimeUsedMs() > ACTION_TIME_LIMIT_MS){
            turnRef.setActionID(static_cast<int>(TnAction::outOfTime));
            turnRef.setTurnAction(TnAction::outOfTime);
            turnRef.setTurnResult(TurnResult::actionTimeUp);
            action = TnAction::outOfTime;
        }
    }
    evaluateAction(action);
    if(turnRef.shouldEvaluateGuess()){
        evaluateGuess();
    }
    displayPuzzle();
    handleTurnEnd(turnRef);
}

void Game::introducePuzzle(Puzzle &currentPuzzle) {
    std::cout << "Each " << PZ_BLANK  << " represents one letter in the puzzle" << std::endl;
    std::cout << "The category is: " << currentPuzzle.getCategory() << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);

    std::cout << "\t" << currentPuzzle.getDisplay() << std::endl << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
}

int Game::calcStartPlayer() const {
    return getCurrentRound() % NUM_PLAYERS;
}

TurnInit Game::generateTurnInit() const {
    TurnInit turnInit{};
    turnInit.playerID = this->getCurrentTurnPlayerID();
    turnInit.turnID = this->getCurrentTurn();

    turnInit.isAfterFinalSpin = this->getIsAfterFinalSpin();
    turnInit.isExpress = this->getIsExpress();
    return turnInit;
}



void Game::setIsAfterFinalSpin(bool isAfs) {
    this->isAfterFinalSpin = isAfs;
}



bool Game::getIsAfterFinalSpin() const {
    return this->isAfterFinalSpin;
}

void Game::setIsExpress(bool ie) {
    this->isExpress = ie;
}

bool Game::getIsExpress() const {
    return this->isExpress;
}

void Game::setRounds(std::vector<Round> rds) {
    this->rounds = std::move(rds);
}

void Game::setRound(Round r, int i) {
    this->rounds[i] = std::move(r);
}

void Game::setTurns(std::vector<Turn> tns) {
    this->turns = std::move(tns);
}

void Game::setTurn(Turn t, int i) {
    this->turns[i] = std::move(t);
}

void Game::setWheels(std::vector<Wheel> ws) {
    this->wheels = std::move(ws);
}

void Game::setWheel(Wheel w, int i) {
    this->wheels[i] = w;
}

std::vector<Round> Game::getRounds() {
    return this->rounds;
}

std::vector<Round>& Game::getRoundsRef() {
    return this->rounds;
}

Round Game::getRound(int i) {
    return this->rounds[i];
}

Round& Game::getRoundRef(int i) {
    return this->rounds[i];
}

std::vector<Turn> Game::getTurns() {
    return this->turns;
}

std::vector<Turn>& Game::getTurnsRef() {
    return this->turns;
}

Turn Game::getTurn(int i) {
    return this->turns[i];
}

Turn& Game::getTurnRef(int i) {
    return turns[i];
}

std::vector<Wheel> Game::getWheels() {
    return this->wheels;
}

std::vector<Wheel>& Game::getWheelsRef() {
    return this->wheels;
}

Wheel Game::getWheel(int i) {
    return this->wheels[i];
}

Wheel& Game::getWheelRef(int i) {
    return this->wheels[i];
}

void Game::incrementTurn() {
    this->setCurrentTurn(this->getCurrentTurn() + 1);
}

void Game::passTurn() {
    int currentPlayerID = this->getCurrentTurnPlayerID();
    if(currentPlayerID == this->getPlayers().size() - 1) {
        this->setCurrentTurnPlayerID(0);
    } else {
        this->setCurrentTurnPlayerID(currentPlayerID + 1);
    }
}

Puzzle Game::selectPuzzle() {
    return this->puzzles[this->getCurrentRound()];
}

Puzzle& Game::getPuzzleRef() {
    return this->puzzles[this->getCurrentRound()];
}

void Game::displayActionChoices() {

    std::cout << "Player " << this->getCurrentTurnPlayerID() + 1 << ", what would you like to do?" << std::endl;
    std::cout << "Your Score is $" << getCurrentPlayerScoreRef().getCash() << std::endl;
    // Vowels remaining and consonants remaining cannot be 0 at the same time.
    // If they were, the puzzle would be solved!
    if (noMoreVowelsInCurrentRound())
    {
       std::cout << "There are no more vowels left." << std::endl;
       std::cout << "Enter 1 to spin or 3 to solve." << std::endl;
    }
    else if (cannotAffordAVowel())
    {
        std::cout << "You do not have enough money to buy a vowel." << std::endl;
        std::cout << "Enter 1 to spin or 3 to solve." << std::endl;
    }
    else if (noMoreConsonantsInCurrentRound())
    {
        std::cout << "There are no more consonants left." << std::endl;
        std::cout << "Enter 2 to buy a vowel or 3 to solve." << std::endl;
    }
    else
    {
        std::cout << "Enter 1 to spin, 2 to buy a vowel," << std::endl;
        std::cout << "or 3 to solve." << std::endl;
    }
}

bool Game::noMoreConsonantsInCurrentRound() {
    int thisRound = this->getCurrentRound();
    return this->getPuzzle(thisRound).areNoConsonantsLeft();
}

bool Game::noMoreVowelsInCurrentRound() {
    int thisRound = this->getCurrentRound();
    return this->getPuzzle(thisRound).areNoVowelsLeft();
}

bool Game::cannotSpin() {
    return this->noMoreConsonantsInCurrentRound();
}

bool Game::canSpin() {
    return !cannotSpin();
}

bool Game::cannotBuyAVowel() {
    return this->noMoreVowelsInCurrentRound() || cannotAffordAVowel();
}

bool Game::canBuyAVowel() {
    return !cannotBuyAVowel();
}

bool Game::cannotAffordAVowel() {
    return getCurrentPlayerCash() < VOWEL_PRICE;
}

int Game::getCurrentPlayerCash() {
    return this->rounds[this->getCurrentRound()].getPlayerScores()[currentTurnPlayerID].getCash();
}



std::pair<int, int> Game::generateActionChoice() {
    int spin = static_cast<int>(TnAction::spin);
    int solve = static_cast<int>(TnAction::solve);
    int choice;
    int timeUsedMs = 0; 
    bool validChoice = false;
    auto jrdTimer = JrdTimer();
    do{
        choice = validate(spin, solve);
        if(isValidActionChoice(choice)) {
            validChoice = true;
        }
    } while(!validChoice);
    timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
    return std::make_pair(choice, timeUsedMs);
}

void Game::handleSpin() {
    Wheel wheel = getWheel(getCurrentRound());
    wheel.spin();
    std::cout << "Spinning wheel ..." << std::endl;
    std::this_thread::sleep_for(oneSecInMs);
    SpinResult spinResult = SpinResult(wheel.getCurrentWedge());
    spinResult.display();
    Turn& turnRef = getCurrentTurnRef();
    turnRef.setTnSpinResult(spinResult);
    if(spinResult.getSpecialID() == static_cast<int>(SpecialType::bankrupt)) {
        bankrupt();
        turnRef.setTurnResult(TurnResult::bankrupt);
        turnRef.setGuess(NULL_CHAR);
    }
    else if (spinResult.getIsTurnEnding()) {
        std::cout << "Lose a turn. Too bad." << std::endl;
        getCurrentTurnRef().setTurnResult(TurnResult::loseATurn);
        passTurn();
    }
    else {

        displayPuzzle();
        displayUsedConsonants();
        auto jrdTimer = JrdTimer();
        char guess = generateGuess();
        int timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
        getTurnRef(currentTurn).setGuess(guess);
        turnRef.setLetterTimeUsedMs(timeUsedMs);
        std::cout << turns[currentTurn].getGuess() << "?" <<std::endl;
    }
}

void Game::handleBuyAVowel() {
    subtractVowelPrice();

    displayPuzzle();
    displayUsedConsonants();
    auto jrdTimer = JrdTimer();
    char guess = generateGuess();
    int timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
    Turn& turnRef = getCurrentTurnRef();
    turnRef.setGuess(guess);
    turnRef.setLetterTimeUsedMs(timeUsedMs);
    std::cout << turnRef.getGuess() << "?" <<std::endl;
}

void Game::handleSolve() {
    displayPuzzle();
    auto jrdTimer = JrdTimer();
    std::string attempt = generateSolveAttempt();
    int timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
    Puzzle& puzzleRef = getPuzzleRef();
    Turn& turnRef = getCurrentTurnRef();
    turnRef.setSolveTimeUsedMs(timeUsedMs);
    turnRef.setTurnAction(TnAction::solve);
    turnRef.setSolveAttempt(attempt);
    if(puzzleRef.isCorrectSolution(attempt) && (mode.getSymbol() == static_cast<char>(GameModeID::light)
    || turnRef.getSolveTimeUsedMs() <= SOLVE_TIME_LIMIT_MS)){
        puzzleRef.setDisplay(attempt);
        turnRef.setSolveResult(SolveResult::right);
        std::cout << "That's right!" << std::endl;
    } else if(turnRef.getSolveTimeUsedMs() > SOLVE_TIME_LIMIT_MS){
        std::cout << "No, " << attempt << " cannot be accepted." << std::endl;
        std::cout << "You're out of time!" << std::endl;
        turnRef.setSolveResult(SolveResult::outOfTime);
    } else {
        std::cout << "No, " << attempt << " is wrong." << std::endl;
        turnRef.setSolveResult(SolveResult::wrong);
    }
}

void Game::bankrupt() {
    PlayerScore playerScore = rounds[getCurrentRound()].getPlayerScore(currentTurnPlayerID);
    playerScore.setCash(0);
    playerScore.setHasPrize(false);
    playerScore.setHasJackpot(false);
    rounds[getCurrentRound()].setPlayerScore(playerScore, currentTurnPlayerID);
    std::cout << "You've gone bankrupt! You lose your score and prizes!" << std::endl;

    char freeSpinChoice = generateFreeSpinChoice();
    if (isUsingFreeSpin(freeSpinChoice))
    {
        useFreeSpin();

    }
    else {
        passTurn();
    }
}

char Game::generateFreeSpinChoice() {
    char choice = NO;
    if(hasFreeSpins()) {
        std::cout << "Do you want to use a free spin?" << std::endl;
        std::cout << "Press " << YES << " for yes." << std::endl;
        std::cin >> choice;
    }
    return choice;
}

bool Game::isUsingFreeSpin(char choice) {
    return choice == YES;
}

bool Game::hasFreeSpins() {
    return getCurrentPlayerFreeSpins();
}

void Game::useFreeSpin() {
    setCurrentPlayerFreeSpins(getCurrentPlayerFreeSpins() - 1);
}

int Game::getCurrentPlayerFreeSpins() {
    return rounds[getCurrentRound()].getPlayerScore(currentTurnPlayerID).getFreeSpins();
}

void Game::setCurrentPlayerFreeSpins(int spins) {
    rounds[getCurrentRound()].getPlayerScore(currentTurnPlayerID).setFreeSpins(spins);
}

void Game::displayUsedConsonants() {
    std::cout << "Used Consonants: " << getUsedConsonants() << std::endl;
}

void Game::displayUsedVowels() {
    std::cout << "Used Vowels: " << getUsedVowels() << std::endl;
}

void Game::displayPuzzle() {
    std::cout << getPuzzleView() << std::endl;
}

std::string Game::getUsedConsonants() {
    return selectPuzzle().getUsedConsonantStr();
}

std::string Game::getUsedVowels() {
    return selectPuzzle().getUsedVowelStr();
}

std::string Game::getPuzzleView() {
    return selectPuzzle().getDisplay();
}

PlayerScore Game::getCurrentPlayerScore() {
    return this->rounds[this->getCurrentRound()].getPlayerScores()[currentTurnPlayerID];
}



char Game::generateGuess() {
    char guess = ' ';
    Puzzle& puzzleRef = getPuzzleRef(currentRound);
    auto turnAction = getTurn(currentTurn).getTurnAction();
    if(turnAction == TnAction::spin) {
        guess = puzzleRef.validateConsonant();
    } else if (turnAction == TnAction::vowel) {
        guess = puzzleRef.validateVowel();
    } else if(isAfterFinalSpin) {
        guess = validateConsonantOrVowel();
    } else {
        guess = validatePuzzleCharacter();
    }
    return guess;
}



char Game::validateConsonantOrVowel() {
    char guess = ' ';
    bool validGuess = false;
    do
    {
        std::cout << "Enter a letter" << std::endl;
        std::cin >> guess;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        guess = toLower(guess);
        if (!isalpha(guess))
        {
            std::cout << "That is not a letter. Please try again." << std::endl;
        }
        else if (getPuzzle(currentRound).isGuessed(guess))
        {
            std::cout << "That letter has already been guessed." << std::endl;
            std::cout << "Pick another letter." << std::endl;
            displayUsedVowels();
        }
        else
        {
            validGuess = true;
        }
    } while (!validGuess);
    return guess;
}

void Game::evaluateGuess() {
    char guess = getTurnRef(currentTurn).getGuess();
    Puzzle& puzzleRef = getPuzzleRef(currentRound);
    int guessResult = 0;
    if(isalpha(guess) && isInTime())
    {
        // See if the letter is in the puzzle
        guessResult = puzzleRef.evaluateGuess(guess);
        respondToGuessResult(guessResult);
    } else {
        getCurrentTurnRef().setTurnResult(TurnResult::guessTimeUp);
        std::cout << "Not in time!" << std::endl;
    }
    if(isInTime()) {
        puzzleRef.applyGuessResult(guess);
    } else {
        std::cout << "Lose a turn." << std::endl;
    }
    auto turnAction = getCurrentTurnRef().getTurnAction();
    if(turnAction== TnAction::spin || turnAction== TnAction::express){
        applySpinEffects();
    }else if(turnAction == TnAction::fsConsonant){
        applyFinalSpinEffects();
    } else if(turnAction == TnAction::fsVowel && guessResult){
        handleSolve();
    }

}



char Game::getGuess() {
    return turns[currentTurn].getGuess();
}

void Game::respondToGuessResult(int guessResult) {

    Turn& turnRef = getCurrentTurnRef();
    char guess = getGuess();
    if(Puzzle::isPzConsonant(guess)){


        getCurrentTurnRef().setConsonantsFound(guessResult);
    }
    if(guessResult == PZ_ERROR) {
        std::cout << "Your guess could not be evaluated." << std::endl;
        turnRef.setTurnResult(TurnResult::error);
     } else if (guessResult == REPEAT_GUESS) {
        std::cout << "That letter has already been guessed. Lose a turn." << std::endl;
        turnRef.setTurnResult(TurnResult::repeatGuess);
    } else if (guessResult > 1) {
        std::cout << "There are " << guessResult << " " << guess << "'s." << std::endl;
        turnRef.setTurnResult(TurnResult::right);
    } else if (guessResult == 1) {
        std::cout << "There is " << guessResult << " " << guess << std::endl;
        turnRef.setTurnResult(TurnResult::right);
    } else {
        std::cout << "Buzz! Sorry, there are no " << guess << "'s." << std::endl;
        turnRef.setTurnResult(TurnResult::wrong);
    }

}

void Game::applySpinSpecialEffects() {
    auto scoreRef = getCurrentPlayerScoreRef();
    auto turnRef = getCurrentTurnRef();
    auto spinResultRef = getCurrentSpinResultRef();
    auto specialType = spinResultRef.getSpecialType();
    if(specialType == SpecialType::express && turnRef.getConsonantsFound()){
        handleExpress();
    }
    else if(specialType == SpecialType::jackpot) {
        scoreRef.setHasJackpot(true);
    } else if (specialType == SpecialType::prize) {
        scoreRef.setHasPrize(true);
    } else if (specialType == SpecialType::freeSpin){
       addFreeSpin();
    } else if (specialType == SpecialType::bitShifter && turnRef.getTurnResult() == TurnResult::wrong){
        negativeBitShift();
    } else if (specialType == SpecialType::bitShifter && turnRef.getTurnResult() == TurnResult::right){
        positiveBitShift();
    }

}

void Game::applySpinEffects() {
    int newScore = getCurrentPlayerScore().getCash();
    Turn& turnRef = getCurrentTurnRef();
    SpinResult& spinResultRef = turnRef.getTnSpinResultRef();
    int spinValue;
    if(isExpress){
        spinValue = Wheel::SPECIAL_VALUE;
        spinResultRef.setSpecialType(SpecialType::express);
    } else {
        spinValue = turnRef.getTnSpinResultRef().getValue();
    }

    int consonantsFound = turnRef.getConsonantsFound();
    newScore += consonantsFound * spinValue;
    getCurrentPlayerScoreRef().setCash(newScore);
    if (spinResultRef.getSpecialType() != SpecialType::normal) {
        applySpinSpecialEffects();
    }
}

void Game::applyFinalSpinEffects() {
    int newScore = getCurrentPlayerScore().getCash();
    Turn& turnRef = getCurrentTurnRef();

    int consonantsFound = turnRef.getConsonantsFound();

    newScore += consonantsFound * finalSpinValue;
    getCurrentPlayerScoreRef().setCash(newScore);
    if(consonantsFound){
        handleSolve();
    }

}

Turn& Game::getCurrentTurnRef() {
    return turns[currentTurn];
}

PlayerScore &Game::getCurrentPlayerScoreRef() {
    return this->getRoundRef(currentRound).getPlayerScoreRef(currentTurnPlayerID);
}

SpinResult &Game::getCurrentSpinResultRef() {
    return getCurrentTurnRef().getTnSpinResultRef();
}

void Game::addFreeSpin() {
    PlayerScore& playerScoreRef = getCurrentPlayerScoreRef();
    playerScoreRef.setFreeSpins(playerScoreRef.getFreeSpins() + 1);
}

void Game::positiveBitShift() {
    PlayerScore& playerScoreRef = getCurrentPlayerScoreRef();
    playerScoreRef.setCash(playerScoreRef.getCash() << BIT_SHIFTER_RIGHT);
    std::cout << "Your score has been shifted left by " << BIT_SHIFTER_RIGHT << " bit." << std::endl;
}

void Game::negativeBitShift() {
    PlayerScore& playerScoreRef = getCurrentPlayerScoreRef();
    playerScoreRef.setCash(playerScoreRef.getCash() >> BIT_SHIFTER_WRONG);
    std::cout << "Your score has been shifted right by " << BIT_SHIFTER_WRONG << " bits." << std::endl;
}

void Game::subtractVowelPrice() {
    PlayerScore& scoreRef = getCurrentPlayerScoreRef();
    scoreRef.setCash(scoreRef.getCash() - VOWEL_PRICE);
}

void Game::checkAndSetIsPuzzleSolved() {
    Puzzle& puzzleRef = getPuzzleRef(currentRound);
    if (isPuzzleSolved(puzzleRef)) {
        puzzleRef.setIsSolved(true);
    }

}

bool Game::isPuzzleSolved(Puzzle& puzzleRef) {
    return puzzleRef.getDisplay() == puzzleRef.getSolution();
}

void Game::handleRoundEnd() {
    PlayerScore& scoreRef = getCurrentPlayerScoreRef();
    scoreRef.setIsSolver(true);
    Player& playerRef = getPlayerRef(currentTurnPlayerID);
    Wheel& wheelRef = getWheelRef(currentRound);
    int previousTotal = playerRef.getTotalWinnings();
    int roundSubTotal = scoreRef.getCash() + SOLVE_BONUS;
    bool hasPrize = scoreRef.getHasPrize();
    bool hasJackpot = scoreRef.getHasPrize();
    int jackpot = wheelRef.getJackpot();
    int newTotal = 0;
    std::cout << "Player " << currentTurnPlayerID << ", you won $" << roundSubTotal << " that round..." << std::endl;
    if(hasPrize){
        std::cout << "...and you won a high-end gaming pc worth $" << PRIZE_VALUE << std::endl;
        newTotal += PRIZE_VALUE;
    }
    if(hasJackpot){
        std::cout << "...and you won the jackpot worth $" << jackpot << std::endl;
        newTotal += jackpot;
    }
    newTotal += previousTotal + roundSubTotal;
    std::cout << "...for a grand total of $" << newTotal << std::endl;
    playerRef.setTotalWinnings(newTotal);
    if(isExpress){
        handleExpressEnd();
    }
}

void Game::handleMainGameEnd() {

    int winningPlayer = determineWinner();
    setWinningPlayerID(winningPlayer);
    std::cout << "Player " << getWinningPlayerID() + 1 << ", you are going to the bonus round!" << std::endl;
    generateBonusRound();
    auto bonusRoundRef = getBonusRoundRef();
    bonusRoundRef.play();
}

 std::string Game::generateSolveAttempt() {
    std::string attempt;
    std::cout << "Solve the puzzle!" << std::endl;
    std::getline(std::cin, attempt);
    if(attempt.empty()){
        attempt.push_back('!');
    }
    return attempt;
}

bool Game::isWrong(Turn & turnRef) {
    return turnRef.getTurnResult() == TurnResult::wrong || turnRef.getTurnResult() == TurnResult::repeatGuess ||
    turnRef.getSolveResult() == SolveResult::wrong;
}

bool Game::isOutOfTime(Turn & turnRef) {
    return turnRef.getTurnResult() == TurnResult::actionTimeUp || turnRef.getTurnResult() == TurnResult::guessTimeUp
    || turnRef.getSolveResult() == SolveResult::outOfTime;
}

void Game::evaluateAction(TnAction action) {
    if(action == TnAction::spin)
    {
        handleSpin();
    }
    else if(action == TnAction::vowel)
    {
        handleBuyAVowel();
    }
    else if(action == TnAction::solve)
    {
        handleSolve();
    }
    else if (action == TnAction::fsConsonant){
        handleFinalSpinLetter();
    }
    else if (action == TnAction::express){
        handleExpressLetter();
    }
    else if (action == TnAction::outOfTime){
        std::cout << "You're out of time!" << std::endl;
        std::cout << "Lose a turn. Too bad." << std::endl;
    }
}

void Game::displayFinalSpinAction() {
    std::cout << "Guess a letter" << std::endl;
    std::cout << "Your current score is $" << getCurrentPlayerCash() << std::endl;
}

void Game::setFinalSpinValue(int fsv) {
    this->finalSpinValue = fsv;
}

int Game::getFinalSpinValue() const {
    return finalSpinValue;
}

void Game::handleFinalSpin() {
    this->setIsAfterFinalSpin(true);
    Wheel& wheelRef = getWheelRef(currentRound);
    std::cout << "It's time for the final spin!" << std::endl;
    std::cout << "Spinning wheel ..." << std::endl;
    std::cout << "Vowels are worth nothing and consonants are worth..." << std::endl;
    wheelRef.spin();
    setFinalSpinValue(static_cast<int>(wheelRef.getCurrentWedge().value) + FINAL_SPIN_BONUS);
    std::this_thread::sleep_for(oneSecInMs);
    std::cout << "$" << getFinalSpinValue() << " each" << std::endl;
}

bool Game::isTimeForFinalSpin() const {
    return this->getCurrentTurn() >= this->getMaxTurns() && !isAfterFinalSpin;
}

void Game::handleFinalSpinLetter() {
    displayPuzzle();
    displayUsedConsonants();
    displayUsedVowels();
    auto jrdTimer = JrdTimer();
    char guess = generateGuess();
    int timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
    Turn& turnRef = getCurrentTurnRef();
    turnRef.setGuess(guess);
    if(Puzzle::isPzVowel(guess)){
        handleSolve();
    }
    std::cout << turns[currentTurn].getGuess() << "?" <<std::endl;
}

int Game::determineWinner() {
    auto result = std::max_element(players.begin(), players.end());
    int winningPlayer = result - players.begin();
    return winningPlayer;
}

void Game::generateBonusRound() {

    BonusRoundInit bri = generateBonusRoundInit();
    BonusRound bonusRoundG = BonusRound(bri);
    setBonusRound(bonusRoundG);
}

BonusRoundInit Game::generateBonusRoundInit() {

    int playerID = getWinningPlayerID();
    Player player = getPlayer(playerID);
    int bonusConsonants = BASE_BONUS_CONSONANTS + player.getFreeSpins();
    int bonusVowels = BASE_BONUS_VOWELS + player.getAwesomePoints();
    Puzzle puzzle = bonusPuzzles[0];
    GameMode gameMode = getGameModeRef();
    BonusRoundInit bri = BonusRoundInit{playerID, player, bonusConsonants, bonusVowels, puzzle, gameMode};
    return bri;
}

void Game::setWinningPlayerID(int wpID) {
    this->winningPlayerID = wpID;
}

int Game::getWinningPlayerID() const {
    return winningPlayerID;
}

void Game::setBonusRound(BonusRound br) {
    this->bonusRound = std::move(br);
}

BonusRound Game::getBonusRound() {
    return this->bonusRound;
}

BonusRound &Game::getBonusRoundRef() {
    return this->bonusRound;
}

void Game::handleExpress() {
    if(isExpress){
        expressTurnLength++;
    } else {
        char expressChoice = generateStartExpressChoice();
        if(expressChoice == YES){
            isExpress = true;
            expressTurnLength = 0;
        } else {
            passTurn();
            return;
        }
    }
}

char Game::generateStartExpressChoice() {
    char choice = NO;

        std::cout << "Do you want to start an express run?" << std::endl;
        std::cout << "You can guess consonants for $" << Wheel::SPECIAL_VALUE << " per letter." << std::endl;
        std::cout << "If you give an incorrect response, you will go bankrupt." << std::endl;
        std::cout << "If not, your turn will end." << std::endl;
        std::cout << "Press " << YES << " for yes." << std::endl;
        std::cin >> choice;

    return choice;
}

void Game::handleExpressLetter() {

    displayPuzzle();
    displayUsedConsonants();
    displayUsedVowels();

    auto jrdTimer = JrdTimer();
    char guess = generateGuess();
    int timeUsedMs = static_cast<int>(jrdTimer.Elapsed().count());
    Turn& turnRef = getCurrentTurnRef();
    turnRef.setGuess(guess);
    turnRef.setLetterTimeUsedMs(timeUsedMs);
    if(Puzzle::isPzVowel(guess)){
        turnRef.setTurnAction(TnAction::expressVowel);
        if(cannotAffordAVowel() || noMoreVowelsInCurrentRound()) {
            turnRef.setGuess(NULL_CHAR);
            handleSolve();
            return;
        }
        subtractVowelPrice();
    }
    std::cout << turns[currentTurn].getGuess() << "?" <<std::endl;
}

void Game::displayExpressAction() {
    std::cout << "Your current score is $" << getCurrentPlayerCash() << std::endl;
    if(cannotAffordAVowel()){
        std::cout << "Enter a consonant to guess it or anything else to solve." << std::endl;
        std::cout << "You do not have enough money to buy a vowel." << std::endl;
    } else {
        std::cout << "Enter a letter to guess it or anything else to solve." << std::endl;
        std::cout << "Vowels still cost $" << VOWEL_PRICE <<"." << std::endl;
    }

}

char Game::validatePuzzleCharacter() {
    char guess = ' ';

    std::cout << "Enter a letter to guess it or anything else to solve" << std::endl;
    std::cin >> guess;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    guess = toLower(guess);
    if (!isalpha(guess)) {
        handleSolve();
        return guess;
    } else if (getPuzzle(currentRound).isGuessed(guess)) {
        std::cout << "That letter has already been guessed." << std::endl;
        std::cout << "Now you will solve." << std::endl;
        handleSolve();
        return NULL_CHAR;
    }
    return guess;
}

void Game::handleExpressEnd() {
    isExpress = false;
    int expressTurns = expressTurnLength;
    expressTurnLength = GAME_NULL_INT;
    int maxTurnAdjustment = calcExpressMaxTurnsAdjustment(expressTurns);
    setMaxTurns(getMaxTurns() + maxTurnAdjustment);
}

int Game::calcExpressMaxTurnsAdjustment(int expressTurns) {
    expressTurns *= EXPRESS_TURN_FRACTION.first;
    expressTurns /= EXPRESS_TURN_FRACTION.second;
    return expressTurns;
}

bool Game::isOutOfPuzzles() {
    return this->getCurrentRound() >= puzzles.size();
}

void Game::handleOutOfPuzzles() {
    std::cout << "We are out of puzzles!" << std::endl;
    this->setIsAfterFinalSpin(true);
}

void Game::handleTurnEnd(Turn & turnRef) {
    if(isWrong(turnRef) && isExpress || isOutOfTime(turnRef) && isExpress){
        isExpress = false;
        handleExpressEnd();
        bankrupt();

    }
    else if (isWrong(turnRef) || isOutOfTime(turnRef)) {
        passTurn();
    }
    incrementTurn();
    checkAndSetIsPuzzleSolved();
}

std::pair<int, int> Game::assignActionChoice() {
    if(isExpress){
        return std::make_pair(static_cast<int>(TnAction::express), 0);
    }
    else if (isAfterFinalSpin) {
        return std::make_pair(static_cast<int>(TnAction::fsConsonant), 0);
    }
    else {
        return generateActionChoice();
    }
}

bool Game::isValidActionChoice(int choice) {
    int spin = static_cast<int>(TnAction::spin);
    int vowel = static_cast<int>(TnAction::vowel);
    int solve = static_cast<int>(TnAction::solve);
    return choice == solve || choice == spin && canSpin() || choice == vowel && canBuyAVowel();
}

void Game::setMode(char gm) {
    GameMode gameMode = GameMode(gm);
    this->mode = gameMode;
}

GameMode &Game::getGameModeRef() {
    return mode;
}

bool Game::isInTime() {
    return mode.getSymbol() == static_cast<char>(GameModeID::light) ||
    getCurrentTurnRef().getLetterTimeUsedMs() <= LETTER_TIME_LIMIT_MS ;
}

void Game::setup() {
    setDefaultPlayers();
    generateRegularPuzzles();
    generateBonusPuzzles();
    char secretHostNameChoice = getSecretHostNameChoice();

    if(secretHostNameChoice == SECRET_HOST) {
        std::string secretHostName = getSecretHostName();
        this->gsHost.setName(secretHostName);
    }
    if(secretHostNameChoice != SECRET_SKIP_INTRO){
        this->gsHost.sayIntroduction();
    }

    int gameLength = GameShowHost::generateGameLength();
    char explainRules = GameShowHost::askToExplainRules();
    if (explainRules == YES) {
        GameShowHost::explainRules();
    }
    char gameMode = GameShowHost::generateGameMode();
    setGameParameters(gameLength, gameMode);
    if(secretHostNameChoice != SECRET_SKIP_INTRO) {
        gsHost.introducePlayers(players);
    }
}

char Game::getSecretHostNameChoice() {
    std::cout << "Press any key to continue..." << std::endl;
    char choice = static_cast<char>(tolower(std::cin.get()));
    return choice;
}

std::string Game::getSecretHostName() {
    std::string myName;
    std::cout << "Hello, game show host. What is your name?" << std::endl;
    std::getline(std::cin >> std::ws, myName);
    return myName;
}

void Game::setGameParameters(int length, char mode2) {
    setMaxTurns(MAX_TURNS[length]);
    setMode(mode2);

    if(maxTurns == 0) {
        std::cout << "So you're a software tester, eh? " << std::endl;
    }
    std::cout << "Let's play for " << maxTurns <<" turns." << std::endl;
    setDefaultPlayers();
    generateRegularPuzzles();
    generateBonusPuzzles();
}





