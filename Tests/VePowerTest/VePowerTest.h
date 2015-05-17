////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePowerTest.h
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <VeMainPCH.h>

class VePowerTest : public VeApplication
{
public:
	VePowerTest();

	virtual void OnInit();

	virtual void OnTerm();

	virtual void OnUpdate();

	virtual void OnKeyPressed(VeKeyboard::InputKey eKey);

	virtual void OnKeyReleased(VeKeyboard::InputKey eKey);
};
