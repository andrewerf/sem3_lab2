#include <iostream>

#include "src/CLInterface.h"
#include "src/CLInterfaceFactory.h"
#include "src/Game.h"
#include "src/Person.h"


int main()
{
    std::string iface_type;
    InterfaceFactory *factory;
    std::cout << "Select interface [cli]: ";
    std::cin >> iface_type;

    if(iface_type == "cli")
        factory = new CLInterfaceFactory();
    else
        throw std::logic_error("Unknown interface");

    auto *user_iface1 = factory->build_user_interface();
    auto *user_iface2 = factory->build_user_interface();
    auto *game_iface = factory->build_game_interface();

    auto player1 = new Person(user_iface1);
    auto player2 = new Person(user_iface2);
    auto *game = new Game(game_iface, player1, player2);
    game->start();
}
