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

	Supervisor::getInstance().setController(Version::legacy, "p1_name", "p2_name", 1, 2); //heap buffer error
	cout << Supervisor::getInstance().getController()->getPlayer1()->getName();

	/*char c;
	int selection;
	Version selected_version;
	string p1_name;
	string p2_name;

	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "Creating a supervisor..." << endl;

	Supervisor::getInstance();

	cout << "Supervisor created." << endl;
	cout << "typer 'o' to continue >";
	
	cin >> c;

	cout << system("CLS") << endl;

	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** VERSION MENU **" << endl;
	cout << "Available versions :" << endl;
	for (auto& v : Versions) {
		cout << v << endl;
	}
	cout << endl << "Please select a version :" << endl;

	cin >> selection;

	int i = 0;
	for (auto& v : Versions) {
		if (i == selection) {
			i = -1;
			selected_version = v;
			break;
		}
		i++;
	}
	if (i != -1) { //no version selected
		exit(1);
	 }

	cout << "Selected version : " << selected_version << endl;

	cout << "typer 'o' to continue >";
	cin >> c;

	cout << system("CLS") << endl;
	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** SETTINGS MENU **" << endl;
	cout << "Player 1 name :" << endl;
	cin >> p1_name;
	cout << "Player 2 name :" << endl;
	cin >> p2_name;

	cout << "Creating controller..." << endl;
	Supervisor::getInstance().setController(selected_version, p1_name, p2_name, 1, 2);
	cout << "end";
	*/
}