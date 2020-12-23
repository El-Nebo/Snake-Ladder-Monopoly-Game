#include "RollDiceAction.h"
#include "Grid.h"
#include "Player.h"
#include "Output.h"
#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{

 }

void RollDiceAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	Player* p = pGrid->GetCurrentPlayer();                   	// Get the "current" player from pGrid

	if (pGrid->GetEndGame())                                  	//  Check if the Game is ended 
	{
		pOut->PrintMessage("Game Already Finished");
		return;
	}

	srand((int)time(NULL));                 // time is for different seed each roll

	int diceNumber = 1 + rand() % 6;      	// Generatew a random number from 1 to 6 
	 
	p->Move(pGrid, diceNumber);                               // Moves the Current Player Steps Equal To The Rolled Dice Num
	
	pGrid->AdvanceCurrentPlayer();                            // Advances the current player number of pGrid

}

RollDiceAction::~RollDiceAction()
{
}
