# pragma once
#include "CopyCardAction.h"
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



CopyCardAction::CopyCardAction(ApplicationManager* pApp):Action(pApp)
{
}
	// Initializes the pManager pointer of Action with the passed pointer

CopyCardAction::~CopyCardAction()
{
}
void CopyCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("select the card you want to copy ");
	cardpos = pIn->GetCellClicked();
	while (cardpos.HCell() == -1 )
	{
		pGrid->PrintErrorMessage("Please enter a valid cell. Click to continue");
		cardpos = pIn->GetCellClicked();	
	}
	
}
void CopyCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	pCard = pGrid->GetCurrentCard(cardpos);
	if (pCard == NULL)		
	{
		pOut->PrintMessage("no card here ");
		return;
	}
	pGrid->SetClipboard(pCard);
	pOut->PrintMessage("copy succesful");

}

