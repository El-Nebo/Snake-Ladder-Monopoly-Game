#include "OpenGridAction.h"
#include "Grid.h"
#include <fstream>

#include "Input.h"
#include "Output.h"

#include "Ladder.h"
#include "Snake.h"

#include "Card.h"
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

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{

}

void OpenGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Enter The File Name: ");
	this->FileName = pIn->GetSrting(pOut) + ".txt";             // Adding Extension 
}

void OpenGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	this->ReadActionParameters();

	ifstream InFile;
	InFile.open(FileName);                                   // Opening The File

	if (!InFile.is_open())                                   // Checks If A File With The Same Name Exists
	{
		string s = "No File With The Name:   " + FileName + "   Was Found";
		pOut->PrintMessage(s);
		return;
	}

	pGrid->ClearGrid();                         // Clears Grid Of Objects For Loading Another Grid

	////========================================////

	int NumOfLadders;
	InFile >> NumOfLadders;                   // Reading Number Of Ladders Then Looping On The Lines And Loading Them

	Ladder* L;

	for (int i = 0; i < NumOfLadders; i++)
	{
		L = new Ladder;
		L->Load(InFile, pGrid);
	}

	//==================================================//	

	int NumOfSnakes;                          // Reading Number Of Snakes Then Looping On The Lines And Loading Them
	InFile >> NumOfSnakes;

	Snake* S;

	for (int i = 0; i < NumOfSnakes; i++)
	{
		S = new Snake;
		S->Load(InFile, pGrid);
	}

	//==================================================//

	int NumOfCards;                          // Reading Number Of Cards Then Looping On The Lines And Loading Them
	InFile >> NumOfCards;

	int num;
	Card* pCard;

	for (int i = 0; i < NumOfCards; i++)
	{
		InFile >> num;                        // Reads Crad's Num Then Creats A Card Of This Number Then  Loads its Parameters

		switch (num)
		{
		case 1:
			pCard = new CardOne();
			break;
		case 2:
			pCard = new CardTwo();
			break;
		case 3:
			pCard = new CardThree();
			break;
		case 4:
			pCard = new CardFour();
			break;
		case 5:
			pCard = new CardFive();
			break;
		case 6:
			pCard = new CardSix();
			break;
		case 7:
			pCard = new CardSeven();
			break;
		case 8:
			pCard = new CardEight();
			break;
		case 9:
			pCard = new Card_9();
			break;
		case 10:
			pCard = new Card_10();
			break;
		case 11:
			pCard = new Card_11();
			break;
		case 12:
			pCard = new Card_12();
			break;
		case 13:
			pCard = new Card_13();
			break;
		case 14:
			pCard = new Card_14();
			break;
		}

		pCard->Load(InFile, pGrid);
	}

	//==================================================//

	InFile.close();                                            // Closes The File

	string s = "Grid Loaded From File:  " + FileName + "  Successfully.";
	pOut->PrintMessage(s);
}

OpenGridAction::~OpenGridAction()
{

}

