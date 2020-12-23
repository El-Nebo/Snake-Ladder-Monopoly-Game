#include "Card_9.h"
#include "CellPosition.h"
#include "Ladder.h"
#include "Snake.h"

Card_9::Card_9(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
}

Card_9::Card_9()
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
}

Card_9::~Card_9(void)
{
}

void Card_9::ReadCardParameters(Grid* pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Get the cell to travel to from the user
	pOut->PrintMessage("This card sends passing player to another cell. Click on the destination cell ...");
	CellToGoTo = pIn->GetCellClicked();
	// 3- Validation to click inside the grid area
	while (!(CellToGoTo.VCell() + 1) || CellToGoTo.GetCellNum() == this->position.GetCellNum())
	{
		if (!(CellToGoTo.VCell() + 1))
			pOut->PrintMessage("Please click on a cell inside the grid ...");

		else if (CellToGoTo.GetCellNum() == this->position.GetCellNum())
			pOut->PrintMessage("Please click on a cell other than start cell");

	CellToGoTo = pIn->GetCellClicked();
	}

	pGrid->PrintErrorMessage("You chose cell :" + to_string(CellToGoTo.GetCellNum()));

}

void Card_9::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Move the player to the destination cell
	pGrid->UpdatePlayerCell(pPlayer, CellToGoTo);


	if (pPlayer->GetCell()->GetGameObject())													//checking for a gameobject in new cell
	{
		//there is a gameobject in new cell
		string s;
		s = "Time to take the ";
		if (dynamic_cast<Ladder*>(pPlayer->GetCell()->GetGameObject()))							// printing a proper message
			s += "ladder";																		//
		else if (dynamic_cast<Snake*>(pPlayer->GetCell()->GetGameObject()))						//determine what kind of object
			s += "snake";																		//
		else if (dynamic_cast<Card*>(pPlayer->GetCell()->GetGameObject()))						//to print it in the message
			s += "card";
		s += ". Click to continue..";
		pGrid->GetOutput()->PrintMessage(s);													//telling the user he/she going to take gamobject
										//waiting for a click
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);							//applying any gameobject in new cell to the player
	}
}


void Card_9::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);

	OutFile << "      " << this->CellToGoTo.GetCellNum() << endl;
}

void  Card_9::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);

	int pos;
	InFile >> pos;
	this->CellToGoTo = CellPosition::GetCellPositionFromNum(pos);
}

Card* Card_9::GetMyCopy(const CellPosition& pos)
{
	Card* pCard;
	pCard = new Card_9(pos);
	((Card_9*)pCard)->CellToGoTo = this->CellToGoTo;
	return pCard;

}
