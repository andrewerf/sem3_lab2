//
// Created by andrew on 11/24/20.
//

#ifndef TIC_TAC_TOE_PLAYER_H
#define TIC_TAC_TOE_PLAYER_H

#include <string>
#include <utility>
#include "utilities.h"


class Game;


class Player {
public:
    virtual Symbol symbol() const = 0;
    virtual std::string name() const = 0;
    virtual void set_game(Game *game) = 0;
    virtual Point move() = 0;
};


#endif //TIC_TAC_TOE_PLAYER_H
