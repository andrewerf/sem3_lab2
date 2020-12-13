#include <iostream>

#include "src/CLInterface.h"
#include "src/CLInterfaceFactory.h"
#include "src/Game.h"
#include "src/Person.h"
#include "src/Computer.h"


int main()
{
    std::string iface_type = "cli";
    InterfaceFactory *factory;
//    std::cout << "Select interface [cli]: ";
//    std::cin >> iface_type;

    if(iface_type == "cli")
        factory = new CLInterfaceFactory();
    else
        throw std::logic_error("Unknown interface");

    auto *game_iface = factory->build_game_interface();

    Player *player1;
    Player *player2;
    auto game_type = game_iface->request_game_type();
    if(game_type == GameType::person_person)
    {
        auto *user_iface1 = factory->build_user_interface();
        auto *user_iface2 = factory->build_user_interface();
        player1 = new Person(user_iface1);
        player2 = new Person(user_iface2);
    }
    else if(game_type == GameType::person_computer)
    {
        auto *user_iface = factory->build_user_interface();
        player1 = new Person(user_iface);
        if(player1->symbol() == 'X')
            player2 = new Computer('O');
        else
            player2 = new Computer('X');
    }
    else if(game_type == GameType::computer_person)
    {
        auto *user_iface = factory->build_user_interface();
        player2 = new Person(user_iface);
        if(player2->symbol() == 'X')
            player1 = new Computer('O');
        else
            player1 = new Computer('X');
    }
    else
    {
        player1 = new Computer('X');
        player2 = new Computer('O');
    }

    auto *game = new Game(game_iface, player1, player2);
    game->start();
}
