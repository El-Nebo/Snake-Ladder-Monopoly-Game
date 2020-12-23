#pragma once

#include "Action.h"


class NewGameAction : public Action
{

	// No Parameters For This Action

public:

	NewGameAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	void Execute();          // Resets Players To Cell 1 , Resets Their Stats ( Wallet , TurnCount) , Gives Turn To PLayer 0 And Removes Owners of Cards 10-14

	~NewGameAction();

};

