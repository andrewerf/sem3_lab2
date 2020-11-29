//
// Created by andrew on 11/26/20.
//

#ifndef TIC_TAC_TOE_FIELD_H
#define TIC_TAC_TOE_FIELD_H

#include <stdexcept>
#include <vector>
#include "utilities.h"


class Field {
public:
    Field(unsigned int size, Symbol p1, Symbol p2, Symbol empty_symbol);

    bool validate_move(Point p) const;
    Symbol check_winner() const;
    bool check_winner(Symbol symbol) const;
    unsigned int max_length(Symbol symbol) const;
    unsigned int winning_length() const {return _winning_length;}
    Symbol empty_symbol() const {return _empty_symbol;}
    std::vector<Point> empty_cells() const;

    unsigned int size() const;
    Symbol get(unsigned int row, unsigned int col) const;
    Symbol get(Point p) const;
    Symbol operator[] (Point p) const;
    void set(unsigned int y, unsigned int x, Symbol val);
    void set(Point p, Symbol val);

private:
    unsigned int _winning_length;
    Symbol _empty_symbol;
    std::pair<Symbol, Symbol> _symbols;
    std::vector<std::vector<Symbol>> _field;
//    std::vector<std::vector<std::vector<short>>> _dp;
};


#endif //TIC_TAC_TOE_FIELD_H
