#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"

//SURCHARGE CALLBACK FUNCTION
void functionCallback(const Version v);
void functionCallback(const string s);

/// SUPERVISOR SETTINGS ///
//SELECT VERSION
Version UIselectVersion(void (*callback) (Version v));
Version UIinterfaceVersionMenu();

/// GAME SETTINGS///
//INTERFACE
string UIselectPlayerName(int i, void (*callback) (const string s));
void UIinterfacePlayerMenu(string players_name[]);