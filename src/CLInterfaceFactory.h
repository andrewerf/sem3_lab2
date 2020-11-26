//
// Created by andrew on 11/25/20.
//

#ifndef TIC_TAC_TOE_CLINTERFACEFACTORY_H
#define TIC_TAC_TOE_CLINTERFACEFACTORY_H

#include "InterfaceFactory.h"


class CLInterfaceFactory : public InterfaceFactory {
public:
    UserInterface* build_user_interface() override;
    GameInterface* build_game_interface() override;
};


#endif //TIC_TAC_TOE_CLINTERFACEFACTORY_H
