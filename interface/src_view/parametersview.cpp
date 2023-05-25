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


void VueParametres::playerChanged(){

    switch (choix->currentIndex()) {
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
    if(name1->text()==""){
        QMessageBox messageBox(QMessageBox::Icon::Warning, "Attention", "Nom du joueur 1 vide");
        messageBox.exec();
        return;
    }

    if(choix->currentIndex()==0 && name2->text()==""){
        QMessageBox messageBox(QMessageBox::Icon::Warning, "Attention", "Nom du joueur 2 vide");
        messageBox.exec();
        return;
    }

    /*else{
        if(choix->currentIndex()==1 || choix->currentIndex()==2) name2->setText("IA");
        VuePartie* partie=new VuePartie(constructeur...);
        this->hide();
        partie->show();
    }*/
}
