#include "Card_13.h"

Card_13::Card_13(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 13; // set the inherited cardNumber data member with the card number (13 here)
	ncards++;
}

Card_13::Card_13()
{
	cardNumber = 13; // set the inherited cardNumber data member with the card number (13 here)
	ncards++;
}

bool Card_13::ongrid=false; // setting ongird intially as flase
Player* Card_13::owner=NULL; // setting owner pointing to NULL before buying the card
int Card_13::fee; // externing static data members
int Card_13::price; // externing static data members
int Card_13::ncards = 0;

bool Card_13::isSaved = 0;
bool Card_13::isLoaded = 0;

void Card_13::RemoveOwner()
{
	owner = NULL;
}

void Card_13::setIsSaved(bool b)
{
	isSaved = b;
}

Card_13::~Card_13(void) //destructor
{
	if (ncards == 1)
	{
		ongrid = false;
		owner = NULL;
		isLoaded = 0;
	}
	ncards--;
}

void Card_13::ReadCardParameters(Grid * pGrid)
{

	 
	if (!ongrid) // if the card is not on grid yet

	{
		Output*pOut=pGrid->GetOutput();
		Input*pIn=pGrid->GetInput();

		int x=0;
		pOut->PrintMessage("Enter card 13 station price :");

		do		 // validating the input not to be negative
		{
			if(x<0)
				pOut->PrintMessage("Please enter a positive value for price :");
		x=pIn->GetInteger(pOut);
		}while(x<0);

		price=x; // setting the price parameter

		x=0;
		pOut->PrintMessage("Enter card 13 station fee :");

		do		// validating the input not to be negative
		{
			if(x<0)
				pOut->PrintMessage("Please enter a positive value for fee :");
		x=pIn->GetInteger(pOut);
		}while(x<0);

		fee=x; // setting the fee parameter

		x=0;  // OCD

		pOut->ClearStatusBar();
		ongrid=true;
	}
	// if the card exist on grid will not ask  for parameters again
}

void Card_13::Apply(Grid* pGrid, Player* pPlayer)
{

	Output*pOut=pGrid->GetOutput();
	Input*pIn=pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);

	if (!owner)  // if the card is already owned by a player , else action_1 is performed
	{
		if (pPlayer->GetWallet()>=price) // if the player doesn't have enough money to buy the card , else action_2 is performed
		{
			string response;
			int x=0;
			do // validating that the idiot player doesn't enter any other letters
			{
				if(!x)
					pOut->PrintMessage("This is card#13 , do you want to buy it with \""+to_string(price)+"$\" for a fee of \""+to_string(fee)+"$\" ??? (Y/N)");
				else 
					pOut->PrintMessage("Reply only with (Y/N)!");

				response =pIn->GetSrting(pOut);
				if (response == "y" || response == "Y")
				{
					owner = pPlayer;
					pPlayer->SetWallet(pPlayer->GetWallet() - price);
					pOut->PrintMessage("You bought Card 13.");
				}
				if (response == "n" || response == "N")
				{
					pOut->PrintMessage("You didn't buy Card 13.");
				}
				x++;
			}while (response != "Y" && response != "y" && response != "n" && response != "N");

			x=0; // OCD
		}
		else // else action_2: player doesn't have enough money for the card
		{
			pOut->PrintMessage("This is card#13 , and you don't have enough money to buy it :(");
		}
	}
	else  // else action_1: for the players not owning the card
	{
		if (pPlayer!=owner)
		{
			pOut->PrintMessage("This is card#13 , you have to pay the fee \""+to_string(fee)+"$\"");
			pPlayer->SetWallet(pPlayer->GetWallet()-fee);
			owner->SetWallet(owner->GetWallet()+fee);
		}

	}

}

void Card_13::Save(ofstream& OutFile)
{
	this->Card::Save(OutFile);

	if (!isSaved)
	{
		OutFile << "      " << this->fee <<"      " << this->price;
		isSaved = 1;
	}
	OutFile << endl;
}

void  Card_13::Load(ifstream& InFile, Grid* pGrid)
{
	this->Card::Load(InFile, pGrid);

	if (!isLoaded)
	{
		InFile >> this->fee >> this->price;
		ongrid = true;
		isLoaded = 1;
	}
	 
}

void Card_13::setongridfalse()
{
	ongrid = false;
}

Card* Card_13::GetMyCopy(const CellPosition& pos)
{
	return new Card_13(pos);
}
