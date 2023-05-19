#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>



class Controller{
private:
	const Version version = Version::legacy;
	Deck* clanDeck = nullptr;
	Board board;
	Game clanGame;
	Player* player1;
	Player* player2;
	bool round = 0;
	friend class Supervisor;

	// permet un arrêt prématuré de la partie,
	// en réponse à des événements spécifiques comme "quitter"
	// j'utilise une variable plutôt qu'un listener à cause
	// des boucles de jeu "while" dont on doit sortir de manière asynchrone
	// asynchrone à cause de l'interface Qt
	bool stop = false;

	// scores de manche stockés ici car impactent directement
	// la fin de boucle de manche et de partie
	int remainingRounds = 0; // initialisation discutable
    int totalRounds = 0;

	// VARIABLE TEMPORAIRE pour faire gagner chaque manche
	// automatiquement après 3 tours
	int TEMP_victory_counter;

	void newRound(); // événement de début de manche
	void checkRound(); // verifie si la manche est gagnée
	void eventStartTurn(); // lance un nouveau tour de joueur

public:
	Controller(const Controller& c) = delete;
	Controller& operator=(const Controller& c) = delete;

	// setting players AI
	// la manière de générer les instances des classes IA
	// peut être très différente, il faudra qu'on en discute
	void setPlayer1(Player* player) { player1 = player; }
    void setPlayer2(Player* player) { player2 = player; }

	void setRemainingRounds(int r) { remainingRounds = r; }
	void setTotalRounds(int r) { totalRounds = r; }

	// initialise la partie, lancé via l'interface
	// tous les paramètres de partie présents sur l'interface doivent lui être passés
	// on pourrait aussi gérer certains paramètres via le Superviseur.
	void eventNewGame(int nbTurns); // (int nbTurns, int typeia, ...)

	void qtDisplayVersionMenu() {
		std::cout << "\n================================ qtDisplayVersionMenu";
		std::cout << "\nenregistre un listener : callback = newGame()";
		std::cout << "\nQT affiche le menu de selection de parametres de partie...";
	}
	void qtDisplayVictoryMenu() {
		std::cout << "\n================================ qtDisplayVictoryMenu";
		std::cout << "\nenregistre un listener : callback = qtDisplayVersionMenu";
		std::cout << "\ngenere les informations qui recapitulent le resultat de la partie";
		std::cout << "\nQT affiche le menu qui recapitule ces informations";
	}
	void qtDisplayPlayerTurn() {
		std::cout << "\n================================ qtDisplayPlayerTurn";
		std::cout << "\nenregistre des callbacks pour choiceDraw(), choicePlay(), choiceEndTurn(), choiceClaim()";
	}
	void qtDisplayStonePicker() {
		std::cout << "\n================================ qtDisplayStonePicker";
		std::cout << "\ndemande a QT d'afficher le menu pour selectionner des bornes";
		std::cout << "\nrecupere la liste des bornes selectionnables d'apres l'etat du jeu";
		std::cout << "\nenvoie la liste des bornes";
		std::cout << "\nc'est elle qui se charge de la stocker dans l'objet";
		std::cout << "\nou au callback de checkStone(); methode du Board";
	}
	void qtDisplayCardPicker() {
		std::cout << "\n================================ qtDisplayCardPicker";
		std::cout << "\ndemande a QT d'afficher le menu pour selectionner des cartes";
		std::cout << "\nrecupere la liste des cartes jouables, la transmet a QT";
		std::cout << "\nla prochaine methode c'est eventCardPicked()";
	}
	void eventCardPicked(string c) {
		std::cout << "\n================================ eventCardPicked";
		std::cout << "\nCarte selectionnee : " << c;
		std::cout << "\nstocke la carte selectionnee par le joueur";
		std::cout << "\ndeclenche l'actif de la carte = appelle la methode active";
		std::cout << "\nl'actif declenchera probablement qtDisplayStonePicker()";
	}
	void eventStonePicked() {
		std::cout << "\nactive l'effet de la carte, les modifications sur l'etat du jeu";
		std::cout << "\nou alors declenche le checking de la borne, selon l'option de jeu en cours";
		std::cout << "\ndeclenche ensuite qtDisplayAlert() ou qtDisplayPlayerTurn() selon l'outcome";
	}
	void qtDisplayAlert() {
		std::cout << "\n================================ qtDisplayAlert";
		std::cout << "\naffiche un message sur le plateau de jeu";
		std::cout << "\nainsi qu'un message pour revenir au choix des cartes";
		std::cout << "\ncallback => qtDisplayPlayerTurn";
	}
	void eventChoiceDraw() {
		std::cout << "\n================================ choiceDraw";
		std::cout << "\ndeclenche la pioche";
		std::cout << "\nmet a jour la variable qui stocke la possibilite de jouer la pioche pour ce tour";
		std::cout << "\nrevient au qtDisplayPlayerTurn()";
	}
	void eventChoicePlay() {
		std::cout << "\n================================ choicePlay";
		std::cout << "\ndeclenche simplement qtDisplayCardPicker()";
	}
	void eventChoiceEndTurn() {
		std::cout << "\n================================ choiceEndTurn";
		std::cout << "\ndeclenche startTurn(), cette fonction intermediaire est la pour la clarete / explicitation";
	}
	void eventChoiceClaim() {
		std::cout << "\n================================ choiceClaim";
		std::cout << "\nrecupere la liste des bornes";
		std::cout << "\ndeclenche qtDisplayStonePicker()";
	}
protected:
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: remainingRounds(0), totalRounds(0), version(v), clanGame(Game(v)), clanDeck(new Deck(Game(v))), board(Board()), player1(new Player(name_player1, id_player1)), player2(new Player(name_player2, id_player2)) {
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy");
	}
	~Controller() {
		delete clanDeck;
		delete player1;
		delete player2;
	}
	Deck& getClanDeck();
  	Board& getBoard();
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	friend class Supervisor;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: Controller(Version::legacy, name_player1, name_player2, id_player1, id_player2), tacticGame(Game(v)), tacticDeck(new Deck(Game(v))) {
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	~TacticController() {
		delete tacticDeck;
	}
	Deck& getTacticDeck();
};
