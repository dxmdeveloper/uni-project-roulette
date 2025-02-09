#pragma once
#include "Player.hpp"
#include "AmericanWheel.hpp"
#include "EuropeanWheel.hpp"

class Game {
public:
    Game(Player player);

    int run();

private:
    void runWheelSelection();

    void runGameLoop();

    void runBetting();

    void toggleExerciseMode();

    static char loopWithChoice(const char *prompt, const char *choices);

    Money askForBet() const;

    Money settleBetResult(char chosenType, Money bet, const Field &field) const;

    Player player;
    std::unique_ptr<Player> playerBackup = nullptr;
    std::unique_ptr<Wheel> wheel = nullptr;
};
