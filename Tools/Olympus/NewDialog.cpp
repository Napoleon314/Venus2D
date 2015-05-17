////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   NewDialog.cpp
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "NewDialog.h"

NewDialog::NewDialog(QWidget *parent)
    : QDialog(parent), m_eType(TYPE_UNKNOWN)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    m_pkModel = new QStandardItemModel(this);
    listView->setModel(m_pkModel);
    QStandardItem* pkItem = new QStandardItem(QIcon(":/Resource/material.png"), tr("Material"));
    pkItem->setEditable(false);
    m_pkModel->appendRow(pkItem);

    connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
}

void NewDialog::itemClicked(QModelIndex index)
{
    if(index.row() < TYPE_UNKNOWN)
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        m_eType = (NewType)index.row();
    }
}
