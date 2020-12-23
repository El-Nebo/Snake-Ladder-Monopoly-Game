#include "ToPlayModeAction.h"

#include "Grid.h"
#include "Output.h"



ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{

}

ToPlayModeAction::~ToPlayModeAction()
{

}
void ToPlayModeAction::ReadActionParameters()
{

}

void ToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();


	pOut->CreatePlayModeToolBar();

	pManager->ExecuteAction(ActionType::NEW_GAME);

}
