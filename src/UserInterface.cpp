#include "../head/UserInterface.h"

///INTERFACE SINGLETON METHODS///
UserInterfaceCmd::Handler UserInterfaceCmd::handler = UserInterfaceCmd::Handler();

UserInterfaceCmd& UserInterfaceCmd::getInstance() {
	if (handler.instance == nullptr) handler.instance = new UserInterfaceCmd();
	return *handler.instance;
}

void UserInterfaceCmd::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}



/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UserInterfaceCmd::UIselectVersion() { //user select version
	Version selected_version;
	int selection = 0;
	int i = 0;

	cout << endl << "Please select a version (number) : ";

	//user input
	cin >> selection;

	//verification
	i = 0;
	for (auto& v : Versions) {
		if (i == selection) {
			i = -1;
			selected_version = v;
			break;
		}
		i++;
	}
	if (i != -1) { //no version selected
		cout << "(UIselectVersion) Incorrect selected version. Exitting the process...";
		exit(1);
	}

	return selected_version;
}

Version UserInterfaceCmd::UIVersionMenu() {
	int i = 0;
	Version selected_version;

	cout << endl << "** VERSION MENU**" << endl;
	cout << "Available versions :" << endl;

	//display versions
	i = 0;
	for (auto& v : Versions) {
		cout << i++ << " : " << v << endl;
	}

	//Version selection + callback
	selected_version = UIselectVersion();

	return selected_version;
}


/// GAME SETTINGS///
//PLAYERS NAME
string UserInterfaceCmd::UIselectPlayerName(int i, int& isIA) {
	string player;

	cout << endl << "Player " << i << " : " << endl;
	cout << "Types of player : " << endl;
	cout << "0 : Human" << endl;
	cout << "1 : Random IA :" << endl;
	cout << "Please choose a type of player (number) : ";
	cin >> isIA;

	cout << "Name " << i << " : ";
	cin >> player;

	//cout << "(UIselectPlayerName) - Player name : " << player;

	return player;
}

void UserInterfaceCmd::UIPlayerMenu(string players_name[], int& isIA1, int& isIA2) {

	cout << endl << "** PLAYER MENU **" << endl;

	players_name[0] = UIselectPlayerName(1, isIA1);
	players_name[1] = UIselectPlayerName(2, isIA2);

	//cout << "(UIPlayerMenu) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIPlayerMenu) - players_name[1] : " << players_name[1] << endl;
}


/// GAME SETTINGS ///
unsigned int UserInterfaceCmd::UISelectRounds() { //to delete ?
	unsigned int i;

	cout << "Please select the desired number of rounds : ";
	cin >> i;

	return i;
}

void UserInterfaceCmd::UIGameInit() {
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	string players_name[2];
	int AI_player1 = 0;
	int AI_player2 = 0;

	Version selected_version = UIVersionMenu();
	UIPlayerMenu(players_name, AI_player1, AI_player2);

	//cout << "(UIGameInit) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIGameInit) - players_name[1] : " << players_name[1] << endl;

	//cout << "(UIGameInit) - isIA1 = " << isIA1;
	//cout << "(UIGameInit) - isIA2 = " << isIA2;

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	unsigned int rounds_nb = UISelectRounds();

	system("pause");

	//initializing controller :
	Supervisor::getInstance().eventStartGame(selected_version, players_name[0], players_name[1], AI_player1, AI_player2, rounds_nb, 4);
	//Supervisor::getInstance().setController(selected_version, players_name[0], players_name[1], isIA1, isIA2);

	//cout << "(UIGameInit) - Controller : Version : " << Supervisor::getInstance().getController()->getVersion() << endl;
	//cout << "(UIGameInit) - Controller : Player 1 name : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	//cout << "(UIGameInit) - Controller : Player 2 name :" << Supervisor::getInstance().getController()->getPlayer2().getName() << endl;
}

void UserInterfaceCmd::UITurnLauncher(Player& curr_player) {
	//play a card
	//draw from deck (deck method)

}

void UserInterfaceCmd::UIRoundLauncher() {
	// A la place : 
	// declenche des evenements dans le controleur
	// utiliser des getters pour recuperer des valeurs (=> cartes selectionnables etc...)
	// rappeler des evenements
	size_t turns_count = 0;
	do {
		turns_count++;
		cout << endl << "TURN " << turns_count << endl;
		//Supervisor::getInstance().getController()->playTurn(Side::s1);
		//Supervisor::getInstance().getController()->playTurn(Side::s2);
		cout << endl;
		//exitting the loop for the tests
		if (turns_count == 3) break;
	} while (Supervisor::getInstance().getController()->getBoard().evaluateGameWinner() == Side::none);
}

unsigned int UserInterfaceCmd::UISelectCard() {
	int card_nb = 0;
	cout << endl << "Select a card to play from your hand (number) : ";

	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA == nullptr) { //not IA
		card_nb = userSelectCard();
	}
	else { //is IA
		card_nb = playerIA->selectCard();
	}

	cout << endl << "Selected card (number) : " << card_nb;
	return card_nb;
}

void UserInterfaceCmd::UIPlayCard() {
	cout << "Play a card" << endl;

	//display cards in player's hand
	cout << "Your hand : " << endl; //CRASHES BC HAND NOT INITIALIZED
	if (Supervisor::getInstance().getController()->getCurSide() == Side::s1) { //curent player is p1
		for (size_t i = 0; i < Supervisor::getInstance().getController()->getPlayer1().getHand()->getSize(); i++) {
			cout << i << " : " << Supervisor::getInstance().getController()->getPlayer1().getHand()->getCard(i)->getName();
		}
	}
	else { //current player is P2
		for (size_t i = 0; i < Supervisor::getInstance().getController()->getPlayer2().getHand()->getSize(); i++) {
			cout << i << " : " << Supervisor::getInstance().getController()->getPlayer2().getHand()->getCard(i)->getName();
		}
	}
	int card_hand_nb = UISelectCard();

	Supervisor::getInstance().getController()->eventCardPicked(card_hand_nb);
}

void UserInterfaceCmd::UIGameView2() {
	cout << "***  ROUND " << Supervisor::getInstance().getController()->getTotalRounds() - Supervisor::getInstance().getController()->getRemainingRounds() + 1 << " (on " << Supervisor::getInstance().getController()->getTotalRounds() << ") ***" << endl;
	cout << "* Turn to player ";
	if (Supervisor::getInstance().getController()->getCurSide() == Side::s1) { //curent player is p1
		cout << 1 << " : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	}
	else { //current player is P2
		cout << 2 << " : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	}

	UIPlayCard();


		/*while (Supervisor::getInstance().getController()->getRemainingRounds() != 0) {
			cout << "* ROUND " << Supervisor::getInstance().getController()->getTotalRounds() - Supervisor::getInstance().getController()->getRemainingRounds() + 1 << " (on " << Supervisor::getInstance().getController()->getTotalRounds() << ") *" << endl;
			//init the elements
				// new hand (player), new deck(s),


			//round
			UIRoundLauncher();

			//decrementing remaining rounds
			unsigned int r = Supervisor::getInstance().getController()->getRemainingRounds();
			Supervisor::getInstance().getController()->setRemainingRounds(r -1);
		}

		//print the winner :
		Player* winner = Supervisor::getInstance().getController()->getWinner();
		if (winner != nullptr) {
			cout << endl << "The winner is : " << winner->getName() << "! Congratulations!" << endl;
		} else {
			cout << endl << "It's a draw! Perhaps could you decide the winner by playing again..." << endl;
		}*/
}

unsigned int UserInterfaceCmd::UISelectStone() {
	unsigned int stone_nb = 0;
	cout << "Select a stone (number) : ";
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA == nullptr) { //not IA
		stone_nb = userSelectCard();
	} else { //is IA
		stone_nb = playerIA->selectCard();
	}

	cout << "Selected stone (number) : " << stone_nb;
	return stone_nb;
}

void UserInterfaceCmd::UIGameView3() {
	cout << "STONES :" << endl;

	//display stones + their combinations
	for (size_t i = 0; i < Supervisor::getInstance().getController()->getBoard().getStoneNb(); i++) {
		cout << "Stone" << i << " : " << endl;
		cout << "Combination Player 1 : " << endl;
		for (size_t k = 0; k < Supervisor::getInstance().getController()->getBoard().getStone(i).getSizeP1(); k++) { //print combination player 1
			cout << k << " : " << Supervisor::getInstance().getController()->getBoard().getStone(i).getCombinationP1()[k]->getName() << endl;
		}
		cout << "Combination Player 2 : " << endl;
		for (size_t k = 0; k < Supervisor::getInstance().getController()->getBoard().getStone(i).getSizeP2(); k++) { //print combination player 1
			cout << k << " : " << Supervisor::getInstance().getController()->getBoard().getStone(i).getCombinationP2()[k]->getName() << endl;
		}
		cout << endl; //saut de ligne
	}

	unsigned int stone_choice = UISelectStone(); //COMMENT JE PASSE LA BORNE EN QUESTION ? 
	Supervisor::getInstance().getController()->eventStonePicked(); //COMMENT JE PASSE LA BORNE EN QUESTION ?????
}

void UserInterfaceCmd::UIGameView4() {
	system("pause");
	Supervisor::getInstance().getController()->qtDisplayPlayerTurn();
}

/// GAME LAUNCHER ///
void UserInterfaceCmd::launchUserInterface() {
	//PARAMATERS ~= Vue QT 1
	UIGameInit();

	//Supervisor::getInstance().setController(selected_version, players_name[0], players_name[1], isIA1, isIA2);

	cout << "(launchUserInterfaceCmd) - Controller : Version : " << Supervisor::getInstance().getController()->getVersion() << endl;
	cout << "(launchUserInterfaceCmd) - Controller : Player 1 name : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	cout << "(launchUserInterfaceCmd) - Controller : Player 2 name :" << Supervisor::getInstance().getController()->getPlayer2().getName() << endl;

	//PLAY THE GAME
	//system("CLS");
	cout << endl << endl << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** LET'S PLAY! **" << endl;

	getState() = 1; 
	while (getState()) {
		switch (getState()) {
		case 0 :
			cout << "exit";
			break;
		case 1: //~= View QT 2 (cards)
			cout << "CASE 1" << endl;
			UIGameView2();
			getState() = 2;
			break;
		case 2: //View QT 3 (stones)
			cout << "CASE 2" << endl;
			UIGameView3();
			getState() = 3;
			break;
		case 3: //~= View QT 4 (click to continue)
			//
			cout << "CASE 3" << endl;
			UIGameView4();
			getState() = 4;
			break;
		case 4:
			// ~= View QT 2 (draw a card from a deck)
			cout << "CASE 4" << endl;

			break;
		case 5:
			//
			cout << "CASE 6" << endl;
			break;
		case 6:
			//
			cout << "CASE 7" << endl;
			break;
		default:
			throw ShottenTottenException("launchUserInterfaceCmd : non valid state");
		}
	}
}