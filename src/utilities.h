//
// Created by andrew on 11/25/20.
//

#ifndef TIC_TAC_TOE_UTILITIES_H
#define TIC_TAC_TOE_UTILITIES_H

#include <vector>
#include <utility>

using Symbol = char;
using Point = std::pair<unsigned int, unsigned int>;

enum class GameType
{
    person_person,
    person_computer,
    computer_person,
    computer_computer
};

#endif //TIC_TAC_TOE_UTILITIES_H
