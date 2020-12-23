#include "CardSix.h"
#include "CellPosition.h"

CardSix::CardSix(const CellPosition & pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 6;			//sets the inherited cardNumber data member with the card number
}

CardSix::CardSix()
{
	cardNumber = 6;			//sets the inherited cardNumber data member with the card number
}



void CardSix:: ReadCardParameters(Grid * pGrid)
{
	//empty function: no parameters for this card
}

void CardSix:: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);																//printing a statement that tells the player he/she stands on card six

	pGrid->GetOutput()->PrintMessage("This card moves you backward same number of steps you just rolled. Click to continue...");
	
	int x , y ;			// for waiting mouse click 
	
	pGrid->GetInput()->GetPointClicked(x,y);			//waiting for a click

	int Rolled_Dice_Number = pPlayer->GetRolledDiceNum();	//Getting the last dice value player rolled

	int New_Cell_Num = pPlayer->GetStepCount() - Rolled_Dice_Number ;			//Getting cell num of cell player should go to
																				//same as player's current cell - last rolled dice value

	CellPosition New_Cell_Position = CellPosition::GetCellPositionFromNum(New_Cell_Num);		//Getting the CellPosition object of new cell
	
	pGrid->UpdatePlayerCell(pPlayer, New_Cell_Num);		//changing player position
	
	pGrid->GetOutput()->ClearStatusBar();		//clearing status bar
	
	if (pPlayer->GetCell()->GetGameObject())			//checking for a gameobject in new cell
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);		//applying any gameobject in new cell to the player
	}
}

Card* CardSix::GetMyCopy(const CellPosition& pos)
{
	return new CardSix(pos);	//returning new constructed CardSix in CellPosition passed to the function 
}

void CardSix::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << endl;
}

void  CardSix::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}

CardSix::~CardSix(void)
{
}
