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
	void setController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2);
	Controller* getController() { return controller; }
};
