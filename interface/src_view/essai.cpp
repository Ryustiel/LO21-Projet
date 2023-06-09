
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
#include "../head_view/essai.h"

//constructeur

Essai::Essai(QWidget *parent) : QWidget(parent),vuecartes(20,nullptr)
{
    setWindowTitle("Essai affichage carte"); //titre fenetre
    //controleur.distribuer(); //distribuer cartes


    label=new QLabel("Coucou");


    //Layouts
    layoutInformations = new QHBoxLayout;
    layoutCartes = new QGridLayout;
    couche = new QVBoxLayout;

    layoutInformations->addWidget(label);


    //afficher carte -> les initialiser avant
    for(size_t i=0;i<20;i++) vuecartes[i]=new VueCarteClan;
    for(size_t i=0;i<20;i++){
        layoutCartes->addWidget(vuecartes[i],i/4,i%4);
        //connexion signaux slots
        connect(vuecartes[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
    }

    //essai du paint avec un 8 bleu => donc utile à chaque fois

    Color color1=Color::blue;
    Number number1=Number::eight;
    Color color2=Color::red;
    Number number2=Number::two;
    Clan *c1=new Clan(color1,number1);
    Clan *c2=new Clan(color2,number2);

    //Tactical *t=new Tactical("boue");

    size_t i=0;
    qDebug() << "message";
    vuecartes[i]->setCarte(*c1);
    i++;
    vuecartes[i]->setCarte(*c2);


    /*
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


void Essai::carteClique(VueCarte* vc){

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


                //QMessageBox message(QMessageBox::Icon::Warning,"Taille 3","Taille 3!");
                //message.exec();

            }
        }
    }
    update();
}

*/

