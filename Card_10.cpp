#include "Card_10.h"

Card_10::Card_10(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (10 here)
	ncards++;
}

Card_10::Card_10()
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (10 here)
	ncards++;
}


bool Card_10::ongrid = false; // setting ongird intially as false
Player* Card_10::owner = NULL; // setting owner pointing to NULL before buying the card
int Card_10::fee; // externing static data members
int Card_10::price; // externing static data members
int Card_10::ncards = 0;
bool Card_10::isSaved = 0;
bool Card_10::isLoaded = 0;

void Card_10::RemoveOwner()
{
	owner = NULL;
}

void Card_10::setIsSaved(bool b)
{
	isSaved = b;
}

Card_10::~Card_10(void) //destructor
{
	if (ncards == 1)
	{
		ongrid = false;
		owner = NULL;
		isLoaded = 0;
	}
	ncards--;
}


void Card_10::ReadCardParameters(Grid* pGrid)
{
	if (!ongrid) // if the card is not on grid yet

	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();

		int x = 0;
		pOut->PrintMessage("Enter card 10 station price :");

		do		 // validating the input not to be negative
		{
			if (x < 0)
				pOut->PrintMessage("Please enter a positive value for price :");
			x = pIn->GetInteger(pOut);
		} while (x < 0);

		price = x; // setting the price parameter

		x = 0;
		pOut->PrintMessage("Enter card 10 station fee :");

		do		// validating the input not to be negative
		{
			if (x < 0)
				pOut->PrintMessage("Please enter a positive value for fee :");
			x = pIn->GetInteger(pOut);
		} while (x < 0);

		fee = x; // setting the fee parameter

		x = 0;  // OCD

		pOut->ClearStatusBar();
		ongrid = true;
	}
	// if the card exist on grid will not ask  for parameters again
}

void Card_10::Apply(Grid* pGrid, Player* pPlayer)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid, pPlayer);

	if (!owner)  // if the card is already owned by a player , else action_1 is performed
	{
		if (pPlayer->GetWallet() >= price) // if the player doesn't have enough money to buy the card , else action_2 is performed
		{
			string response;
			int x = 0;
			do // validating that the idiot player doesn't enter any other letters
			{
				if (!x)
					pOut->PrintMessage("This is card#10 , do you want to buy it with \"" + to_string(price) + "$\" for a fee of \"" + to_string(fee) + "$\" ??? (Y/N)");
				else
					pOut->PrintMessage("Reply only with (Y/N)!");

				response = pIn->GetSrting(pOut);
				if (response == "y" || response == "Y")
				{
					owner = pPlayer;
					pPlayer->SetWallet(pPlayer->GetWallet() - price);
					pOut->PrintMessage("You bought Card 10.");
				}
				if (response == "n" || response == "N")
				{
					pOut->PrintMessage("You didn't buy Card 10.");
				}
				x++;
			} while (response != "Y" && response != "y" && response != "n" && response != "N");

			x = 0; // OCD
		}
		else // else action_2: player doesn't have enough money for the card
		{
			pOut->PrintMessage("This is card#10 , and you don't have enough money to buy it :(");
		}
	}
	else  // else action_1: for the players not owning the card
	{
		if (pPlayer != owner)
		{
			pOut->PrintMessage("This is card#10 , you have to pay the fee \"" + to_string(fee) + "$\"");
			pPlayer->SetWallet(pPlayer->GetWallet() - fee);
			owner->SetWallet(owner->GetWallet() + fee);
		}

	}

}

void Card_10::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);

	if (!isSaved)
	{
		OutFile << "      " << this->fee << "      " << this->price;
		isSaved = 1;
	}
	OutFile << endl;
}

void  Card_10::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);

	if (!isLoaded)
	{
		InFile >> this->fee >> this->price;
		ongrid = true;
		isLoaded = 1;
	}
}

void Card_10::setongridfalse()
{
	ongrid = false;
}

Card* Card_10::GetMyCopy(const CellPosition& pos)
{
	return new Card_10(pos);
}
