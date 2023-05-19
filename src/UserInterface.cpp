#include "../head/UserInterface.h"


void functionCallback(Version v) { //callback
	cout << endl << "(callback function) Selection : " << v << endl;
}

void UIselectVersion(void (*callback) (Version v)) { //user select version
	Version selected_version;
	int selection = 0;
	int i = 0;

	cout << endl << "(UIselectVersion) Please select a version (number) :" << endl;

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
}

void UIinterfaceMenu() {
	int i = 0;

	cout << "***  SCHOTTEN TOTTEN  ***" << endl << endl;
	cout << "** VERSION MENU **" << endl;
	cout << "Available versions :" << endl;

	//display versions
	i = 0;
	for (auto& v : Versions) {
		cout << i++ << " : " << v << endl;
	}
	
	//Version selection + callback
	UIselectVersion(functionCallback);
}