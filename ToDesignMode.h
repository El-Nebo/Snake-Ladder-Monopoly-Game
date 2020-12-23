#pragma once
#include "Action.h"

class ToDesignMode : public Action
{
public:
	ToDesignMode(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	virtual ~ToDesignMode();


};

