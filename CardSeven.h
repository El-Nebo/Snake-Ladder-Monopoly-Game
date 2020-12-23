#pragma once
#include "Card.h"

// [ CardSeven ] Summary:
// Its Apply() Function:Gives the player another dice roll.
// Its Parameters: this card has no parameters to read

class CardSeven : public Card
{
	//No card parameters

public:
	CardSeven(const CellPosition &);	//non-defualt constructor takes cardposition of the card
	CardSeven();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);			// Reads the parameters of CardSeven 
														// No parameters for this card

	virtual void Apply(Grid* , Player*);				//Applies the effect of CardSeven on passed player
														//by giving passed player another dice roll  

	virtual Card* GetMyCopy(const CellPosition&);		//returns a new constructed CardSeven with same datamembers 

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~CardSeven ();	//A virtual destructor
};

