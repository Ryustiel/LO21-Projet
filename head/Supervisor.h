#pragma once
#include "Controller.h"

//using design pattern Singleton
class Supervisor {
private :
	Controller* controller = nullptr;

	Supervisor() {}
	~Supervisor() {}
	struct Handler {
		Supervisor* instance = nullptr;
		~Handler() { delete instance; }
	};
	static Handler handler;
public :
	static Supervisor& getInstance();
	static void freeInstance();
};
