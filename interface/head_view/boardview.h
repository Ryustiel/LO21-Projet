
#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QWidget>
#include <vector>
#include <set>
#include "../../head/Card.h"
#include "cardview.h"
#include "boardview.h"
#include "../../head/Controller.h"
#include "qlabel.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;
class VueCarte;

class VuePartie : public QWidget
{
    Q_OBJECT
public:
    explicit VuePartie(QWidget *parent = nullptr);
private:
    Controller controleur; // controleur de la partie a ajouter
    QLabel* joueur1;
    QLabel* joueur2;
    QLabel* scorej1; // texte "Score joueur1"
    QLabel* scorej2; // texte "Score joueur 2"
    QLCDNumber* scoreJoueur1; // affichage du score j1
    QLCDNumber* scoreJoueur2; // affichage du score j2
    QLabel* instructions;
    QLabel* manche;
    QLCDNumber* mancheValue;
    QLabel* pioche; // texte "Pioche"
    QProgressBar* nbCartesPioche; // progression de la pioche
    QHBoxLayout* layoutInformations;
    QGridLayout* layoutCartes; // grille des cartes
    QVBoxLayout* layoutPioches;
    QGridLayout* layoutMain;
    QVBoxLayout* couche;
    vector<VueBorne*> bornes;
    vector<VueCarte*> cartesPlateau; // adresses des objets VueCarte
    vector<VueCarte*> cartesMain1;
    vector<VueCarte*> cartesMain2;
private slots:
    // slots qui gère les clics sur les cartes
    void selectioncarte(VueCarte* vc);
    void selectionborne(VueBorne* vb);
};

class VuePartieTactique : public VuePartie {
    QObject
public :
    explicit VuePartieTactique(QWidget *parent = nullptr);
private :
    QLabel* pioche2;
    QProgressBar* nbCartesPioche2;
};


#endif // BOARDVIEW_H
