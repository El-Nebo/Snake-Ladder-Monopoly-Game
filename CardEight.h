#pragma once
#include "Card.h"

// [ CardSeven ] Summary:
// Its Apply() Function:prevents the player from rolling the dice next time.
// Its Parameters: this card has no parameters to read

class CardEight : public Card
{
	//No card parameters

public:
	CardEight(const CellPosition &);	//non-defualt constructor takes cardposition of the card

	CardEight();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);			// Reads the parameters of CardEight 
														// No parameters for this card

	virtual void Apply(Grid* , Player*);				//Applies the effect of CardEight on passed player
														//by preventint the player from rolling the dice next time

	virtual Card* GetMyCopy(const CellPosition&);		//returns a new constructed CardEight with same datamembers 

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~CardEight ();	//A virtual destructor
};

