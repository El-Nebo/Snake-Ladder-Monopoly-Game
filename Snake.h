#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the Snake's "Start Cell Position"

	CellPosition endCellPos; // here is the Snake's End Cell Position

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization
	
	Snake();

	virtual void Draw(Output* pOut) const; // Draws a Snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to Snake's end cell

	virtual	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	void Save(ofstream& OutFile);

	void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~Snake(); // Virtual destructor
};

