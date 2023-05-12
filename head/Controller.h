#pragma once
#include "Board.h"
#include "Player.h"

class Controller {
private:
    bool stop = false;
    bool tour;
    Player* player1;
    Player* player2;
    int manches_restantes;
    int manches_total;
    Board* board;
    int TEMP_victory_counter;
    void handleNewManche();
    void runMancheLoop();
    void runChecks(); // running card checks on the board
public:
    Controller() { board = new Board; }
    void setPlayer1(Player* player) { player1 = player; }
    void setPlayer2(Player* player) { player2 = player; }
    static Controller* getController() { static Controller instance; return &instance; }
    void newGame(int nmanches);
};