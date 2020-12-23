#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>

#include "Input.h"
#include "Output.h"

#include "Card_9.h"
#include "Card_10.h"
#include "Card_11.h"
#include "Card_12.h"
#include "Card_13.h"
#include "Card_14.h"


SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{

}

void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Enter The File Name: ");
	this->FileName = pIn->GetSrting(pOut) + ".txt";       // Make The File of Type Text
}

void SaveGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	this->ReadActionParameters();

	ofstream OutFile;
	OutFile.open(FileName);                             // Opens The File With The Entered Name , If It Doesnt Exist Creates it

	if (!OutFile.is_open())                             // Makes Sure The File is Open To Avoid Unexpected Errors
		return;


	////========================================////

	OutFile << pGrid->GetNumOfLadders() << endl;	     	 // Gets Number Of Ladders In The Grid
	pGrid->SaveAll(OutFile, ObjectType::TLadder);	     	 // Writes it to The File
													     	 
	OutFile << pGrid->GetNumOfSnakes() << endl;		     	 // Gets Number Of Snakes In The Grid
	pGrid->SaveAll(OutFile, ObjectType::TSnake);	     	 // Writes it to The File
													     	 
	OutFile << pGrid->GetNumOfCards() << endl;		     	 // Gets Number Of Cards In The Grid
	pGrid->SaveAll(OutFile, ObjectType::TCard);		     	 // Writes it to The File
									                          
	Card_10::setIsSaved(0);                                  // Resetting Saved Parameter For Next Save Action
	Card_11::setIsSaved(0);
	Card_12::setIsSaved(0);
	Card_13::setIsSaved(0);
	Card_14::setIsSaved(0);

	OutFile.close();                                        // Closes File (Important For Buffer)

	string s = "Grid Is Saved To The File:  " + FileName + "  Succeesfully.";  // Message To The User
	pOut->PrintMessage(s);
}

SaveGridAction::~SaveGridAction()
{

}

