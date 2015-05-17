////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   SceneEditor.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "SceneEditor.h"
#include "MainWindow.h"
#include "CenterView.h"
#include "Console.h"
#include "RollupBar.h"
#ifdef Q_WS_WIN
#define VE_PLATFORM_WIN
#endif
#include <VenusEditor.h>

extern MainWindow* g_pkWindow;

void SetFPS(const char* pcFPS)
{
    g_pkWindow->m_pkCenterView->pkFPS->setText(pcFPS);
}

void AppendLog(const char* pcLog)
{
    QTextEdit* pkLogBox = g_pkWindow->m_pkConsole->m_pkLogBox;
    pkLogBox->append(pcLog);
    QTextCursor kCursor = pkLogBox->textCursor();
    kCursor.movePosition(QTextCursor::End);
    pkLogBox->setTextCursor(kCursor);
}

#ifdef Q_WS_WIN

SceneEditorD3D11::SceneEditorD3D11(QWidget* pkParent)
    : QWidget(pkParent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    VeEditorSetLogFunc(AppendLog);
}

SceneEditorD3D11::~SceneEditorD3D11()
{
    VeEditorRendererTerm();
    VeEditorTermD3D11();
}

QPaintEngine* SceneEditorD3D11::paintEngine() const
{
    return NULL;
}

void SceneEditorD3D11::paintEvent(QPaintEvent*)
{
    if(!VeEditorHasRenderer())
    {
        VeEditorInitD3D11(winId());
        VeEditorRendererInit();
        VeEditorSetFPSFunc(&SetFPS);
        QTimer* pkTimer = new QTimer(this);
        connect(pkTimer, SIGNAL(timeout()), this, SLOT(OnUpdateFrame()));
        pkTimer->start(5);
    }
}

void SceneEditorD3D11::resizeEvent(QResizeEvent* pkEvent)
{
    VeEditorResize(pkEvent->size().width(), pkEvent->size().height());
}

void SceneEditorD3D11::OnUpdateFrame()
{
    VeEditorUpdateFrame();
}

#endif

SceneEditorOGL::SceneEditorOGL(QWidget* pkParent)
    : QGLWidget(pkParent)
{
    VeEditorSetLogFunc(AppendLog);
}

SceneEditorOGL::~SceneEditorOGL()
{
    VeEditorRendererTerm();
    VeEditorTerm();
}

void SceneEditorOGL::initializeGL()
{
    if(!VeEditorHasRenderer())
    {
        VeEditorInit();
        VeEditorRendererInit();
        VeEditorSetFPSFunc(&SetFPS);
        QTimer* pkTimer = new QTimer(this);
        connect(pkTimer, SIGNAL(timeout()), this, SLOT(update()));
        pkTimer->start(5);
    }
}

void SceneEditorOGL::paintGL()
{
    VeEditorUpdateFrame();
}

void SceneEditorOGL::resizeGL(int iWidth, int iHeight)
{
    VeEditorResize(iWidth, iHeight);
}
