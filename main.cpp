#include <iostream>
#include <string>
#include "src/Board.cpp"
#include "src/Controller.cpp"
#include "src/Player.cpp"
#include "head/Game.h"
#include "src/Version.cpp"
#include "src/Supervisor.cpp"

int main() {
  std::cout << "Hello World!\n";
  std::cout << "Hello there!\n";
  std::cout << "Anoukhan Skywalker\n";
  std::cout << "coucou";

  Supervisor supervisor = Supervisor::getInstance();
  supervisor.setController(current_version, "Mike", "Pencie", 1, 2);
  Controller* controller = supervisor.getController();
  controller->newGame(3);

  std::cout << "\n\ndone";
}

// salut salut