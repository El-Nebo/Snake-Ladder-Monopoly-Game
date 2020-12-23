#pragma once

#include"Action.h"

class EditCardAction : public Action
{
	CellPosition cardPosition; // cell position of the card will be edited
	Card* card;
public:
	EditCardAction(ApplicationManager* pApp); // a constructor

	virtual void ReadActionParameters();


	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							 // and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~EditCardAction(); // A Virtual Destructor

};


