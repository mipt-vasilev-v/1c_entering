#include "SpiderGame.hpp"

SpiderGame::SpiderGame(std::vector<CardHeap>& heaps, unsigned seed)
    : heaps(heaps), moves(0), seed_(seed){
}

bool SpiderGame::SpiderGame::is_winnable() {
    for (int i = 0; i < algo_moves; ++i) {
        if (cards_amount <= 18) {
            return true;
        }
        bool best_turns = generate_possible_moves();
        if (moves.empty()) {
            return false;
        }
        size_t pos = 0;
        if (!best_turns) {
            pos = rand() % moves.size();
        }
        Move current_move = moves[pos];
        heaps[current_move.from_heap].replace_cards(
            heaps[current_move.to_heap], current_move.amount);
        if (best_turns) {
            if (heaps[current_move.to_heap].can_drop_street()) { 
                heaps[current_move.to_heap].drop_street();
                cards_amount -= 9;
            }
        }
    }
    return false;
}

bool SpiderGame::generate_possible_moves() {
    moves.clear();
    int cur_max_stack = 3;
    int move_index = -1;
    for (int i = 0; i < heaps_amount; ++i) {
        for (int j = 1; j < heaps[i].get_max_stack(); ++j) {
            for (int k = 0; k < heaps_amount; ++k) {
                if (k == i) {
                    continue;
                }
                if (heaps[i].can_replace_cards(heaps[k], j)) {
                    moves.emplace_back(Move{i, k, j});
                    if (heaps[i].max_stack_after_move(heaps[k], j) > cur_max_stack) {
                        cur_max_stack = heaps[i].max_stack_after_move(heaps[k], j);
                        move_index = moves.size() - 1;
                    }
                    if (heaps[j].is_empty() && cur_max_stack <= 3 && heaps[i].top() == 9) {
                        move_index = moves.size() - 1;
                    }
                }
                
            }
        }
    }
    if (move_index != -1) {
        std::swap(moves[0], moves[move_index]);
        return true;
    }
    return false;
}
