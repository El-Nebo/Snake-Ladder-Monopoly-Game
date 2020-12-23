#include "CardThree.h"
#include "Ladder.h"

CardThree::CardThree(const CellPosition & pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 3;	//sets the ingereited cardNumber data member with the card number
}


CardThree::CardThree()
{
	cardNumber = 3;	//sets the ingereited cardNumber data member with the card number
}


void CardThree:: ReadCardParameters(Grid * pGrid)
{
	//empty function: no parameters for this card
}


void CardThree:: Apply(Grid * pGrid , Player* pPlayer)
{
	Card::Apply(pGrid , pPlayer);	//printing a statement that tells the player he/she stands on card three

	pGrid->GetOutput()->PrintMessage("This card moves you to the start of the next ladder. Click to continue...");
	
	int x, y;		//for waiting mouse click
	
	pGrid->GetInput()->GetPointClicked(x, y);			//waiting for a click

	CellPosition Current_CellPosition = pPlayer->GetCell()->GetCellPosition();		//CellPosition object of the current player
	
	Ladder*  Next_Ladder = pGrid->GetNextLadder(Current_CellPosition);				//pointer to the next ladder
	
	if (!Next_Ladder)		//if no ladders ahead
	{
		pGrid->GetOutput()->PrintMessage("No ladders in the coming cells");
		return ;		//returning from funcion (do noting)
	}

	pGrid->UpdatePlayerCell(pPlayer , Next_Ladder->GetPosition());	//moving the player to the start of the next ladder

	Next_Ladder->Apply(pGrid, pPlayer);		//applying the ladder to the player
}

Card* CardThree::GetMyCopy(const CellPosition& pos)
{
	return new CardThree(pos);		//returning new constructed CardThree in CellPosition passed to the function 
}

void CardThree::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile  << endl;
}

void  CardThree::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}

CardThree::~CardThree()
{
}
