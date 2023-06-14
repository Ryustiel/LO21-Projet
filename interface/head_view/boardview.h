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
#include "cardview.h"
#include "stoneview.h"
#include "deckview.h"

class VuePartie : public QWidget, public UserInterface
{
    Q_OBJECT
    //explicit VuePartie(QWidget *parent = nullptr);
    int receivedHandCard = -1;
    int receivedBorne = -1;
    VuePioche* receivedDeck = nullptr;
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
    unsigned int uiSelectStoneForCombatMode(bool* pickable)final {};
    int uiSelectStoneForClaim(bool* pickable) final {};
    bool uiWantClaimStone() final;
    Deck* uiSelectDeck() final;
    void uiSelectCardAndStone(Side s, int& cardNb, int& stoneNb, bool* pickableCards) final {};
    bool uiSelectPlayOrDiscard() {};
    void uiUpdateView() final;

    void updateStonesView();

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
    QProgressBar* nbCartesPiocheClan; // progression de la pioche
    QVBoxLayout* pbPioches;
    VuePioche* clanDeck;
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
    virtual void actionCarteMain(int nb);
protected slots:
    // slots qui gère les clics sur les cartes

    virtual void actionBorne(int i);
    void actionPioche(VuePioche* vp);
    void receiveVersionInfos();
};

class VuePartieTactique : public VuePartie {
    Q_OBJECT
public :
    VuePartieTactique();
    static void setInstance() {
        if (handler.instance == nullptr) handler.instance = new VuePartieTactique;
    }
    //~VuePartieTactique();
private :
    //explicit VuePartieTactique(QWidget *parent = nullptr);
    QLabel* piocheTactique;
    QProgressBar* nbCartesPiocheT;
    VuePioche* tacticDeck;
    VueCarte* discard;
private slots:
    void actionCartePlateau(VueCarte* vc);
    void actionBorne(VueBorne* vb);
    void actionPioche(VuePioche* vp);
    void actionDefausse();
};


#endif // BOARDVIEW_H
