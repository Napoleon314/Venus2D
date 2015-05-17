////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   MaterialEditor.h
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QtGui>

class MaterialDoc;

class AddRenderObjectDialog : public QDialog
{
    Q_OBJECT

public:
    enum Type
    {
        TYPE_BLEND_STATE,
        TYPE_DEPTH_STENCIL_STATE,
        TYPE_RASTERIZE_STATE,
        TYPE_SAMPLER_STATE,
        TYPE_INPUT_LAYOUT,
        TYPE_VERTEX_SHADER,
        TYPE_PIXEL_SHADER,

        TYPE_MAX
    };

    AddRenderObjectDialog(QWidget* pkParent = NULL);

    void ClearNameEdit();

    int Start();

    QLineEdit* m_pkNameEdit;
    QComboBox* m_pkComboBox;
    QDialogButtonBox* m_pkButtons;
    int m_iIndex;

public slots:
    void OnIndexChanged(int iIndex);

    void OnTextChanged(const QString& kString);

};

class AddNodeDataDialog : public QDialog
{
    Q_OBJECT
public:
    AddNodeDataDialog(QWidget* pkParent = NULL);

    void ClearNameEdit();

    int Start();

    QLineEdit* m_pkNameEdit;
    QDialogButtonBox* m_pkButtons;

public slots:
    void OnTextChanged(const QString& kString);

};

class AddRenderTick : public QDialog
{
    Q_OBJECT
public:
    AddRenderTick(QWidget* pkParent = NULL);

    void ClearEdit();

    int Start();

    QVBoxLayout* m_pkLayout;
    QComboBox* m_pkComboBox;
    QDialogButtonBox* m_pkButtons;
    int m_iIndex;

public slots:
    void OnTypeChanged(int iIndex);

};

class MaterialEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MaterialEditor(QWidget *parent = 0);
    ~MaterialEditor();

    unsigned int m_uiNewCount;

    QToolBar* m_pkToolBar;
    QTabWidget* m_pkTabWidget;
    AddRenderObjectDialog* m_pkAddObjectDialog;
    AddNodeDataDialog* m_pkAddNodeDataDialog;
    AddRenderTick* m_pkRenderTick;

    QAction* m_pkSaveAsDoc;
    QAction* m_pkCloseDoc;
    QAction* m_pkAdd;
    QAction* m_pkDelete;

    void InitActions();

    void Close(int iIndex);

    void UpdateClose();

public slots:
    void NewMaterial();

    void OpenMaterial(const char* pcName, QDataStream& kStream);
    
    void ShowContextMenu(const QPoint& kPos);

    void OnCloseAct();

    void OnTableChanged(int iIndex);

    void OnCurrentItemChanged(QTreeWidgetItem* pkCur);

    void OnAdd();

    void OnSaveAs();

public:
    int m_iCurTable;

};
