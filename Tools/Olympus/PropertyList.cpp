////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   PropertyList.cpp
//  Version:     v1.00
//  Created:     15/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "PropertyList.h"

PropertyString::PropertyString(QWidget* pkParent, Callback pfuncCallback, void* pvData)
    : QLineEdit(pkParent), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(OnChange(QString)));
}

void PropertyString::OnChange(const QString& kValue)
{
    if(m_pfuncCallback)
    {
        m_pfuncCallback(kValue, m_pvData);
    }
}

PropertyBool::PropertyBool(QWidget* pkParent, Callback pfuncCallback, void* pvData)
    : QCheckBox(pkParent), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{
    connect(this, SIGNAL(toggled(bool)), this, SLOT(OnChange(bool)));
}

void PropertyBool::OnChange(bool bState)
{
    if(m_pfuncCallback)
    {
        m_pfuncCallback(bState, m_pvData);
    }
}

PropertyInt::PropertyInt(QWidget* pkParent, int iValue, int iMin, int iMax, Callback pfuncCallback, void* pvData)
    : QSpinBox(pkParent), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{
    setMinimum(iMin);
    setMaximum(iMax);
    setValue(iValue);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(OnChange(int)));
}

void PropertyInt::OnChange(int iValue)
{
    if(m_pfuncCallback)
    {
        m_pfuncCallback(iValue, m_pvData);
    }
}

PropertyFloat::PropertyFloat(QWidget* pkParent, float fValue, float fMin, float fMax, float fStep, Callback pfuncCallback, void* pvData)
    : QDoubleSpinBox(pkParent), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{
    setMinimum(fMin);
    setMaximum(fMax);
    setSingleStep(fStep);
    setValue(fValue);
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(OnChange(double)));
}

void PropertyFloat::OnChange(double dValue)
{
    if(m_pfuncCallback)
    {
        m_pfuncCallback(dValue, m_pvData);
    }
}

PropertyEnum::PropertyEnum(QWidget* pkParent, const QStringList& kNames, const QVector<int>& kValues, int iInit, Callback pfuncCallback, void* pvData)
    : QComboBox(pkParent), m_kValues(kValues), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{
    for(QStringList::const_iterator it = kNames.begin(); it != kNames.end(); ++it)
    {
        addItem(*it);
    }
    setCurrentIndex(0);
    for(int i(0); i < kValues.size(); ++i)
    {
        if(kValues[i] == iInit) setCurrentIndex(i);
    }

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChange(int)));
}

void PropertyEnum::OnChange(int iValue)
{
    if(m_pfuncCallback)
    {
        m_pfuncCallback(m_kValues[iValue], m_pvData);
    }
}

PropertyMask::PropertyMask(QWidget* pkParent, const QVector< QPair<QString,int> >& kValues, Callback pfuncCallback, void* pvData)
    : QLabel(pkParent), m_kValues(kValues), m_pfuncCallback(pfuncCallback), m_pvData(pvData)
{

}

void PropertyMask::OnUpdateLabel()
{
    QString kValue;
    Q_ASSERT(m_kValues.size());
    for(int i(0); i < m_kCheckArray.size(); ++i)
    {
        if(m_kCheckArray[i]->isChecked())
        {
            if(kValue != "")
            {
                kValue += tr("|");
            }
            kValue += m_kValues[i].first;
        }
    }
    if(kValue == "")
    {
        kValue = tr("none");
    }
    setText(kValue);
}

void PropertyMask::OnChange()
{
    OnUpdateLabel();
    if(m_pfuncCallback)
    {
        int iValue = 0;
        for(int i(0); i < m_kCheckArray.size(); ++i)
        {
            if(m_kCheckArray[i]->isChecked())
            {
                iValue |= 1 << (m_kValues[i].second);
            }
        }
        m_pfuncCallback(iValue, m_pvData);
    }
}

PropertyList::PropertyList(QWidget *parent)
    : QTreeWidget(parent)
{
    setColumnCount(2);
    QStringList kLabels;
    kLabels << tr("Property") << tr("Value");
    setHeaderLabels(kLabels);
}

PropertyList::~PropertyList()
{
    Clear();
}

void PropertyList::AddType(const QString& kName)
{
    QTreeWidgetItem* pkType = new QTreeWidgetItem(this);
    pkType->setText(0, kName);
    pkType->setExpanded(true);
    addTopLevelItem(pkType);
}

void PropertyList::DelItem(QTreeWidgetItem* pkItem)
{
    while(pkItem->childCount())
    {
        QTreeWidgetItem* pkChild = pkItem->child(0);
        QWidget* pkWidget = itemWidget(pkChild, 1);
        if(pkWidget)
        {
            removeItemWidget(pkChild, 1);
            delete pkWidget;
        }
        pkItem->takeChild(0);
        DelItem(pkChild);
        delete pkChild;
    }
}

void PropertyList::DelType(int iType)
{
    if(iType < topLevelItemCount())
    {
        DelItem(topLevelItem(iType));
        delete takeTopLevelItem(iType);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, const QString& kValue, PropertyString::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        QLineEdit* pkEdit = new PropertyString(this, pfuncCallback, pvData);
        pkEdit->setText(kValue);
        setItemWidget(pkChildren, 1, pkEdit);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, bool bValue, PropertyBool::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        QCheckBox* pkEdit = new PropertyBool(this, pfuncCallback, pvData);
        pkEdit->setChecked(bValue);
        setItemWidget(pkChildren, 1, pkEdit);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, int iInitValue, int iMinValue, int iMaxValue, PropertyInt::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        QSpinBox* pkEdit = new PropertyInt(this, iInitValue, iMinValue, iMaxValue, pfuncCallback, pvData);
        setItemWidget(pkChildren, 1, pkEdit);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, float fInitValue, float fMinValue, float fMaxValue, float fStep, PropertyFloat::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        QDoubleSpinBox* pkEdit = new PropertyFloat(this, fInitValue, fMinValue, fMaxValue, fStep, pfuncCallback, pvData);
        setItemWidget(pkChildren, 1, pkEdit);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, const QStringList& kNames, const QVector<int>& kValues, int iInit, PropertyInt::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        QComboBox* pkEdit = new PropertyEnum(this, kNames, kValues, iInit, pfuncCallback, pvData);
        setItemWidget(pkChildren, 1, pkEdit);
    }
}

void PropertyList::AddProperty(int iType, const QString& kProperty, const QVector< QPair<QString,int> >& kValues, int iInit, PropertyInt::Callback pfuncCallback, void* pvData)
{
    if(iType < topLevelItemCount())
    {
        QTreeWidgetItem* pkItem = topLevelItem(iType);
        QTreeWidgetItem* pkChildren = new QTreeWidgetItem(pkItem);
        pkChildren->setText(0, kProperty);
        PropertyMask* pkMask = new PropertyMask(this, kValues, pfuncCallback, pvData);
        setItemWidget(pkChildren, 1, pkMask);
        for(int i(0); i < kValues.size(); ++i)
        {
            const QPair<QString,int>& kPair = kValues[i];
            QCheckBox* pkCheckBox = new QCheckBox(this);
            pkCheckBox->setChecked(iInit & (1 << kPair.second));
            QTreeWidgetItem* pkSubItem = new QTreeWidgetItem(pkChildren);
            pkSubItem->setText(0, kPair.first);
            setItemWidget(pkSubItem, 1, pkCheckBox);
            pkMask->m_kCheckArray.push_back(pkCheckBox);
            connect(pkCheckBox, SIGNAL(stateChanged(int)), pkMask, SLOT(OnChange()));
        }
        pkMask->OnUpdateLabel();
    }
}

void PropertyList::Clear()
{
    while(topLevelItemCount())
    {
        DelType(0);
    }
}
