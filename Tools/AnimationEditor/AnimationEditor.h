#pragma once

#include <QMainWindow>

class AnimationEditor : public QMainWindow
{
    Q_OBJECT
public:
    AnimationEditor(QWidget* pkParent = NULL);

    ~AnimationEditor();

    void closeEvent(QCloseEvent* pkEvent);

    void ReadSettings();

    void WriteSettings();

    void CreateActions();

    void CreateMenus();

    void CreateToolBars();

    void CreateStatusBar();

    void CreateDockWindows();

    QAction* m_pkNewAct;

    QMenu* m_pkFileMenu;

    QToolBar* m_pkFileToolBar;

    //CenterView* m_pkCenterView;

private slots:
    void OnStatusBarChanged(const QString& kStatus);

    void OnNewAct();

};
