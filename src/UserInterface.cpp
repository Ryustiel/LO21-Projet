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

int UserInterfaceCmd::uiSelectStoneForClaim() {
	int stone_nb = 0;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA != nullptr) {
		stone_nb = playerIA->selectUnclaimedStone();
	}
	else {
		stone_nb = userSelectStoneForClaim();
	}
	if (stone_nb >= 0) { //correct input
		return stone_nb;
	}
	return -1;
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

unsigned int UserInterfaceCmd::uiSelectCard(Stone * stone, Side side) {
	int card_nb = 0;
	cout << endl << "Select a card from this stone (type in a number) : ";
	size_t nstones; // number on cards on a stone

	// fetching the number of cards placed on the one side
	if (side == Side::s1) {
		nstones = stone->getSizeP1();
	}
	else {
		nstones = stone->getSizeP2();
	}

	// fetching a card number from either the interface or the AI methods
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA == nullptr) {
		card_nb = playerIA->selectCard(nstones);
	}
	else {
		card_nb = UserInterfaceCmd::userSelectCard(nstones, "This is not a number, or there is no card bearing this number.");
	}
	return card_nb;
}

void UserInterfaceCmd::uiPlayCard() {
	cout << "Play a card" << endl;

	//display cards in player's hand
	cout << "Your hand : " << endl;
	Hand& curr_player_hand = Supervisor::getInstance().getController()->getCurrentPlayerHand();
	/*
	for (size_t i = 0; i < cur_player_hand.getSize(); i++) {
		cout << i << " : " << Supervisor::getInstance().getController()->getPlayer1().getHand()->getCard(i)->getName();
	}
	*/
	size_t i = 0;
	for (auto card : curr_player_hand) { std::cout << i++ << " : " << card->getName(); }
	unsigned int card_hand_nb = uiSelectCard();
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
		stone_nb = (playerIA == nullptr) ? userSelectStone() : playerIA->selectStone();

		if (stone_nb < 0 || stone_nb >= c->getBoard().getStoneNb()) {
			cout << endl << "DEBUG in UserInterfaceCmd::uiSelectStone()";
			cout << endl << stone_nb << " STONE NB" << endl << c->getBoard().getStoneNb() << " GET BOARD STONE NB" << endl;
			cout << "This stone number is not valid !" << endl;
			continue;
		}
		else if (!playableStones[stone_nb]) {
			cout << "This Stone is full! Choose an another one!" << endl;
			continue;
		}
		cout << "Selected stone (number): " << stone_nb << endl;
		return stone_nb;
	}
}

unsigned int UserInterfaceCmd::uiSelectStoneCombatMode() {
	unsigned int stone_nb;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	TacticController* c = dynamic_cast <TacticController*>(Supervisor::getInstance().getController());
	if (c == nullptr) throw ShottenTottenException("UserInterfaceCmd::uiSelectStoneCombatMode - controller isn't tactical !");
	bool* playableStonesCM = c->getPlayableCombatModeStones();
	while (true) { //user input until correct
		stone_nb = (playerIA == nullptr) ? userSelectStone() : playerIA->selectStone();

		if (stone_nb < 0 || stone_nb >= c->getBoard().getStoneNb()) {
			cout << "This number isn't valid !" << endl;
			continue;
		}
		else if (!playableStonesCM[stone_nb]) {
			cout << "This Stone already bears a Combat Mode card! Please select another stone." << endl;
			continue;
		}
		cout << "Selected stone (number): " << stone_nb << endl;
		return stone_nb;
	}
}

unsigned int UserInterfaceCmd::uiSelectStoneForCombatMode() { //TO DO
	unsigned int stone_nb;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	TacticController* c = dynamic_cast<TacticController*>(Supervisor::getInstance().getController());
	if (c == nullptr) throw ShottenTottenException("UserInterface::uiSelectStoneForCombatMode error : no TacticController found !");
	bool* playableStones = c->getPlayableStonesCombatMode();
	while (true) { //user input until correct
		cout << "Select a stone (number) : ";

		stone_nb = (playerIA == nullptr) ? userSelectStone() : playerIA->selectStone();

		if (stone_nb < 0 || stone_nb >= c->getBoard().getStoneNb()) {
			cout << "This STONE number isn't valid ! (combat mode)" << endl;
			continue;
		}
		else if (!playableStones[stone_nb]) {
			cout << "This Stone already have a combat mode ! Choose an another one !" << endl;
			continue;
		}
		return stone_nb;
	}
}

Deck* UserInterfaceCmd::uiSelectDeck() {
	cout << "Deck Selection : "<<endl;
	Controller* c = Supervisor::getInstance().getController();
	TacticController* tc = dynamic_cast<TacticController*>(c);
	if (c->getClanDeck().isEmpty()) {
		if (tc && !tc->getTacticDeck().isEmpty()) {
			cout << "Tactical deck is empty ! Drawing the Clan deck instead" << endl;
			return &tc->getTacticDeck();
		}
		else {
			cout << "All decks are empty !" << endl;
			return nullptr;
		}
	}
	else {
		if (tc) {
			if (tc && !tc->getTacticDeck().isEmpty()) {
				int choice = -1;
				while (true) {
					cout << "Select a Deck (0: default, 1: tactic) : ";
					PlayerAIRandom* cur_player = dynamic_cast<PlayerAIRandom*>(Supervisor::getInstance().getController()->getCurrentPlayer());
					if (cur_player) choice = cur_player->selectDeck();
					else cin >> choice;
					if (choice >= 2 || choice < 0) {
						cout << "Invalid choice." << endl;
					}
					else {
						break;
					}
				}
				if (choice) {
					cout << "Tactic Deck selected !" << endl;
					return &tc->getTacticDeck();
				}
			}
			else {
				cout << "Clan deck is empty ! Drawing the Tactical deck instead." << endl;
			}

		}
		else {
			cout << "Legacy Deck Selected !" << endl;
		}
		return &c->getClanDeck();
	}


	switch (c->getVersion()) {
	case Version::tactic:
		int choice;
		if (!tc->getTacticDeck().isEmpty()) {
			while (true) {
				cout << "Select a Deck (0: default, 1: tactic) : ";
				cin >> choice;
				if (choice >= 2 || choice < 0) {
					cout << "Choix invalide" << endl;
				}
				else {
					break;
				}
			}
			if (choice) {
				return &tc->getTacticDeck();
			}
		}
		else {
			cout << "Tactic Deck is empty !"<< endl;
		}

	default:
	case Version::legacy:
		if (c->getClanDeck().isEmpty()) {
			cout << "Clan Deck is empty !" << endl;
			return nullptr;
		}
		return &c->getClanDeck();
	}

}

void UserInterfaceCmd::uiGameView3() { //TO DELETE
	cout << "STONES :" << endl;

	//display stones + their combinations
	for (size_t i = 0; i < Supervisor::getInstance().getController()->getBoard().getStoneNb(); i++) {
		cout << "Stone" << i << " : ";
		Stone& cur_stone = Supervisor::getInstance().getController()->getBoard().getStone(i);
		if (cur_stone.getRevendication() == Side::none) {
			cout << "Unclaimed" << endl;
		}
		else if (cur_stone.getRevendication() == Side::s1) {
			cout << "Claimed by Player 1" << endl;
		}
		else { //claimed by player 2
			cout << "Claimed by Player 1" << endl;
		}
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
	Supervisor::getInstance().getController();
}

void UserInterfaceCmd::uiPrintPlayerHand() {
	Hand& cur_hand = Supervisor::getInstance().getController()->getCurrentPlayerHand();
	cout << endl << Supervisor::getInstance().getController()->getCurrentPlayer()->getName() << "'s hand :" << endl;
	for (size_t i = 0; i < cur_hand.getSize(); i++) {
		cout << i << " : " << cur_hand.getCard(i)->getName() << endl;
	}
}

void UserInterfaceCmd::uiPrintCurrentPlayer() {
	Player* cur_player = Supervisor::getInstance().getController()->getCurrentPlayer();
	cout << endl << "--------------------------------------" << cur_player->getName() << " (current score : " << cur_player->getScore() << " point(s)) - ";
	if (Supervisor::getInstance().getController()->getCurSide() == Side::s1) {
		cout << " player 1 ";
	}
	else {
		cout << " player 2 ";
	}
	cout << "--------------------------------------" << endl;
}

void UserInterfaceCmd::uiPrintGame() {
	Board& cur_board = Supervisor::getInstance().getController()->getBoard();
	cout << endl;
	for (size_t i = 0; i < cur_board.getStoneNb(); i++) { //for each stone
		cout << "Stone " << i << " : ";
		Stone& cur_stone = cur_board.getStone(i);
		if (cur_stone.getRevendication() == Side::none) {
			cout << "Unclaimed" << endl;
		}
		else if (cur_stone.getRevendication() == Side::s1) {
			cout << "Claimed by Player 1" << endl;
		}
		else { //claimed by player 2
			cout << "Claimed by Player 1" << endl;
		}
		if (cur_stone.getCombatMode()) {
			cout << "	Combat mode : " << cur_stone.getCombatMode()->getName() << endl;
		}
		cout << "	Player 1 ( " << Supervisor::getInstance().getController()->getPlayer1().getName() << " ) combination :" << endl;
		for (size_t k = 0; k < cur_stone.getSizeP1(); k++) { //display P1 combination
			cout << "		Card " << k << " : " << cur_stone.getCombinationP1()[k]->getName() << endl;
		}
		cout << "	Player 2 ( " << Supervisor::getInstance().getController()->getPlayer2().getName() << " ) combination :" << endl;
		for (size_t k = 0; k < cur_stone.getSizeP2(); k++) { //display P1 combination
			cout << "		Card " << k << " : " << cur_stone.getCombinationP2()[k]->getName() << endl;
		}
		cout << endl;
	}
}

unsigned int UserInterfaceCmd::uiSelectUnclaimedStone() {
	unsigned int stone_nb = 0;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA != nullptr) {
		stone_nb = playerIA->selectUnclaimedStone();
	}
	else {
		stone_nb = userSelectUnclaimedStone();
	}
	return stone_nb;
}

int UserInterfaceCmd::uiSelectCardOnStone(Side s, unsigned int stone_nb) {
	//displayStone() //TO DO
	if (s == Side::none) throw ShottenTottenException("(UserInterfaceCmd::uiSelectCardOnStone) - side s can't be Side::none");

	//selection on the side given
	int card_nb = -1;
	PlayerAIRandom* playerIA = dynamic_cast<PlayerAIRandom*> (Supervisor::getInstance().getController()->getCurrentPlayer());
	if (playerIA != nullptr) {
		card_nb = playerIA->selectCardOnStone(s, stone_nb);
	}
	else {
		card_nb = userSelectCardOnStone(s, stone_nb);
	}
	return card_nb;
}

/// GAME LAUNCHER ///
void UserInterfaceCmd::launchUserInterface() {
	uiGameInit();
}

void UserInterfaceCmd::quickLaunch(int ia1, int ia2, Version v) {

	string players_name[2] = { "Le Gontil", "Le Michon" };
	int AI_player1 = ia1;
	int AI_player2 = ia2;

	Version selected_version = v;

	//cout << "(uiGameInit) - players_name[0] : " << [0] << endl;
	//cout << "(uiGameInit) - players_name[1] : " << playplayers_nameers_name[1] << endl;

	//cout << "(uiGameInit) - isIA1 = " << isIA1;
	//cout << "(uiGameInit) - isIA2 = " << isIA2;

	unsigned int rounds_nb = 5;

	Supervisor::getInstance().eventStartGame(selected_version, players_name[0], players_name[1], AI_player1, AI_player2, rounds_nb, 4, this);
}

void UserInterfaceCmd::uiPrintDiscard() {
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) {
		throw ShottenTottenException("(UserInterfaceCmd::uiPrintDiscard) - error: no tactic controller !");
	}

	cout << "Discard :" << endl;
	if (tc->getDiscard().getSize() == 0) {
		cout << "	Discard is empty.";
		return;
	}

	for (size_t i = 0; i < tc->getDiscard().getSize(); i++) {
		cout << "	" << i << " : " << tc->getDiscard().getCards()[i]->getName() << endl;
	}

}