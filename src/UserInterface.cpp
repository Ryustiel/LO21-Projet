#include "../head/UserInterface.h"

//SURCHARGE CALLBACK FUNCTION
void functionCallback(const Version v) { //callback
	cout << endl << "(callback function) Selection : " << v << endl;
}

void functionCallback(const string s) {
	cout << endl << "(callback function) Selection : " << s << endl;
}


/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UIselectVersion(void (*callback) (Version v)) { //user select version
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

Version UIinterfaceVersionMenu() {
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
	system("pause");

	return selected_version;
}


/// GAME SETTINGS///
//PLAYERS NAME
string UIselectPlayerName(int i, void (*callback) (string s)) {
	string player;

	cout << "Player " << i << " : ";
	cin >> player;
	//cout << "(UIselectPlayerName) - Player name : " << player;

	callback(player);

	return player;
}

void UIinterfacePlayerMenu(string players_name[]) {

	system("CLS");
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** GAME SETTINGS **" << endl;
	cout << endl;

	players_name[0] = UIselectPlayerName(1, functionCallback);
	players_name[1] =  UIselectPlayerName(2, functionCallback);

	//cout << "(UIinterfacePlayerMenu) - players_name[0] : " << players_name[0] << endl;
	//cout << "(UIinterfacePlayerMenu) - players_name[1] : " << players_name[1] << endl;

	system("pause");
}


