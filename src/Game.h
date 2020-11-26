//
// Created by andrew on 11/24/20.
//

#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include <utility>
#include <vector>
#include "Interface.h"
#include "utilities.h"


class Player;


class Game {
public:
    Game(GameInterface *iface, Player *p1, Player *p2);

    const Field& get_field() const;
    void start();
    void step();
    bool validate_move(Point p) const;
    short check_winner() const;
    bool check_winner(Symbol symbol) const;

private:
    bool _ended;
    unsigned int _steps;
    GameInterface *_iface;
    const std::pair<Player*, Player*> _players;
    Field _field;
    const Symbol _empty_symbol;
    unsigned int _winning_length;
};


#endif //TIC_TAC_TOE_GAME_H
