#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"
#include "Player.h"
#include "../exception/ShottenTottenException.h"

class UserInterface { //singleton
private:

    unsigned int state = 0;

    UserInterface() {}
    ~UserInterface() {}

    struct Handler {
        UserInterface* instance = nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    void setState(const unsigned int i) { state = i; }

    //get l'UserInterface
    static UserInterface& getInstance();
    static void freeInstance();

    void launchUserInterface(); //main
    
    //SETTINGS
    void UIGameInit();
    unsigned int UISelectRounds(); //select nb rounds (user input)

    /// SUPERVISOR SETTINGS ///
    //SELECT VERSION
    Version UIselectVersion(); //user input
    Version UIVersionMenu();

    /// GAME SETTINGS///
    //PLAYERS NAME
    string UIselectPlayerName(int i, int& isIA1);
    void UIPlayerMenu(string players_name[], int& isIA1, int& isIA2);

    unsigned int UISelectCard();
    unsigned int UISelectStone();
    unsigned int UISelectStoneForCombatMode();
    bool UIWantClaimStone() { return false; };

    //INPUT USERS
    unsigned int userSelectCard() const {
        unsigned int card_nb = 0;
        cin >> card_nb;
        return card_nb;
    }

    unsigned int userSelectStone() const {
        unsigned int stone_nb = 0;
        cin >> stone_nb;
        return stone_nb;
    }

    ///PLAY THE GAME
    void UIGameView2(); //pick a card
    void UIGameView3(); //pick a stone (always after UIGameView2) ; can be skipped
    void UIGameView4(); //click to continue
    void UIGameView5(); //draw a card
    void UIRoundLauncher(); //launches the round
    void UITurnLauncher(Player& curr_player); //launches the turn

    void UIPlayCard();

};