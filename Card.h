#pragma once
#include "Player.h"
#include "GameObject.h"


// Base Class of All Types of Cards (CardOne, CardTwo, CardThree, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card Number


class Card : public GameObject
{
protected:
	int cardNumber; // an integer representing the card number

public:
	Card(const CellPosition & pos);  // A Constructor for card that takes the cell position of it
									 
	Card();							 //Zero arguments constructor


	void SetCardNumber(int cnum);   // The setter of card number
	
	int GetCardNumber();            // The getter of card number

	void Draw(Output* pOut) const;  // Draws the card number in the cell position of the card
	                                // It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid * pGrid); // It reads the parameters specific for each Card Type
	                                               // It is a virtual function (implementation depends on Card Type)

	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed player
	                                                   // It is a virtual function (implementation depends on Card Type)

	virtual Card* GetMyCopy(const CellPosition&) = 0 ;	//Rerrurn Card pointer to a new card constructed inside the funcion
														//virtual as it constructs a new card of the same type of the card calling it

	virtual void Save(ofstream& OutFile);				// Saves Card's data 

	virtual void Load(ifstream& InFile, Grid* pGrid);	// Loads and Reads the GameObject parameters from the file

	virtual ~Card(); // A Virtual Destructor
};

