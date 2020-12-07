//
// Created by andrew on 11/26/20.
//

#include <cmath>
#include <functional>
#include "Computer.h"
#include "Game.h"


Computer::Computer(Symbol symbol):
    _symbol(symbol),
    _name("computer"),
    _game(nullptr)
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

    if(game->field().size() == 3)
        _max_depth = 11;
    else
        _max_depth = 7;

}


Point Computer::move()
{
    Field field = _game->field();
    return find_best_move_mt(field);
}


int find_max_depth(long double n, long double N=9)
{
//    long double n_fact = sqrtl(2.0*M_PI*n)*powl(n / M_E, n);
//    long double t = (n - powl((n_fact * expl(n)) / (sqrtl(2*M_PI) * powl(10, N)), 1 / (n + 0.5)) - 1) / 2;
    if(n < 15)
        return n;

    long double d = 0;
    long double res = 0;
    while(res <= powl(10, N) and n > d)
    {
        d += 1;
        res = powl(n/(n-d), n+0.5) * powl((n-d)/M_E, d);
    }
    return ceil(d-1);
}


Point Computer::find_best_move_mt(Field &field)
{
    std::vector<std::thread> threads;
//    auto all_empty_cells = field.empty_cells();
//    _max_depth = find_max_depth(all_empty_cells.size());
    printf("Max depth is: %d\n", _max_depth);

//    auto possible_moves = all_empty_cells.size() == field.size() * field.size() ? field.circle_empty_cells(10) : field.empty_cells_roi(2);
    auto possible_moves = field.circle_empty_cells(20);
    std::mutex best_mutex;
    int best_val = -10000;
    Point best_move;
    threads.reserve(possible_moves.size());
    _running = true;

    auto func =
    [this, &field, &best_val, &best_mutex, &best_move](Point p, unsigned int max_depth, int breadth){
        Field _field = field;
        _field.set(p, _symbol);
        auto val = maxmin_step(_field, false, -10000, 10000, 0, max_depth, breadth);

        auto lock = std::lock_guard(best_mutex);
        if(val > best_val)
        {
            best_val = val;
            best_move = p;
        }
    };

    for(auto p : possible_moves)
    {
        threads.emplace_back(std::thread(func, p, _max_depth, 12));
    }

    for(auto &t : threads)
        t.join();
    _cache.clear();
    return best_move;
}


int
Computer::maxmin_step(Field &field, bool maximizing, int alpha, int beta, unsigned int depth, unsigned int max_depth,
                      int breadth)
{
    if(_cache.contains(field))
        return _cache.at(field);

    std::vector<Point> empty_cells = field.circle_empty_cells(20);

    if(field.check_winner() == _symbol)
    {
        return 100 - depth;
    }
    else if(field.check_winner() == _opposite_symbol)
    {
        return -100 + depth;
    }
    else if(empty_cells.empty())
    {
        return 0;
    }
    else if(not _running)
    {
        if(maximizing)
            return -1000;
        else
            return 1000;
    }
    else if(depth >= max_depth)
    {
        unsigned int this_max_length = field.max_length(_symbol);
        unsigned int opposit_max_length = field.max_length(_opposite_symbol);
        return this_max_length*this_max_length - opposit_max_length*opposit_max_length;
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
        auto val = maxmin_step(field, not maximizing, alpha, beta, depth + 1, max_depth, breadth);
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

    _cache_mutex.lock();
    _cache[field] = best_val;
    _cache_mutex.unlock();
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