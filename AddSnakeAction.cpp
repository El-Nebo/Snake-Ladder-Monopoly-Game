#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
		// Read the startPos parameter
	

		pOut->PrintMessage("New Snake: Click on its Start Cell ...");
		startPos = pIn->GetCellClicked();

		// Read the endPos parameter
		pOut->PrintMessage("New Snake: Click on its End Cell ...");
		endPos = pIn->GetCellClicked();

		pOut->ClearStatusBar(); 

	///TODO: Make the needed validations on the read parameters


	// Clear messages
}
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if ((startPos.GetCellNum() > endPos.GetCellNum()) && (startPos.HCell() == endPos.HCell()) && (startPos.GetCellNum() != 99))
		// Create a Ladder object with the parameters read from the user
	{
		Snake* pSnake = new Snake(startPos, endPos);

		if ((pGrid->IsOverlappingSnake(pSnake) == 1) && (pGrid->SnakeCheck(pSnake) == 1))
		{

			Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager


			// Add the card object to the GameObject of its Cell:
			bool added = pGrid->AddObjectToCell(pSnake);
			// if the GameObject cannot be added
			if (!added)
			{
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}

		}
		else
		{
			if (pGrid->IsOverlappingSnake(pSnake) != 1)
				pGrid->PrintErrorMessage("Error cannot handle an overlapping");
			if (pGrid->SnakeCheck(pSnake) != 1)
				pGrid->PrintErrorMessage("Error cannot have a ladder or snake in the same start position or End position  ");
			
		}
	}



	if (startPos.GetCellNum() < endPos.GetCellNum())
	{
		pOut->PrintMessage("Careful you have to select from upper to lower in snake *-_-* !   ");
	}
	if ((startPos.GetCellNum() == 99))
	{
		pOut->PrintMessage("Sorry cannot put snake on last cell  ! ");
	}
	if ((startPos.HCell() != endPos.HCell()))
		pGrid->PrintErrorMessage("You have to select the same column please ");

}