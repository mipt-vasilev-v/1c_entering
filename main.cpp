#include <iostream>
#include <cstdlib>
#include "SpiderGame.cpp"

enum CONSTS {
    x = 29,
    mod = 1000000007,
    games_tries = 25,
};

unsigned generate_seed(int x, long long mod, std::vector<CardHeap>& buffer) {
    unsigned res = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 9; ++j) {
            res = (res + buffer[i][j]) * x % mod; 
        }
    }
    return res;
}

void welcome() {
    std::cout << "Please, enter each heap with one card in a line\n";
    std::cout << "Entering rules:\n" << "    A for ace,\n" << "    K for king,\n";
    std::cout << "    Q for queen,\n" << "    J for jack,\n" << "    enter numbers from 10 to 6 as numbers.\n";
}

bool solve() {
    std::vector<std::string> heap;
    std::vector<CardHeap> game_buffer;
    std::string card;
    game_buffer.reserve(8);
    welcome();
    std::vector<unsigned> seeds(0);
    seeds.reserve(games_tries);
    for (int i = 0; i < 8; ++i) {
        std::cout << "Entering the " << i + 1 << " heap\n"; 
        for (int j = 0; j < 9; ++j) {
            std::cin >> card;
            heap.push_back(card);
        } 
        game_buffer.emplace_back(CardHeap(heap));
    }

    unsigned main_seed = generate_seed(x, mod, game_buffer);
    for (int i = 0; i < games_tries; ++i) {
        srand(main_seed);
        for (int j = 0; j < 3; ++j) {
            rand();
        } 
        seeds[i] = rand();
    }

    bool winning = 0;
    for (int i = 0; i < games_tries; ++i) {
        SpiderGame Game(game_buffer, seeds[i]);
        if (Game.is_winnable()) {
            winning = 1;
            break;
        }
    }
    return winning;
}

int main() {
    bool winning = solve();
    std::cout << (winning ? "YES\n" : "NO\n");
}