#include "Card.h"

Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

Card::Card()
{

}

void Card::SetCardNumber(int cnum)
{
	cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(GameObject::GetPosition(), cardNumber);


}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	int x, y;
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");

}


void Card::Save(ofstream& OutFile)
{
	if (!OutFile.is_open())		//do noting if the card is not oped 
		return;

	OutFile << this->cardNumber << "      " << this->position.GetCellNum();		//printing cardnumber and position
}

void  Card::Load(ifstream& InFile, Grid* pGrid)
{
	int b;
	InFile >> b;	

	this->position = (CellPosition::GetCellPositionFromNum(b));		//loading position of the card 

	pGrid->AddObjectToCell(this);		//adding the card to the cellposition loaded from the file
}

Card::~Card()
{
}
