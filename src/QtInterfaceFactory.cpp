//
// Created by andrew on 5/18/21.
//

#include "QtInterfaceFactory.h"

UserInterface *QtInterfaceFactory::build_user_interface()
{
    return new QtGameInterface::QtUserInterface(_game_iface);
}

GameInterface *QtInterfaceFactory::build_game_interface()
{
    _game_iface = new QtGameInterface;
    _game_iface->show();
    return _game_iface;
}
