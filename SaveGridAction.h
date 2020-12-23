#pragma once

#include "Action.h"

class SaveGridAction : public Action
{
	string FileName;                            // The Name of The File To Save To

public:

	SaveGridAction(ApplicationManager* pApp);   // A Constructor

	virtual void ReadActionParameters();        // Reads AddCardAction action parameters (File's Name)

	virtual void Execute();                     // Writes Information To The File

	virtual ~SaveGridAction();                  // A Virtual Destructor

};

