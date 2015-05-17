////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   Console.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "Console.h"

Console::Console(QWidget* pkParent)
    : QWidget(pkParent)
{
    m_pkLogBox = new QTextEdit();
    m_pkLogBox->setMinimumHeight(28);
    m_pkLogBox->setReadOnly(true);
    QVBoxLayout* pkVLayout = new QVBoxLayout();
    pkVLayout->setMargin(0);
    pkVLayout->setSpacing(0);
    pkVLayout->addWidget(m_pkLogBox);
    m_pkCommandBox = new QTextEdit();
    m_pkCommandBox->setFixedHeight(22);
    m_pkCommandBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pkCommandBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pkVariables = new QPushButton(tr("..."));
    m_pkVariables->setFixedWidth(25);
    m_pkVariables->setFixedHeight(22);
    QHBoxLayout* pkHLayout = new QHBoxLayout();
    pkHLayout->setMargin(0);
    pkHLayout->setSpacing(0);
    pkHLayout->addWidget(m_pkCommandBox);
    pkHLayout->addWidget(m_pkVariables);
    pkVLayout->addLayout(pkHLayout);
    setLayout(pkVLayout);
}

Console::~Console()
{

}

QSize Console::sizeHint() const
{
    return minimumSizeHint();
}
