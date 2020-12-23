#pragma once
#include "Action.h"

class DeleteGameObjectAction : public Action
{
	CellPosition startPos; // 1- The start position of the delete object 
public :
	DeleteGameObjectAction(ApplicationManager* pApp);
	 virtual void ReadActionParameters();
	 virtual void Execute();
	 virtual ~DeleteGameObjectAction
();
};



