#include "ApplicationManager.h"

#include "Grid.h"
#include "ToPlayModeAction.h"
#include "NewGameAction.h"
#include "AddLadderAction.h"
#include "AddSnakeAction.h"
#include "AddCardAction.h"
#include "CopyCardAction.h"
#include "CutCardAction.h"
#include "PasteCardAction.h"
#include "EditCardAction.h"
#include "DeleteGameObjectAction.h"
#include "RollDiceAction.h"
#include "InputDiceValueAction.h"
#include "SaveGridAction.h"
#include "OpenGridAction.h"
#include "ToDesignMode.h"

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case DELETE_GAME_OBJECT:
		pAct = new DeleteGameObjectAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case COPY_CARD:
		pAct = new CopyCardAction(this);
		break;

	case  CUT_CARD:
		pAct = new CutCardAction(this);
		break;
	case PASTE_CARD:
		pAct = new PasteCardAction(this);
		break;
	case EDIT_CARD:
		pAct = new EditCardAction(this);
		break;

	case EXIT:
		break;

	case TO_PLAY_MODE:
		pAct = new ToPlayModeAction(this);
		break;

	case ROLL_DICE:
		pAct = new RollDiceAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new ToDesignMode(this);
		break;
	

	case SAVE_GRID:

		pAct = new SaveGridAction(this);
		break;

	case OPEN_GRID:
		pAct = new OpenGridAction(this);
		break;

	case INPUT_DICE_VALUE:
		pAct = new InputDiceValueAction(this);
		break;

	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;


	case MENU_KILLER:

		break;


	case EMPTY:

		break;

	case GRID_AREA:
		return;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
