#include "..\head\Controller.h"

Controller::Handler Controller::handler = Controller::Handler();


const Controller& Controller::getInstance() {
	if (handler.instance == nullptr) handler.instance = new Controller;
	return *handler.instance;
}

void Controller::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;

}
