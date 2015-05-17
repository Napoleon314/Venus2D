////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   CenterView.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "CenterView.h"
#include "SceneEditor.h"

CenterView::CenterView(QWidget* pkParent)
    : QWidget(pkParent)
{
    pkViewName = new QLabel(tr(" Perspective"));
    pkViewName->setFixedHeight(28);
    pkFPS = new QLabel(tr("FPS: "));
    pkFPS->setFixedHeight(28);
    m_pkSceneEditor = new SceneEditorD3D11();
    //m_pkSceneEditor = new SceneEditorOGL();
    QVBoxLayout* pkVLayout = new QVBoxLayout();
    pkVLayout->setMargin(0);
    pkVLayout->setSpacing(0);
    pkVLayout->addWidget(pkViewName);
    pkVLayout->addWidget(m_pkSceneEditor);
    pkVLayout->addWidget(pkFPS);
    setLayout(pkVLayout);
}

CenterView::~CenterView()
{

}
