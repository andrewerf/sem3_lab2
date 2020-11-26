//
// Created by andrew on 11/24/20.
//

#include "Person.h"
#include "Game.h"


Person::Person(UserInterface *iface):
    Person(iface, iface->request_symbol(), iface->request_name())
{}


Person::Person(UserInterface *iface, Symbol symbol):
    Person(iface, symbol, iface->request_name())
{}

Person::Person(UserInterface *iface, Symbol symbol, const std::string &name):
    _symbol(symbol),
    _name(name),
    _iface(iface),
    _game(nullptr)
{
    _iface->set_player(this);
}


std::string Person::name() const
{
    return _name;
}


Symbol Person::symbol() const
{
    return _symbol;
}


void Person::set_game(Game *game)
{
    _game = game;
}


Point Person::move()
{
    return _iface->request_move();
}
