#include"EditCardAction.h"

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




EditCardAction::EditCardAction(ApplicationManager* pApp) :Action(pApp) // a constructor
{

}

EditCardAction::~EditCardAction() // the destructor
{

}

void EditCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Click on the card will be edited:");
	cardPosition = pIn->GetCellClicked();

	card = pGrid->GetCurrentCard(cardPosition);

}


void EditCardAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();

	ReadActionParameters();
	if (!card)
	{
		pGrid->PrintErrorMessage("Cell has no card ! ... Click to continue ");
		return;
	}

	if (dynamic_cast<Card_10*>(card))
		((Card_10*)card)->setongridfalse();
	else
		if (dynamic_cast<Card_11*>(card))
			((Card_11*)card)->setongridfalse();
		else
			if (dynamic_cast<Card_12*>(card))
				((Card_12*)card)->setongridfalse();
			else
				if (dynamic_cast<Card_13*>(card))
					((Card_13*)card)->setongridfalse();
				else
					if (dynamic_cast<Card_14*>(card))
						((Card_14*)card)->setongridfalse();
					else
						if (dynamic_cast<CardOne*>(card) || dynamic_cast<CardTwo*>(card) || dynamic_cast<Card_9*>(card));

						else
						{
							pGrid->PrintErrorMessage("Card has no parameters ! ... Click to continue ");
							return;
						}

	card->ReadCardParameters(pGrid);
	pGrid->GetOutput()->PrintMessage("Edit Done !");

}

