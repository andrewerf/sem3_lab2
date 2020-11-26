//
// Created by andrew on 11/25/20.
//

#include "CLInterfaceFactory.h"
#include "CLInterface.h"


GameInterface* CLInterfaceFactory::build_game_interface()
{
    return new GameCLInterface();
}

UserInterface* CLInterfaceFactory::build_user_interface()
{
    return new UserCLInterface();
}
