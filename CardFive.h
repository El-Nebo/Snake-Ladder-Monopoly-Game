#pragma once
#include "Card.h"

// [ CardFive ] Summary:
// Its Apply() Function:Moves the player forward the same number of steps dice just rolled 
//						(if the player reach a ladder or a snake at the end of moving forward, player should take it).
// Its Parameters: this card has no parameters to read


class CardFive : public Card
{
	//No card parameters

public:
	CardFive(const CellPosition &);		//non-defualt constructor takes cardposition of the card
	
	CardFive();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);			// Reads the parameters of CardFive 
														// No parameters for this card

	virtual void Apply(Grid* , Player*);				//Applies the effect of CardFive on passed player
														//by moving the player forward the same number of steps dice just rolled
														//and apply any found game object

	virtual Card* GetMyCopy(const CellPosition&);		//returns a new constructed CardFive with same datamembers 

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~CardFive();	//A virtual destructor
};

