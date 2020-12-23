#include "AddLadderAction.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

    

	///TODO: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if ((startPos.GetCellNum() < endPos.GetCellNum()) && (startPos.HCell() == endPos.HCell())&& (startPos.GetCellNum() !=1))
		// Create a Ladder object with the parameters read from the user

	{

		Ladder* pLadder = new Ladder(startPos, endPos);

		if ((pGrid->IsOverlappingLadder(pLadder) == 1) && (pGrid->LadderCheck(pLadder) == 1) )

		{
			Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		   // Add the card object to the GameObject of its Cell:
			bool added = pGrid->AddObjectToCell(pLadder);

			// if the GameObject cannot be added
			if (!added)
			{
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}
			// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
		}
		else
		{ 
			
			if (pGrid->IsOverlappingLadder(pLadder) != 1)
				pGrid->PrintErrorMessage("Error cannot handle an overlapping");
			if (pGrid-> LadderCheck(pLadder) != 1)
				pGrid->PrintErrorMessage("Error cannot have a ladder or snake in the same position or the same end position  ");
		}

	}
	else
	{
		if ((startPos.GetCellNum() > endPos.GetCellNum()))
			pOut->PrintMessage(" you have to select from less one to upper one *_*");
		if ((startPos.GetCellNum() == 1))
			pOut->PrintMessage("Cannot have a ladder on first cell  "); 
		if (startPos.HCell() != endPos.HCell())
			pOut->PrintMessage("You have to select the same column please ");
	}

}
