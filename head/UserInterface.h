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


    virtual unsigned int uiSelectCard(bool taticCheck = true) = 0;
    virtual unsigned int uiSelectCard(Stone* stone, Side side) = 0;
    virtual unsigned int uiSelectStone() = 0;
    virtual unsigned int uiSelectStoneCombatMode() = 0;
    virtual unsigned int uiSelectStoneForCombatMode() = 0;
    virtual int uiSelectStoneForClaim() = 0;
    virtual int userSelectStoneForClaim() const = 0;
    virtual bool uiWantClaimStone() = 0;
    virtual Deck* uiSelectDeck() = 0;
    virtual unsigned int uiSelectUnclaimedStone() = 0;
    virtual unsigned int uiSelectCardOnStone(Side s, unsigned int stone_nb) = 0;
    virtual void uiSelectCardAndStone(Side s, unsigned int& cardNb, unsigned int& stoneNb) =0;
    virtual bool uiSelectPlayOrDiscard() = 0;
    void uiInvalidChoiceMsg() { cout << "Invalid choice." << endl; }

    virtual void uiPrintPlayerHand()=0;
    virtual void uiPrintGame()=0;
    virtual void uiPrintDiscard()=0;
    virtual void uiPrintCurrentPlayer() =0;
    virtual void uiControllerReady() = 0;

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



    unsigned int uiSelectCard(bool taticCheck = true) final;
    unsigned int uiSelectCard(Stone* stone, Side side) final;
    unsigned int uiSelectStone() final;
    unsigned int uiSelectStoneForCombatMode() final;
    int uiSelectStoneForClaim() final; //TO DELETE
    bool uiWantClaimStone() final {
        cout << "Do you want to claim a stone ? (0: yes, 1: no)" << endl;
        int result;
        while (true) {
            cin >> result;
            if (result < 2 && result >= 0) {
                return !result;
            }
        }
        return 1;
    };
    Deck* uiSelectDeck() final;

    

    //INPUT USERS
    unsigned int userSelectCard() const {
        unsigned int card_nb = 0;
        cout << endl << "Select a card to play from your hand (number) : ";
        cin >> card_nb;
        size_t card_hand_count = 0; // la valeur sera mise à jour avec getPickableCards()
        bool* pickable = Supervisor::getInstance().getController()->getPickableCards(&card_hand_count);
        while (((card_nb < 0) || (card_nb >= card_hand_count)) || (!pickable[card_nb])) { // user input until correct
            cout << endl << "You can't play this card. Please select a card to play from your hand : ";
            cin >> card_nb;
        }
        return card_nb;
    }

    unsigned int userSelectCard(unsigned int option_count, const string& retry_message) const {
        unsigned int card_nb = 0;
        cin >> card_nb;
        while ((card_nb < 0) || (card_nb >= option_count)) { // repeat until user enters a valid input
            cout << endl << retry_message;
            cin >> card_nb;
        }
        return card_nb;
    }

    unsigned int userSelectUnclaimedStone() const {
        unsigned int stone_nb = 0;
        unsigned int stone_count = Supervisor::getInstance().getController()->getBoard().getStoneNb();
        cout << "Select a stone (number) : ";
        cin >> stone_nb;
        while (stone_nb < 0 || stone_nb >= stone_count || !Supervisor::getInstance().getController()->getUnclaimedStones()[stone_nb]) { //user input until correct
            cout << "You can't choose this stone. Please select another stone : ";
            cin >> stone_nb;
        }
        return stone_nb;
    }

    unsigned int userSelectStone() const {
        unsigned int stone_nb = 0;
        unsigned int stone_count = Supervisor::getInstance().getController()->getBoard().getStoneNb();
        cout << "Select a stone (number) : ";
        cin >> stone_nb;
        while (stone_nb < 0 || stone_nb >= stone_count ||  !Supervisor::getInstance().getController()->getPlayableStones()[stone_nb]) { //user input until correct
            cout << "You can't choose this stone. Please select another stone : ";
            cin >> stone_nb;
        }
        return stone_nb;
    }

    int userSelectStoneForClaim() const {
        unsigned int stone_nb = 0;
        unsigned int stone_count = Supervisor::getInstance().getController()->getBoard().getStoneNb();
        cout << endl << "Please select a stone to claim (number) : ";
        cin >> stone_nb;
        cout << endl;
        if (stone_nb < 0 || stone_nb >= stone_count || !Supervisor::getInstance().getController()->getUnclaimedStones()[stone_nb]) { //unique user input
            cout << "You can't claim this stone." << endl;
            return -1;
        }
        return stone_nb;
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

    unsigned int uiSelectStoneCombatMode() override;
    ///PLAY THE GAME
    void uiGameView2(); //pick a card
    void uiGameView3(); //pick a stone (always after uiGameView2) ; can be skipped
    void uiGameView4(); //click to continue
    void uiGameView5(); //draw a card
    void uiRoundLauncher(); //launches the round
    void uiTurnLauncher(Player& curr_player); //launches the turn


    unsigned int uiSelectUnclaimedStone() override;
    unsigned int uiSelectCardOnStone(Side s, unsigned int stone_nb) override;
    void uiSelectCardAndStone(Side s, unsigned int& cardNb, unsigned int& stoneNb) override;
    bool uiSelectPlayOrDiscard() override;

    //affichage
    void uiPrintCurrentPlayer() final;
    void uiPrintPlayerHand() final;
    void uiPrintGame() final;
    void uiPrintDiscard() final;
    void uiControllerReady() final{};

protected :
    UserInterfaceCmd() {}
    virtual ~UserInterfaceCmd() {}

};
