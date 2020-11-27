//
// Created by andrew on 11/24/20.
//

#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include <map>
#include <utility>
#include <vector>
#include "Field.h"
#include "Interface.h"
#include "utilities.h"


class Player;


class Game {
public:
    Game(GameInterface *iface, Player *p1, Player *p2);

    const Field& field() const;
    void start();
    void step();
    short check_winner() const;
    const std::pair<Player*, Player*>& players() const;
    const std::map<Player*, std::vector<Point>>& history() const;

private:
    bool _ended;
    unsigned int _steps;
    GameInterface *_iface;
    const std::pair<Player*, Player*> _players;
    const std::map<Player*, std::vector<Point>> _history;
    Field _field;
};


#endif //TIC_TAC_TOE_GAME_H
