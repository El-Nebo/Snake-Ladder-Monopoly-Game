#pragma once

#include "Action.h"

class OpenGridAction : public Action
{
	string FileName;                                     // Name Of The File To Load From

public:

	OpenGridAction(ApplicationManager* pApp);            // A Constructor
											             
	virtual void ReadActionParameters();                 // Reads  Action parameters (File's Name)
										                 
	virtual void Execute();                              // Opens A File And Reads Data From It

	virtual ~OpenGridAction();                           // A Virtual Destructor


};

