#include <iostream>
#include <string>
//#include "src/Controller.cpp"
//#include "src/Player.cpp"
#include "head/Game.h"
#include "head/Supervisor.h"
#include "head/Card.h"
#include "head/Board.h"
#include "head/Version.h"

int main() {
	int selection;
	Version selected_version;
	string p1_name;
	string p2_name;
	int i = 0;
	
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "Creating a supervisor..." << endl;

	Supervisor::getInstance();

	cout << "Supervisor created." << endl;

	system("pause");
	system("CLS");

	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** VERSION MENU **" << endl;
	cout << "Available versions :" << endl;

	i = 0;
	for (auto& v : Versions) {
		cout << i++ << " : " << v << endl;
	}
	cout << endl << "Please select a version (number) :" << endl;

	cin >> selection;

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
		cout << "Incorrect selected version. Exitting the process...";
		exit(1);
	 }

	cout << "Selected version : " << selected_version << endl;

	system("pause");
	system("CLS");

	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** SETTINGS MENU **" << endl;
	cout << "Player 1 name :" << endl;
	cin >> p1_name;
	cout << "Player 2 name :" << endl;
	cin >> p2_name;

	cout << "Creating controller..." << endl;
	Supervisor::getInstance().setController(selected_version, p1_name, p2_name, 1, 2);
	cout << Supervisor::getInstance().getController()->getPlayer1()->getName() << endl;
	cout << Supervisor::getInstance().getController()->getPlayer2()->getName() << endl;
	cout << "end";
}