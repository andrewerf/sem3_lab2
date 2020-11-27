//
// Created by andrew on 11/26/20.
//

#ifndef TIC_TAC_TOE_FIELD_H
#define TIC_TAC_TOE_FIELD_H

#include <stdexcept>
#include <vector>
#include "utilities.h"


class Field : public std::vector<std::vector<Symbol>> {
public:
    Field(unsigned int size, Symbol p1, Symbol p2, Symbol empty_symbol);

    bool validate_move(Point p) const;
    Symbol check_winner() const;
    bool check_winner(Symbol symbol) const;
    unsigned int max_length(Symbol symbol) const;
    unsigned int winning_length() const {return _winning_length;}
    Symbol empty_symbol() const {return _empty_symbol;}
    std::vector<Point> empty_cells() const;

private:
    unsigned int _winning_length;
    Symbol _empty_symbol;
    std::pair<Symbol, Symbol> _symbols;
};


#endif //TIC_TAC_TOE_FIELD_H
