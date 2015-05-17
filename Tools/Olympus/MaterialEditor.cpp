////////////////////////////////////////////////////////////////////////////
//
//  Olympus Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   MaterialEditor.cpp
//  Version:     v1.00
//  Created:     2/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "MaterialEditor.h"
#include "MaterialDoc.h"

class TabBarShell : public QTabWidget
{
public:
    QTabBar* GetTabBar()
    {
        return tabBar();
    }
};

AddRenderObjectDialog::AddRenderObjectDialog(QWidget* pkParent)
    : QDialog(pkParent), m_iIndex(0)
{
    setWindowTitle(tr("Add Render Object"));
    setMinimumWidth(250);
    setModal(true);

    QLabel* pkLabel = new QLabel(this);
    pkLabel->setText(tr("Name:"));

    m_pkNameEdit = new QLineEdit(this);

    QHBoxLayout* pkNameEditLayout = new QHBoxLayout;
    pkNameEditLayout->addWidget(pkLabel);
    pkNameEditLayout->addWidget(m_pkNameEdit);

    m_pkComboBox = new QComboBox(this);
    m_pkComboBox->addItem(tr("Blend State"));
    m_pkComboBox->addItem(tr("Depth Stencil State"));
    m_pkComboBox->addItem(tr("Rasterize State"));
    m_pkComboBox->addItem(tr("Sampler State"));
    m_pkComboBox->addItem(tr("Input Layout"));
    //m_pkComboBox->addItem(tr("Vertex Shader"));
    //m_pkComboBox->addItem(tr("Pixel Shader"));
    m_pkComboBox->setCurrentIndex(0);
    m_pkButtons = new QDialogButtonBox(this);
    m_pkButtons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout* pkLayout = new QVBoxLayout;
    pkLayout->addLayout(pkNameEditLayout);
    pkLayout->addWidget(m_pkComboBox);
    pkLayout->addWidget(m_pkButtons);
    setLayout(pkLayout);

    connect(m_pkNameEdit, SIGNAL(textChanged(QString)), this, SLOT(OnTextChanged(QString)));
    connect(m_pkButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_pkButtons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_pkComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnIndexChanged(int)));
}

void AddRenderObjectDialog::ClearNameEdit()
{
    m_pkNameEdit->setText(tr(""));
    m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
}

int AddRenderObjectDialog::Start()
{
    ClearNameEdit();
    return exec();
}

void AddRenderObjectDialog::OnIndexChanged(int iIndex)
{
    m_iIndex = iIndex;
}

void AddRenderObjectDialog::OnTextChanged(const QString& kString)
{
    if(kString == "")
    {
        m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

AddNodeDataDialog::AddNodeDataDialog(QWidget* pkParent)
    : QDialog(pkParent)
{
    setWindowTitle(tr("Add Node Data"));
    setMinimumWidth(250);
    setModal(true);

    QLabel* pkLabel = new QLabel(this);
    pkLabel->setText(tr("Name:"));

    m_pkNameEdit = new QLineEdit(this);

    QHBoxLayout* pkNameEditLayout = new QHBoxLayout;
    pkNameEditLayout->addWidget(pkLabel);
    pkNameEditLayout->addWidget(m_pkNameEdit);

    m_pkButtons = new QDialogButtonBox(this);
    m_pkButtons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout* pkLayout = new QVBoxLayout;
    pkLayout->addLayout(pkNameEditLayout);
    pkLayout->addWidget(m_pkButtons);
    setLayout(pkLayout);

    connect(m_pkNameEdit, SIGNAL(textChanged(QString)), this, SLOT(OnTextChanged(QString)));
    connect(m_pkButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_pkButtons, SIGNAL(rejected()), this, SLOT(reject()));
}

void AddNodeDataDialog::ClearNameEdit()
{
    m_pkNameEdit->setText(tr(""));
    m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
}

int AddNodeDataDialog::Start()
{
    ClearNameEdit();
    return exec();
}

void AddNodeDataDialog::OnTextChanged(const QString& kString)
{
    if(kString == "")
    {
        m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        m_pkButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

AddRenderTick::AddRenderTick(QWidget* pkParent)
    : QDialog(pkParent), m_iIndex(0)
{
    setWindowTitle(tr("Add Render Tick"));
    setMinimumWidth(250);
    setModal(true);

    m_pkComboBox = new QComboBox(this);
    m_pkComboBox->addItem(tr("IA_INDEX_BUFFER"));
    m_pkComboBox->addItem(tr("IA_INPUT_LAYOUT"));
    m_pkComboBox->addItem(tr("IA_PRIMITIVE_TOPOLOGY"));
    m_pkComboBox->addItem(tr("IA_VERTEX_BUFFER"));
    m_pkComboBox->addItem(tr("VS_CONSTANT_BUFFER"));
    m_pkComboBox->addItem(tr("VS_SHADER"));
    m_pkComboBox->addItem(tr("RS_SCISSOR_RECT"));
    m_pkComboBox->addItem(tr("RS_STATE"));
    m_pkComboBox->addItem(tr("RS_VIEWPORT"));
    m_pkComboBox->addItem(tr("PS_SAMPLER"));
    m_pkComboBox->addItem(tr("PS_SHADER"));
    m_pkComboBox->addItem(tr("PS_SHADER_RESOURCE"));
    m_pkComboBox->addItem(tr("OM_BLEND_STATE"));
    m_pkComboBox->addItem(tr("OM_DEPTH_STENCIL_STATE"));
    m_pkComboBox->addItem(tr("OM_RENDER_TARGET_VIEW"));
    m_pkComboBox->addItem(tr("OM_DEPTH_STENCIL_VIEW"));
    m_pkComboBox->setCurrentIndex(0);

    m_pkButtons = new QDialogButtonBox(this);
    m_pkButtons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_pkLayout = new QVBoxLayout(this);
    m_pkLayout->addWidget(m_pkComboBox);
    m_pkLayout->addWidget(m_pkButtons);
    setLayout(m_pkLayout);

    connect(m_pkButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_pkButtons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_pkComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTypeChanged(int)));
}

void AddRenderTick::ClearEdit()
{
    //m_pkComboBox->setCurrentIndex(0);
}

int AddRenderTick::Start()
{
    ClearEdit();
    return exec();
}

void AddRenderTick::OnTypeChanged(int iIndex)
{
    m_iIndex = iIndex;
}

MaterialEditor::MaterialEditor(QWidget* pkParent)
    : QWidget(pkParent), m_uiNewCount(0), m_iCurTable(-1)
{
    m_pkToolBar = new QToolBar("Material Editor", this);
    m_pkTabWidget = new QTabWidget(this);
    QVBoxLayout* pkVLayout = new QVBoxLayout();
    pkVLayout->setMargin(0);
    pkVLayout->setSpacing(0);
    pkVLayout->addWidget(m_pkToolBar);
    pkVLayout->addWidget(m_pkTabWidget);
    setLayout(pkVLayout);

    connect(m_pkTabWidget, SIGNAL(currentChanged(int)), this, SLOT(OnTableChanged(int)));

    QTabBar* pkBar = ((TabBarShell*)m_pkTabWidget)->GetTabBar();
    pkBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pkBar, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    m_pkAddObjectDialog = new AddRenderObjectDialog(this);
    m_pkAddNodeDataDialog = new AddNodeDataDialog(this);
    m_pkRenderTick = new AddRenderTick(this);
}

MaterialEditor::~MaterialEditor()
{

}

void MaterialEditor::InitActions()
{
    m_pkSaveAsDoc = new QAction(QIcon(":/Resource/saveas.png"), tr("Save &As..."), this);
    m_pkSaveAsDoc->setShortcut(QKeySequence::SaveAs);
    m_pkSaveAsDoc->setStatusTip(tr("Save as another document"));
    connect(m_pkSaveAsDoc, SIGNAL(triggered()), this, SLOT(OnSaveAs()));
    m_pkToolBar->addAction(m_pkSaveAsDoc);
    m_pkSaveAsDoc->setEnabled(false);

    m_pkCloseDoc = new QAction(QIcon(":/Resource/close.png"), tr("&Close..."), this);
    m_pkCloseDoc->setShortcuts(QKeySequence::Close);
    connect(m_pkCloseDoc, SIGNAL(triggered()), this, SLOT(OnCloseAct()));
    m_pkToolBar->addAction(m_pkCloseDoc);

    m_pkAdd = new QAction(QIcon(":/Resource/add.png"), tr("&Add..."), this);
    m_pkAdd->setEnabled(false);
    connect(m_pkAdd, SIGNAL(triggered()), this, SLOT(OnAdd()));
    m_pkToolBar->addAction(m_pkAdd);

    m_pkDelete = new QAction(QIcon(":/Resource/delete.png"), tr("&Delete..."), this);
    m_pkDelete->setEnabled(false);
    m_pkToolBar->addAction(m_pkDelete);

    UpdateClose();
}

void MaterialEditor::Close(int iIndex)
{
    if(iIndex >= 0 && iIndex < m_pkTabWidget->count())
    {
        MaterialDoc* pkDoc = (MaterialDoc*)(m_pkTabWidget->widget(iIndex));
        m_pkTabWidget->removeTab(iIndex);
        delete pkDoc;
    }
    UpdateClose();
    if(m_pkTabWidget->count() == 0)
    {
        m_pkSaveAsDoc->setEnabled(false);
    }
}

void MaterialEditor::UpdateClose()
{
    m_pkCloseDoc->setEnabled(m_pkTabWidget->count() > 0);
}

void MaterialEditor::NewMaterial()
{
    MaterialDoc* pkDoc = new MaterialDoc(QString("Untitled%1").arg(m_uiNewCount++), m_pkTabWidget);
    int iIndex = m_pkTabWidget->addTab(pkDoc, QIcon(":/Resource/material.png"), pkDoc->m_kName);
    m_pkTabWidget->setCurrentIndex(iIndex);
    connect(pkDoc->m_pkLeft, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(OnCurrentItemChanged(QTreeWidgetItem*)));
    UpdateClose();
    m_pkSaveAsDoc->setEnabled(true);
}

void MaterialEditor::OpenMaterial(const char* pcName, QDataStream& kStream)
{

    MaterialDoc* pkDoc = new MaterialDoc(pcName, m_pkTabWidget);
    int iIndex = m_pkTabWidget->addTab(pkDoc, QIcon(":/Resource/material.png"), pkDoc->m_kName);
    m_pkTabWidget->setCurrentIndex(iIndex);
    connect(pkDoc->m_pkLeft, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(OnCurrentItemChanged(QTreeWidgetItem*)));
    UpdateClose();
    m_pkSaveAsDoc->setEnabled(true);
    pkDoc->LoadFromStream(kStream);
}

void MaterialEditor::ShowContextMenu(const QPoint& kPos)
{
    QTabBar* pkBar = ((TabBarShell*)m_pkTabWidget)->GetTabBar();
    m_iCurTable = pkBar->tabAt(kPos);
    QMenu kMenu(this);
    kMenu.addAction(m_pkCloseDoc);
    kMenu.exec(QCursor::pos());
}

void MaterialEditor::OnCloseAct()
{
    Close(m_iCurTable);
}

void MaterialEditor::OnTableChanged(int iIndex)
{
    m_iCurTable = iIndex;
}

void MaterialEditor::OnCurrentItemChanged(QTreeWidgetItem* pkCur)
{
    MaterialDoc* pkDoc = (MaterialDoc*)(m_pkTabWidget->widget(m_iCurTable));
    pkDoc->m_pkCurrentOnProcess = pkCur;
    MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap[pkDoc->m_pkCurrentOnProcess];
    switch(kData.m_eType)
    {
    case MaterialDoc::LTYPE_ROOT:
        m_pkAdd->setEnabled(true);
        m_pkDelete->setEnabled(false);
        break;
    case MaterialDoc::LTYPE_PLATFORM:
        m_pkAdd->setEnabled(false);
        m_pkDelete->setEnabled(kData.m_uiTypeSec ? true : false);
        break;
    case MaterialDoc::LTYPE_RENDEROBJ_ROOT:
    case MaterialDoc::LTYPE_NODEDATA_ROOT:
    case MaterialDoc::LTYPE_NODE_ROOT:
    case MaterialDoc::LTYPE_MATERIAL_ROOT:
        m_pkAdd->setEnabled(true);
        m_pkDelete->setEnabled(false);
        break;
    case MaterialDoc::LTYPE_RENDEROBJ:
        m_pkAdd->setEnabled(false);
        m_pkDelete->setEnabled(true);
        break;
    case MaterialDoc::LTYPE_NODEDATA:
        m_pkAdd->setEnabled(true);
        m_pkDelete->setEnabled(false);
        break;
    default:
        m_pkAdd->setEnabled(false);
        m_pkDelete->setEnabled(false);
        break;
    }
    pkDoc->UpdateRight();
}

void MaterialEditor::OnAdd()
{
    MaterialDoc* pkDoc = (MaterialDoc*)(m_pkTabWidget->widget(m_iCurTable));
    MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap[pkDoc->m_pkCurrentOnProcess];
    switch(kData.m_eType)
    {
    case MaterialDoc::LTYPE_ROOT:
        pkDoc->CreatePlatform();
        break;
    case MaterialDoc::LTYPE_RENDEROBJ_ROOT:
        if(m_pkAddObjectDialog->Start() == QDialog::Accepted)
        {
            QTreeWidgetItem* pkRenderObj = new QTreeWidgetItem(pkDoc->m_pkCurrentOnProcess);
            MaterialDoc::LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, m_pkAddObjectDialog->m_iIndex, NULL};
            MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            switch(kData.m_uiTypeSec)
            {
            case AddRenderObjectDialog::TYPE_BLEND_STATE:
                kData.m_pkData = new MaterialDoc::BlendState(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("BlendState") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_DEPTH_STENCIL_STATE:
                kData.m_pkData = new MaterialDoc::DepthStencilState(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("DepthStencilState") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_RASTERIZE_STATE:
                kData.m_pkData = new MaterialDoc::RasterizerState(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("RasterizerState") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_SAMPLER_STATE:
                kData.m_pkData = new MaterialDoc::SamplerState(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("SamplerState") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_VERTEX_SHADER:
                kData.m_pkData = new MaterialDoc::VertexShader(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("VertexShader") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_PIXEL_SHADER:
                kData.m_pkData = new MaterialDoc::PixelShader(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("PixelShader") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            case AddRenderObjectDialog::TYPE_INPUT_LAYOUT:
                kData.m_pkData = new MaterialDoc::InputLayout(m_pkAddObjectDialog->m_pkNameEdit->text());
                pkRenderObj->setText(0, tr("InputLayout") + tr("(") + m_pkAddObjectDialog->m_pkNameEdit->text() + tr(")"));
                break;
            default:
                Q_ASSERT(0);
                break;
            }
            pkDoc->m_pkLeft->setCurrentItem(pkRenderObj);
            pkDoc->Edit();
        }
        break;
    case MaterialDoc::LTYPE_NODEDATA_ROOT:
        if(m_pkAddNodeDataDialog->Start() == QDialog::Accepted)
        {
            QTreeWidgetItem* pkNodeData = new QTreeWidgetItem(pkDoc->m_pkCurrentOnProcess);
            MaterialDoc::LeftItemData kDataInit = {MaterialDoc::LTYPE_NODEDATA, 0, NULL};
            MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap.insert(pkNodeData, kDataInit).value();
            kData.m_pkData = new MaterialDoc::NodeData(m_pkAddNodeDataDialog->m_pkNameEdit->text());
            pkNodeData->setText(0, tr("NodeData") + tr("(") + m_pkAddNodeDataDialog->m_pkNameEdit->text() + tr(")"));
            pkDoc->m_pkLeft->setCurrentItem(pkNodeData);
            pkDoc->Edit();
        }
        break;
    case MaterialDoc::LTYPE_NODEDATA:
        if(m_pkRenderTick->Start() == QDialog::Accepted)
        {
            MaterialDoc* pkDoc = (MaterialDoc*)(m_pkTabWidget->widget(m_iCurTable));
            MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap[pkDoc->m_pkCurrentOnProcess];
            MaterialDoc::NodeData* pkData = (MaterialDoc::NodeData*)(kData.m_pkData);
            switch(m_pkRenderTick->m_iIndex)
            {
            case MaterialDoc::NodeData::IA_INDEX_BUFFER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::IndexBuffer("none"));
                break;
            case MaterialDoc::NodeData::IA_INPUT_LAYOUT:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::InputLayout("none"));
                break;
            case MaterialDoc::NodeData::IA_PRIMITIVE_TOPOLOGY:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::PrimitiveTopology());
                break;
            case MaterialDoc::NodeData::IA_VERTEX_BUFFER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::VertexBuffer("none"));
                break;
            case MaterialDoc::NodeData::VS_CONSTANT_BUFFER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ConstantBufferVS("none"));
                break;
            case MaterialDoc::NodeData::VS_SHADER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ShaderVS("none"));
                break;
            case MaterialDoc::NodeData::RS_SCISSOR_RECT:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ScissorRect());
                break;
            case MaterialDoc::NodeData::RS_STATE:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::RasterizerState("none"));
                break;
            case MaterialDoc::NodeData::RS_VIEWPORT:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ViewPort());
                break;
            case MaterialDoc::NodeData::PS_SAMPLER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::SamplerPS("none"));
                break;
            case MaterialDoc::NodeData::PS_SHADER:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ShaderPS("none"));
                break;
            case MaterialDoc::NodeData::PS_SHADER_RESOURCE:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::ShaderResPS("none"));
                break;
            case MaterialDoc::NodeData::OM_BLEND_STATE:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::BlendState("none"));
                break;
            case MaterialDoc::NodeData::OM_DEPTH_STENCIL_STATE:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::DepthStencilState("none"));
                break;
            case MaterialDoc::NodeData::OM_RENDER_TARGET_VIEW:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::RenderTargetView("none"));
                break;
            case MaterialDoc::NodeData::OM_DEPTH_STENCIL_VIEW:
                pkData->m_kRenderTickArray.push_back(new MaterialDoc::NodeData::DepthStencilView("none"));
                break;
            default:
                break;
            }
            pkDoc->UpdateRight();
        }
        break;
    case MaterialDoc::LTYPE_NODE_ROOT:
        {
            QTreeWidgetItem* pkNode = new QTreeWidgetItem(pkDoc->m_pkCurrentOnProcess);
            MaterialDoc::LeftItemData kDataInit = {MaterialDoc::LTYPE_NODE, 0, NULL};
            MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap.insert(pkNode, kDataInit).value();
            kData.m_pkData = new MaterialDoc::Node();
            pkNode->setText(0, tr("Node"));
            pkDoc->m_pkLeft->setCurrentItem(pkNode);
            pkDoc->Edit();
        }
        break;
    case MaterialDoc::LTYPE_MATERIAL_ROOT:
        {
            QTreeWidgetItem* pkMaterial = new QTreeWidgetItem(pkDoc->m_pkCurrentOnProcess);
            MaterialDoc::LeftItemData kDataInit = {MaterialDoc::LTYPE_MATERIAL, 0, NULL};
            MaterialDoc::LeftItemData& kData = pkDoc->m_kLeftItemMap.insert(pkMaterial, kDataInit).value();
            kData.m_pkData = new MaterialDoc::Material();
            pkMaterial->setText(0, tr("Material"));
            pkDoc->m_pkLeft->setCurrentItem(pkMaterial);
            pkDoc->Edit();
        }
        break;
    default:
        break;
    }
}

void MaterialEditor::OnSaveAs()
{
    QString kFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), ".", tr("Material (*.mat)"));
    QFile kFile(kFileName);
    if(kFile.open(QFile::WriteOnly))
    {
        QDataStream kOut(&kFile);
        kOut.setByteOrder(QDataStream::LittleEndian);
        MaterialDoc* pkDoc = (MaterialDoc*)(m_pkTabWidget->widget(m_iCurTable));
        pkDoc->SaveToStream(kOut);
    }
}
