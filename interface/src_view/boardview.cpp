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
#include "../head_view/boardview.h"

//constructeur
VuePartie::VuePartie(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Jeu Schotten Totten AHHHHHH"); //titre fenetre
    //setFixedSize(800, 600); //dimensions fenetre
    //distribuer cartes grace au controleur


    pioche=new QLabel("Pioche");
    scorej1=new QLabel("Score j1");
    scorej2=new QLabel("Score j2");

    auto nb_cartes_jeu=54;
    auto nb_cartes_pioche=10;
    //barre de progression pioche
    nbCartesPioche=new QProgressBar;
    nbCartesPioche->setRange(0,nb_cartes_jeu);
    nbCartesPioche->setValue(nb_cartes_pioche);
    nbCartesPioche->setFixedHeight(30);

    //Scores joueurs
    scoreJoueur1 = new QLCDNumber;
    scoreJoueur1->display(0);
    scoreJoueur1->setFixedHeight(30);

    scoreJoueur2 = new QLCDNumber;
    scoreJoueur2->display(0);
    scoreJoueur2->setFixedHeight(30);

    //Layouts
    layoutInformations = new QHBoxLayout;
    layoutCartes = new QGridLayout;
    couche = new QVBoxLayout;

    layoutInformations->addWidget(pioche);
    layoutInformations->addWidget(nbCartesPioche);
    layoutInformations->addWidget(scorej1);
    layoutInformations->addWidget(scorej2);
    layoutInformations->addWidget(scoreJoueur1);
    layoutInformations->addWidget(scoreJoueur2);

    //afficher carte -> les initialiser avant
    for(size_t i=0;i<20;i++) cartesPlateau[i]=new VueCarte;
    for(size_t i=0;i<20;i++){
        layoutCartes->addWidget(cartesPlateau[i],i/4,i%4);
        //connexion signaux slots
        connect(cartesPlateau[i],SIGNAL(actioncarte(VueCarte*)),this,SLOT(actioncarte(VueCarte*)));
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



