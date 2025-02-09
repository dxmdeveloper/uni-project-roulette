#pragma once
#include <algorithm>
#include <vector>

#include "Money.hpp"

class Player {
public:
    explicit Player(const char *name);

    Player(const Player &copied) noexcept;

    Player(Player &&moved) noexcept;

    ~Player();

    void setAccountBalance(Money balance);

    Money getAccountBalance() const;

    void creditWin(Money amount);

    void noteLoss(Money lossInfo);

    void placeBet(Money amount);

    void showStats() const;

    Player &operator=(Player &&moved) noexcept;

    Player &operator=(const Player &copied) noexcept;

    const char *getName() const;

    void setName(const char *name);

private:
    char *name = nullptr;
    int winCount = 0;
    int betsCount = 0;
    std::vector<std::pair<bool, Money> > finishedBets{};
    Money accountBalance{0};
};
