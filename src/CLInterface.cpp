//
// Created by andrew on 11/25/20.
//

#include <iostream>
#include "CLInterface.h"
#include "Player.h"
#include "Game.h"

using namespace std;

GameCLInterface::GameCLInterface() = default;


void GameCLInterface::set_game(Game *game)
{
    _game = game;
}


GameType GameCLInterface::request_game_type()
{
    static const std::map<std::string, GameType> mapping = {
            {"person-person", GameType::person_person},
            {"person-computer", GameType::person_computer},
            {"computer-person", GameType::computer_person},
            {"computer-computer", GameType::computer_computer}
    };

    std::string all_types = "";
    for(const auto &p : mapping)
        all_types += p.first + ",";
    all_types.pop_back();

    std::string selected_type;
    do {
        cout << "Select game type [" << all_types << "]: ";
        cin >> selected_type;
    } while(not mapping.contains(selected_type));

    return mapping.at(selected_type);
}


unsigned int GameCLInterface::request_field_size()
{
    unsigned int size;
    cout << "Select field size: ";
    cin >> size;
    return size;
}


void GameCLInterface::startgame_message()
{
    cout << "Welcome to tic-tac-toe!\n";
}


void GameCLInterface::endgame_message(short winner_n)
{
    if(winner_n < 0)
        cout << "The end. Draw.";
    else
        cout << "The end. Player " << winner_n << " won.\n";
}


void GameCLInterface::bad_step_message(short player_n)
{
    cout << "You can't move like this\n";
}


void GameCLInterface::show_field()
{
    auto field = _game->field();
    if (field.size() < 16) {
        for (size_t i = 0; i < field.size(); i++)
        {
            for (size_t k = 0; k < field.size(); k++){
                if (k > 0)
                    cout << " | ";
                if (k == 0)
                    cout << " ";

                cout << field[i][k];
            }
            cout << endl;
            if (i < field.size() - 1) {
                for (size_t k = 0; k < 3.5*field.size()+1; k++)
                    cout << "-";
                cout << endl;
            }
        }
    }
}


UserCLInterface::UserCLInterface():
    _player(nullptr)
{}


void UserCLInterface::set_player(Player *player)
{
    _player = player;
}


Point UserCLInterface::request_move()
{
    cout << "Your move " << _player->name() << ": ";
    unsigned int x, y;
    cin >> x >> y;

    return {x-1, y-1};
}

std::string UserCLInterface::request_name()
{
    std::string name;
    cout << "Enter your name: ";
    cin >> name;
    return name;
}

Symbol UserCLInterface::request_symbol()
{
    Symbol symbol;
    do {
        cout << "Select your symbol (any character except '_'): ";
        cin >> symbol;
    }
    while(symbol == '_');

    return symbol;
}