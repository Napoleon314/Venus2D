////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   MainWindow.cpp
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
#include "RollupBar.h"
#include "CenterView.h"
#include "Console.h"
#include "NewDialog.h"
#include "MaterialEditor.h"

MainWindow::MainWindow(QWidget* pkParent)
    : QMainWindow(pkParent)
{
    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreateStatusBar();
    CreateDockWindows();
    setWindowTitle(tr("Olympus"));
    setMinimumSize(640, 480);
    resize(1024,768);
    ReadSettings();
    setUnifiedTitleAndToolBarOnMac(true);

    m_pkNewDialog = new NewDialog(this);
}

MainWindow::~MainWindow()
{
    delete m_pkNewDialog;
}

void MainWindow::closeEvent(QCloseEvent* pkEvent)
{
    WriteSettings();
    pkEvent->accept();
}

void MainWindow::CreateActions()
{
    m_pkNewAct = new QAction(QIcon(":/Resource/new.png"), tr("&New..."), this);
    m_pkNewAct->setShortcuts(QKeySequence::New);
    m_pkNewAct->setStatusTip(tr("Create a new document"));
    connect(m_pkNewAct, SIGNAL(triggered()), this, SLOT(OnNewAct()));

    m_pkOpenAct = new QAction(QIcon(":/Resource/open.png"), tr("&Open..."), this);
    m_pkOpenAct->setShortcut(QKeySequence::Open);
    m_pkOpenAct->setStatusTip(tr("Open an existing document"));
    connect(m_pkOpenAct, SIGNAL(triggered()), this, SLOT(OnOpenAct()));

    m_pkQuitAct = new QAction(QIcon(":/Resource/quit.png"), tr("&Quit"), this);
    m_pkQuitAct->setShortcut(tr("Ctrl+Q"));
    m_pkQuitAct->setStatusTip(tr("Quit the application;prompts to save documents"));
    connect(m_pkQuitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::CreateMenus()
{
    m_pkFileMenu = menuBar()->addMenu(tr("&File"));
    m_pkFileMenu->addAction(m_pkNewAct);
    m_pkFileMenu->addAction(m_pkOpenAct);

    m_pkFileMenu->addSeparator();
    m_pkFileMenu->addAction(m_pkQuitAct);
}

void MainWindow::CreateToolBars()
{
    m_pkFileToolBar = addToolBar(tr("&File"));
    m_pkFileToolBar->addAction(m_pkNewAct);
    m_pkFileToolBar->addAction(m_pkOpenAct);
}

void MainWindow::CreateStatusBar()
{
    OnStatusBarChanged(tr(""));
    connect(statusBar(), SIGNAL(messageChanged(const QString&)), this, SLOT(OnStatusBarChanged(const QString&)));
}

void MainWindow::CreateDockWindows()
{
    m_pkCenterView = new CenterView();
    setCentralWidget(m_pkCenterView);

    QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
    QMainWindow::setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
    QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    m_pkRollupBarDock = new QDockWidget(tr("RollupBar"), this);
    m_pkRollupBar = new RollupBar(m_pkRollupBarDock);
    m_pkRollupBarDock->setWidget(m_pkRollupBar);
    addDockWidget(Qt::RightDockWidgetArea, m_pkRollupBarDock);

    m_pkConsoleDock = new QDockWidget(tr("Console"), this);
    m_pkConsoleDock->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_pkConsole = new Console(m_pkConsoleDock);
    m_pkConsoleDock->setWidget(m_pkConsole);
    addDockWidget(Qt::BottomDockWidgetArea, m_pkConsoleDock);

    m_pkMaterialEditorDock = new QDockWidget(tr("Material Editor"), this);
    m_pkMaterialEditorDock->setMinimumSize(640, 480);
    m_pkMaterialEditorDock->resize(800,600);
    m_pkMaterialEditor = new MaterialEditor(m_pkMaterialEditorDock);
    m_pkMaterialEditorDock->setWidget(m_pkMaterialEditor);
    addDockWidget(Qt::BottomDockWidgetArea, m_pkMaterialEditorDock);
    m_pkMaterialEditorDock->setFloating(true);
    m_pkMaterialEditorDock->setAllowedAreas((Qt::DockWidgetAreas)0);
    //m_pkMaterialEditorDock->setVisible(false);
    m_pkMaterialEditor->m_pkToolBar->addAction(m_pkNewAct);
    m_pkMaterialEditor->m_pkToolBar->addAction(m_pkOpenAct);
    m_pkMaterialEditor->InitActions();

    //m_pkMaterialEditor->setContextMenuPolicy(Qt::ActionsContextMenu);
    //m_pkMaterialEditor->addAction(m_pkNewAct);

    connect(m_pkMaterialEditor->m_pkTabWidget, SIGNAL(selected(const QString&)), this, SLOT(OnMaterialChanged(const QString&)));
}

void MainWindow::ReadSettings()
{
    QSettings kSettings("Venus Interaction Entertainment Inc.", "Olympus");
    restoreGeometry(kSettings.value("geometry").toByteArray());
    //restoreState(kSettings.value("dockstate").toByteArray());

    //qDebug()<<kSettings.value("API").toInt();
}

void MainWindow::WriteSettings()
{
    QSettings kSettings("Venus Interaction Entertainment Inc.", "Olympus");
    kSettings.setValue("geometry", saveGeometry());
    //kSettings.setValue("dockstate", saveState());
}

void MainWindow::OnNewAct()
{
    if(isActiveWindow())
    {
        if(m_pkNewDialog->exec() == QDialog::Accepted)
        {
            m_pkMaterialEditor->NewMaterial();
            m_pkMaterialEditorDock->setVisible(true);
            m_pkMaterialEditorDock->activateWindow();
        }
    }
    else if(m_pkMaterialEditorDock->isActiveWindow())
    {
        m_pkMaterialEditor->NewMaterial();
    }
}

void MainWindow::OnOpenAct()
{
    if(isActiveWindow())
    {
        qDebug()<<"OnOpenAct";
        return;
    }
    else if(m_pkMaterialEditorDock->isActiveWindow())
    {
        QString kFileName = QFileDialog::getOpenFileName(this,
            tr("Open Material"), ".", tr("Material (*.mat)"));
        if(kFileName.isEmpty()) return;
        QFile kFile(kFileName);
        if(kFile.open(QFile::ReadOnly))
        {
            QDataStream kInput(&kFile);
            kInput.setByteOrder(QDataStream::LittleEndian);
            const char* pcName = kFileName;
            pcName += kFileName.findRev('/') + 1;
            quint32 u32FileID;
            kInput >> u32FileID;
            if(u32FileID == ('V' | 'M' << 8 | 'A' << 16 | 'T' << 24))
            {
                m_pkMaterialEditor->OpenMaterial(pcName, kInput);
            }
        }
    }
}

void MainWindow::OnStatusBarChanged(const QString& kStatus)
{
    if(kStatus == "")
    {
        statusBar()->showMessage(tr("Ready"));
    }
}

void MainWindow::OnMaterialChanged(const QString& kName)
{
    if(kName == "")
    {
        m_pkMaterialEditorDock->setWindowTitle(tr("Material Editor"));
    }
    else
    {
        m_pkMaterialEditorDock->setWindowTitle(QString("[%1] - %2").arg(kName, tr("Material Editor")));
    }
}
