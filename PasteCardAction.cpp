#include "PasteCardAction.h"
#pragma once
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

PasteCardAction::PasteCardAction(ApplicationManager* pApp) :Action(pApp)
{

}
void PasteCardAction ::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter the place of your card ");
	cardPosition = pIn->GetCellClicked();

}
void PasteCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	Card* pCard;
	pCard = pGrid->GetClipboard();
	if ( !pCard)
	{
		pGrid->PrintErrorMessage("Please copy/cut the card you want to paste");
		return;
	}
	Card* pnewCard;
	pnewCard = pCard->GetMyCopy(cardPosition);
	bool val=pGrid->AddObjectToCell(pnewCard);
		if (!val)
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		else 
			pnewCard->Draw(pGrid->GetOutput());
}
PasteCardAction::~PasteCardAction()
{

}