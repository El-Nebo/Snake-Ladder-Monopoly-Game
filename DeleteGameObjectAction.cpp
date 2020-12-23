#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include"GameObject.h"
DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{

}
void DeleteGameObjectAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
		pOut->PrintMessage("select the first cell of the deleted object: Click on its Start Cell ...");
		startPos = pIn->GetCellClicked();
	
}
void DeleteGameObjectAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	// We get a pointer to the Grid from the ApplicationManager
	Output* pOut = pGrid->GetOutput();
	
	pGrid->RemoveObjectFromCell(startPos);
	pGrid->UpdateInterface();
	pOut->ClearStatusBar();
}
DeleteGameObjectAction::~DeleteGameObjectAction()
{}; 