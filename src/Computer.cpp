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
    _root(nullptr),
    _max_depth(9)
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

    _root = new Node(0, 0);
    Field field = _game->field();
    maxmin_step(field, maximizing, _root);
}


Point Computer::move()
{
    Field field = _game->field();

    for(const auto &p : _game->history())
        if(p.first != this)
            _root = _root->go(p.second.back());

    int best_val = -10000;
    Point best_move;
    for(auto p : _root->children){
        if(p.second->estimated > best_val)
        {
            best_val = p.second->estimated;
            best_move = p.first;
        }
    }
    _root = _root->go(best_move);

    return best_move;
}



Computer::Node::Node(int _estimated, int _depth):
    estimated(_estimated),
    depth(_depth),
    leaf(false)
{}

Computer::Node* Computer::Node::go(Point move)
{
    Node *t = children[move];
    children.clear();
    delete this;

    return t;
}

Computer::Node::~Node()
{
    for(auto child : children)
        delete child.second;
    children.clear();
}


int Computer::maxmin_step(Field &field, bool maximizing, Node *root)
{
    std::vector<Point> empty_cells = field.empty_cells();

    if(field.check_winner() == _symbol)
    {
        root->estimated = 10;
        root->leaf = true;
        return 10;
    }
    else if(field.check_winner() == _opposite_symbol)
    {
        root->estimated = -10;
        root->leaf = true;
        return -10;
    }
    else if(empty_cells.empty())
    {
        root->estimated = 0;
        root->leaf = true;
        return 0;
    }
    else if(root->depth >= _max_depth)
    {
        unsigned int this_max_length = field.max_length(_symbol);
        unsigned int opposit_max_length = field.max_length(_opposite_symbol);
        root->estimated = this_max_length - opposit_max_length;
        root->leaf = true;
        return root->estimated;
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
        if(root->leaf or (not root->children.contains(cell)))
        {
            field.set(cell.first, cell.second, symb);
            Node *child = new Node(0, root->depth+1);
            root->children[cell] = child;
            auto val = maxmin_step(field, not maximizing, child);
            field.set(cell.first, cell.second, '_');

            if(f(val, best_val))
                best_val = val;
        }
    }

    root->estimated = best_val;
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