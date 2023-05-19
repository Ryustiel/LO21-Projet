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

//APPLICATION LAUNCHER
void UserInterface::launchUserInterface() {
	switch (state) {
	case 0 :
		//BEGIN INTERFACE IF NEEDED
		break;
	case 1 :
		//SELECT : VERSION
		Version selected_version = UIinterfaceVersionMenu();
		break;
	case 2 :
		//SELECT : GAME SETTINGS
		///Nombre de tours
		break;
	case 3 :
		//SELECT : TURN : PLAYER ACTION
		break;
	case 4 :
		//SELECT : TURN : ACTION : CARD IN HAND
		break;
	case 5 :
		//SELECT : TURN : ACTION : SELECT A STONE
		break;
	case 6 :
		//SELECT : CONTINUE BUTTON
		break;
	default :
		break;
	}
}

/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UserInterface::UIselectVersion(void (*callback) (Version v)) { //user select version
	Version selected_version;
	int selection = 0;
	int i = 0;

	cout << endl << "(UIselectVersion) Please select a version (number) : ";

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

	//callback
	callback(selected_version);

	return selected_version;
}

Version UserInterface::UIinterfaceVersionMenu() {
	int i = 0;
	Version selected_version;

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** VERSION MENU **" << endl;
	cout << "Available versions :" << endl;

	//display versions
	i = 0;
	for (auto& v : Versions) {
		cout << i++ << " : " << v << endl;
	}
	
	//Version selection + callback
	selected_version = UIselectVersion(functionCallback);

	state += 1;
	system("pause");

	return selected_version;
}


/// GAME SETTINGS///
//PLAYERS NAME
string UserInterface::UIselectPlayerName(int i, void (*callback) (string s)) {
	string player;

	cout << "Player " << i << " : ";
	cin >> player;
	//cout << "(UIselectPlayerName) - Player name : " << player;

	callback(player);

	return player;
}

void UserInterface::UIinterfacePlayerMenu(string players_name[]) {

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	players_name[0] = UIselectPlayerName(1, functionCallback);
	players_name[1] = UIselectPlayerName(2, functionCallback);

	//cout << "(UIinterfacePlayerMenu) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIinterfacePlayerMenu) - players_name[1] : " << players_name[1] << endl;

	system("pause");
}


