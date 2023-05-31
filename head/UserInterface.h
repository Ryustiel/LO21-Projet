#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"
#include "Player.h"
#include "../exception/ShottenTottenException.h"


class UserInterface { //parent class
private :
    unsigned int state = 0;

public :
    static void freeInstance();

    unsigned int getState() const { return state; }
    unsigned int& getState() { return state; }

    //get l'UserInterface
    virtual void launchUserInterface() = 0; //main

    virtual void setState(const unsigned int i) { state = i; }

    virtual void UIGameInit() = 0;
    virtual unsigned int UISelectRounds() = 0; //select nb rounds (user input)
   

    /// SUPERVISOR SETTINGS ///
    //SELECT VERSION
    virtual  Version UIselectVersion() = 0; //user input
    virtual Version UIVersionMenu() = 0;

    /// GAME SETTINGS///
    //PLAYERS NAME
    virtual string UIselectPlayerName(int i, int& isIA1) = 0;
    virtual void UIPlayerMenu(string players_name[], int& isIA1, int& isIA2) = 0;

    virtual unsigned int UISelectCard() = 0;
    virtual unsigned int UISelectStone() = 0;
    virtual unsigned int UISelectStoneForCombatMode() = 0;
    virtual bool UIWantClaimStone() = 0;
    virtual Deck& UISelectDeck() = 0;
protected:
    UserInterface() {}
    virtual ~UserInterface() {}
    struct Handler { //singleton
        UserInterface* instance = nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
};


class UserInterfaceCmd : public UserInterface {
private:

public:

    static UserInterface* getInstance();
    static void setInstance();
        
    void launchUserInterface() final; //main

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

    unsigned int UISelectCard() final;
    unsigned int UISelectStone() final;
    unsigned int UISelectStoneForCombatMode() final;
    bool UIWantClaimStone() final {
        cout << "Do you want to claim a stone ? (0: yes, 1: no)" << endl;
        int result;
        while (true) {
            cin >> result;
            if (result < 2 && result >= 0) {
                return !result;
            }
        }

    };
    Deck& UISelectDeck() final;

    //INPUT USERS
    unsigned int userSelectCard() const {
        unsigned int card_nb = 0;
        cin >> card_nb;
        unsigned int card_hand_count = Supervisor::getInstance().getController()->getCurrentPlayer()->getHand()->getSize();
        while (((card_nb < 0) || (card_nb >= card_hand_count)) || (!Supervisor::getInstance().getController()->getPickableCards()[card_nb])) { //user input until correct
            cout << endl << "You can't play this card. Please select a card to play from your hand : ";
            cin >> card_nb;
        }
        return card_nb;
    }

    unsigned int userSelectStone() const {
        unsigned int stone_nb = 0;
        cin >> stone_nb;
        while (!Supervisor::getInstance().getController()->getPlayableStones()[stone_nb]) { //user input until correct
            cout << "You can't play this card. Please select a card to play from your hand : ";
            cin >> stone_nb;
        }
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

protected :
    UserInterfaceCmd() {}
    virtual ~UserInterfaceCmd() {}

};