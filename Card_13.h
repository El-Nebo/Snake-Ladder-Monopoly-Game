#pragma once

#include "Card.h"

// [ Card_13 ] Summary:
// Its Apply() Function: Asks the player to buy this card , or force the player to pay fee for standing on this card
// Its Parameters: Price of the station , Fees to pay for the station

class Card_13 :	public Card
{
		//design mode parameters
	static int price;
	static int fee;
	static bool ongrid;
		//play mode parameters
	static Player*owner;
		// static because the parameters are shared amoung the whole cards with #13
	static int ncards;

	static bool  isSaved;      //for saving paramerters only once
	static bool isLoaded;      //for loading paramerters only once

public:

	static void RemoveOwner();

	static void setIsSaved(bool b);

	void setongridfalse();

	Card_13(const CellPosition & pos); // a constructor takes card position

	Card_13();

	virtual void ReadCardParameters(Grid * pGrid); // function to read card parameters

	virtual void Apply(Grid* pGrid, Player* pPlayer); // function to apply card action of players
	                     
	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual Card* GetMyCopy(const CellPosition&);

	~Card_13(); // virtual distructor
};
