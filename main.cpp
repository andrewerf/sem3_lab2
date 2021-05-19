#include <iostream>

#include "src/CLInterface.h"
#include "src/CLInterfaceFactory.h"
#include "src/QtInterfaceFactory.h"
#include "src/Game.h"
#include "src/Person.h"
#include "src/Computer.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    std::string iface_type = "qt";
    InterfaceFactory *factory;
//    std::cout << "Select interface [cli]: ";
//    std::cin >> iface_type;

    if(iface_type == "cli")
        factory = new CLInterfaceFactory();
    else if(iface_type == "qt")
        factory = new QtInterfaceFactory();
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
        if(player1->symbol() == 'X' or player1->symbol() == 'x')
            player2 = new Computer('O');
        else
            player2 = new Computer('X');
    }
    else if(game_type == GameType::computer_person)
    {
        auto *user_iface = factory->build_user_interface();
        player2 = new Person(user_iface);
        if(player2->symbol() == 'X' or player2->symbol() == 'x')
            player1 = new Computer('O');
        else
            player1 = new Computer('X');
    }
    else
    {
        player1 = new Computer('X');
        player2 = new Computer('O');
    }

    std::thread thrd([&]{
        auto *game = new Game(game_iface, player1, player2);
        game->start();
    });
    thrd.detach();

    return app.exec();
}
