#pragma once
#include"Card.h"

// [ CardFour ] Summary:
// Its Apply() Function: moves the passed player to the start of the next snake, if no skane ahead, do nothing 
// Its Parameters: this card has no parameters to read


class CardFour : public Card
{
	//No card parameters

public:
	CardFour(const CellPosition &);		//non-defualt constructor takes cardposition of the card
	
	CardFour();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);			// Reads the parameters of CardFour 
														// No parameters for this card

	virtual void Apply(Grid* , Player*);				//Applies the effect of CardFour on passed player
														//by moving the player to the start of the next snake 

	virtual Card* GetMyCopy(const CellPosition&);		//returns a new constructed CardFour with same datamembers 

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~CardFour ();	//A virtual destructor
};

