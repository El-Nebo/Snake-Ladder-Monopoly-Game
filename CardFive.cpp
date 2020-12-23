#include "CardFive.h"
#include "CellPosition.h"
#include "Ladder.h"
#include "Snake.h"


CardFive::CardFive(const CellPosition& pos) : Card(pos)
{
	cardNumber = 5;	//sets the inherited cardNumber data member with the card number
}

CardFive::CardFive()
{
	cardNumber = 5;	//sets the inherited cardNumber data member with the card number
}



void CardFive::ReadCardParameters(Grid* pGrid)
{
	//empty function: no parameters for this card
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);		//printing a statement that tells the player he/she stands on card five

	pGrid->GetOutput()->PrintMessage("This card moves you forward same number of steps you just rolled. Click to continue...");
	
	int x, y;		//for  waiting mouse click
	
	pGrid->GetInput()->GetPointClicked(x, y);			//waiting for a click


	int Rolled_Dice_Number = pPlayer->GetRolledDiceNum();		//Getting the last dice value player rolled

	int New_Cell_Num = pPlayer->GetStepCount() + Rolled_Dice_Number;		//Getting cell num of cell player should go to
																			//same as player's current cell + last rolled dice value

	CellPosition New_Cell_Position = CellPosition::GetCellPositionFromNum(New_Cell_Num);	//Getting the CellPosition object of new cell

	pGrid->UpdatePlayerCell(pPlayer, New_Cell_Num);		//changing player position
		
	pGrid->GetOutput()->ClearStatusBar();				//clearing status bar 

	if (pPlayer->GetCell()->GetGameObject())			//checking for a gameobject in new cell
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);	//applying any gameobject in new cell to the player
	}

}

Card* CardFive::GetMyCopy(const CellPosition& pos)
{
	return new CardFive(pos);	//returning new constructed CardFive in CellPosition passed to the function 
}

void CardFive::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << endl;
}

void  CardFive::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}
		

CardFive::~CardFive(void)
{
}
