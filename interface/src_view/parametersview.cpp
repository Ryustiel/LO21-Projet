#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include "../head_view/parametersview.h"
#include "../head_view/boardview.h"


void VueParametres::player1Changed(){

    switch (choix1->currentIndex()) {
    case 0: //Humain
        nom1->show(); //afficher le champ pour le nom du joueur 2
        name1->show();
        break;
    case 1: //IA aléatoire
        nom1->hide(); //cacher le champ pour le nom du joueur 2
        name1->hide();
        break;
    case 2: //IA stratégique
        nom1->hide(); //cacher le champ pour le nom du joueur 2
        name1->hide();
        break;
    }

}

void VueParametres::player2Changed(){

    switch (choix2->currentIndex()) {
    case 0: //Humain
        nom2->show(); //afficher le champ pour le nom du joueur 2
        name2->show();
        break;
    case 1: //IA aléatoire
        nom2->hide(); //cacher le champ pour le nom du joueur 2
        name2->hide();
        break;
    case 2: //IA stratégique
        nom2->hide(); //cacher le champ pour le nom du joueur 2
        name2->hide();
        break;
    }

}

void VueParametres::handleContinuer(){
    if(choix1->currentIndex()==0 && name1->text()==""){
        QMessageBox messageBox(QMessageBox::Icon::Warning, "Attention", "Nom du joueur 1 vide");
        messageBox.exec();
        return;
    }

    if(choix2->currentIndex()==0 && name2->text()==""){
        QMessageBox messageBox(QMessageBox::Icon::Warning, "Attention", "Nom du joueur 2 vide");
        messageBox.exec();
        return;
    }

    /*else{
        if(choix1->currentIndex()==1 || choix1->currentIndex()==2) name1->setText("IA1");
        if(choix2->currentIndex()==1 || choix2->currentIndex()==2) name1->setText("IA2");
        this->hide();
        partie->show();
    }*/
}
