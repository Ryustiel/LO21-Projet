#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include "../../head/Supervisor.h"
#include "../../head/Version.h"
#include "../head_view/cardview.h"
#include "../head_view/boardview.h"
#include <QEventLoop>

//constructeur
VuePartie::VuePartie() : QWidget(){}

void VuePartie::startWindow(){
    cartesPlateau = vector<VueCarte *>(Supervisor::getInstance().getController()->getBoard().getStoneNb()*3*2,nullptr);
    cartesMain1 = vector<VueCarte *>(Supervisor::getInstance().getController()->getPlayer1().getHand()->getSize(),nullptr);
    cartesMain2  = vector<VueCarte *>(Supervisor::getInstance().getController()->getPlayer2().getHand()->getSize(),nullptr);
    bornes = vector<VueBorne *>(Supervisor::getInstance().getController()->getBoard().getStoneNb(),nullptr);


    setWindowTitle("Schotten Totten"); //titre fenetre
    //setFixedSize(800, 600); //dimensions fenetre
    //distribuer cartes grace au controleur


    //barre de progression pioche
    piocheClan=new QLabel("Pioche clan");
    auto nb_cartes_jeu=Supervisor::getInstance().getController()->getClanGame().getCardCount();
    auto nb_cartes_pioche=Supervisor::getInstance().getController()->getClanDeck().getCardCount();

    nbCartesPiocheClan=new QProgressBar;
    nbCartesPiocheClan->setRange(0,nb_cartes_jeu);
    nbCartesPiocheClan->setValue(nb_cartes_pioche);
    nbCartesPiocheClan->setFixedHeight(20);
    nbCartesPiocheClan->setFixedWidth(250);

    QHBoxLayout* piocheC = new QHBoxLayout;
    piocheC->addWidget(piocheClan);
    piocheC->addWidget(nbCartesPiocheClan);

    pbPioches = new QVBoxLayout;
    pbPioches->addLayout(piocheC);

    //manches restantes
    manche = new QLabel("Manches restantes :");
    mancheValue = new QLCDNumber;
    mancheValue->display(Supervisor::getInstance().getController()->getRemainingRounds());

    QVBoxLayout* manches= new QVBoxLayout;
    manches->addWidget(manche);
    manches->addWidget(mancheValue);

    //Joueur actuel
    tourJeu = new QLabel("Tour de " + QString::fromStdString(Supervisor::getInstance().getController()->getCurrentPlayer()->getName()));

    QVBoxLayout* tour = new QVBoxLayout;
    tour->addWidget(tourJeu);
    tour->setContentsMargins(20,0,20,0);

    //Scores joueurs
    QString joueur1 = "Score " + QString::fromStdString(Supervisor::getInstance().getController()->getPlayer1().getName());
    scorej1=new QLabel(joueur1);
    QString joueur2 = "Score " + QString::fromStdString(Supervisor::getInstance().getController()->getPlayer2().getName());
    scorej2=new QLabel(joueur2);

    scoreJoueur1 = new QLCDNumber;
    scoreJoueur1->display(static_cast<int>(Supervisor::getInstance().getController()->getPlayer1().getScore()));
    scoreJoueur1->setFixedHeight(30);

    scoreJoueur2 = new QLCDNumber;
    scoreJoueur2->display(static_cast<int>(Supervisor::getInstance().getController()->getPlayer2().getScore()));
    scoreJoueur2->setFixedHeight(30);

    QHBoxLayout* j1= new QHBoxLayout;
    QHBoxLayout* j2=new QHBoxLayout;
    j1->addWidget(scorej1);
    j1->addWidget(scoreJoueur1);
    j2->addWidget(scorej2);
    j2->addWidget(scoreJoueur2);

    QVBoxLayout* scores = new QVBoxLayout;
    scores->addLayout(j1);
    scores->addLayout(j2);

    //Bandeau d'informations
    layoutInformations = new QHBoxLayout;
    layoutInformations->addLayout(pbPioches);
    layoutInformations->addLayout(manches);
    layoutInformations->addLayout(tour);
    layoutInformations->addLayout(scores);


    //affichage plateau
    layoutCartes = new QGridLayout;
    int k=3-1;

    int nbBornes= Supervisor::getInstance().getController()->getBoard().getStoneNb();
    int nbCartes= Supervisor::getInstance().getController()->getBoard().getStone(0).getMaxSize();
    //size_t k=nbCartes-1;
    //REMPLACER TOUS LES 3 PAR NBCARTES QUAND CA FONCTIONNERA (en haut aussi)
    cout<<"nb cartes : "<<nbCartes;

    for(int i=0;i<nbBornes*3;i++) {
        cartesPlateau[i]=new VueCarte();//dynamic_cast<const Clan*>(Supervisor::getInstance().getController()->getBoard().getStone(i%nbBornes).getCombinationP1()[k])
        cartesPlateau[i]->setContentsMargins(0,0,0,0);
        if (i%(nbBornes-1)==0) k--;
    }
    for(int i=0;i<nbBornes*3;i++) layoutCartes->addWidget(cartesPlateau[i],i/nbBornes,i%nbBornes);

    for(int i=0; i<nbBornes; i++){
        bornes[i]=new VueBorne();//Supervisor::getInstance().getController()->getBoard().getStone(i)
        bornes[i]->setContentsMargins(0,0,0,0);
        bornes [i]->setNb(i);
        size_t j=i+nbBornes*3;
        layoutCartes->addWidget(bornes[i], j/nbBornes, j%nbBornes);
        connect(bornes[i],SIGNAL(borneClicked(int)),this,SLOT(actionBorne(int)));
    }

    k=0;
    for(int i=nbBornes*3;i<nbBornes*3*2;i++) {
        cartesPlateau[i]=new VueCarte();//Supervisor::getInstance().getController()->getBoard().getStone(i%nbBornes).getCombinationP2()[k]
        cartesPlateau[i]->setContentsMargins(0,0,0,0);
        if (i%(nbBornes-1)==0) k++;
    }

    for(int i=3*nbBornes; i<nbBornes*3*2; i++){
        size_t j=i+nbBornes;
        layoutCartes->addWidget(cartesPlateau[i],j/nbBornes,j%nbBornes);
    }

    layoutCartes->setSpacing(0);

    /*
    //pour associer au vues cartes l'adresse d'une carte Clan
    size_t i=0;
    for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
        vuecartes[i]->setCarte(*it);
        i++;
    }
    */

    //Pioche

    clanDeck = new VuePioche(Supervisor::getInstance().getController()->getClanDeck());
    connect(clanDeck, SIGNAL(piocheClicked()),this, SLOT(actionPioche()));

    QVBoxLayout* clan = new QVBoxLayout;
    QLabel* piocheClan2 =new QLabel("Pioche clan");
    clan->addWidget(piocheClan2);
    clan->addWidget(clanDeck);

    layoutPioches = new QVBoxLayout;
    layoutPioches->addLayout(clan);
    layoutPioches->setContentsMargins(20,200,0,200);

    QHBoxLayout* plateau = new QHBoxLayout;
    plateau->addLayout(layoutCartes);
    plateau->addLayout(layoutPioches);
    plateau->setContentsMargins(0,25,0,25);

    //Mains
    QLabel* mainj1 = new QLabel("Main "+QString::fromStdString(Supervisor::getInstance().getController()->getPlayer1().getName()));
    QFont font = QFont();
    font.setPointSize(11);
    mainj1->setFont(font);
    mainj1->setContentsMargins(0,0,20,0);

    layoutMain1 = new QGridLayout;
    for(int i=0; i<Supervisor::getInstance().getController()->getPlayer1().getHand()->getSize(); i++)
    {
        cartesMain1[i]= new VueCarte();//dynamic_cast<const Clan*>(Supervisor::getInstance().getController()->getPlayer1().getHand()->getCard(i))
        cartesMain1[i]->setNb(i);
        connect(cartesMain1[i],SIGNAL(carteClicked(int)),this,SLOT(actionCarteMain(int)));
        layoutMain1->addWidget(cartesMain1[i],0,i);
    }

    QHBoxLayout* main1 = new QHBoxLayout;
    main1->addWidget(mainj1);
    main1->addLayout(layoutMain1);
    main1->setContentsMargins(10,0,260,0);


    QLabel* mainj2 = new QLabel("Main "+QString::fromStdString(Supervisor::getInstance().getController()->getPlayer2().getName()));
    mainj2->setFont(font);
    mainj2->setContentsMargins(0,0,20,0);

    layoutMain2 = new QGridLayout;
    for(int i=0; i<Supervisor::getInstance().getController()->getPlayer2().getHand()->getSize(); i++)
    {
        cartesMain2[i]= new VueCarte();//dynamic_cast<const Clan*>(Supervisor::getInstance().getController()->getPlayer2().getHand()->getCard(i))
        cartesMain1[i]->setNb(i);
        connect(cartesMain2[i],SIGNAL(carteClicked(int)),this,SLOT(actionCarteMain(int)));
        layoutMain2->addWidget(cartesMain2[i],0,i);
    }

    QHBoxLayout* main2 = new QHBoxLayout;
    main2->addWidget(mainj2);
    main2->addLayout(layoutMain2);
    main2->setContentsMargins(10,0,260,0);

    //ajouter layouts a fenetre globale
    couche = new QVBoxLayout;
    couche->addLayout(layoutInformations);
    couche->addLayout(plateau);
    couche->addLayout(main1);
    couche->addLayout(main2);

    switch(Supervisor::getInstance().getController()->getCurSide()){
    case(Side::s1):
        couche->removeItem(main2);
        break;

    case(Side::s2):
        couche->removeItem(main1);

    }

    setLayout(couche);
    show();
}

void VuePartie::launchUserInterface(){
    connect(&(vVersion.getVueParametres()), SIGNAL(isDone()), this, SLOT(receiveVersionInfos()));
    vVersion.show();

}

void VuePartie::StartSupervisor(){

}

void VuePartie::uiControllerReady(){
    startWindow();
}

void VuePartie::receiveVersionInfos(){
    VueParametres& vp = vVersion.getVueParametres();
    Supervisor::getInstance().eventStartGame(vVersion.getVersion(),vp.getNom1().toStdString(),vp.getNom2().toStdString(),vp.est_IA1(),vp.est_IA2(),vp.getRoundNb(),4);
}

void VuePartie::quickLaunch(int ia1, int ia2, Version v) {

    string players_name[2] = { "Le Gontil", "Le Michon" };
    int AI_player1 = ia1;
    int AI_player2 = ia2;

    Version selected_version = v;

    //cout << "(uiGameInit) - players_name[0] : " << [0] << endl;
    //cout << "(uiGameInit) - players_name[1] : " << playplayers_nameers_name[1] << endl;

    //cout << "(uiGameInit) - isIA1 = " << isIA1;
    //cout << "(uiGameInit) - isIA2 = " << isIA2;

    unsigned int rounds_nb = 5;

    Supervisor::getInstance().eventStartGame(selected_version, players_name[0], players_name[1], AI_player1, AI_player2, rounds_nb, 4);
}
//cas version TACTIQUE
//constructeur
VuePartieTactique::VuePartieTactique() : VuePartie()
{
    //ajout bar de progression pioche tactique
    piocheTactique=new QLabel("Pioche tactique");
    TacticController* controller=dynamic_cast<TacticController*>(Supervisor::getInstance().getController());
    auto nb_cartes_jeu=controller->getTacticGame().getCardCount();
    auto nb_cartes_pioche=controller->getTacticDeck().getCardCount();

    nbCartesPiocheT=new QProgressBar;
    nbCartesPiocheT->setRange(0,nb_cartes_jeu);
    nbCartesPiocheT->setValue(nb_cartes_pioche);
    nbCartesPiocheT->setFixedHeight(20);
    nbCartesPiocheT->setFixedWidth(250);

    QHBoxLayout* piocheT = new QHBoxLayout;
    piocheT->addWidget(piocheTactique);
    piocheT->addWidget(nbCartesPiocheT);

    pbPioches->addLayout(piocheT);
    pbPioches->update();


    //pioches et défausse
    disconnect(clanDeck, SIGNAL(piocheClicked()),this, SLOT(actionPioche()));
    connect(clanDeck, SIGNAL(piocheClicked(VuePioche*)),this, SLOT(actionPioche(VuePioche*)));

    tacticDeck = new VuePioche(controller->getTacticDeck());
    connect(tacticDeck, SIGNAL(piocheClicked(VuePioche*)),this, SLOT(actionPioche(VuePioche*)));

    QVBoxLayout* tactic = new QVBoxLayout;
    QLabel* piocheTactique2=new QLabel("Pioche tactique");
    tactic->addWidget(piocheTactique2);
    tactic->addWidget(tacticDeck);

    //défausse
    QLabel* defausse = new QLabel("Défausse");
    discard= new VueCarte(); //*(controller->getDiscard()->begin()) OU controller->getDiscard()->begin().currentItem()
    connect(discard,SIGNAL(carteClicked()),this,SLOT(actionDefausse()));

    QVBoxLayout* Discard = new QVBoxLayout;
    Discard->addWidget(defausse);
    Discard->addWidget(discard);

    layoutPioches->addLayout(tactic);
    layoutPioches->addLayout(Discard);
    layoutPioches->setContentsMargins(20,60,0,60);
    layoutPioches->update();

    couche->update();

    setLayout(couche);
}

unsigned int VuePartie::uiSelectCard(bool taticCheck){
    //vVersion.show();

    QEventLoop loop;
    connect(this, SIGNAL(clickCardReceived()), & loop, SLOT(quit()));
    loop.exec();
    return receivedHandCard;
};
unsigned int uiSelectCard(Stone* stone, Side side) {return 1;};
unsigned int VuePartie::uiSelectStone() {
    QEventLoop loop;
    connect(this, SIGNAL(clickStoneReceived()), & loop, SLOT(quit()));
    loop.exec();
    return receivedBorne;
};
unsigned int uiSelectStoneCombatMode() {return 1;};
unsigned int uiSelectStoneForCombatMode() {return 1;};
int uiSelectStoneForClaim() {return 1;};
int userSelectStoneForClaim() {return 1;};
bool VuePartie::uiWantClaimStone() {return 0;};
Deck* VuePartie::uiSelectDeck() {return &Supervisor::getInstance().getController()->getClanDeck();};
unsigned int uiSelectUnclaimedStone() { return 0;};
int uiSelectCardOnStone(Side s, unsigned int stone_nb) {return 1;};

void uiPrintPlayerHand() {return;};
void uiPrintGame() {return;};
void uiPlayCard() {return;};
void uiPrintCurrentPlayer() {return;};
void uiPrintDiscard() {return;};


void VuePartie::actionCarteMain(int nb){
    receivedHandCard = nb;
    emit clickCardReceived();
}
void VuePartieTactique::actionCartePlateau(VueCarte* vc){}
void VuePartie::actionBorne(int i){
    receivedBorne = i;
    emit clickStoneReceived();
}
void VuePartieTactique::actionBorne(VueBorne* vb){}
void VuePartie::actionPioche(VuePioche* vp){
    receivedDeck = vp;
    emit clickDeckReceived();
}
void VuePartieTactique::actionPioche(VuePioche* vp){}
void VuePartieTactique::actionDefausse(){}

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



