#pragma once
#include"Card.h"

// [ CardThree ] Summary:
// Its Apply() Function: moves the passed player to the start of the next ladder, if no ladder ahead, do nothing 
// Its Parameters: this card has no parameters to read


class CardThree : public Card
{
	//No card parameters

public:
	CardThree(const CellPosition &);						//non-defualt constructor takes cardposition of the card
	
	CardThree();		// Zero arguments constructor

	virtual void ReadCardParameters(Grid *);				// Reads the parameters of CardThree 
															// No parameters for this card

	virtual void Apply(Grid* , Player*);					//Applies the effect of CardThree on passed player
															//by moving the player to the start of the next ladder 

	virtual Card* GetMyCopy(const CellPosition&);			//returns a new constructed CardThree with same datamembers

	virtual void Save(ofstream& OutFile);					// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);		// Loads and Reads the GameObject parameters from the file

	virtual ~CardThree();	//A virtual destructor
};

