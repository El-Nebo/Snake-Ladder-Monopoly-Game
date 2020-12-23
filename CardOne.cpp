#include "CardOne.h"

CardOne::CardOne(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::CardOne()
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}


CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid* pGrid)
{

	int x, y;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."


	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar



	// prints a message to tell the user the function of this card and asks the user to input the paramenters
	pGrid->GetOutput()->PrintMessage("CardOne: this card decrements the value of the passing player’s wallet by a specific value. Please, enter the desired value.");

	walletAmount = pGrid->GetInput()->GetInteger(pGrid->GetOutput());	//Get walletamount value from user 


	while (walletAmount < 1)			//check if used input is negative (invalid case)
	{
		pGrid->GetOutput()->PrintMessage("Please, enter a positive value");
		walletAmount = pGrid->GetInput()->GetInteger(pGrid->GetOutput());		//re-enter walletamount value and check again 
	}
	pGrid->GetOutput()->ClearStatusBar();		//clearing status bar 
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne


	Card::Apply(pGrid, pPlayer);	//printing a statement that tells the player he/she stands on this card

	pPlayer->SetWallet((pPlayer->GetWallet()) - walletAmount);	//sets the wallet of the player on the card by the new value
																//new value = old value - walletAmount

	string s = "Your wallet has been reduced by \"" + to_string(walletAmount) + "$\". Click to continue";
	
	pGrid->GetOutput()->PrintMessage(s);		//telling user his wallet amount is reduced 
	
	int x, y;		//for waiting mouse click

	pGrid->GetInput()->GetPointClicked(x,y);		//wainting mouse click
	
	pGrid->GetOutput()->ClearStatusBar();			//clearing satus bar
}

Card* CardOne::GetMyCopy(const CellPosition& pos)
{
	Card* pCard = new CardOne (pos);			//construct a new CardOne in the CellPosition passed to the function 
	((CardOne*)pCard)->walletAmount = this->walletAmount;		//Equalize datatmembers of the new card 
	return pCard;		//returning the new constructed card 
}

 void CardOne::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);			//Printing card numbre and its position 

	OutFile << "      " << this->walletAmount<<endl;		//printing  data members (walletamount)
}

 void  CardOne::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);		//loading card number and position 

	InFile >> walletAmount;			//loading data members (walletamout)
 }
