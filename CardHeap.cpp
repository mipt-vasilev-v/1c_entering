#include "CardHeap.hpp"

CardHeap::CardHeap(std::vector<std::string>& heap) : buffer_(heap.size(), 0) {
    for (size_t i = 0; i < heap.size(); ++i) {
        buffer_[i] = bijection[heap[i]];
    }
}

int CardHeap::top() {
    if (is_empty()) {
        return -1;
    }
    return buffer_[0];
}

bool CardHeap::is_empty() {
    return buffer_.empty();
}

bool CardHeap::can_replace_cards(CardHeap& other, int amount) {
    if (amount > max_stack_len || amount >= last_opened) {
        return false;
    }
    return (other.is_empty() || buffer_[amount - 1] + 1 == other.top());
}

void CardHeap::replace_cards(CardHeap& other, int amount) {
    assert(this->can_replace_cards(other, amount) == true);

    std::vector<int> cur_new_buffer(buffer_.size() - amount, 0);
    for (int i = amount; i < buffer_.size(); ++i) {
        cur_new_buffer[i - amount] = buffer_[amount];
    }

    std::vector<int> other_new_buffer(amount + other.buffer_.size(), 0);
    for (int i = 0; i < amount; ++i) {
        other_new_buffer[i] = buffer_[i];
    }
    for (int i = 0; i < other.buffer_.size(); ++i) {
        other_new_buffer[i + amount] = other.buffer_[i];
    }

    buffer_ = std::move(cur_new_buffer);
    last_opened = (last_opened > amount - 1) ? last_opened - amount : 0;
    calculate_max_stack();
    other.buffer_ = std::move(other_new_buffer);
    other.calculate_max_stack();
    other.last_opened = other.last_opened + amount;
}

bool CardHeap::can_drop_street() {
    return (max_stack_len == 8);
}

void CardHeap::drop_street() {
    assert(can_drop_street() == true);
    std::vector<int> new_buffer(buffer_.size() - 9);
    for (int i = 9; i < buffer_.size(); ++i) {
        new_buffer[i - 9] = buffer_[i];
    }
    buffer_ = std::move(new_buffer);
    last_opened = (last_opened > 8) ? last_opened - 9 : 0;
    calculate_max_stack();
}

int CardHeap::operator[](int pos) {
    assert(pos < buffer_.size());
    return buffer_[pos];
}

// deprecated
bool CardHeap::can_drop_street_after_move(CardHeap& other, int amount) {
    if (buffer_[0] != 1) {
        return false;
    }
    for (int i = 0; i <= other.last_opened; ++i) {
        if (other.buffer_[i] != i + amount + 1) {
            return false;
        }
        if (other.buffer_[i] == 9) {
            return true;
        }
    }
    return false;
}

int CardHeap::max_stack_after_move(CardHeap& other, int amount) {
    if (other.is_empty()) {
        return amount;
    }
    for (int i = 0; i <= other.last_opened; ++i) {
        if (other.buffer_[i] != i + amount + buffer_[0]) {
            return amount + i;
        }
        if (other.buffer_[i] == 9) {
            return 10 - buffer_[0];
        }
    }
    return -1;
}

int CardHeap::get_max_stack() {
    return max_stack_len;
}


void CardHeap::calculate_max_stack() {
    if (is_empty()) {
        max_stack_len = 0;
        last_opened = -1;
        return;
    }
    max_stack_len = 1;
    for (int i = 0; i < last_opened; ++i) {
        if (buffer_[i] + 1 == buffer_[i + 1]) {
            max_stack_len++;
        }
    }
}
