#include "CardFour.h"
#include "Snake.h"

CardFour::CardFour(const CellPosition & pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 4;	//sets the inherited cardNumber data member with the card number
}

CardFour::CardFour()
{
	cardNumber = 4;	//sets the inherited cardNumber data member with the card number
}



void CardFour:: ReadCardParameters(Grid * pGrid)
{
	//empty function: no parameters for this card
}


void CardFour:: Apply(Grid * pGrid , Player* pPlayer)
{
	Card::Apply(pGrid , pPlayer);	//printing a statement that tells the player he/she stands on card four

	pGrid->GetOutput()->PrintMessage("This card moves you to the start of the next snake. Click to continue...");
	
	int x , y ;			//for waiting mouse click
	
	pGrid->GetInput()->GetPointClicked(x,y);			//waiting for a click

	CellPosition Current_CellPosition = pPlayer->GetCell()->GetCellPosition();		//CellPosition object of the current player
	
	Snake*  Next_Snake = pGrid->GetNextSnake(Current_CellPosition);					//pointer to the next snake
	
	if (!Next_Snake)		//if no snakes ahead 
	{
		pGrid->GetOutput()->PrintMessage("No snake in the coming cells");
		return ;		//return from funcion (do noting)
	}
	CellPosition Next_Snake_pos = Next_Snake->GetPosition();

	pGrid->UpdatePlayerCell(pPlayer , Next_Snake_pos);		//changing player position to the start of the next snake
	
	Next_Snake->Apply(pGrid , pPlayer);		//applying the snake to the player
}

Card* CardFour::GetMyCopy(const CellPosition& pos)
{
	return new CardFour(pos);	//returning new constructed CardFour in CellPosition passed to the function 
}

void CardFour::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << endl;
}

void  CardFour::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}

CardFour::~CardFour()
{
}
