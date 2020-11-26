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
    _empty_symbol('_')
{
    iface->set_game(this);
    unsigned int size = iface->request_field_size();
    _field = std::vector(size, std::vector<Symbol>(size, '_'));
    _winning_length = std::min<unsigned int>(5, size);

    if(p1->symbol() == p2->symbol())
        throw std::logic_error("Players symbols should not be the same");

    p1->set_game(this);
    p2->set_game(this);
}


const Field& Game::get_field() const
{
    return _field;
}


void Game::start()
{
    _iface->startgame_message();
    _ended = false;
    short winner;
    while(not _ended)
    {
        _iface->show_field();
        step();
        winner = check_winner();
        if(winner >= 0)
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

    if(validate_move(move))
    {
        _field[move.first][move.second] = current_player->symbol();
        _steps++;
    }
    else
    {
        _iface->bad_step_message(current_player_n);
    }
}


bool Game::validate_move(Point p) const
{
    return p.first <= _field.size() and p.second <= _field.size() and _field[p.first][p.second] == _empty_symbol;
}


short Game::check_winner() const
{
    bool w1 = check_winner(_players.first->symbol());
    bool w2 = check_winner(_players.second->symbol());

    if(w1 and w2)
        throw std::logic_error("Something strange happened and both players has won. Congratulations.");
    else if(w1)
        return 0;
    else if(w2)
        return 1;
    else
        return -1;

}


bool Game::check_winner(Symbol symbol) const
{
    std::vector<std::vector<std::vector<short>>> dp(
            _field.size(),
            std::vector<std::vector<short>>(_field.size(), {0,0,0,0})
    );

    for(unsigned int y = 0; y < _field.size(); ++y)
    {
        for(unsigned int x = 0; x < _field.size(); ++x)
        {
            if(_field[y][x] == symbol)
            {
                for(unsigned short k = 0; k < 4; ++k)
                    dp[y][x][k] = 1;

                if(x > 0 and y > 0)
                    dp[y][x][0] += dp[y-1][x-1][0];
                if(y > 0 and x+1 < _field.size())
                    dp[y][x][1] += dp[y-1][x+1][1];
                if(x > 0)
                    dp[y][x][2] += dp[y][x-1][2];
                if(y > 0)
                    dp[y][x][3] += dp[y-1][x][3];
            }
        }
    }

    for(const auto &vx : dp)
        for(const auto &el : vx)
            for(const auto &k : el)
                if(k >= _winning_length)
                    return true;

    return false;
}