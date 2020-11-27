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
    _root(nullptr)
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

    if(players.first == this)
    {
        _maximizing = true;
        _opposite_symbol = players.second->symbol();
    }
    else
    {
        _maximizing = false;
        _opposite_symbol = players.first->symbol();
    }

//    build_tree();
}


Point Computer::move()
{
//    static Node* node = _root;
//    auto opp_hist = _game->history().at(_opposite_symbol);

    Field field = _game->field();

    int best_val = -10000;
    Point best_move;
    for(Point cell : field.empty_cells()){
        field[cell.first][cell.second] = _symbol;
        int move = maxmin_step(field, false, true);
        field[cell.first][cell.second] = field.empty_symbol();

        if(move > best_val)
        {
            best_val = move;
            best_move = cell;
        }
    }

    return best_move;
}



Computer::Node::Node(int _estimated, int _depth):
    estimated(_estimated),
    depth(_depth)
{}

Computer::Node::~Node()
{
    for(auto child : children)
        delete child.second;
    children.clear();
}


int Computer::maxmin_step(Field &field, bool maximizing, bool first=false)
{
    static int depth = 1;
    if(first)
        depth = 1;

    std::vector<Point> empty_cells;
    for(unsigned int i = 0; i < field.size(); ++i)
        for(unsigned int j = 0; j < field.size(); ++j)
            if(field[i][j] == '_')
                empty_cells.emplace_back(i, j);

    if(field.check_winner() == _symbol)
    {
        return 10;
    }
    else if(field.check_winner() == _opposite_symbol)
    {
        return -10;
    }
    else if(empty_cells.empty())
    {
        return 0;
    }

    std::function<bool(int, int)> f;
    int best_val;
    Symbol symb = depth % 2 == 0 ? _symbol : _opposite_symbol;
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
        field[cell.first][cell.second] = symb;
        ++depth;
        auto val = maxmin_step(field, not maximizing);
        --depth;
        field[cell.first][cell.second] = '_';

        if(f(val, best_val))
            best_val = val;
    }

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