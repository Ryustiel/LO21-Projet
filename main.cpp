#include <iostream>
#include <string>
#include "src/Controller.cpp"
#include "src/Board.cpp"
#include "src/Player.cpp"
#include "head/Game.h"

int main() {
  std::cout << "Hello World!\n";
  std::cout << "Hello there!\n";
  std::cout << "Anoukhan Skywalker\n";
  std::cout << "coucou";

  Controller* controller = Controller::getController();
  
  controller->setPlayer1( new Player );
  controller->setPlayer2( new Player );
  controller->newGame(3);

  std::cout << "\n\ndone";
}

// salut salut