//
// Created by andrew on 11/24/20.
//

#ifndef TIC_TAC_TOE_INTERFACE_H
#define TIC_TAC_TOE_INTERFACE_H

#include <vector>
#include <string>
#include "utilities.h"


class Player;
class Game;


class GameInterface {
public:
    virtual void set_game(Game *game) = 0;

    virtual unsigned int request_field_size() = 0;
    virtual GameType request_game_type() = 0;

    virtual void startgame_message() = 0;
    virtual void bad_step_message(short player_n) = 0;
    virtual void endgame_message(short winner_n) = 0;
    virtual void show_field() = 0;
};

class UserInterface {
public:
    virtual void set_player(Player *player) = 0;

    virtual std::string request_name() = 0;
    virtual Symbol request_symbol() = 0;
    virtual Point request_move() = 0;
};


#endif //TIC_TAC_TOE_INTERFACE_H
