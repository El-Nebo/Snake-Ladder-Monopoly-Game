#include "CardSeven.h"


CardSeven::CardSeven(const CellPosition & pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 7;			//sets the inherited cardNumber data member with the card number
}

CardSeven::CardSeven()
{
	cardNumber = 7;			//sets the inherited cardNumber data member with the card number
}


void CardSeven:: ReadCardParameters(Grid * pGrid)
{
	//empty function: no parameters for this card
}

void CardSeven:: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);		//printing a statement that tells the player he/she stands on card Seven
	
	pGrid->GetOutput()->PrintMessage("This card gives you another dice roll. Click to continue...");
	
	int x , y ;			//for waiting mouse click 
	
	pGrid->GetInput()->GetPointClicked(x,y);			//waiting for a click

	int Player_Num = pPlayer->GetPlayerNum();		//Getting the number of the player ( 0 to 3 )
	
	Player_Num += 3;								//To make to turn return to the same player when 
													//RollDiceAction class increments the currplayernum 
	
	pGrid->SetCurrPlayerNum(Player_Num);			//Setting the order of the player to roll to dice to the same player 
	
	pGrid->GetOutput()->PrintMessage("It is player " + to_string(Player_Num-3) + " turn, again.");
	
	pPlayer->SetRollingAgain(true);			//setting plyaer datamember resposible for rolling the dice again to true
}

Card* CardSeven::GetMyCopy(const CellPosition& pos)
{
	return new CardSeven(pos);	//returning new constructed CardSeven in CellPosition passed to the function 
}

void CardSeven::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << endl;
}

void  CardSeven::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 
}

CardSeven::~CardSeven(void)
{
}
