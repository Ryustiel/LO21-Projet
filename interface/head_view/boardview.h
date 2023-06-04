#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <vector>
#include <set>
#include "cardview.h"
#include "stoneview.h"
#include "../../head/Supervisor.h"
#include "../../head/UserInterface.h"
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
    explicit VuePartie(QWidget *parent = nullptr);
public:
    static void setInstance() {
        if (handler.instance == nullptr) handler.instance = new VuePartie;
    }
    unsigned int uiSelectCard() final;
    unsigned int uiSelectCard(Stone* stone, Side side) final;
    unsigned int uiSelectStone() final;
    unsigned int uiSelectStoneCombatMode() final;
    unsigned int uiSelectStoneForCombatMode() final;
    int uiSelectStoneForClaim() final;
    int userSelectStoneForClaim() const final;
    bool uiWantClaimStone() final;
    Deck* uiSelectDeck() final;
    unsigned int uiSelectUnclaimedStone() final;
    int uiSelectCardOnStone(Side s, unsigned int stone_nb) final;

    void uiPrintPlayerHand() final;
    void uiPrintGame() final;
    void uiPlayCard() final;
    void uiPrintCurrentPlayer() final;
    void uiPrintDiscard() final;

    //void uiInvalidChoiceMsg() { cout << "Invalid choice." << endl; }
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
    vector<VueCarte*> cartesPlateau; // adresses des objets VueCarte
    vector<VueCarte*> cartesMain1;
    vector<VueCarte*> cartesMain2;
protected slots:
    // slots qui gère les clics sur les cartes
    virtual void actionCarteMain(VueCarte* vc);
    virtual void actionBorne(VueBorne* vb);
    void actionPioche();
};

class VuePartieTactique : public VuePartie {
    Q_OBJECT
public :
    static void setInstance() {
        if (handler.instance == nullptr) handler.instance = new VuePartieTactique;
    }
    //~VuePartieTactique();
private :
    explicit VuePartieTactique(QWidget *parent = nullptr);
    QLabel* piocheTactique;
    QProgressBar* nbCartesPiocheT;
    VuePioche* tacticDeck;
    VueCarte* discard;
private slots:
    void actionCarteMain(VueCarte* vc);
    void actionCartePlateau(VueCarte* vc);
    void actionBorne(VueBorne* vb);
    void actionPioche(VuePioche* vp);
    void actionDefausse();
};


#endif // BOARDVIEW_H
