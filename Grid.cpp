#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		Cell* pCell = CellList[pos.VCell()][pos.HCell()];
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		delete pCell->GetGameObject();
		pCell->SetGameObject(NULL);

	}
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);
		
	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

void Grid::SetCurrPlayerNum(int n)
{
	currPlayerNumber = n;

}

Player* Grid::GetPlayerByNum(int n)
{
	return PlayerList[n];
}

// ========= Other Getters =========


Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}


Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())// ????
			{
				Ladder* p = CellList[i][j]->HasLadder();
				return p;
			}


		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

int Grid::GetNumOfLadders() const
{
	int counter = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
			if (CellList[i][j]->HasLadder())
				counter++;
	return counter;
}

// ========= User Interface Functions =========

bool Grid::LadderCheck(Ladder* Pnew)
{
	
	
		CellPosition c1 = Pnew->GetPosition();
		CellPosition c2 = Pnew->GetEndPosition();
		if (CellList[c1.VCell()][c1.HCell()]->HasSnake() || CellList[c2.VCell()][c2.HCell()]->HasSnake())
		{
			return 0;
		}
		if (c1.VCell() == GetEndSnake(c1.HCell()).VCell())
		{
			return 0 ; 
		}
		else return 1;
	

}
	bool Grid::SnakeCheck(Snake * Pnew)

	{
			CellPosition c1 = Pnew->GetPosition();
			CellPosition c2 = Pnew->GetEndPosition();
			if (CellList[c1.VCell()][c1.HCell()]->HasLadder() || CellList[c2.VCell()][c2.HCell()]->HasLadder())
			{
				return 0;

			}
			else return 1;
	
	}


Snake* Grid::GetNextSnake(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasSnake())// ????
			{
				Snake* p = CellList[i][j]->HasSnake();
				return p;
			}
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

int Grid::GetNumOfSnakes() const
{
	int counter = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
			if (CellList[i][j]->HasSnake())
				counter++;
	return counter;
}

bool Grid::IsOverlappingLadder(Ladder* PNewgame)
{

		CellPosition P = PNewgame->GetPosition();
		CellPosition E = PNewgame->GetEndPosition();

		int j = P.HCell();

		for (int i = 0; i < 8; i++)
		{
			if (CellList[i][j]->HasLadder() != NULL)
			{
				int pos1 = PNewgame->GetPosition().GetCellNum();
				int pos2 = PNewgame->GetEndPosition().GetCellNum();
				Ladder* error = CellList[i][j]->HasLadder();
				int q = error->GetPosition().GetCellNum();
				int m = error->GetEndPosition().GetCellNum();
				while (q <= m)
				{
					if (q == P.GetCellNum() || q == E.GetCellNum())
					{
						return 0;
					}
					q += 11;
				}
			}
		}
		for (int i = E.VCell(); i < P.VCell(); i++)
		{
			if (!(CellList[i][j]->HasLadder() == NULL))
			{
				return 0;
			}
		}
		return 1;
	}
		bool Grid::IsOverlappingSnake(Snake * PNewgame)

		{
		CellPosition P = PNewgame->GetPosition();
		CellPosition E = PNewgame->GetEndPosition();

		int j = P.HCell();

		for (int i = 0; i < 8; i++)
		{
			if (CellList[i][j]->HasSnake() != NULL)
			{
				Snake* error = CellList[i][j]->HasSnake();
				int q = error->GetPosition().GetCellNum();
				int m = error->GetEndPosition().GetCellNum();
				while (m <= q)
				{
					if (q == P.GetCellNum() || q == E.GetCellNum())
					{
						return 0;
					}
					q -= 11;
				}
			}
		}
		for (int i = E.VCell(); i > P.VCell(); i--)
		{
			if (!(CellList[i][j]->HasSnake() == NULL))
			{
				return 0;
			}
		}
		return 1;
	}


Card* Grid::GetCurrentCard(const CellPosition& position)
{
	if (CellList[position.VCell()][position.HCell()]->HasCard())
		return CellList[position.VCell()][position.HCell()]->HasCard();

	return NULL; // not found
}

int Grid::GetNumOfCards() const
{
	int counter = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
			if (CellList[i][j]->HasCard())
				counter++;
	return counter;
}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& OutFile, ObjectType Type)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) //   cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) //   cells from left to right
		{
			if (Type == ObjectType::TLadder)
			{
				if (CellList[i][j]->HasLadder())
					CellList[i][j]->GetGameObject()->Save(OutFile);
			}

			else if (Type == ObjectType::TSnake)
			{
				if (CellList[i][j]->HasSnake())
					CellList[i][j]->GetGameObject()->Save(OutFile);
			}

			else if (Type == ObjectType::TCard)
				if (CellList[i][j]->HasCard())
					CellList[i][j]->GetGameObject()->Save(OutFile);
		}
	}
}

void  Grid::ClearGrid()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
			{
				delete CellList[i][j]->GetGameObject();
				CellList[i][j]->SetGameObject(NULL);
			}
		}
	}
}
CellPosition Grid::GetEndSnake(int  ps )
{

	 
	for (int i = 0; i < 8; i++)
	{
		if (CellList[i][ps]->HasSnake() != NULL)
		{
			Snake* p = CellList[i][ps]->HasSnake(); 
			return p->GetEndPosition(); 
		}
		
 }
	CellPosition p;
	return p; 

}




Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
				delete CellList[i][j];
		}
	}
	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}