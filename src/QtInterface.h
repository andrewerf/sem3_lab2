//
// Created by andrew on 5/18/21.
//

#ifndef TIC_TAC_TOE_QTINTERFACE_H
#define TIC_TAC_TOE_QTINTERFACE_H

#include <QtWidgets/QtWidgets>
#include "ui_main.h"
#include "ui_entry_dialog.h"
#include "Interface.h"
#include "Player.h"
#include "Game.h"



class TicTacToeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TicTacToeScene(int full_size, int field_size, QObject *parent = nullptr);

    void fit_in_cell(QGraphicsItem *item, QPoint cell) const;
    QGraphicsSimpleTextItem* addSimpleText(const QString& text, QPoint cell);

    void enable_move(Symbol symbol);
    void disable_move();
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    int full_size() const;
    double cell_size() const;
    Point get_last_move() const;
signals:
    void move();

private:
    Point _last_move;
    int _full_size;
    int _field_size;
    double _cell_size;

    bool _enabled;
    Symbol _enabled_symbol;
};


Q_DECLARE_INTERFACE(GameInterface, "GameInterface.Interface")
class QtGameInterface : public QWidget, public GameInterface, public Ui::Form
{
    Q_OBJECT
    Q_INTERFACES(GameInterface)

public:
    QtGameInterface();

    void set_game(Game *game) override;

    unsigned int request_field_size() override;
    GameType request_game_type() override;

    void startgame_message() override;
    void bad_step_message(short player_n) override;
    void endgame_message(short winner_n) override;
    void show_field() override;

    class QtUserInterface : public UserInterface
    {
    public:
        explicit QtUserInterface(QtGameInterface *game_iface);
        void set_player(Player *player) override;

        std::string request_name() override;
        Symbol request_symbol() override;
        Point request_move() override;

    private:
        QtGameInterface *_game_iface;
        Player *_player;
    };

    friend class TicTacToeScene;

private:
    Game *_game;

    unsigned int _field_size;
    GameType _game_type;
    std::pair<Symbol, Symbol> _symbols;


    TicTacToeScene *_scene;
};



#endif //TIC_TAC_TOE_QTINTERFACE_H
