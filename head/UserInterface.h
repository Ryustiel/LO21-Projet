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
    static UserInterface* getInstance();
    static void freeInstance();

    unsigned int getState() const { return state; }
    unsigned int& getState() { return state; }

    //get l'UserInterface
    virtual void launchUserInterface() = 0; //main
    virtual void quickLaunch(int ia1, int ia2, Version v) = 0;

    virtual void setState(const unsigned int i) { state = i; }

    virtual void uiGameInit() = 0;
    virtual unsigned int uiSelectRounds() = 0; //select nb rounds (user input)

    /// SUPERVISOR SETTINGS ///
    //SELECT VERSION
    virtual  Version uiSelectVersion() = 0; //user input
    virtual Version uiVersionMenu() = 0;

    /// GAME SETTINGS///
    //PLAYERS NAME
    virtual string uiSelectPlayerName(int i, int& isIA1) = 0;
    virtual void uiPlayerMenu(string players_name[], int& isIA1, int& isIA2) = 0;

    virtual unsigned int uiSelectCard() = 0;
    virtual unsigned int uiSelectCard(Stone* stone, Side side) = 0;
    virtual unsigned int uiSelectStone() = 0;
    virtual unsigned int uiSelectStoneCombatMode() = 0;
    virtual unsigned int uiSelectStoneForCombatMode() = 0;
    virtual int uiSelectStoneForClaim() = 0;
    virtual int userSelectStoneForClaim() const = 0;
    virtual bool uiWantClaimStone() = 0;
    virtual Deck* uiSelectDeck() = 0;
    virtual unsigned int uiSelectUnclaimedStone() = 0;
    virtual int uiSelectCardOnStone(Side s, unsigned int stone_nb) = 0;

    virtual void uiPrintPlayerHand() = 0;
    virtual void uiPrintGame() = 0;
    virtual void uiPlayCard() = 0;
    virtual void uiPrintCurrentPlayer() = 0;
    virtual void uiPrintDiscard() = 0;

    void uiInvalidChoiceMsg() { cout << "Invalid choice." << endl; }

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
    void quickLaunch(int ia1, int ia2, Version v) final;

    //SETTINGS
    void uiGameInit();
    unsigned int uiSelectRounds(); //select nb rounds (user input)

    /// SUPERVISOR SETTINGS ///
    //SELECT VERSION
    Version uiSelectVersion(); //user input
    Version uiVersionMenu();

    /// GAME SETTINGS ///
    //PLAYERS NAME
    string uiSelectPlayerName(int i, int& isIA1);
    void uiPlayerMenu(string players_name[], int& isIA1, int& isIA2);

    unsigned int uiSelectCard() final;
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

    void uiPrintCurrentPlayer() final;

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

        while (card_nb < 0 || card_nb >= 9) {
            cout << "Your choice is incorrect. Please select a card to steal :";
            cin >> card_nb;
            cout << endl;
        }
        return card_nb;
    }

    unsigned int uiSelectStoneCombatMode() override;
    ///PLAY THE GAME
    void uiGameView2(); //pick a card
    void uiGameView3(); //pick a stone (always after uiGameView2) ; can be skipped
    void uiGameView4(); //click to continue
    void uiGameView5(); //draw a card
    void uiRoundLauncher(); //launches the round
    void uiTurnLauncher(Player& curr_player); //launches the turn

    void uiPlayCard();

    unsigned int uiSelectUnclaimedStone() override;
    int uiSelectCardOnStone(Side s, unsigned int stone_nb) override;

    //affichage
    void uiPrintPlayerHand();
    void uiPrintGame();
    void uiPrintDiscard() override;

protected :
    UserInterfaceCmd() {}
    virtual ~UserInterfaceCmd() {}

};
