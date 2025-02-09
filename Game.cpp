#include "Game.hpp"

#include <cassert>
#include <cstring>
#include <thread>

Game::Game(Player player) : player(std::move(player)) {
}

int Game::run() {
    runWheelSelection();
    runGameLoop();

    return EXIT_SUCCESS;
}

char Game::loopWithChoice(const char *prompt, const char *choices) {
    char c;
    std::string input;
    while (true) {
        std::cout << prompt << std::endl << "> ";
        std::getline(std::cin, input);
        c = input[0];
        if (strchr(choices, c) != nullptr)
            break;

        std::cout << "Invalid choice." << std::endl;
    }
    return c;
}

Money Game::askForBet() const {
    while (true) {
        std::string input;
        std::cout << "Account balance: " << player.getAccountBalance() << std::endl;
        std::cout << "Enter the amount to bet (v = Va banque): ";
        std::getline(std::cin, input);

        if (input[0] == 'v')
            return player.getAccountBalance();

        try {
            Money amount{input};
            if (amount > player.getAccountBalance()) {
                std::cout << "You don't have enough money." << std::endl;
                continue;
            }
            if (amount == 0) {
                std::cout << "You can't bet 0." << std::endl;
                continue;
            }
            return amount;
        } catch (std::exception &e) {
            std::cout << "Invalid amount." << std::endl;
        }
    }
}

Money Game::settleBetResult(char chosenType, Money bet, const Field &field) const {
    switch (chosenType) {
        case 'g':
            assert(wheel->getFieldCount() > 36);
            // x36 if one zero, x18 if two zeros, x12 if three zeros
            if (field.color == Field::Color::GREEN)
                return bet * (36 / (wheel->getFieldCount() - 36));
            break;
        case 'b':
            if (field.color == Field::Color::BLACK)
                return bet * 2;
            break;
        case 'r':
            if (field.color == Field::Color::RED)
                return bet * 2;
            break;
        case 'e':
            if (field.number % 2 == 0)
                return bet * 2;
            break;
        case 'o':
            if (field.number % 2 != 0)
                return bet * 2;
            break;
        default: assert(false);
    }
    return Money{};
}

void Game::runWheelSelection() {
    char choice = loopWithChoice("Choose a wheel: \na - American,\ne - European", "ae");
    if (choice == 'a')
        wheel = std::make_unique<AmericanWheel>();
    else
        wheel = std::make_unique<EuropeanWheel>();
}

void Game::runGameLoop() {
    while (true) {
        if (player.getAccountBalance() == 0) {
            std::cout << "You have no money left." << std::endl;
            if (playerBackup) {
                std::cout << "Exiting exercise mode..." << std::endl;
                toggleExerciseMode();
                continue;
            }
            return;
        }

        std::cout << "\nPlayer: " << player.getName() << std::endl;
        std::cout << "Account balance: " << player.getAccountBalance() << std::endl;
        char choice = loopWithChoice("Choose an action: \n"
                                     "b - bet,\n"
                                     "s - show stats,\n"
                                     "e - enable/disable exercise mode,\n"
                                     "q - quit", "bseq");
        switch (choice) {
            case 'b': runBetting();
                break;
            case 'e': toggleExerciseMode();
                break;
            case 'q':
                return;
            case 's': player.showStats();
                break;
            default: assert(false);
        }
    }
}

void Game::runBetting() {
    Money amount = askForBet();
    player.placeBet(amount);

    char type = loopWithChoice("\nChoose a bet type: \n"
                               "g - green,\n"
                               "b - black,\n"
                               "r - red,\n"
                               "e - even,\n"
                               "o - odd", "gbreo");

    Field field = wheel->spin();
    std::cout << "Spinning the wheel... " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    std::cout << "Result: " << field.toString() << std::endl;
    Money win = settleBetResult(type, amount, field);
    if (win) {
        std::cout << "You won " << win << " !!!\n";
        player.creditWin(win);
        return;
    }
    std::cout << "You lost " << amount << std::endl;
    player.noteLoss(amount);
}

void Game::toggleExerciseMode() {
    if (!playerBackup) {
        playerBackup = std::make_unique<Player>(player); // copy constructor
        // modify current player
        std::string name = player.getName();
        name += " (exercise)";
        player.setName(name.c_str());
        return;
    }
    player = std::move(*playerBackup); // move assignment
    playerBackup.reset();
}
