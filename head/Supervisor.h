#pragma once
#include "Controller.h"
#include <iostream>
#include <string>

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
	
	// declenchement initial de l'interface
	void qtStart() {
		std::cout << "\n================================ qtStart";
		std::cout << "\ninitialisation de QT, creer un objet QT et le stocke dans le Superviseur";
		std::cout << "\nstocke une reference a QT dans le Superviseur";
		std::cout << "\nlance qtDisplayMainMenu()";
	}
	void eventRunVersion(string v) { 
		std::cout << "\n================================ runVersion";
		std::cout << "\nnom de la version : " << v;
		std::cout << "\ngenere un controleur avec setController()";
		std::cout << "\nlance getController()->qtDisplayVersionMenu()";
	}
	void qtDisplayMainMenu() {
		std::cout << "\n================================ qtDisplayMainMenu";
		std::cout << "\nenregistre un listener : callback = runVersion()";
		std::cout << "\nQT affiche le menu principal...";
	}

	void quitGame() {
		std::cout << "\n================================ quitGame";
		std::cout << "\nenvoie un signal a QT pour revenir a l'ecran principal";
		std::cout << "\nplus simplement, declenche qtDisplayMainMenu()";
	}

	void quitApp() {
		std::cout << "\n================================ quitApp";
		std::cout << "\nquitte l'application, libere la memoire...";
	}
};
