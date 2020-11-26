//
// Created by andrew on 11/25/20.
//

#ifndef TIC_TAC_TOE_INTERFACEFACTORY_H
#define TIC_TAC_TOE_INTERFACEFACTORY_H

#include "Interface.h"


class InterfaceFactory {
public:
    virtual UserInterface* build_user_interface() = 0;
    virtual GameInterface* build_game_interface() = 0;
};


#endif //TIC_TAC_TOE_INTERFACEFACTORY_H
