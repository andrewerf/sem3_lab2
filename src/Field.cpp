//
// Created by andrew on 11/26/20.
//

#include "Field.h"


Field::Field(unsigned int size, Symbol p1, Symbol p2, Symbol empty_symbol):
        _winning_length(std::min<unsigned int>(size, 5)),
        _empty_symbol(empty_symbol),
        _symbols({p1, p2}),
        vector(size, std::vector<Symbol>(size, empty_symbol))
{}


bool Field::validate_move(Point p) const
{
    return p.first <= size() and p.second <= size() and at(p.first).at(p.second) == _empty_symbol;
}


Symbol Field::check_winner() const
{
    bool w1 = check_winner(_symbols.first);
    bool w2 = check_winner(_symbols.second);

    if(w1 and w2)
        throw std::logic_error("Something strange happened and both players has won. Congratulations.");
    else if(w1)
        return _symbols.first;
    else if(w2)
        return _symbols.second;
    else
        return _empty_symbol;
}


unsigned int Field::max_length(Symbol symbol) const
{
    std::vector<std::vector<std::vector<short>>> dp(
            size(),
            std::vector<std::vector<short>>(size(), {0,0,0,0})
    );

    for(unsigned int y = 0; y < size(); ++y)
    {
        for(unsigned int x = 0; x < size(); ++x)
        {
            if(at(y).at(x) == symbol)
            {
                for(unsigned short k = 0; k < 4; ++k)
                    dp[y][x][k] = 1;

                if(x > 0 and y > 0)
                    dp[y][x][0] += dp[y-1][x-1][0];
                if(y > 0 and x+1 < size())
                    dp[y][x][1] += dp[y-1][x+1][1];
                if(x > 0)
                    dp[y][x][2] += dp[y][x-1][2];
                if(y > 0)
                    dp[y][x][3] += dp[y-1][x][3];
            }
        }
    }

    unsigned int ret = 0;
    for(const auto &vx : dp)
        for(const auto &el : vx)
            for(const auto &k : el)
                if(k > ret)
                    ret = k;

    return ret;
}


bool Field::check_winner(Symbol symbol) const
{
    return max_length(symbol) >= _winning_length;
}

std::vector<Point> Field::empty_cells() const
{
    std::vector<Point> empty_cells;
    for(unsigned int i = 0; i < size(); ++i)
        for(unsigned int j = 0; j < size(); ++j)
            if(at(i).at(j) == '_')
                empty_cells.emplace_back(i, j);

    return empty_cells;
}
