#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>

#include "../head_view/cardview.h"
#include "../head_view/gameview.h"

//constructeur
VuePartie::VuePartie(QWidget *parent) : QWidget(parent),vuecartes(20,nullptr)
{
    setWindowTitle("Set !"); //titre fenetre
    //distribuer cartes grace au controleur

    pioche=new QLabel("Pioche");
    score=new QLabel("Score");

    auto nb_cartes_jeu=54;
    auto nb_cartes_pioche=54;
    //barre de progression pioche
    nbCartesPioche=new QProgressBar;
    nbCartesPioche->setRange(0,nb_cartes_jeu);
    nbCartesPioche->setValue(nb_cartes_pioche);
    nbCartesPioche->setFixedHeight(30);

    //Score
    scoreJoueur = new QLCDNumber;
    scoreJoueur->display(0);
    scoreJoueur->setFixedHeight(30);

    //Layouts
    layoutInformations = new QHBoxLayout;
    layoutCartes = new QGridLayout;
    couche = new QVBoxLayout;

    layoutInformations->addWidget(pioche);
    layoutInformations->addWidget(nbCartesPioche);
    layoutInformations->addWidget(score);
    layoutInformations->addWidget(scoreJoueur);

    //afficher carte -> les initialiser avant
    for(size_t i=0;i<20;i++) vuecartes[i]=new VueCarte;
    for(size_t i=0;i<20;i++){
        layoutCartes->addWidget(vuecartes[i],i/4,i%4);
        //connexion signaux slots
        connect(vuecartes[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
    }

    /*
    //pour associer au vues cartes l'adresse d'une carte Clan
    size_t i=0;
    for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
        vuecartes[i]->setCarte(*it);
        i++;
    }
    */


    //ajouter layout a fenetre globale
    couche->addLayout(layoutInformations);
    couche->addLayout(layoutCartes);
    setLayout(couche);
}

/*
void VuePartie::carteClique(VueCarte* vc){
    if(!vc->cartePresente()){
        if(controleur.getPioche().getNbCartes()==0){
            QMessageBox message(QMessageBox::Icon::Information,"Attention","La pioche est vide !");
            message.exec();
        }
        else{
            controleur.distribuer();
            size_t i=0;
            for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
                vuecartes[i]->setCarte(*it);
                i++;
            }
            nbCartesPioche->setValue(controleur.getPioche().getNbCartes());
        }
    }
    else{
        if(!vc->isChecked()){
            selectionCartes.erase(&vc->getCarte());
        }
        else{
            selectionCartes.insert(&vc->getCarte());

            if(selectionCartes.size()==3){
                vector<const Set::Carte*> c(selectionCartes.begin(),selectionCartes.end());

                Set::Combinaison comb(*c[0],*c[1],*c[2]);
                if(comb.estUnSET()){
                    controleur.getPlateau().retirer(*c[0]);
                    controleur.getPlateau().retirer(*c[1]);
                    controleur.getPlateau().retirer(*c[2]);

                    selectionCartes.clear();

                    if(controleur.getPlateau().getNbCartes()<12)
                        controleur.distribuer();

                    scoreValue++;
                    scoreJoueur->display(scoreValue);

                    for(size_t i=0;i<vuecartes.size();i++){
                        vuecartes[i]->setNoCarte();

                    }
                    size_t i=0;
                    for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
                        vuecartes[i]->setCarte(*it);
                        i++;
                    }

                    nbCartesPioche->setValue(controleur.getPioche().getNbCartes());



                }else{
                    QMessageBox message(QMessageBox::Icon::Warning,"Attention","ce n'est pas un set");
                    message.exec();

                    for(size_t i=0;i<vuecartes.size();i++){
                        vuecartes[i]->setChecked(false);

                    }
                    selectionCartes.clear();

                }


            }
        }
    }
    update();
}
*/



