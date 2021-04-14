#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <map>

class CardHeap {
  public:
    CardHeap(std::vector<std::string>& heap);

    int top();

    bool is_empty();

    bool can_replace_cards(CardHeap& other, int amount);

    void replace_cards(CardHeap& other, int amount);

    bool can_drop_street();

    void drop_street();

    int operator[](int pos);
    
    // deprecated
    bool can_drop_street_after_move(CardHeap& other, int amount);

    int max_stack_after_move(CardHeap& other, int amount);

    int get_max_stack();


  private:
    void calculate_max_stack();

    std::vector<int> buffer_;
    int last_opened{0};
    int max_stack_len{1};
    std::map<std::string, int> bijection{
        {"A", 9}, {"K", 8},  {"Q", 7},
        {"J", 6}, {"10", 5}, {"9", 4},
        {"8", 3}, {"7", 2},  {"6", 1}
    };
};
