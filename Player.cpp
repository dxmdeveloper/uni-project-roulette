#include "Player.hpp"

#include <cassert>
#include <cstring>
#include "common.hpp"

Player::Player(const char *name) {
    setName(name);
}

Player::Player(const Player &copied) noexcept {
    operator=(copied);
}

Player::Player(Player &&moved) noexcept {
    this->operator=(std::move(moved));
}

Player::~Player() {
    delete [] name;
}

void Player::setAccountBalance(Money balance) {
    accountBalance = balance;
}

Money Player::getAccountBalance() const {
    return accountBalance;
}

void Player::creditWin(Money amount) {
    winCount++;
    accountBalance += amount;
    finishedBets.emplace_back(true, amount);
}

void Player::noteLoss(Money lossInfo) {
    finishedBets.emplace_back(false, lossInfo);
}

void Player::placeBet(Money amount) {
    assert(accountBalance >= amount);

    betsCount++;
    accountBalance -= amount;
}

Player &Player::operator=(Player &&moved) noexcept {
    delete [] name;

    name = moved.name;
    winCount = moved.winCount;
    betsCount = moved.betsCount;
    accountBalance = moved.accountBalance;
    finishedBets = std::move(moved.finishedBets);

    moved.name = nullptr;
    return *this;
}

Player &Player::operator=(const Player &copied) noexcept {
    setName(copied.getName());

    winCount = copied.winCount;
    betsCount = copied.betsCount;
    accountBalance = copied.accountBalance;
    finishedBets = copied.finishedBets;

    return *this;
}

const char *Player::getName() const {
    return name;
}

void Player::setName(const char *name) {
    delete [] this->name;

    size_t nameLen = strlen(name);
    this->name = new char[nameLen + 1];
    strcpy(this->name, name);
}

void Player::showStats() const {
    std::cout << "Player: " << name << std::endl;
    std::cout << "Wins: " << winCount << std::endl;
    std::cout << "Bets: " << betsCount << std::endl;
    std::cout << "Account balance: " << accountBalance << std::endl << std::endl;
    std::cout << " === Bets table (best and worst) === " << std::endl;

    constexpr int showBets{10};
    auto sorted = finishedBets;

    std::sort(sorted.begin(), sorted.end(), [](const auto &lhs, const auto &rhs) {
        auto [lSign, lVal] = lhs;
        auto [rSign, rVal] = rhs;

        if (lSign && !rSign)
            return true;
        if (!lSign && rSign)
            return false;
        return lSign ? lVal > rVal : lVal < rVal;
    });

    processFirstAndLastN(showBets / 2, sorted.data(), sorted.size(),
                         [](size_t i, const auto &bet) {
                             std::cout << i + 1 << ". " << (bet.first ? '+' : '-') << bet.second << std::endl;
                         }, [] {
                             std::cout << "..." << std::endl;
                         });
}
