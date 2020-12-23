#include "Player.h"
#include "CellPosition.h"

#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(1), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;

	this->turnCount = 0;                  // Initial Values for turncount and Prevented

	Prevented = false;

	AnotherRoll = false;

	sp_counter = sp_Ice = sp_Fire = sp_Poison = sp_Lighting = 1;      // Initializing Specials

	Fired = Poisoned = 0;

	fired_c = poisoned_c = 0;
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;

	stepCount = CellPosition::GetCellNumFromPosition(cell->GetCellPosition());   // Updating stepcount to be new cellnum
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int        Player::GetStepCount() const
{
	return stepCount;
}

void       Player::SetStepCount(int s)
{
	stepCount = s;
}

const int  Player::GetPlayerNum() const
{
	return playerNum;
}

bool       Player::IncreaseTurnCount()
{
	if (turnCount == 2)                                 // Every 3rd turn
	{
		turnCount = 0;
		return false;
	}

	turnCount++;
	return true;
}

void       Player::SetRolledDiceNum(int n)
{
	justRolledDiceNum = n;
}

int        Player::GetRolledDiceNum() const
{
	return justRolledDiceNum;
}


// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];                        // Gets this players color

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);    // Draws PLayer  
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;     // Gets Cell's Color

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);                    // Clears Player By Drawing on top of it
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	string c, s;

	if (this->Fired)                                    // If This Player Is Fired
	{
		wallet -= 20;
		fired_c++;
		if (fired_c == 3)
		{
			Fired = 0;
			fired_c = 0;
		}
	}

	if (this->Poisoned)                                  // If This Player Is Poisoned
	{
		diceNumber--;
		poisoned_c++;
		if (poisoned_c == 5)
		{
			Poisoned = 0;
			poisoned_c = 0;
		}
	}

	if (this->IsPrevented())                                       // Checks If The Player is Prevented From PLaying This Turn
	{
		string s = "Player " + to_string(this->GetPlayerNum()) + " is prevented from rolling the dice";
		pOut->PrintMessage(s);
		this->IncreaseTurnCount();				//increasing turn count
		this->SetPrevented(false);                                 // Removes Prevention
		return;
	}

	if (this->RollingAgain())			// if player has another game roll from card 7 
	{
		this->IncreaseTurnCount();
		this->IncreaseTurnCount();
		//double increaseing the turn count to make same player play again 

		this->SetRollingAgain(false);			//setting teh roll dice false (normal condition)
	}

	if (!IncreaseTurnCount())               // Checking if it is Recharge Turn or not
	{
		if (sp_counter < 3)                 // If Player Still Has Attacks
		{
			s = "Player: " + to_string(playerNum) + ",Do You Wish To Launch A Special Attack Instead Of Recharging ? y/n";
			pOut->PrintMessage(s);
			c = pIn->GetSrting(pOut);

			if (c == "y" || c == "Y")
			{
				s = "Choose A Special Attack :";

				if (sp_Ice)           s += "  1-Ice";
				if (sp_Fire)          s += "  2-Fire";
				if (sp_Poison)        s += "  3-Poison";
				if (sp_Lighting)      s += "  4-Lightning";

				pOut->PrintMessage(s);
				y = pIn->GetInteger(pOut);

				if ((y == 1 && sp_Ice) || (y == 2 && sp_Fire) || (y == 3 && sp_Poison) || (y == 4 && sp_Lighting)) // A choice = y and y is availible
				{
					this->SpecialAttack(y, pGrid);        // Call Func With Attack Type 

					sp_counter++;                          // increase counter of attacks

					return;
				}
			}
		}

		wallet += 10 * diceNumber;          // Increasing Wallet

		string s = "Player: " + to_string(playerNum) + " Increased Money By: " + to_string(diceNumber * 10) + '$';
		pGrid->PrintErrorMessage(s);
		return;
	}

	//================================================================//

	if (wallet < 1)                         // A player Cant Move if he has less than 1 coin
	{
		s = "Player: " + to_string(playerNum) + " Cant Move For Havnig Money Less Than 1";
		pOut->PrintMessage(s);
		return;
	}

	justRolledDiceNum = diceNumber;        	// Sets the justRolledDiceNum with the passed diceNumber

	CellPosition* newpos;                                             // New Cellposition Pointer 

	s = "Player: " + to_string(playerNum) + " Has Rolled : ";       // Indication For User

	if (diceNumber + stepCount < 98)
	{
		newpos = new CellPosition(justRolledDiceNum + stepCount);     // New Cellposition Go To

		s += to_string(diceNumber);
	}
	else                                                               // Prevents Player From Going Past Cell 99
	{
		newpos = new CellPosition(99);

		s += to_string(99 - stepCount);
	}

	pGrid->PrintErrorMessage(s);

	pGrid->UpdatePlayerCell(this, *newpos);                    // Updates pCell In player And Calls DrawPLayer in New Cell

	delete newpos;                                             // Deallocating Allocated Memory And Removing its Address
	newpos = NULL;

	if (pCell->GetGameObject() )                        // Applying the game object of the reached cell (if any)
	{
		(pCell->GetGameObject())->Apply(pGrid, this);
	}

	// Checking if the player reached the end cell of the whole game, and if yes, Set endgame with true

	if (CellPosition::GetCellNumFromPosition(pCell->GetCellPosition()) == 99)
	{
		pGrid->SetEndGame(true);
		string s = "Player: " + std::to_string(playerNum) + " Has Won !!";
		pGrid->PrintErrorMessage(s);
	}



}

void Player::AppendPlayerInfo(string& playersInfo) const          // Printing Players' Info 
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

bool Player::IsPrevented()
{
	return Prevented;
}

void Player::SetPrevented(bool b)
{
	Prevented = b;
}

bool Player::RollingAgain()
{
	return AnotherRoll;
}

void Player::SetRollingAgain(bool a)
{
	AnotherRoll = a;
}


bool Player::IsFired()   const
{
	return Fired;
}

void Player::SetFired(bool b)
{
	Fired = b;
}

bool Player::IsPoisoned()   const
{
	return Poisoned;
}

void Player::SetPoisoned(bool b)
{
	Poisoned = b;
}

void Player::SpecialAttack(int Type, Grid* pGrid)          // 1-Ice  2-Fire  3-Poison  4-Lightning
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	string s;
	Player* p;

	if (Type == 4)
	{
		pOut->PrintMessage("Lightning !!!! All Other Players Lose 20 Coins");

		for (int i = 0; i < MaxPlayerCount; i++)
			if (i != playerNum)
				pGrid->GetPlayerByNum(i)->wallet -= 20;

		sp_Lighting = 0;
		return;
	}

	pOut->PrintMessage("Choose A Player To Attack 0-3");
	x = pIn->GetInteger(pOut);

	while (x < 0 || x > 3 || x == playerNum)
	{
		pOut->PrintMessage("Enter A Number From 0 To 3 Except This Player's Number Please");
		x = pIn->GetInteger(pOut);
	}

	p = pGrid->GetPlayerByNum(x);                                      // Getting Player With Num = x


	switch (Type)                                              // Switch for Each Case
	{
	case 1:                                                              // 1 = Ice
		while (p->Prevented)                                                 // Checking if Player Is Already Frozen
		{
			s = "Player: " + to_string(p->playerNum) + " Is Already Frozen By Other Game Objects, Please Choose Another Player To Freeze";
			pOut->PrintMessage(s);
			x = pIn->GetInteger(pOut);

			while (x < 0 || x > 3 || x == playerNum)
			{
				pOut->PrintMessage("Enter A Number From 0 To 3 Except This Player's Number Please");
				x = pIn->GetInteger(pOut);
			}

			p = pGrid->GetPlayerByNum(x);
		}

		p->Prevented = 1;

		s = "Player: " + to_string(playerNum) + " Successfully Froze Player: " + to_string(x);
		pOut->PrintMessage(s);

		sp_Ice = 0;
		return;

	case 2:                                                              // 2 = Fire

		while (p->Fired)                                                 // Checking if Player Is Already Fired
		{
			s = "Player: " + to_string(p->playerNum) + " Is Already Fired By Other Game Objects, Please Choose Another Player To Fired";
			pOut->PrintMessage(s);
			x = pIn->GetInteger(pOut);

			while (x < 0 || x > 3 || x == playerNum)
			{
				pOut->PrintMessage("Enter A Number From 0 To 3 Except This Player's Number Please");
				x = pIn->GetInteger(pOut);
			}
			p = pGrid->GetPlayerByNum(x);
		}
		p->Fired = 1;

		s = "Player: " + to_string(playerNum) + " Successfully Fired Player: " + to_string(x);
		pOut->PrintMessage(s);

		sp_Fire = 0;
		return;

	case 3:                                                              // 3 = Poison

		while (p->Poisoned)                                              // Checking if Player Is Already Poisoned
		{
			s = "Player: " + to_string(p->playerNum) + " Is Already Poisoned By Other Game Objects, Please Choose Another Player To Poison";
			pOut->PrintMessage(s);
			x = pIn->GetInteger(pOut);

			while (x < 0 || x > 3 || x == playerNum)
			{
				pOut->PrintMessage("Enter A Number From 0 To 3 Except This Player's Number Please");
				x = pIn->GetInteger(pOut);
			}
			p = pGrid->GetPlayerByNum(x);
		}
		p->Poisoned = 1;

		s = "Player: " + to_string(playerNum) + " Successfully Poisoned Player: " + to_string(x);
		pOut->PrintMessage(s);

		sp_Poison = 0;
		return;

	}
}

void Player::Reset()
{

	wallet = 100;                     // Initial Values for turncount , wallet and Prevented

	this->turnCount = 0;

	Prevented = false;
	AnotherRoll = false;

	sp_counter = sp_Ice = sp_Fire = sp_Poison = sp_Lighting = 1;      // Initializing Specials

	Fired = Poisoned = 0;

	fired_c = poisoned_c = 0;
}