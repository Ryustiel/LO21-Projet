#include "..\head\Controller.h"

Controller* Controller::instance = nullptr;

Controller& Controller::getInstance() {
	if (instance == nullptr) {
		instance = new Controller();
	}
	return *instance;
}

void Controller::freeInstance() {
	delete instance;
	instance = nullptr;
}
