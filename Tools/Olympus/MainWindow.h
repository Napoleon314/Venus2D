////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   MainWindow.h
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QMainWindow>

class CenterView;
class RollupBar;
class Console;
class MaterialEditor;
class NewDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget* pkParent = NULL);
    ~MainWindow();

    void closeEvent(QCloseEvent* pkEvent);

    void CreateActions();
    void CreateMenus();
    void CreateToolBars();
    void CreateStatusBar();
    void CreateDockWindows();

    void ReadSettings();
    void WriteSettings();

    QAction* m_pkNewAct;
    QAction* m_pkOpenAct;
    QAction* m_pkSaveAct;
    QAction* m_pkSaveAsAct;
    QAction* m_pkQuitAct;

    QMenu* m_pkFileMenu;

    QToolBar* m_pkFileToolBar;

    CenterView* m_pkCenterView;
    RollupBar* m_pkRollupBar;
    Console* m_pkConsole;
    MaterialEditor* m_pkMaterialEditor;
    QDockWidget* m_pkRollupBarDock;
    QDockWidget* m_pkConsoleDock;
    QDockWidget* m_pkMaterialEditorDock;

    NewDialog* m_pkNewDialog;

private slots:
    void OnNewAct();
    void OnOpenAct();

    void OnStatusBarChanged(const QString& kStatus);

public slots:
    void OnMaterialChanged(const QString& kName);

};
