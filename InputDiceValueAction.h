#pragma once

#include "Action.h"

class InputDiceValueAction : public Action
{
	int Value;

public:

	InputDiceValueAction(ApplicationManager* pApp);

	 void ReadActionParameters();                      // Read Actions Parameters (DiceNum)

	 void Execute();                                   // Moves PLayer Steps Equal To The Input Num

	 ~InputDiceValueAction();

};

