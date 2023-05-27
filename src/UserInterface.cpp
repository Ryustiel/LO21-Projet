#include "../head/UserInterface.h"

//SURCHARGE CALLBACK FUNCTION
void functionCallback(const Version v) { //callback
	cout << endl << "(callback function) Selection : " << v << endl;
}

void functionCallback(const string s) {
	cout << endl << "(callback function) Selection : " << s << endl;
}

///INTERFACE SINGLETON METHODS///
UserInterface::Handler UserInterface::handler = UserInterface::Handler();

UserInterface& UserInterface::getInstance() {
	if (handler.instance == nullptr) handler.instance = new UserInterface();
	return *handler.instance;
}

void UserInterface::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}



/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UserInterface::UIselectVersion() { //user select version
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

Version UserInterface::UIVersionMenu() {
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
string UserInterface::UIselectPlayerName(int i, int& isIA) {
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

void UserInterface::UIPlayerMenu(string players_name[], int& isIA1, int& isIA2) {

	cout << endl << "** PLAYER MENU **" << endl;

	players_name[0] = UIselectPlayerName(1, isIA1);
	players_name[1] = UIselectPlayerName(2, isIA2);

	//cout << "(UIPlayerMenu) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIPlayerMenu) - players_name[1] : " << players_name[1] << endl;
}


/// GAME SETTINGS ///
void UserInterface::UIGameInit() {
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	string players_name[2];
	int isIA1 = 0;
	int isIA2 = 0;

	Version selected_version = UIVersionMenu();
	UIPlayerMenu(players_name, isIA1, isIA2);

	//cout << "(UIGameInit) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIGameInit) - players_name[1] : " << players_name[1] << endl;

	//cout << "(UIGameInit) - isIA1 = " << isIA1;
	//cout << "(UIGameInit) - isIA2 = " << isIA2;

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	unsigned int rounds_nb = UISelectRounds();

	//initializing controller :
	Supervisor::getInstance().eventStartGame(selected_version, players_name[0], players_name[1], rounds_nb, 2);
	//Supervisor::getInstance().setController(selected_version, players_name[0], players_name[1], isIA1, isIA2);

	//cout << "(UIGameInit) - Controller : Version : " << Supervisor::getInstance().getController()->getVersion() << endl;
	//cout << "(UIGameInit) - Controller : Player 1 name : " << Supervisor::getInstance().getController()->getPlayer1().getName() << endl;
	//cout << "(UIGameInit) - Controller : Player 2 name :" << Supervisor::getInstance().getController()->getPlayer2().getName() << endl;

	system("pause");
}

unsigned int UserInterface::UISelectRounds() {
	unsigned int i;

	cout << "Please select the desired number of rounds :";
	cin >> i;

	return i;
}

void UserInterface::UITurnLauncher(Player& curr_player) {
	//play a card
	//draw from deck (deck method)

}

void UserInterface::UIRoundLauncher() {
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

void UserInterface::UISelectCard() {
	std::cout << "\nenvoie à qt la liste des cartes jouables pour ce joueur";
	std::cout << "\ndemande a QT d'afficher le menu pour selectionner des cartes, piocher, ou revandiquer une borne";
	Supervisor::getInstance().getController()->eventCardPicked("test");
}

void UserInterface::UIGameLauncher() {
	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** LET'S PLAY! **" << endl << endl;
	cout << endl;

	while (Supervisor::getInstance().getController()->getRemainingRounds() != 0) {
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
	}
}

/// GAME LAUNCHER ///
void UserInterface::launchUserInterface() {
	//PARAMATERS
	UIGameInit(); //done

	//PLAY THE GAME
	UIGameLauncher();

}