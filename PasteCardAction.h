#pragma once
#include "Action.h"

class PasteCardAction : public Action
{
	// [Action Parameters]
	int cardNumber;            // 1- the card number
	CellPosition cardPosition; // will be getted either from cut or paste 
public:
	PasteCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~PasteCardAction(); // A Virtual Destructor

};