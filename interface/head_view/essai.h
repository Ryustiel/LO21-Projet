
#ifndef ESSAI_H
#define ESSAI_H

#include <QWidget>
#include <vector>
#include <set>
#include "../../head/Card.h"


class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;

class VueCarte;
class Essai : public QWidget
{
    Q_OBJECT
public:
    explicit Essai(QWidget *parent = nullptr);
private:

    QLabel* label; // texte "Score"

    QHBoxLayout* layoutInformations;
    QGridLayout* layoutCartes; // grille des cartes
    QVBoxLayout* couche;
    vector<VueCarte*> vuecartes; // adresses des objets VueCarte
    //std::set<const Set::Carte*> selectionCartes; // ensemble des cartes sélectionnées

private slots:
    // slots qui gère les clics sur les cartes
    void carteClique(VueCarte* vc);
};


#endif // ESSAI_H
