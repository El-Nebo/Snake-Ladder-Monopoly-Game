#include "Snake.h"
#include "Player.h"

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

Snake::Snake()
{

}


void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
	
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	if (pPlayer->GetCell()->GetGameObject())			//checking for a gameobject in new cell
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);		//applying any gameobject in new cell to the player
	}

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream& OutFile)
{
	if (OutFile.is_open())
		OutFile << (this->position.GetCellNum()) << "      " << (this->endCellPos.GetCellNum()) << endl;
}

void Snake::Load(ifstream& InFile, Grid* pGrid) 
{
	int start, end;
	InFile >> start >> end;
	this->position = CellPosition::GetCellPositionFromNum(start);
	this->endCellPos = CellPosition::GetCellPositionFromNum(end);
	pGrid->AddObjectToCell(this);
}

Snake::~Snake()
{
}
