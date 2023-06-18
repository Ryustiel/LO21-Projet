#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <vector>
#include <array>
#include <set>
#include "cardview.h"
#include "stoneview.h"
#include "../../head/Supervisor.h"
#include "../../head/Card.h"
#include "../../head/UserInterface.h"
#include "versionview.h"
#include "qlabel.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include "stoneview.h"
#include "deckview.h"

class VuePartie : public QWidget, public UserInterface
{
    Q_OBJECT
    //explicit VuePartie(QWidget *parent = nullptr);
    int receivedHandCard = -1;
    int receivedBorne = -1;
    int receivedSide = -1;
    Deck* receivedDeck = nullptr;
    bool wantToClaim;
    Version version;
public:
    VuePartie();
    static void setInstance() {
        if (handler.instance == nullptr) handler.instance = new VuePartie;
    }

    void launchUserInterface();
    void startWindow();
    void StartSupervisor();
    void quickLaunch(int ia1, int ia2, Version v);

    int uiSelectCard(bool* possibleChoice) final;
    int uiSelectStone(bool* pickable) final;
    unsigned int uiSelectStoneForCombatMode(bool* pickable)final;
    int uiSelectStoneForClaim(bool* pickable) final;
    bool uiWantClaimStone() final;
    Deck* uiSelectDeck() final;
    void uiSelectCardAndStone(Side s, int& cardNb, int& stoneNb, bool* pickableCards) final;
    bool uiSelectPlayOrDiscard() final;
    void uiUpdateView() final;

    void updateStonesView();

    void uiShowMessage(const string s);

    void uiPrintPlayerHand() {};
    void uiPrintGame() {};
    void uiPrintDiscard() {};
    void uiPrintCurrentPlayer() {};
    void uiControllerReady() final;

    //void uiInvalidChoiceMsg() { cout << "Invalid choice." << endl; }
    VueVersion vVersion;
signals:
    void clickCardReceived();
    void clickStoneReceived();
    void clickDeckReceived();
    void clickCardOnBorneReceived();
protected:
    QLabel* tourJeu;
    QLabel* tourJoueur;
    QLabel* scorej1; // texte "Score joueur1"
    QLabel* scorej2; // texte "Score joueur 2"
    QLCDNumber* scoreJoueur1; // affichage du score j1
    QLCDNumber* scoreJoueur2; // affichage du score j2
    QLabel* instructions;
    QLabel* manche;
    QLCDNumber* mancheValue;
    QLabel* piocheClan; // texte "Pioche"
    QLabel* piocheTactique;
    QProgressBar* nbCartesPiocheClan; // progression de la pioche
    QProgressBar* nbCartesPiocheT;
    QVBoxLayout* pbPioches;
    VuePioche* clanDeck;
    VuePioche* tacticDeck;
    QHBoxLayout* layoutInformations;
    QGridLayout* layoutCartes; // grille des cartes
    QVBoxLayout* layoutPioches;
    QGridLayout* layoutMain1;
    QGridLayout* layoutMain2;
    QVBoxLayout* couche;
    vector<VueBorne*> bornes;
    vector<array<vector<VueCarte*>,2>> cartesPlateau; // adresses des objets VueCarte
    vector<VueCarte*> cartesMain1;
    QLabel* handLabel;
public slots:
    void actionCarteMain(int nb);
    void actionCarteBorne(int nb, int stoneNb, int side);
protected slots:
    // slots qui gère les clics sur les cartes

    void actionBorne(int i);
    void actionPioche(Deck* vp);
    void receiveVersionInfos();
    void claimAccepted();
    void claimRefused();
};




#endif // BOARDVIEW_H
