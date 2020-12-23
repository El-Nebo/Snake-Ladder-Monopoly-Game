#include "InputDiceValueAction.h"

#include "Output.h"
#include "Input.h"
#include "Grid.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{

}

 void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	while (true)                                                          // Loops Till User Enerts A Valid Num
	{																	  
		pOut->PrintMessage("Please Enter A Value From 1 To 6: ");		  
		Value = pIn->GetInteger(pOut);									  // Stores Input 
		if (Value < 7 && Value >0)										  // Checks If Valid
			break;														  // Exits Loop If Valid
	}
}

 void InputDiceValueAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	Player* p = pGrid->GetCurrentPlayer();                         


	if (pGrid->GetEndGame())                                  // Checks If Game Already Finished
	{														  
		pOut->PrintMessage("Game Already Finished");		  
		return;												  
	}														  

	this->ReadActionParameters();							
															
	p->Move(pGrid, Value);                                  // Calls Move With Input Value

	pGrid->AdvanceCurrentPlayer();							// Next PLayer's Turn
}

 InputDiceValueAction::~InputDiceValueAction()
{


}
