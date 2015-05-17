////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   CenterView.h
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <QLabel>

class SceneEditor;

class CenterView : public QWidget
{
    Q_OBJECT
    
public:
    CenterView(QWidget* pkParent = NULL);
    ~CenterView();

    QWidget* m_pkSceneEditor;
    QLabel* pkViewName;
    QLabel* pkFPS;

};
