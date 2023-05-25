#ifndef PARAMETERSVIEW_H
#define PARAMETERSVIEW_H

#include <QWidget>
#include "../head_view/versionview.h"

#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class VueParametres : public QWidget {
    Q_OBJECT
public:
    explicit VueParametres(QWidget *parent = nullptr): QWidget(parent){
        setWindowTitle("Paramètres");

        choixJ = new QLabel("Choisir le type de joueur adverse :");

        choix = new QComboBox(parent);
        choix->addItem("Humain");
        choix->addItem("IA aléatoire");
        choix->addItem("IA stratégique");

        connect(choix, SIGNAL(currentIndexChanged(int)), this, SLOT(playerChanged()));

        nom1 = new QLabel("Nom du joueur 1 :");
        name1 = new QLineEdit(parent);

        nom2 = new QLabel("Nom du joueur 2 :");
        name2 = new QLineEdit(parent);

        go = new QPushButton(parent);
        go->setText("Continuer");
        connect(go, SIGNAL(clicked()), this, SLOT(handleContinuer()));

        Choix = new QHBoxLayout;
        Choix->addWidget(choixJ);
        Choix->addWidget(choix);

        nomJ1 = new QHBoxLayout;
        nomJ1->addWidget(nom1);
        nomJ1->addWidget(name1);


        nomJ2 = new QHBoxLayout;
        nomJ2->addWidget(nom2);
        nomJ2->addWidget(name2);

        noms = new QVBoxLayout;
        noms->addLayout(nomJ1);
        noms->addLayout(nomJ2);

        couche = new QVBoxLayout;
        couche->addLayout(Choix);
        couche->addLayout(noms);
        couche->addWidget(go);

        setLayout(couche);
    };
    const QString getNom1() const {return name1->text();}
    const QString getNom2() const {return name2->text();}
    bool est_IA() const {return (choix->currentIndex()==1 || choix->currentIndex()==2);}
private:
    QComboBox* choix;
    QLabel* choixJ;
    QLabel* nom1;
    QLabel* nom2;
    QLineEdit* name1;
    QLineEdit* name2;
    QHBoxLayout* nomJ1;
    QHBoxLayout* nomJ2;
    QVBoxLayout* noms;
    QHBoxLayout* Choix;
    QVBoxLayout* couche;
    QPushButton* go;
private slots:
    // slots qui gère les clics sur le bouton
    void playerChanged();
    void handleContinuer();
};



#endif // PARAMETERSVIEW_H
