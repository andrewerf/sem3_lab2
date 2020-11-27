//
// Created by andrew on 11/26/20.
//

#ifndef TIC_TAC_TOE_COMPUTER_H
#define TIC_TAC_TOE_COMPUTER_H

#include <map>
#include "Field.h"
#include "Player.h"


class Computer : public Player {
public:
    explicit Computer(Symbol symbol);

    std::string name() const override;
    Symbol symbol() const override;
    void set_game(Game *game) override;
    Point move() override;


    class Node {
    public:
        Node(int _estimated, int _depth);

        int estimated;
        int depth;
        std:: map<Point, Node*> children;

        ~Node();
    } *_root;

    int maxmin_step(Field &field, bool maximizing, bool first);

//    void build_tree();
//    void build_tree(Node *parent, int thresh);
private:
    const Symbol _symbol;
    Symbol _opposite_symbol;
    bool _maximizing;
    const std::string _name;
    Game *_game;
};


#endif //TIC_TAC_TOE_COMPUTER_H
