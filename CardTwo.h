#pragma once
#include "Card.h"

// [ CardTwo ] Summary:
// Its Apply() Function: Increment the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to increase --> put it as a "data member" and read it in ReadCardParameters()


class CardTwo : public Card
{
private:
	int walletAmount;	// the wallet value that will be added to player's wallet

public:
	CardTwo(const CellPosition &);		//non-defualt constructor takes cardposition of the card

	CardTwo();		//Zero arguments constructor

	virtual void ReadCardParameters(Grid *);				// Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* , Player*);					// Applies the effect of CardTwo on the passed Player
															// by incrementing the player's wallet by the walletAmount data member

	Card* GetMyCopy(const CellPosition& pos);				//returns a new constructed CardTwo with same datamembers (walletamount)

	virtual void Save(ofstream& OutFile);					// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);		// Loads and Reads the GameObject parameters from the file

	virtual ~CardTwo();	//A virtual destructor
};

