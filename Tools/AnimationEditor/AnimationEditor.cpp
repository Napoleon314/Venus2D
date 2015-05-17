#include "AnimationEditor.h"
#include <QThread>
#include <QAction>
#include <QToolBar>
#include <QSettings>
#include <QCloseEvent>
#include <QMenuBar>
#include <QStatusBar>

//--------------------------------------------------------------------------
AnimationEditor::AnimationEditor(QWidget* pkParent)
    : QMainWindow(pkParent)
{

    setMinimumSize(800, 600);
    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreateStatusBar();
    CreateDockWindows();
    setWindowTitle(tr("AnimationEditor"));
    setMinimumSize(640, 480);
    resize(800, 600);
    setUnifiedTitleAndToolBarOnMac(true);
    ReadSettings();
    QThread::sleep(1);
}
//--------------------------------------------------------------------------
AnimationEditor::~AnimationEditor()
{

}
//--------------------------------------------------------------------------
void AnimationEditor::closeEvent(QCloseEvent* pkEvent)
{
    WriteSettings();
    pkEvent->accept();
}
//--------------------------------------------------------------------------
void AnimationEditor::ReadSettings()
{
    QSettings kSettings("Venus Interaction Entertainment Inc.", "AnimationEditor");
    restoreGeometry(kSettings.value("geometry").toByteArray());
}
//--------------------------------------------------------------------------
void AnimationEditor::WriteSettings()
{
    QSettings kSettings("Venus Interaction Entertainment Inc.", "AnimationEditor");
    kSettings.setValue("geometry", saveGeometry());
}
//--------------------------------------------------------------------------
void AnimationEditor::CreateActions()
{
    m_pkNewAct = new QAction(QIcon("://res/saveas.png"), tr("&New"), this);
    m_pkNewAct->setShortcuts(QKeySequence::New);
    m_pkNewAct->setStatusTip(tr("NewActTip"));
    connect(m_pkNewAct, SIGNAL(triggered()), this, SLOT(OnNewAct()));
}
//--------------------------------------------------------------------------
void AnimationEditor::CreateMenus()
{
    m_pkFileMenu = menuBar()->addMenu(tr("&File"));
    m_pkFileMenu->addAction(m_pkNewAct);
}
//--------------------------------------------------------------------------
void AnimationEditor::CreateToolBars()
{
    m_pkFileToolBar = addToolBar(tr("&File"));
    m_pkFileToolBar->addAction(m_pkNewAct);
}
//--------------------------------------------------------------------------
void AnimationEditor::CreateStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
    connect(statusBar(), SIGNAL(messageChanged(const QString&)), this, SLOT(OnStatusBarChanged(const QString&)));
}
//--------------------------------------------------------------------------
void AnimationEditor::CreateDockWindows()
{

}
//--------------------------------------------------------------------------
void AnimationEditor::OnStatusBarChanged(const QString& kStatus)
{
    if(kStatus == "")
    {
        statusBar()->showMessage(tr("Ready"));
    }
}
//--------------------------------------------------------------------------
void AnimationEditor::OnNewAct()
{

}
//--------------------------------------------------------------------------
