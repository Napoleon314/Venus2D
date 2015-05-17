////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   Main.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "MainWindow.h"

MainWindow* g_pkWindow = NULL;

int main(int argc, char *argv[])
{
    QApplication kApp(argc, argv);
    MainWindow kWin;
    g_pkWindow = &kWin;
    kWin.show();
    return kApp.exec();
}
