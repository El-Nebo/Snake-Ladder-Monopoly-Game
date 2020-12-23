#include "CardTwo.h"


CardTwo::CardTwo(const CellPosition &pos) : Card(pos)	//sets the cellposition of this card
{
	cardNumber = 2; // sets the inherited cardNumber data member with the card number
}


CardTwo::CardTwo()
{
	cardNumber = 2; // sets the inherited cardNumber data member with the card number
}


void CardTwo:: ReadCardParameters(Grid * pGrid)
{
	// prints a message to tell the user the function of this card and asks the user to input the paramenters
	pGrid->GetOutput()->PrintMessage("CardTwo: this card increments the value of the passing player’s wallet by a specific value. Please, enter the desired value.");
	
	walletAmount = pGrid->GetInput()->GetInteger(pGrid->GetOutput());		//Getting datamembers from the user (walletamount)

	while (walletAmount < 1)			//check if used input is negative (invalid case)
	{
		pGrid->GetOutput()->PrintMessage("Please, enter a positive value");
		walletAmount = pGrid->GetInput()->GetInteger(pGrid->GetOutput());;		//re-enter walletamount value and check again 
	}
	
	pGrid->GetOutput()->ClearStatusBar();		//clearing status bar 
}


void CardTwo:: Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid , pPlayer);	//printing a statement that tells the player he/she stands on card two

	pPlayer->SetWallet((pPlayer->GetWallet()) + walletAmount);	//sets the wallet of the player on the card by the new value
																//new value = old value + walletAmount

	string s = "Your wallet has been increased by \"" + to_string(walletAmount) + "$\". Click to continue";
	
	pGrid->GetOutput()->PrintMessage(s);		//telling user his wallet amount is increased 
	
	int x , y;		//for waiting mouse click
	
	pGrid->GetInput()->GetPointClicked(x,y);		//wainting mouse click
	
	pGrid->GetOutput()->ClearStatusBar();			//clearing satus bar
}

Card* CardTwo::GetMyCopy(const CellPosition& pos)
{
	Card* pCard = new CardTwo(pos);			//construct a new CardTwo in the CellPosition passed to the function 
	((CardTwo*)pCard)->walletAmount = this->walletAmount;		//Equalize datatmembers of the new card 
	return pCard;		//returning the new constructed card 
}

 void CardTwo::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << "      " << this->walletAmount<<endl;		//printing  data members (walletamount)
}

 void  CardTwo::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 

	InFile >> this->walletAmount;		//loading data members (walletamout)
 }

CardTwo::~CardTwo()
{
}
