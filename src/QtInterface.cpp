//
// Created by andrew on 5/18/21.
//

#include "QtInterface.h"
#include <set>


void QtGameInterface::set_game(Game *game)
{
    _game = game;
}

QtGameInterface::QtGameInterface()
{
    setupUi(this);

    QDialog dialog;
    Ui::Dialog dialog_ui;
    dialog_ui.setupUi(&dialog);

    int ex = dialog.exec();
    if(!ex)
        exit(ex);

    _game = nullptr;
    _field_size = dialog_ui.spn_field->value();
    _game_type = static_cast<GameType>(dialog_ui.cmb_game->currentIndex());
    _symbols = {dialog_ui.lne_symb0->text().toStdString()[0], dialog_ui.lne_symb1->text().toStdString()[0]};

    _scene = new TicTacToeScene(480, _field_size, this);
    grv_view->setScene(_scene);
}

unsigned int QtGameInterface::request_field_size()
{
    return _field_size;
}

GameType QtGameInterface::request_game_type()
{
    return _game_type;
}

void QtGameInterface::startgame_message()
{
    lbl_status->setText("Игра началась!");
}

void QtGameInterface::bad_step_message(short player_n)
{
    lbl_status->setText("Так ходить нельзя!");
}

void QtGameInterface::endgame_message(short winner_n)
{
    std::string txt;
    if(winner_n < 0)
        txt = "Ничья";
    else
    {
        txt = "Победил игрок ";
        if(winner_n == 0)
            txt += _game->players().first->name();
        else
            txt += _game->players().second->name();
    }
    _game->players().first->name();
    lbl_status->setText(QString::fromStdString(txt));
}

void QtGameInterface::show_field()
{
    static bool first_time = false;
    if(!first_time)
    {
        grv_view->fitInView(_scene->itemsBoundingRect());
        first_time = true;
    }

    QMetaObject::invokeMethod(this, [&]{
        static std::map<std::pair<int, int>, QGraphicsItem*> text_items;

        auto field = _game->field();

        for(int y = 0; y < field.size(); ++y)
        for(int x = 0; x < field.size(); ++x)
        if(field.get(y, x) != field.empty_symbol())
        if(!text_items.contains({y,x}))
        {
            auto text = _scene->addSimpleText(QString::fromStdString(std::string(1, field.get(y, x))), {y,x});
            text_items[{y,x}] = text;
        }
    });
}


QtGameInterface::QtUserInterface::QtUserInterface(QtGameInterface *game_iface):
    _game_iface(game_iface)
{}

void QtGameInterface::QtUserInterface::set_player(Player *player)
{
    _player = player;
}

std::string QtGameInterface::QtUserInterface::request_name()
{
//    if(_player == _game_iface->_game->players().first)
//        return std::string(1, _game_iface->_symbols.first);
//    else
//        return std::string(1, _game_iface->_symbols.second);
    return "";
}

Symbol QtGameInterface::QtUserInterface::request_symbol()
{
    static int i = 0;
    if(i == 0)
    {
        ++i;
        return _game_iface->_symbols.first;
    }
    else
        return _game_iface->_symbols.second;
}

Point QtGameInterface::QtUserInterface::request_move()
{
    _game_iface->_scene->enable_move(_player->symbol());
    QEventLoop loop;
    connect(_game_iface->_scene, &TicTacToeScene::move, &loop, &QEventLoop::quit);
    loop.exec();
    _game_iface->_scene->disable_move();

    return _game_iface->_scene->get_last_move();
}



TicTacToeScene::TicTacToeScene(int full_size, int field_size, QObject *parent):
    _full_size(full_size),
    _field_size(field_size),
    _cell_size(static_cast<double>(full_size) / field_size),
    QGraphicsScene (parent)
{
    for(uint i = 0; i <= _field_size; ++i)
    {
        addLine(_cell_size * i, 0, _cell_size * i, _full_size);
        addLine(0, _cell_size * i, _full_size, _cell_size * i);
    }
}


void TicTacToeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_enabled)
        return;
    auto *parent = qobject_cast<QtGameInterface*>(this->parent());
    auto cell = event->scenePos() / _cell_size;
    QPoint cell_round(std::floor(cell.x()), std::floor(cell.y()));
    auto text = this->addSimpleText(QString::fromStdString(std::string(1, _enabled_symbol)),
                                    cell_round);
    _last_move = {cell_round.x(), cell_round.y()};
    emit move();
}

void TicTacToeScene::fit_in_cell(QGraphicsItem *item, QPoint cell) const
{
    auto brect = item->boundingRect();
    item->setPos(_cell_size * cell.x() + (_cell_size - brect.width()) / 2, _cell_size * cell.y() + (_cell_size - brect.height()) / 2);
}

int TicTacToeScene::full_size() const
{
    return _full_size;
}

double TicTacToeScene::cell_size() const
{
    return _cell_size;
}

Point TicTacToeScene::get_last_move() const
{
    return _last_move;
}

QGraphicsSimpleTextItem* TicTacToeScene::addSimpleText(const QString& text, QPoint cell)
{
    auto text_item = QGraphicsScene::addSimpleText(text);
    text_item->setFont(QFont("Arial", _cell_size / 2));
    fit_in_cell(text_item, cell);

    return text_item;
}

void TicTacToeScene::enable_move(Symbol symbol)
{
    _enabled = true;
    _enabled_symbol = symbol;
}

void TicTacToeScene::disable_move()
{
    _enabled = false;
}
