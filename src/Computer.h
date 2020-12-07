//
// Created by andrew on 11/26/20.
//

#ifndef TIC_TAC_TOE_COMPUTER_H
#define TIC_TAC_TOE_COMPUTER_H

#include <thread>
#include <future>
#include <unordered_map>
#include <map>
#include "Field.h"
#include "Player.h"


class Computer : public Player {
public:
    explicit Computer(Symbol symbol);

    std::string name() const override;
    Symbol symbol() const override;
    void set_game(Game *game) override;
    Point move() override;

    int maxmin_step(Field &field, bool maximizing, int alpha, int beta, unsigned int depth, unsigned int max_depth,
                    int breadth);

    Point find_best_move_mt(Field &field);
private:
    const Symbol _symbol;
    Symbol _opposite_symbol;
    const std::string _name;
    int _max_depth;
    Game *_game;
    std::atomic<bool> _running;
    std::unordered_map<Field, int> _cache;
    std::mutex _cache_mutex;
};


#endif //TIC_TAC_TOE_COMPUTER_H
