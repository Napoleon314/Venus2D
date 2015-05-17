////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   PropertyList.h
//  Version:     v1.00
//  Created:     15/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QtGui>

class PropertyString : public QLineEdit
{
    Q_OBJECT
public:
    typedef void (*Callback)(const QString& kValue, void* pvData);

    PropertyString(QWidget* pkParent, Callback pfuncCallback = NULL, void* pvData = NULL);

    Callback m_pfuncCallback;
    void* m_pvData;

public slots:
    void OnChange(const QString& kValue);

};

class PropertyBool : public QCheckBox
{
    Q_OBJECT
public:
    typedef void (*Callback)(bool bValue, void* pvData);

    PropertyBool(QWidget* pkParent, Callback pfuncCallback = NULL, void* pvData = NULL);

    Callback m_pfuncCallback;
    void* m_pvData;

public slots:
    void OnChange(bool bState);

};

class PropertyInt : public QSpinBox
{
    Q_OBJECT
public:
    typedef void (*Callback)(int iValue, void* pvData);

    PropertyInt(QWidget* pkParent, int iValue, int iMin, int iMax, Callback pfuncCallback = NULL, void* pvData = NULL);

    Callback m_pfuncCallback;
    void* m_pvData;

public slots:
    void OnChange(int iValue);

};

class PropertyFloat : public QDoubleSpinBox
{
    Q_OBJECT
public:
    typedef void (*Callback)(float fValue, void* pvData);

    PropertyFloat(QWidget* pkParent, float fValue, float fMin, float fMax, float fStep, Callback pfuncCallback = NULL, void* pvData = NULL);

    Callback m_pfuncCallback;
    void* m_pvData;

public slots:
    void OnChange(double dValue);

};

class PropertyEnum : public QComboBox
{
    Q_OBJECT
public:
    typedef void (*Callback)(int iValue, void* pvData);

    PropertyEnum(QWidget* pkParent, const QStringList& kNames, const QVector<int>& kValues, int iInit, Callback pfuncCallback = NULL, void* pvData = NULL);

    QVector<int> m_kValues;
    Callback m_pfuncCallback;
    void* m_pvData;

public slots:
    void OnChange(int iValue);
};

class PropertyMask : public QLabel
{
    Q_OBJECT
public:
    typedef void (*Callback)(int iValue, void* pvData);

    PropertyMask(QWidget* pkParent, const QVector< QPair<QString,int> >& kValues, Callback pfuncCallback = NULL, void* pvData = NULL);

    void OnUpdateLabel();

    QVector< QPair<QString,int> > m_kValues;
    Callback m_pfuncCallback;
    void* m_pvData;
    QVector<QCheckBox*> m_kCheckArray;

public slots:
    void OnChange();

};

class PropertyList : public QTreeWidget
{
    Q_OBJECT
public:
    explicit PropertyList(QWidget *parent = NULL);

    ~PropertyList();

    void AddType(const QString& kName);

    void DelType(int iType);

    void AddProperty(int iType, const QString& kProperty, const QString& kValue, PropertyString::Callback pfuncCallback = NULL, void* pvData = NULL);

    void AddProperty(int iType, const QString& kProperty, bool bValue, PropertyBool::Callback pfuncCallback = NULL, void* pvData = NULL);

    void AddProperty(int iType, const QString& kProperty, int iInitValue, int iMinValue, int iMaxValue, PropertyInt::Callback pfuncCallback = NULL, void* pvData = NULL);

    void AddProperty(int iType, const QString& kProperty, float fInitValue, float fMinValue, float fMaxValue, float fStep, PropertyFloat::Callback pfuncCallback = NULL, void* pvData = NULL);

    void AddProperty(int iType, const QString& kProperty, const QStringList& kNames, const QVector<int>& kValues, int iInit, PropertyInt::Callback pfuncCallback = NULL, void* pvData = NULL);

    void AddProperty(int iType, const QString& kProperty, const QVector< QPair<QString,int> >& kValues, int iInit, PropertyInt::Callback pfuncCallback = NULL, void* pvData = NULL);

    void Clear();
    
private:
    void DelItem(QTreeWidgetItem* pkItem);
    
};
