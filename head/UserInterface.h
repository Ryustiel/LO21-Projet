#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"
#include "Player.h"
#include "../exception/ShottenTottenException.h"

//SURCHARGE CALLBACK FUNCTION
void functionCallback(const Version v);
void functionCallback(const string s);

class UserInterface { //singleton
private:
    int state = 0;

    UserInterface() {}
    ~UserInterface() {}

    struct Handler {
        UserInterface* instance = nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    //get l'UserInterface
    static UserInterface& getInstance();
    static void freeInstance();

    void setState(int i) {
        if (i < 0 || i > 6) throw ShottenTottenException("setState : incorrect integer int");
        state = i;
    }

    void launchUserInterface();
    
    //SETTINGS
    void UIGameInit();
    void UIGameSettings();
    unsigned int UISelectRounds(); //select nb rounds (user input)

    /// SUPERVISOR SETTINGS ///
    //SELECT VERSION
    Version UIselectVersion(void (*callback) (Version v));
    Version UIVersionMenu();

    /// GAME SETTINGS///
    //PLAYERS NAME
    string UIselectPlayerName(int i, int& isIA1, void (*callback) (const string s));
    void UIPlayerMenu(string players_name[], int& isIA1, int& isIA2);


    ///PLAY THE GAME
    void UIGameLauncher();

};