#pragma once

#include "Action.h"

class ToPlayModeAction : public Action
{

	// No parameters for this action

public:
	ToPlayModeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ToPlayModeAction();
};

