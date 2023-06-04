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

        choixJ1 = new QLabel("Choisir le type de joueur 1 :");

        choix1 = new QComboBox(parent);
        choix1->addItem("Humain");
        choix1->addItem("IA aléatoire");
        choix1->addItem("IA stratégique");

        connect(choix1, SIGNAL(currentIndexChanged(int)), this, SLOT(player1Changed()));

        choixJ2 = new QLabel("Choisir le type de joueur 2 :");

        choix2 = new QComboBox(parent);
        choix2->addItem("Humain");
        choix2->addItem("IA aléatoire");
        choix2->addItem("IA stratégique");

        connect(choix2, SIGNAL(currentIndexChanged(int)), this, SLOT(player2Changed()));

        nom1 = new QLabel("Nom du joueur 1 :");
        name1 = new QLineEdit(parent);

        nom2 = new QLabel("Nom du joueur 2 :");
        name2 = new QLineEdit(parent);

        go = new QPushButton(parent);
        go->setText("Continuer");
        connect(go, SIGNAL(clicked()), this, SLOT(handleContinuer()));

        Choix1 = new QHBoxLayout;
        Choix1->addWidget(choixJ1);
        Choix1->addWidget(choix1);

        Choix2 = new QHBoxLayout;
        Choix2->addWidget(choixJ2);
        Choix2->addWidget(choix2);

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
        couche->addLayout(Choix1);
        couche->addLayout(Choix2);
        couche->addLayout(noms);
        couche->addWidget(go);

        setLayout(couche);
    };
    const QString getNom1() const {return name1->text();}
    const QString getNom2() const {return name2->text();}
    bool est_IA1() const {return (choix1->currentIndex()==1 || choix1->currentIndex()==2);}
    bool est_IA2() const {return (choix2->currentIndex()==1 || choix2->currentIndex()==2);}
private:
    QComboBox* choix1;
    QLabel* choixJ1;
    QComboBox* choix2;
    QLabel* choixJ2;
    QLabel* nom1;
    QLabel* nom2;
    QLineEdit* name1;
    QLineEdit* name2;
    QHBoxLayout* nomJ1;
    QHBoxLayout* nomJ2;
    QVBoxLayout* noms;
    QHBoxLayout* Choix1;
    QHBoxLayout* Choix2;
    QVBoxLayout* couche;
    QPushButton* go;
private slots:
    // slots qui gère les clics sur le bouton
    void player1Changed();
    void player2Changed();
    void handleContinuer();
};



#endif // PARAMETERSVIEW_H
