#include <iostream>
#include "Game.hpp"

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);
    Player player{playerName.c_str()};
    player.setAccountBalance(100);

    Game game{std::move(player)};
    return game.run();
}