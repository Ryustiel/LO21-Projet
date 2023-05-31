#include "../head/UserInterface.h"

///INTERFACE SINGLETON METHODS///
UserInterface::Handler UserInterface::handler = UserInterface::Handler();

UserInterface* UserInterface::getInstance() {
	if (UserInterface::handler.instance == nullptr) throw ShottenTottenException("ui getIntsance : doesn't exist!");
	return UserInterface::handler.instance;
}

void UserInterface::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}

void UserInterfaceCmd::setInstance() {
	if (handler.instance == nullptr) handler.instance = new UserInterfaceCmd();
}


/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UserInterfaceCmd::uiSelectVersion() { //user select version
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
		cout << "(uiSelectVersion) Incorrect selected version. Exitting the process...";
		exit(1);
	}

	return selected_version;
}

Version UserInterfaceCmd::uiVersionMenu() {
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
	selected_version = uiSelectVersion();

	return selected_version;
}


/// GAME SETTINGS///
//PLAYERS NAME
string UserInterfaceCmd::uiSelectPlayerName(int i, int& isIA) {
	string player;

	cout << endl << "Player " << i << " : " << endl;
	cout << "Types of player : " << endl;
	cout << "0 : Human" << endl;
	cout << "1 : Random IA :" << endl;
	cout << "Please choose a type of player (number) : ";
	cin >> isIA;

	cout << "Name " << i << " : ";
	cin >> player;

	//cout << "(uiSelectPlayerName) - Player name : " << player;

	return player;
}

void UserInterfaceCmd::uiPlayerMenu(string players_name[], int& isIA1, int& isIA2) {

	cout << endl << "** PLAYER MENU **" << endl;

	players_name[0] = uiSelectPlayerName(1, isIA1);
	players_name[1] = uiSelectPlayerName(2, isIA2);

	//cout << "(uiPlayerMenu) - players_name[0] : " << players_name[0] << endl;
	//cout << "(uiPlayerMenu) - players_name[1] : " << players_name[1] << endl;
}


/// GAME SETTINGS ///
unsigned int UserInterfaceCmd::uiSelectRounds() { //to delete ?
	unsigned int i;

	cout << "Please select the desired number of rounds : ";
	cin >> i;

	return i;
}

void UserInterfaceCmd::uiGameInit() {
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	string players_name[2];
	int AI_player1 = 0;
	int AI_player2 = 0;

	Version selected_version = uiVersionMenu();
	uiPlayerMenu(players_name, AI_player1, AI_player2);

	//cout << "(uiGameInit) - players_name[0] : " << [0] << endl;
	//cout << "(uiGameInit) - players_name[1] : " << playplayers_nameers_name[1] << endl;

	//cout << "(uiGameInit) - isIA1 = " << isIA1;
	//cout << "(uiGameInit) - isIA2 = " << isIA2;

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	unsigned int rounds_nb = uiSelectRounds();

	system("pause");

	//initializing controller :
	Supervisor::getInstance().eventStartGame(selected_version, players_name[0], players_name[1], AI_player1, AI_player2, rounds_nb, 4, this);
	//Supervisor::getInstance().setController(selected_version, players_name[0], players_name[1], isIA1, isIA2);

	//cout << "(uiGameInit) - Controller : Version : " << Supervisor::getInstance().getController()->getVersion() << endl;
	//cout << "(uiGameInit) - Controller : Player 1 name : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	//cout << "(uiGameInit) - Controller : Player 2 name :" << Supervisor::getInstance().getController()->getPlayer2().getName() << endl;
}

void UserInterfaceCmd::uiTurnLauncher(Player& curr_player) {
	//play a card
	//draw from deck (deck method)

}

void UserInterfaceCmd::uiRoundLauncher() {
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

unsigned int UserInterfaceCmd::uiSelectCard() {
	int card_nb = 0;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA == nullptr) { //not IA
		card_nb = userSelectCard();
	}
	else { //is IA
		card_nb = playerIA->selectCard();
	}

	cout << "Selected card (number) : " << card_nb << endl;
	return card_nb;
}

int UserInterfaceCmd::uiSelectStoneForClaim() {
	int stone_nb = 0;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA != nullptr) {
		stone_nb = playerIA->selectStoneForClaim();
	}
	else {
		stone_nb = userSelectStoneForClaim();
	}
	if (stone_nb >= 0) { //correct input
		return stone_nb;
	}
	return -1;
}

void UserInterfaceCmd::uiPlayCard() {
	cout << "Play a card" << endl;

	//display cards in player's hand
	cout << "Your hand : " << endl;
	Hand& cur_player_hand = Supervisor::getInstance().getController()->getCurrentPlayerHand();
	for (size_t i = 0; i < cur_player_hand.getSize(); i++) {
		cout << i << " : " << Supervisor::getInstance().getController()->getPlayer1().getHand()->getCard(i)->getName();

	}
	int card_hand_nb = uiSelectCard();
	Supervisor::getInstance().getController()->eventCardPicked(card_hand_nb);
}

void UserInterfaceCmd::uiGameView2() {
	cout << "***  ROUND " << Supervisor::getInstance().getController()->getTotalRounds() - Supervisor::getInstance().getController()->getRemainingRounds() + 1 << " (on " << Supervisor::getInstance().getController()->getTotalRounds() << ") ***" << endl;
	cout << "* Turn to player ";
	if (Supervisor::getInstance().getController()->getCurSide() == Side::s1) { //curent player is p1
		cout << 1 << " : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	}
	else { //current player is P2
		cout << 2 << " : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	}

	uiPlayCard();


		/*while (Supervisor::getInstance().getController()->getRemainingRounds() != 0) {
			cout << "* ROUND " << Supervisor::getInstance().getController()->getTotalRounds() - Supervisor::getInstance().getController()->getRemainingRounds() + 1 << " (on " << Supervisor::getInstance().getController()->getTotalRounds() << ") *" << endl;
			//init the elements
				// new hand (player), new deck(s),


			//round
			uiRoundLauncher();

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

//A COMPLETER !
unsigned int UserInterfaceCmd::uiSelectStone() {
	unsigned int stone_nb;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	Controller* c = Supervisor::getInstance().getController();
	bool* playableStones = c->getPlayableStones();
	while (true) { //user input until correct
		stone_nb = (playerIA == nullptr) ? userSelectStone() : playerIA->selectCard();
		
		if (stone_nb < 0 || stone_nb >= c->getBoard().getStoneNb()) {
			cout << "This number isn't valid !" << endl;
			continue;
		}
		else if (!playableStones[stone_nb]) {
			cout << "This Stone is full ! Choose an another one !" << endl;
			continue;
		}
		cout << "Selected stone (number) : " << stone_nb << endl;
		return stone_nb;
	} 
}

unsigned int UserInterfaceCmd::uiSelectStoneForCombatMode() {
	unsigned int stone_nb;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	TacticController* c = dynamic_cast<TacticController*>(Supervisor::getInstance().getController());
	if (c == nullptr) throw ShottenTottenException("UserInterface::uiSelectStoneForCombatMode error : no TacticController found !");
	bool* playableStones = c->getPlayableStonesCombatMode();
	while (true) { //user input until correct
		cout << "Select a stone (number) : ";

		stone_nb = (playerIA == nullptr) ? userSelectStone() : playerIA->selectCard();

		if (stone_nb < 0 || stone_nb >= c->getBoard().getStoneNb()) {
			cout << "This number isn't valid !" << endl;
			continue;
		}
		else if (!playableStones[stone_nb]) {
			cout << "This Stone already have a combat mode ! Choose an another one !" << endl;
			continue;
		}
		return stone_nb;
	}
}

Deck& UserInterfaceCmd::uiSelectDeck() {
	Controller* c = Supervisor::getInstance().getController();
	switch (c->getVersion()) {
	case Version::tactic:
		int choice;
		while (true){
			cout << "Select a Deck (0: default, 1: tactic) : ";
			cin >> choice;
			if (choice >= 2 || choice < 0) {
				cout << "Choix invalide" << endl;
			}
			else {
				break;
			}
		}
		if (!choice) {
			TacticController* tc = dynamic_cast<TacticController*>(c);
			return tc->getTacticDeck();
		}
		
	default:
	case Version::legacy:
			return c->getClanDeck();
	}

}

void UserInterfaceCmd::uiGameView3() {
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

	unsigned int stone_choice = uiSelectStone(); //COMMENT JE PASSE LA BORNE EN QUESTION ?
	Supervisor::getInstance().getController()->eventStonePicked(); //COMMENT JE PASSE LA BORNE EN QUESTION ?????
}

void UserInterfaceCmd::uiGameView4() {
	system("pause");
	Supervisor::getInstance().getController()->qtDisplayPlayerTurn();
}

void UserInterfaceCmd::uiPrintPlayerHand() {
	Hand& cur_hand = Supervisor::getInstance().getController()->getCurrentPlayerHand();
	cout << endl << Supervisor::getInstance().getController()->getCurrentPlayer()->getName() << "'s hand :" << endl;
	for (size_t i = 0; i < cur_hand.getSize(); i++) {
		cout << i << " : " << cur_hand.getCard(i)->getName() << endl;
	}
}

void UserInterfaceCmd::uiPrintGame() {
	Board& cur_board = Supervisor::getInstance().getController()->getBoard();
	cout << endl;
	for (size_t i = 0; i < cur_board.getStoneNb(); i++) { //for each stone
		cout << "Stone " << i << endl;
		Stone& cur_stone = cur_board.getStone(i);
		cout << "	Player 1 ( " << Supervisor::getInstance().getController()->getPlayer1().getName() << " ) combination :" << endl;
		for (size_t k = 0; k < cur_stone.getSizeP1(); k++) { //display P1 combination
			cout << "		" << k << " : " << cur_stone.getCombinationP1()[k]->getName() << endl;
		}
		cout << "	Player 2 ( " << Supervisor::getInstance().getController()->getPlayer2().getName() << " ) combination :" << endl;
		for (size_t k = 0; k < cur_stone.getSizeP2(); k++) { //display P1 combination
			cout << "		" << k << " : " << cur_stone.getCombinationP2()[k]->getName() << endl;
		}
		cout << endl;
	}
}

/// GAME LAUNCHER ///
void UserInterfaceCmd::launchUserInterface() {
	//PARAMATERS ~= Vue QT 1
	uiGameInit();
	/*
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
			uiGameView2();
			getState() = 2;
			break;
		case 2: //View QT 3 (stones)
			cout << "CASE 2" << endl;
			uiGameView3();
			getState() = 3;
			break;
		case 3: //~= View QT 4 (click to continue)
			//
			cout << "CASE 3" << endl;
			uiGameView4();
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
	*/
}
