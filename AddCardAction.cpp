#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"

#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "Card_9.h"
#include "Card_10.h"
#include "Card_11.h"
#include "Card_12.h"
#include "Card_13.h"
#include "Card_14.h"


AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Enter the Card's number:");
	cardNumber = pIn->GetInteger(pOut);

	// 3- Validat cardNumber
	if (cardNumber > 14 || cardNumber < 1) {
		pGrid->PrintErrorMessage("Error: Invalid card number ! Click to continue ...");
		return;
	}



	// 4- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Click on the new card's cell");
	cardPosition = pIn->GetCellClicked();
	
	// 5- Validat cell inside grid
	if (!cardPosition.IsValidCell()) {
		pGrid->PrintErrorMessage("Error: There is no cells to click outside the grid area ! Click to continue ...");
		return;
	}
	if (cardPosition.GetCellNum() == 1 || cardPosition.GetCellNum() == 99)
	{
		pGrid->PrintErrorMessage("You cannot set card in first or last cell");
		cardNumber = 0;
		return;
	}

	// 6- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	if (cardPosition.IsValidCell())
	{
		switch (cardNumber)
		{
		case 1:
			pCard = new CardOne(cardPosition);
			break;
		case 2:
			pCard = new CardTwo(cardPosition);
			break;
		case 3:
			pCard = new CardThree(cardPosition);
			break;
		case 4:
			pCard = new CardFour(cardPosition);
			break;
		case 5:
			pCard = new CardFive(cardPosition);
			break;
		case 6:
			pCard = new CardSix(cardPosition);
			break;
		case 7:
			pCard = new CardSeven(cardPosition);
			break;
		case 8:
			pCard = new CardEight(cardPosition);
			break;
		case 9:
			pCard = new Card_9(cardPosition);
			break;
		case 10:
			pCard = new Card_10(cardPosition);
			break;
		case 11:
			pCard = new Card_11(cardPosition);
			break;
		case 12:
			pCard = new Card_12(cardPosition);
			break;
		case 13:
			pCard = new Card_13(cardPosition);
			break;
		case 14:
			pCard = new Card_14(cardPosition);
			break;

			// A- Add the remaining cases

		}
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:
		bool val = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!val)
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction
		else
		{
			pCard->Draw(pGrid->GetOutput());
			string s = "Card " + to_string(cardNumber) + " established successfully in cell " + to_string(cardPosition.GetCellNum()) + ". Click to continue";
			pGrid->GetOutput()->PrintMessage(s);
			int x, y;
			pGrid->GetInput()->GetPointClicked(x, y);
			pGrid->GetOutput()->ClearStatusBar();
		}
	}

}
