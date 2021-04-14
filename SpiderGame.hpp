#include "CardHeap.cpp"

class SpiderGame {
  public:
    SpiderGame(std::vector<CardHeap>& heaps, unsigned seed);

    bool is_winnable();

  private:
    struct Move {
        int from_heap;
        int to_heap;
        int amount;
    };

    std::vector<Move> moves;
    std::vector<CardHeap> heaps;
    unsigned seed_;
    int cards_amount{72};
    int algo_moves{1000};
    const int heaps_amount{8};

    bool generate_possible_moves();

};
