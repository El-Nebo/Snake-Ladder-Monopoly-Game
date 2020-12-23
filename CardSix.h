#pragma once
#include "Card.h"

// [ CardSix ] Summary:
// Its Apply() Function:Moves the player Backward the same number of steps dice just rolled 
// Its Parameters: this card has no parameters to read

class CardSix : public Card
{
	//No card parameters

public:
	CardSix(const CellPosition &);	//non-defualt constructor takes cardposition of the card
	
	CardSix();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);			// Reads the parameters of CardSix 
														// No parameters for this card

	virtual void Apply(Grid* , Player*);				//Applies the effect of CardSix on passed player
														//by moving the player Backward the same number of steps dice just rolled 

	virtual Card* GetMyCopy(const CellPosition&);		//returns a new constructed CardSix with same datamembers 

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~CardSix ();	//A virtual destructor
};

