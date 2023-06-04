#pragma once
#include "Controller.h"
#include <iostream>
#include <string>

//using design pattern Singleton
class Supervisor {
private :
	Controller* controller = nullptr;
	bool isQT = false;

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
	void setController(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2);
	Controller* getController() { return controller; }
	bool getIsQT() const { return isQT; }
	
	// declenchement initial de l'interface
	void eventFirstStart() {
		std::cout << "\n================================ eventFirstStart";
		// événements lors de l'initialisation du contrôleur
		qtDisplayMainMenu();
	}
    void eventStartGame(Version v, const string& p1name, const string& p2name,unsigned int AI_player1, unsigned int AI_player2, int nrounds, int winthreshold) { // game version, number of rounds
		std::cout << "\n================================ eventStartGame";
		Supervisor::getInstance().setController(v, p1name, p2name, AI_player1, AI_player2);
		Supervisor::getInstance().getController()->runGame(nrounds, winthreshold);
	}
	void qtDisplayMainMenu() {
		std::cout << "\n================================ qtDisplayMainMenu";
		std::cout << "\nQT affiche le menu principal...";
	}

	void quitGame() {
		std::cout << "\n================================ quitGame";
		qtDisplayMainMenu();
	}

	void quitApp() {
		std::cout << "\n================================ quitApp";
		std::cout << "\nquitte l'application, libere la memoire...";
	}
};
