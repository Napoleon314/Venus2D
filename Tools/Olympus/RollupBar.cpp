////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   RollupBar.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "RollupBar.h"

RollupBar::RollupBar(QWidget* pkParent)
    : QWidget(pkParent)
{
    setMinimumWidth(200);
    setMinimumHeight(100);
}

RollupBar::~RollupBar()
{

}
