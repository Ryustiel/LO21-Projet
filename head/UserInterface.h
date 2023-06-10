#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"
#include "Player.h"
#include "../exception/ShottenTottenException.h"


class UserInterface { //parent class
public :
    static UserInterface* getInstance();
    static void freeInstance();


    virtual void launchUserInterface() = 0; 
    virtual void quickLaunch(int ia1, int ia2, Version v) = 0;


    virtual int uiSelectCard(bool* possibleChoice) = 0;
    virtual int uiSelectStone(bool* pickable) = 0;
    virtual unsigned int uiSelectStoneForCombatMode(bool* pickable) = 0;
    virtual int uiSelectStoneForClaim(bool* pickable) = 0;
    virtual bool uiWantClaimStone() = 0;
    virtual Deck* uiSelectDeck() = 0;
    virtual void uiSelectCardAndStone(Side s, int& cardNb, int& stoneNb, bool* pickableCards) =0;
    virtual bool uiSelectPlayOrDiscard() = 0;
    void uiInvalidChoiceMsg() { cout << "Invalid choice." << endl; }

    virtual void uiPrintPlayerHand()=0;
    virtual void uiPrintGame()=0;
    virtual void uiPrintDiscard()=0;
    virtual void uiPrintCurrentPlayer() =0;

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
    static void setInstance();

    void launchUserInterface() final; //main
    void quickLaunch(int ia1, int ia2, Version v);


    /// SUPERVISOR SETTINGS ///
    Version uiSelectVersion(); //user input
    Version uiVersionMenu();
    unsigned int uiSelectRounds(); //select nb rounds (user input)

    /// GAME SETTINGS ///
    string uiSelectPlayerName(int i, int& isIA1);
    void uiPlayerMenu(string players_name[], int& isIA1, int& isIA2);



    virtual int uiSelectCard(bool* pickable) final;
    int uiSelectStone(bool* pickable) final;
    unsigned int uiSelectStoneForCombatMode(bool* pickable) final;
    int uiSelectStoneForClaim(bool* pickable) final; 
    bool uiWantClaimStone() final {
        cout << "Do you want to claim a stone ? (0: no, 1: yes)" << endl;
        int result;
        while (true) {
            cin >> result;
            if (result < 2 && result >= 0) {
                return result;
            }
        }
        return 1;
    };
    Deck* uiSelectDeck() final;

    

    //INPUT USERS

    unsigned int userInputChoice(unsigned int option_count, const string& retry_message) const {
        unsigned int card_nb = 0;
        cin >> card_nb;
        while ((card_nb < 0) || (card_nb >= option_count)) { // repeat until user enters a valid input
            cout << endl << retry_message;
            cin >> card_nb;
        }
        return card_nb;
    }

    int userSelectCardOnStone(Side s, unsigned int stone_nb) {
        Stone& cur_stone = Supervisor::getInstance().getController()->getBoard().getStone(stone_nb);
        size_t stone_size = cur_stone.getSideSize(s);
        if (stone_size == 0) return -1; //no card on this side

        int card_nb = 0;
        cout << "Select a card to steal : ";
        cin >> card_nb;
        cout << endl;

        while (card_nb < 0 || card_nb >= stone_size) {
            cout << "Your choice is incorrect. Please select a card to steal :";
            cin >> card_nb;
            cout << endl;
        }
        return card_nb;
    }

    bool userBooleanChoice() {
        bool choice = 0;
        cin >> choice;
        return choice;
    }
    ///PLAY THE GAME
    void uiGameView2(); //pick a card
    void uiGameView3(); //pick a stone (always after uiGameView2) ; can be skipped
    void uiGameView4(); //click to continue
    void uiGameView5(); //draw a card
    void uiRoundLauncher(); //launches the round
    void uiTurnLauncher(Player& curr_player); //launches the turn


    void uiSelectCardAndStone(Side s, int& cardNb, int& stoneNb, bool* pickableCards) final;
    unsigned int uiSelectCardOnStone(Side s, unsigned int stone_nb);
    bool uiSelectPlayOrDiscard() final;

    //affichage
    void uiPrintCurrentPlayer();
    void uiPrintPlayerHand();
    void uiPrintGame();
    void uiPrintDiscard() ;

protected :
    UserInterfaceCmd() {}
    virtual ~UserInterfaceCmd() {}

};
