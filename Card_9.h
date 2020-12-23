#pragma once

#include "Card.h"

// [ Card_9 ] Summary:
// Its Apply() Function: Moving the player to a specific cell determined by the user in the Design Mode
// Its Parameters: The CellPosition of the cell that player travels to

class Card_9 :	public Card
{
	// Card_9 Parameters:
	CellPosition CellToGoTo; // the cell position of the cell that player travels to

public:
	Card_9(const CellPosition & pos); // A Constructor takes card position
	Card_9();

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of Card_9 which is: CellToGoTo

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of Card_9 on the passed Player
	                                                  // by moving the player to the specified cell
	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~Card_9(); // A Virtual Destructor

	virtual Card* GetMyCopy(const CellPosition&);

};