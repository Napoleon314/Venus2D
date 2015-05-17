////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   NewDialog.h
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include "ui_NewDialog.h"

class NewDialog : public QDialog, public Ui::NewDialog
{
    Q_OBJECT
    
public:
    enum NewType
    {
        TYPE_MATERIAL,
        TYPE_UNKNOWN
    };

    explicit NewDialog(QWidget *parent = 0);

    QStandardItemModel* m_pkModel;
    NewType m_eType;

private slots:
    void itemClicked(QModelIndex index);

};
