#pragma once
#include "Game.h"
#include "Supervisor.h"
#include "Card.h"
#include "Board.h"
#include "Version.h"

void functionCallback(Version v);
void UIselectVersion(void (*UIinterfaceMenu) (Version v));
void UIinterfaceMenu();