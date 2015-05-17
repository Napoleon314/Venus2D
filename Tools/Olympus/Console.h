////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   Console.h
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

class Console : public QWidget
{
    Q_OBJECT
    
public:
    Console(QWidget* pkParent = NULL);
    ~Console();

    virtual QSize sizeHint() const;

    QTextEdit* m_pkLogBox;
    QTextEdit* m_pkCommandBox;
    QPushButton* m_pkVariables;

};
