//
// Created by andrew on 11/26/20.
//

#include <functional>
#include "Computer.h"
#include "Game.h"


Computer::Computer(Symbol symbol):
    _symbol(symbol),
    _name("computer"),
    _game(nullptr),
    _max_depth(8)
{}


std::string Computer::name() const
{
    return _name;
}


Symbol Computer::symbol() const
{
    return _symbol;
}


void Computer::set_game(Game *game)
{
    _game = game;

    auto players = game->players();
    bool maximizing;
    if(players.first == this)
    {
        maximizing = true;
        _opposite_symbol = players.second->symbol();
    }
    else
    {
        maximizing = false;
        _opposite_symbol = players.first->symbol();
    }

}


Point Computer::move()
{
    Field field = _game->field();
    return find_best_move_mt(field);
}


Point Computer::find_best_move_mt(Field &field)
{
    std::vector<std::thread> threads;
    auto possible_moves = field.sorted_empty_cells(8);
    std::mutex best_mutex;
    int best_val = -10000;
    Point best_move;
    int alpha = -10000, beta = 10000;
    threads.reserve(possible_moves.size());
    _running = true;

    for(auto p : possible_moves)
    {
        threads.emplace_back(std::thread([this, &field, &alpha, &beta, &best_val, &best_mutex, &best_move, p]{
            Field _field = field;
            _field.set(p, _symbol);
            auto val = maxmin_step(_field, false, alpha, beta, 0);

            auto lock = std::lock_guard(best_mutex);
            if(val > best_val)
            {
                best_val = val;
                best_move = p;
            }
            if(best_val > alpha)
                alpha = best_val;
            if(alpha > beta)
                _running.store(false);
        }));
    }

    for(auto &t : threads)
        t.join();

    return best_move;
}


int Computer::maxmin_step(Field &field, bool maximizing, int alpha, int beta, unsigned int depth)
{
//    if(_cache.contains(field))
//        return _cache.at(field);

    std::vector<Point> empty_cells = field.sorted_empty_cells(6);

    if(field.check_winner() == _symbol)
    {
        return 100;
    }
    else if(field.check_winner() == _opposite_symbol)
    {
        return -100;
    }
    else if(empty_cells.empty())
    {
        return 0;
    }
    else if(depth >= _max_depth or not _running)
    {
        unsigned int this_max_length = field.max_length(_symbol);
        unsigned int opposit_max_length = field.max_length(_opposite_symbol);
        return this_max_length*this_max_length - opposit_max_length*opposit_max_length - depth;
    }

    std::function<bool(int, int)> f;
    int best_val;
    Symbol symb = maximizing ? _symbol : _opposite_symbol;
    if(maximizing)
    {
        f = std::greater<>();
        best_val = -10000;
    }
    else
    {
        f = std::less<>();
        best_val = 10000;
    }

    for(Point cell : empty_cells)
    {
        field.set(cell, symb);
        auto val = maxmin_step(field, not maximizing, alpha, beta, depth+1);
        field.set(cell, '_');

        if(f(val, best_val))
            best_val = val;
        if(maximizing)
            alpha = std::max(alpha, best_val);
        else
            beta = std::min(beta, best_val);

        if(alpha >= beta)
            break;
    }

//    _cache[field] = best_val;
    return best_val;
}


/*

void Computer::build_tree()
{
    _root = new Node(0, 0);
    build_tree(_root, 0);
    return;
}

void Computer::build_tree(Node *parent, int thresh)
{
    static Field field = _game->field();
    if(parent->depth == 0)
        field = _game->field();

    std::vector<Point> empty_cells;
    for(unsigned int i = 0; i < field.size(); ++i)
        for(unsigned int j = 0; j < field.size(); ++j)
            if(field[i][j] == '_')
                empty_cells.emplace_back(i, j);

    Symbol win_symb = field.check_winner();
    if(win_symb == _symbol)
    {
        parent->estimated = 10;
        return;
    }
    else if(win_symb != _opposite_symbol)
    {
        parent->estimated = -10;
        return;
    }
    else if(empty_cells.empty())
    {
        parent->estimated = 0;
        return;
    }

    Symbol symb;
    std::function<bool(int, int)> f;
    int best_val;
    if(parent->depth % 2 == 0)
    {
        f = std::greater<>();
        best_val = -10000;
        symb = _symbol;
    }
    else
    {
        f = std::less<>();
        best_val = 10000;
        symb = _symbol + 1;
    }

    for(auto p : empty_cells){
        auto child = new Node(0, parent->depth + 1);
        field[p.first][p.second] = symb;
        parent->children[p] = child;
        build_tree(child, 0);
        field[p.first][p.second] = '_';

        if(f(child->estimated, best_val))
            best_val = child->estimated;
    }
    parent->estimated = best_val;


}

*/