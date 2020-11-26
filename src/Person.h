//
// Created by andrew on 11/24/20.
//

#ifndef TIC_TAC_TOE_PERSON_H
#define TIC_TAC_TOE_PERSON_H

#include "Player.h"
#include "Interface.h"


class Person : public Player {
public:
    explicit Person(UserInterface *iface);
    Person(UserInterface *iface, Symbol symbol);
    Person(UserInterface *iface, Symbol symbol, const std::string &name);

    std::string name() const override;
    Symbol symbol() const override;
    void set_game(Game *game) override;
    Point move() override;

private:
    const Symbol _symbol;
    const std::string _name;
    Game *_game;
    UserInterface *_iface;
};


#endif //TIC_TAC_TOE_PERSON_H
