#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell* pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
						   // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells

	int wallet;		       // player's wallet (how many coins he has -- integer)

	int justRolledDiceNum; // the current dice number which is just rolled by the player

	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
						   // and reset again when reached 3
						   // it is used to indicate when to move and when to add to your wallet

	bool Prevented;        // Indicate if a player is preveneted from playing Card 8  True = Prevented
	bool AnotherRoll;		// Indicates if a player has another roll dice from Playing Card 7 Ture=roll again

	int sp_counter;            // Special Attacks Counter Max = 2
	bool sp_Ice;			   //  Ice
	bool sp_Fire;			   //  Fire
	bool sp_Poison;			   //  Poison
	bool sp_Lighting;		   //  Lightning

	bool Fired;                //  Fire Indicator
	bool Poisoned;             //  Poison Indicator

	int fired_c;               // Counter For Fire Special Attack
	int poisoned_c;            // Counter For Poison special Attack
public:

	Player(Cell* pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell* cell);	        	// A setter for the pCell

	Cell* GetCell() const;		         	// A getter for the pCell

	void SetWallet(int wallet);	        	// A setter for the wallet

	int GetWallet() const;		        	// a getter for the wallet

	int GetTurnCount() const;	        	// A getter for the turnCount

	bool       IncreaseTurnCount();         // if turncount=3 reset return false,else increases it and return true

	const int  GetPlayerNum() const;        // A getter for player's num , const as it doesnt need to modify anything

	int        GetStepCount() const;        // A getter for stepcount

	void       SetStepCount(int s);         // A setter for stepcount

	void       SetRolledDiceNum(int n);     // A setter for justRolledDiceNum

	int        GetRolledDiceNum() const;    // A getter for justRolledDiceNum

	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid* pGrid, int diceNumber);		// Moves the Player with the passed diceNumber 
												// and Applies the Game Object's effect (if any) of the end reached cell 
												// for example, if the end cell contains a ladder, take it

	void AppendPlayerInfo(string& playersInfo) const; // Appends player's info to the input string, 
													   // for example: P0(wallet, turnCount)

	bool IsPrevented();                                // A Getter For the variable prevented

	void SetPrevented(bool);                         // A setter the variable prevented 
													 
	bool RollingAgain();							 // Getter for rolling again bool
													 
	void SetRollingAgain(bool);						 // Setter for RollingAgain bool

	bool IsFired() const;                                  // A Getter For the variable Fired
		
	void SetFired(bool);

	bool IsPoisoned() const; 							  // A Getter For the variable Poisoned

	void SetPoisoned(bool);

	void SpecialAttack(int , Grid*);                         // Specail Attacks  I
	
	void Reset();
};

