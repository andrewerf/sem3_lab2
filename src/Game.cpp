//
// Created by andrew on 11/24/20.
//

#include <stdexcept>

#include "Player.h"
#include "Game.h"


Game::Game(GameInterface *iface, Player *p1, Player *p2):
    _ended(false),
    _iface(iface),
    _steps(0),
    _players({p1, p2}),
    _field(iface->request_field_size(), p1->symbol(), p2->symbol(), '_')
{
    if(p1->symbol() == p2->symbol())
        throw std::logic_error("Players symbols should not be the same");

    iface->set_game(this);
    p1->set_game(this);
    p2->set_game(this);
}


const Field& Game::field() const
{
    return _field;
}


void Game::start()
{
    _iface->startgame_message();
    _ended = false;
    short winner = -1;
    while(not _ended)
    {
        _iface->show_field();
        step();
        winner = check_winner();
        if(winner >= 0 or _field.empty_cells().empty())
        {
            _ended = true;
        }
    }
    _iface->show_field();
    _iface->endgame_message(winner);
}


void Game::step()
{
    Player *current_player;
    short current_player_n;
    if(_steps % 2 == 0)
    {
        current_player = _players.first;
        current_player_n = 0;
    }
    else
    {
        current_player = _players.second;
        current_player_n = 1;
    }

    Point move = current_player->move();

    if(_field.validate_move(move))
    {
        _field[move.first][move.second] = current_player->symbol();
        _history[current_player].push_back(move);
        _steps++;
    }
    else
    {
        _iface->bad_step_message(current_player_n);
    }
}


short Game::check_winner() const
{
    Symbol win_symb = _field.check_winner();
    if(win_symb == _players.first->symbol())
        return 0;
    else if(win_symb == _players.second->symbol())
        return 1;
    else
        return -1;
}

const std::map<Player*, std::vector<Point>>& Game::history() const {
    return _history;
}

const std::pair<Player*, Player*> &Game::players() const {
    return _players;
}
