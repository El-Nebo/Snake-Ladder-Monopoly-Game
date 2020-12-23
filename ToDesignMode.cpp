#include "ToDesignMode.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Player.h"

ToDesignMode::ToDesignMode(ApplicationManager* pApp) : Action(pApp)
{

}

ToDesignMode::~ToDesignMode()
{

}

void ToDesignMode::ReadActionParameters()
{

}
void ToDesignMode::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();


	pManager->ExecuteAction(NEW_GAME);

	pOut->CreateDesignModeToolBar();
	pOut->ClearStatusBar();

}
