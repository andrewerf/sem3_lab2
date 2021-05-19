//
// Created by andrew on 5/18/21.
//

#ifndef TIC_TAC_TOE_QTINTERFACEFACTORY_H
#define TIC_TAC_TOE_QTINTERFACEFACTORY_H

#include "InterfaceFactory.h"
#include "QtInterface.h"


class QtInterfaceFactory : public InterfaceFactory
{
public:
    UserInterface* build_user_interface() override;
    GameInterface* build_game_interface() override;

private:
    QtGameInterface *_game_iface;
};


#endif //TIC_TAC_TOE_QTINTERFACEFACTORY_H
