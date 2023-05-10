#include "..\head\Supervisor.h"

Supervisor::Handler Supervisor::handler = Supervisor::Handler();

Supervisor& Supervisor::getInstance() {
	if (handler.instance == nullptr) handler.instance = new Supervisor();
	return *handler.instance;
}

void Supervisor::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}