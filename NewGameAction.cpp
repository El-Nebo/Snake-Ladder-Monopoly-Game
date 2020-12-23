#include "NewGameAction.h"

#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Player.h"

#include "Card_10.h"
#include "Card_11.h"
#include "Card_12.h"
#include "Card_13.h"
#include "Card_14.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{

}

void NewGameAction::ReadActionParameters()
{

}


void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	const CellPosition* c1 = new CellPosition(1);       // Creating A New CellPosition With CellNum 1
	Player* p;

	for (int i = 0; i < MaxPlayerCount; i++)          // Looping On All Players
	{												  
		p = pGrid->GetCurrentPlayer();				  // Gets Current PLayer's Address
													  							
		p->Reset();                                   // Resets All Parameters
		pGrid->UpdatePlayerCell(p, *c1);              // Resets Player Cell To 1

		pGrid->AdvanceCurrentPlayer();				  // Advances Player To Reset Other Players
	}
	delete c1;

	pGrid->SetCurrPlayerNum(0);                       // start with the first player
													  
	pGrid->SetClipboard(NULL);                  	  // Initialize Clipboard with NULL
													  
	pGrid->SetEndGame(false);                   	  // Initialize endGame with false

	Card_10::RemoveOwner();
	Card_11::RemoveOwner();
	Card_12::RemoveOwner();                           // Removing Owners Of Cards 10-14
	Card_13::RemoveOwner();
	Card_14::RemoveOwner();

	pOut->PrintMessage("New Game !");
}


NewGameAction::~NewGameAction()
{

}