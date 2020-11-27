//
// Created by andrew on 11/25/20.
//

#ifndef TIC_TAC_TOE_CLINTERFACE_H
#define TIC_TAC_TOE_CLINTERFACE_H

#include "Interface.h"


class GameCLInterface : public GameInterface {
public:
    GameCLInterface();

    void set_game(Game *game) override;

    unsigned int request_field_size() override;
    GameType request_game_type() override;

    void startgame_message() override;
    void bad_step_message(short player_n) override;
    void endgame_message(short winner_n) override;
    void show_field() override;

private:
    const Game *_game;
};


class UserCLInterface : public UserInterface {
public:
    UserCLInterface();

    void set_player(Player *player) override;

    Point request_move() override;
    Symbol request_symbol() override;
    std::string request_name() override;
private:
    const Player *_player;
};


#endif //TIC_TAC_TOE_CLINTERFACE_H
