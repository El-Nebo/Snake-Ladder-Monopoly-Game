#include "CardEight.h"
#include "Card.h"

CardEight::CardEight(const CellPosition& pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 8;			//sets the inherited cardNumber data member with the card number
}

CardEight::CardEight()
{
	cardNumber = 8;			//sets the inherited cardNumber data member with the card number
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	//empty function: no parameters for this card
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);		//printing a statement that tells the player he/she stands on card six

	pGrid->GetOutput()->PrintMessage("This card prevent the player from rolling the next time. Click to continue...");
	
	int x, y;		//for waiting mouse click 
	
	pGrid->GetInput()->GetPointClicked(x, y);			//waiting for a click

	pPlayer->SetPrevented(true);			//Setting player datamember responsible for preventing rollind dive to true

	pGrid->GetOutput()->ClearStatusBar();		//clearing status bar
}

Card* CardEight::GetMyCopy(const CellPosition& pos)
{
	return new CardEight(pos);		//returning new constructed CardEight in CellPosition passed to the function 
}

void CardEight::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << endl;
}

void  CardEight::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}

CardEight::~CardEight(void)
{
}
