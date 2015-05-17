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
#include "PropertyList.h"
#include "MaterialDoc.h"
#include "MaterialEditor.h"
#include "MainWindow.h"

void DeleteItem(QTreeWidgetItem* pkItem)
{
    while(pkItem->childCount())
    {
        DeleteItem(pkItem->takeChild(0));
    }
    delete pkItem;
}

MaterialDoc::MaterialDoc(const QString& kName, QWidget* pkParent)
    : QWidget(pkParent), m_kName(kName), m_pkCurrentOnProcess(NULL), m_bEdited(false)
{
    InitLeft();
    InitRight();
    QLayout* pkHLayout = new QHBoxLayout();
    pkHLayout->addWidget(m_pkLeft);
    pkHLayout->addWidget(m_pkRight);
    setLayout(pkHLayout);
}

MaterialDoc::~MaterialDoc()
{
    CleanLeft();
    QLayout* pkLayout = layout();
    pkLayout->removeWidget(m_pkLeft);
    pkLayout->removeWidget(m_pkRight);
    delete m_pkLeft;
    delete m_pkRight;
}

void MaterialDoc::Edit()
{
    if(!m_bEdited)
    {
        m_bEdited = true;
        UpdateName();
    }
}

void MaterialDoc::InitLeft()
{
    m_pkLeft = new QTreeWidget(this);
    m_pkLeft->setHeaderLabel(tr("Object"));

    QTreeWidgetItem* pkRoot = new QTreeWidgetItem(m_pkLeft);
    pkRoot->setText(0, tr("Root"));
    pkRoot->setExpanded(true);
    LeftItemData kRootData = {LTYPE_ROOT, 0, NULL};
    m_kLeftItemMap.insert(pkRoot, kRootData);

    QTreeWidgetItem* pkGeneral = new QTreeWidgetItem(pkRoot);
    pkGeneral->setText(0, tr("General"));
    pkGeneral->setExpanded(true);
    LeftItemData kGeneralData = {LTYPE_PLATFORM, 0, NULL};
    m_kLeftItemMap.insert(pkGeneral, kGeneralData);

    QTreeWidgetItem* pkRenderObject = new QTreeWidgetItem(pkGeneral);
    pkRenderObject->setText(0, tr("RenderObject"));
    pkRenderObject->setExpanded(true);
    LeftItemData kRenderObjectData = {LTYPE_RENDEROBJ_ROOT, 0, NULL};
    m_kLeftItemMap.insert(pkRenderObject, kRenderObjectData);

    QTreeWidgetItem* pkNodeData = new QTreeWidgetItem(pkGeneral);
    pkNodeData->setText(0, tr("NodeData"));
    pkNodeData->setExpanded(true);
    LeftItemData kNodeDataData = {LTYPE_NODEDATA_ROOT, 0, NULL};
    m_kLeftItemMap.insert(pkNodeData, kNodeDataData);

    QTreeWidgetItem* pkNode = new QTreeWidgetItem(pkGeneral);
    pkNode->setText(0, tr("Node"));
    pkNode->setExpanded(true);
    LeftItemData kNodeData = {LTYPE_NODE_ROOT, 0, NULL};
    m_kLeftItemMap.insert(pkNode, kNodeData);

    QTreeWidgetItem* pkMaterial = new QTreeWidgetItem(pkGeneral);
    pkMaterial->setText(0, tr("Material"));
    pkMaterial->setExpanded(true);
    LeftItemData kMaterialData = {LTYPE_MATERIAL_ROOT, 0, NULL};
    m_kLeftItemMap.insert(pkMaterial, kMaterialData);

    m_pkLeft->addTopLevelItem(pkRoot);
    m_pkLeft->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_pkLeft, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowLeftTreeContextMenu(const QPoint&)));
    //connect(m_pkLeft, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(OnCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void MaterialDoc::InitRight()
{
    m_pkRight = new PropertyList(this);
    m_pkRight->setColumnWidth(0, 180);
}

void MaterialDoc::ShowLeftTreeContextMenu(const QPoint& kPos)
{
    m_pkCurrentOnProcess = m_pkLeft->itemAt(kPos);
    //QTreeWidgetItem* pkItem = m_pkLeft->itemAt(kPos);
    //LeftItemData& kData = m_kLeftItemMap[pkItem];
    //switch()


    qDebug() << "ShowContextMenu";
}

void MaterialDoc::CleanLeft()
{
    for(int i(0); i < m_pkLeft->topLevelItemCount(); ++i)
    {
        DeleteItem(m_pkLeft->takeTopLevelItem(i));
    }
    m_pkLeft->clear();
    m_kLeftItemMap.clear();
}

void MaterialDoc::UpdateRight()
{
    m_pkRight->Clear();
    MaterialDoc::LeftItemData& kData = m_kLeftItemMap[m_pkCurrentOnProcess];
    switch(kData.m_eType)
    {
    case LTYPE_RENDEROBJ:
        switch(kData.m_uiTypeSec)
        {
        case AddRenderObjectDialog::TYPE_BLEND_STATE:
            {
                BlendState* pkBlendState = (BlendState*)kData.m_pkData;
                m_pkRight->AddType(tr("BlendState"));
                m_pkRight->AddProperty(0, tr("name"), pkBlendState->m_kName, BlendState::OnNameChange, pkBlendState);
                m_pkRight->AddProperty(0, tr("alpha to coverage"), pkBlendState->m_u16AlphaToCoverageEnable ? true : false, BlendState::OnAlphaToCoverageEnableChange, pkBlendState);
                m_pkRight->AddProperty(0, tr("rendertarget number"), pkBlendState->m_u16NumRTDesc, 1, 8, BlendState::OnNumRTDescChange, pkBlendState);
                UpdateBlendState(pkBlendState);
            }
            break;
        case AddRenderObjectDialog::TYPE_DEPTH_STENCIL_STATE:
            {
                DepthStencilState* pkDepthState = (DepthStencilState*)kData.m_pkData;
                m_pkRight->AddType(tr("DepthStencilState"));
                m_pkRight->AddType(tr("DepthState"));
                m_pkRight->AddType(tr("StencilState"));
                UpdateDepthStencilState(pkDepthState);
            }
            break;
        case AddRenderObjectDialog::TYPE_RASTERIZE_STATE:
            {
                RasterizerState* pkRasterizerState = (RasterizerState*)kData.m_pkData;
                m_pkRight->AddType(tr("RasterizerState"));
                UpdateRasterizerState(pkRasterizerState);
            }
            break;
        case AddRenderObjectDialog::TYPE_SAMPLER_STATE:
            {
                SamplerState* pkSamplerState = (SamplerState*)kData.m_pkData;
                m_pkRight->AddType(tr("SamplerState"));
                UpdateSamplerState(pkSamplerState);
            }
            break;
        case AddRenderObjectDialog::TYPE_VERTEX_SHADER:
            {
                VertexShader* pkVertexShader = (VertexShader*)kData.m_pkData;
                m_pkRight->AddType(tr("VertexShader"));
                m_pkRight->AddProperty(0, tr("name"), pkVertexShader->m_kName, VertexShader::OnNameChange, pkVertexShader);
            }
            break;
        case AddRenderObjectDialog::TYPE_PIXEL_SHADER:
            {
                PixelShader* pkPixelShader = (PixelShader*)kData.m_pkData;
                m_pkRight->AddType(tr("PixelShader"));
                m_pkRight->AddProperty(0, tr("name"), pkPixelShader->m_kName, PixelShader::OnNameChange, pkPixelShader);
            }
            break;
        case AddRenderObjectDialog::TYPE_INPUT_LAYOUT:
            {
                InputLayout* pkInputLayout = (InputLayout*)kData.m_pkData;
                m_pkRight->AddType(tr("InputLayout"));
                m_pkRight->AddProperty(0, tr("name"), pkInputLayout->m_kName, InputLayout::OnNameChange, pkInputLayout);
                m_pkRight->AddProperty(0, tr("vertex shader"), pkInputLayout->m_kVertexShader, InputLayout::OnVertexShaderChange, pkInputLayout);
                m_pkRight->AddProperty(0, tr("number elements"), pkInputLayout->m_u32NumElements, 1, 32, InputLayout::OnNumElementsChange, pkInputLayout);
                UpdateInputLayoutElements(pkInputLayout);
            }
            break;
        default:
            break;
        }
        break;
    case LTYPE_NODEDATA:
        {
            static QStringList s_kIndexFormatEnumStr;
            static QVector<int> s_kIndexFormatEnum;
            static QStringList s_kTopologyEnumStr;
            static QVector<int> s_kTopologyEnum;
            if(s_kIndexFormatEnumStr.empty())
            {
                s_kIndexFormatEnumStr.push_back("FMT_R32_UINT");
                s_kIndexFormatEnumStr.push_back("FMT_R16_UINT");
                s_kIndexFormatEnum.push_back(NodeData::IndexBuffer::R32_UINT);
                s_kIndexFormatEnum.push_back(NodeData::IndexBuffer::R16_UINT);

                s_kTopologyEnumStr.push_back("TOPOLOGY_UNDEFINED");
                s_kTopologyEnumStr.push_back("TOPOLOGY_POINTLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_LINELIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_LINESTRIP");
                s_kTopologyEnumStr.push_back("TOPOLOGY_TRIANGLELIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_TRIANGLESTRIP");
                s_kTopologyEnumStr.push_back("TOPOLOGY_LINELIST_ADJ");
                s_kTopologyEnumStr.push_back("TOPOLOGY_LINESTRIP_ADJ");
                s_kTopologyEnumStr.push_back("TOPOLOGY_TRIANGLELIST_ADJ");
                s_kTopologyEnumStr.push_back("TOPOLOGY_TRIANGLESTRIP_ADJ");
                s_kTopologyEnumStr.push_back("TOPOLOGY_1_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_2_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_3_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_4_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_5_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_6_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_7_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_8_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_9_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_10_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_11_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_12_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_13_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_14_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_15_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_16_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_17_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_18_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_19_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_20_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_21_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_22_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_23_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_24_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_25_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_26_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_27_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_28_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_29_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_30_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_31_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnumStr.push_back("TOPOLOGY_32_CONTROL_POINT_PATCHLIST");
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_UNDEFINED);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_POINTLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_LINELIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_LINESTRIP);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_TRIANGLELIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_TRIANGLESTRIP);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_LINELIST_ADJ);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_LINESTRIP_ADJ);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_TRIANGLELIST_ADJ);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_TRIANGLESTRIP_ADJ);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_1_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_2_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_5_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_6_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_7_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_8_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_9_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_10_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_11_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_12_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_13_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_14_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_15_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_16_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_17_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_18_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_19_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_20_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_21_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_22_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_23_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_24_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_25_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_26_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_27_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_28_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_29_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_30_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_31_CONTROL_POINT_PATCHLIST);
                s_kTopologyEnum.push_back(NodeData::PrimitiveTopology::TOPOLOGY_32_CONTROL_POINT_PATCHLIST);
            }

            NodeData* pkNodeData = (NodeData*)kData.m_pkData;
            m_pkRight->AddType(tr("NodeData"));
            m_pkRight->AddProperty(0, tr("name"), pkNodeData->m_kName, NodeData::OnNameChange, pkNodeData);
            for(int i(0); i < pkNodeData->m_kRenderTickArray.size(); ++i)
            {
                NodeData::RenderTick* pkTick = pkNodeData->m_kRenderTickArray[i];
                switch(pkTick->m_eRenderTick)
                {
                case MaterialDoc::NodeData::IA_INDEX_BUFFER:
                    m_pkRight->AddType(tr("index buffer"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::IndexBuffer*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("format"), s_kIndexFormatEnumStr, s_kIndexFormatEnum, ((NodeData::IndexBuffer*)pkTick)->m_eFormat, NodeData::OnIndexFormatChange, pkTick);
                    break;
                case MaterialDoc::NodeData::IA_INPUT_LAYOUT:
                    m_pkRight->AddType(tr("input layout"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::InputLayout*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    break;
                case MaterialDoc::NodeData::IA_PRIMITIVE_TOPOLOGY:
                    m_pkRight->AddType(tr("primitive topology"));
                    m_pkRight->AddProperty(i + 1, tr("format"), s_kTopologyEnumStr, s_kTopologyEnum, ((NodeData::PrimitiveTopology*)pkTick)->m_eTopology, NodeData::OnTopologyChange, pkTick);
                    break;
                case MaterialDoc::NodeData::IA_VERTEX_BUFFER:
                    m_pkRight->AddType(tr("vertex buffer"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::VertexBuffer*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::VertexBuffer*)pkTick)->m_u16Slot, 0, 15, NodeData::OnVertexBufferSlotChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("stride"), ((NodeData::VertexBuffer*)pkTick)->m_u16Stride, 0, 255, NodeData::OnVertexBufferStrideChange, pkTick);
                    break;
                case MaterialDoc::NodeData::VS_CONSTANT_BUFFER:
                    m_pkRight->AddType(tr("vs constant buffer"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::ConstantBufferVS*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::ConstantBufferVS*)pkTick)->m_u32Slot, 0, 15, NodeData::OnContantBufferSlotChange, pkTick);
                    break;
                case MaterialDoc::NodeData::VS_SHADER:
                    m_pkRight->AddType(tr("vertex shader"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::ShaderVS*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    break;
                case MaterialDoc::NodeData::RS_SCISSOR_RECT:
                    m_pkRight->AddType(tr("scissor rect"));
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::ScissorRect*)pkTick)->m_u32Slot, 0, 15, NodeData::OnScissorSlotChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("x"), ((NodeData::ScissorRect*)pkTick)->x, 0, 4096, NodeData::OnScissorxChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("y"), ((NodeData::ScissorRect*)pkTick)->y, 0, 4096, NodeData::OnScissoryChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("w"), ((NodeData::ScissorRect*)pkTick)->w, 0, 4096, NodeData::OnScissorwChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("h"), ((NodeData::ScissorRect*)pkTick)->h, 0, 4096, NodeData::OnScissorhChange, pkTick);
                    break;
                case MaterialDoc::NodeData::RS_STATE:
                    m_pkRight->AddType(tr("rasterizer state"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::RasterizerState*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    break;
                case MaterialDoc::NodeData::RS_VIEWPORT:
                    m_pkRight->AddType(tr("viewport"));
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::ViewPort*)pkTick)->m_u32Slot, 0, 15, NodeData::OnViewportSlotChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("x"), ((NodeData::ViewPort*)pkTick)->x, 0.0f, 4096.0f, 1.0f, NodeData::OnViewportxChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("y"), ((NodeData::ViewPort*)pkTick)->y, 0.0f, 4096.0f, 1.0f, NodeData::OnViewportyChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("w"), ((NodeData::ViewPort*)pkTick)->w, 0.0f, 4096.0f, 1.0f, NodeData::OnViewportwChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("h"), ((NodeData::ViewPort*)pkTick)->h, 0.0f, 4096.0f, 1.0f, NodeData::OnViewporthChange, pkTick);
                    break;
                case MaterialDoc::NodeData::PS_SAMPLER:
                    m_pkRight->AddType(tr("ps sampler"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::SamplerPS*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::SamplerPS*)pkTick)->m_u32Slot, 0, 15, NodeData::OnSamplerSlotChange, pkTick);
                    break;
                case MaterialDoc::NodeData::PS_SHADER:
                    m_pkRight->AddType(tr("pixel shader"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::ShaderPS*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    break;
                case MaterialDoc::NodeData::PS_SHADER_RESOURCE:
                    m_pkRight->AddType(tr("ps shader res"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::ShaderResPS*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::ShaderResPS*)pkTick)->m_u32Slot, 0, 15, NodeData::OnSamplerSlotChange, pkTick);
                    break;
                case MaterialDoc::NodeData::OM_BLEND_STATE:
                    m_pkRight->AddType(tr("blend state"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::BlendState*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("factor r"), ((NodeData::BlendState*)pkTick)->m_fFactorR, 0.0f, 1.0f, 0.1f, NodeData::OnBlendFactorRChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("factor g"), ((NodeData::BlendState*)pkTick)->m_fFactorG, 0.0f, 1.0f, 0.1f, NodeData::OnBlendFactorGChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("factor b"), ((NodeData::BlendState*)pkTick)->m_fFactorB, 0.0f, 1.0f, 0.1f, NodeData::OnBlendFactorBChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("factor a"), ((NodeData::BlendState*)pkTick)->m_fFactorA, 0.0f, 1.0f, 0.1f, NodeData::OnBlendFactorAChange, pkTick);
                    break;
                case MaterialDoc::NodeData::OM_DEPTH_STENCIL_STATE:
                    m_pkRight->AddType(tr("depth stencil state"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::DepthStencilState*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("stencil ref"), ((NodeData::DepthStencilState*)pkTick)->m_u32StencilRef, 0, 255, NodeData::OnStencilRefChange, pkTick);
                    break;
                case MaterialDoc::NodeData::OM_RENDER_TARGET_VIEW:
                    m_pkRight->AddType(tr("render target view"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::RenderTargetView*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    m_pkRight->AddProperty(i + 1, tr("slot"), ((NodeData::RenderTargetView*)pkTick)->m_u32Slot, 0, 15, NodeData::OnRTVSlotChange, pkTick);
                    break;
                case MaterialDoc::NodeData::OM_DEPTH_STENCIL_VIEW:
                    m_pkRight->AddType(tr("depth stencil view"));
                    m_pkRight->AddProperty(i + 1, tr("name"), ((NodeData::DepthStencilView*)pkTick)->m_kName, NodeData::OnRenderTickNameChange, pkTick);
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case LTYPE_NODE:
        {
            Node* pkNode = (Node*)kData.m_pkData;
            m_pkRight->AddType(tr("Node"));
            m_pkRight->AddProperty(0, tr("name"), pkNode->m_kName, Node::OnNameChange, pkNode);
            m_pkRight->AddProperty(0, tr("data name"), pkNode->m_kDataName, Node::OnDataNameChange, pkNode);
            m_pkRight->AddProperty(0, tr("parent name"), pkNode->m_kParent, Node::OnParentNameChange, pkNode);
        }
        break;
    case LTYPE_MATERIAL:
        {
            Material* pkMaterial = (Material*)kData.m_pkData;
            m_pkRight->AddType(tr("Material"));
            m_pkRight->AddProperty(0, tr("name"), pkMaterial->m_kName, Material::OnNameChange, pkMaterial);
            m_pkRight->AddProperty(0, tr("num scheme"), pkMaterial->m_kNodeList.size(), 0, 8, Material::OnSchemeNumChange, pkMaterial);
            UpdateMaterial(pkMaterial);
        }
        break;
    case LTYPE_PLATFORM:
        if(kData.m_uiTypeSec)
        {
            Platform* pkPlatform = (Platform*)kData.m_pkData;
            m_pkRight->AddType(tr("Platform"));
            m_pkRight->AddProperty(0, tr("windows"), pkPlatform->m_bWindows, Platform::OnWindowsChange, pkPlatform);
            m_pkRight->AddProperty(0, tr("linux"), pkPlatform->m_bLinux, Platform::OnLinuxChange, pkPlatform);
            m_pkRight->AddProperty(0, tr("macosx"), pkPlatform->m_bMacosx, Platform::OnMacosxChange, pkPlatform);
            m_pkRight->AddProperty(0, tr("ios"), pkPlatform->m_bIOS, Platform::OnIOSChange, pkPlatform);
            m_pkRight->AddProperty(0, tr("android"), pkPlatform->m_bAndroid, Platform::OnAndroidChange, pkPlatform);
            m_pkRight->AddProperty(0, tr("win mob sim"), pkPlatform->m_bWinMobSim, Platform::OnWinMobSimChange, pkPlatform);
        }
    default:
        break;
    }
}

void MaterialDoc::UpdateBlendState(BlendState* pkBlendState)
{
    static QStringList s_kBlendEnumStr;
    static QVector<int> s_kBlendEnum;
    static QStringList s_kBlendOpEnumStr;
    static QVector<int> s_kBlendOpEnum;
    static QVector< QPair<QString,int> > s_kWriteMasks;
    if(s_kBlendEnum.empty())
    {
        s_kBlendEnumStr.push_back("BLEND_ZERO");
        s_kBlendEnumStr.push_back("BLEND_ONE");
        s_kBlendEnumStr.push_back("BLEND_SRC_COLOR");
        s_kBlendEnumStr.push_back("BLEND_INV_SRC_COLOR");
        s_kBlendEnumStr.push_back("BLEND_SRC_ALPHA");
        s_kBlendEnumStr.push_back("BLEND_INV_SRC_ALPHA");
        s_kBlendEnumStr.push_back("BLEND_DEST_ALPHA");
        s_kBlendEnumStr.push_back("BLEND_INV_DEST_ALPHA");
        s_kBlendEnumStr.push_back("BLEND_DEST_COLOR");
        s_kBlendEnumStr.push_back("BLEND_INV_DEST_COLOR");
        s_kBlendEnumStr.push_back("BLEND_SRC_ALPHA_SAT");
        s_kBlendEnumStr.push_back("BLEND_BLEND_FACTOR");
        s_kBlendEnumStr.push_back("BLEND_INV_BLEND_FACTOR");
        s_kBlendEnumStr.push_back("BLEND_SRC1_COLOR");
        s_kBlendEnumStr.push_back("BLEND_INV_SRC1_COLOR");
        s_kBlendEnumStr.push_back("BLEND_SRC1_ALPHA");
        s_kBlendEnumStr.push_back("BLEND_INV_SRC1_ALPHA");
        s_kBlendEnum.push_back(BlendState::BLEND_ZERO);
        s_kBlendEnum.push_back(BlendState::BLEND_ONE);
        s_kBlendEnum.push_back(BlendState::BLEND_SRC_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_SRC_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_SRC_ALPHA);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_SRC_ALPHA);
        s_kBlendEnum.push_back(BlendState::BLEND_DEST_ALPHA);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_DEST_ALPHA);
        s_kBlendEnum.push_back(BlendState::BLEND_DEST_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_DEST_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_SRC_ALPHA_SAT);
        s_kBlendEnum.push_back(BlendState::BLEND_BLEND_FACTOR);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_BLEND_FACTOR);
        s_kBlendEnum.push_back(BlendState::BLEND_SRC1_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_SRC1_COLOR);
        s_kBlendEnum.push_back(BlendState::BLEND_SRC1_ALPHA);
        s_kBlendEnum.push_back(BlendState::BLEND_INV_SRC1_ALPHA);
        s_kBlendOpEnumStr.push_back("BLEND_OP_ADD");
        s_kBlendOpEnumStr.push_back("BLEND_OP_SUBTRACT");
        s_kBlendOpEnumStr.push_back("BLEND_OP_REV_SUBTRACT");
        s_kBlendOpEnumStr.push_back("BLEND_OP_MIN");
        s_kBlendOpEnumStr.push_back("BLEND_OP_MAX");
        s_kBlendOpEnum.push_back(BlendState::BLEND_OP_ADD);
        s_kBlendOpEnum.push_back(BlendState::BLEND_OP_SUBTRACT);
        s_kBlendOpEnum.push_back(BlendState::BLEND_OP_REV_SUBTRACT);
        s_kBlendOpEnum.push_back(BlendState::BLEND_OP_MIN);
        s_kBlendOpEnum.push_back(BlendState::BLEND_OP_MAX);
    }

    if(s_kWriteMasks.empty())
    {
        s_kWriteMasks.push_back(qMakePair(tr("r"), 0));
        s_kWriteMasks.push_back(qMakePair(tr("g"), 1));
        s_kWriteMasks.push_back(qMakePair(tr("b"), 2));
        s_kWriteMasks.push_back(qMakePair(tr("a"), 3));
    }

    while(m_pkRight->topLevelItemCount() > 1)
    {
        m_pkRight->DelType(1);
    }
    for(quint16 i(0); i < pkBlendState->m_u16NumRTDesc; ++i)
    {
        Q_ASSERT(i < pkBlendState->m_kStateArray.size());
        m_pkRight->AddType(QString("BlendStateRenderTarget%1").arg(i));
        m_pkRight->AddProperty(i + 1, tr("enable"), pkBlendState->m_kStateArray[i].m_u8Enable ? true : false, BlendState::OnBlendEnableChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("src blend"), s_kBlendEnumStr, s_kBlendEnum, pkBlendState->m_kStateArray[i].m_u8SrcBlend, BlendState::OnSrcBlendChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("dst blend"), s_kBlendEnumStr, s_kBlendEnum, pkBlendState->m_kStateArray[i].m_u8DstBlend, BlendState::OnDstBlendChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("blend op"), s_kBlendOpEnumStr, s_kBlendOpEnum, pkBlendState->m_kStateArray[i].m_u8BlendOp, BlendState::OnBlendOpChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("src blend alpha"), s_kBlendEnumStr, s_kBlendEnum, pkBlendState->m_kStateArray[i].m_u8SrcBlendAlpha, BlendState::OnSrcBlendAlphaChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("dst blend alpha"), s_kBlendEnumStr, s_kBlendEnum, pkBlendState->m_kStateArray[i].m_u8DstBlendAlpha, BlendState::OnDstBlendAlphaChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("blend op alpha"), s_kBlendOpEnumStr, s_kBlendOpEnum, pkBlendState->m_kStateArray[i].m_u8BlendOpAlpha, BlendState::OnBlendOpAlphaChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
        m_pkRight->AddProperty(i + 1, tr("write mask"), s_kWriteMasks, pkBlendState->m_kStateArray[i].m_u8WriteMask, BlendState::OnWriteMaskChange, (BlendState::State*)&(pkBlendState->m_kStateArray[i]));
    }
}

void MaterialDoc::UpdateDepthStencilState(DepthStencilState* pkDepthState)
{
    static QStringList s_kComparisonEnumStr;
    static QVector<int> s_kComparisonEnum;
    static QStringList s_kStencilOpEnumStr;
    static QVector<int> s_kStencilOpEnum;
    if(s_kComparisonEnumStr.empty())
    {
        s_kComparisonEnumStr.push_back("COMPARISON_NEVER");
        s_kComparisonEnumStr.push_back("COMPARISON_LESS");
        s_kComparisonEnumStr.push_back("COMPARISON_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_LESS_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_GREATER");
        s_kComparisonEnumStr.push_back("COMPARISON_NOT_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_GREATER_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_ALWAYS");
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_NEVER);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_LESS);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_LESS_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_GREATER);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_NOT_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_GREATER_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_ALWAYS);

        s_kStencilOpEnumStr.push_back("STENCIL_OP_KEEP");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_ZERO");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_REPLACE");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_INCR_SAT");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_DECR_SAT");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_INVERT");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_INCR");
        s_kStencilOpEnumStr.push_back("STENCIL_OP_DECR");
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_KEEP);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_ZERO);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_REPLACE);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_INCR_SAT);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_DECR_SAT);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_INVERT);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_INCR);
        s_kStencilOpEnum.push_back(DepthStencilState::STENCIL_OP_DECR);
    }

    m_pkRight->AddProperty(0, tr("name"), pkDepthState->m_kName, DepthStencilState::OnNameChange, pkDepthState);
    m_pkRight->AddProperty(1, tr("enable"), pkDepthState->m_u8ZEnable ? true : false, DepthStencilState::OnZEnableChange, pkDepthState);
    m_pkRight->AddProperty(1, tr("write"), pkDepthState->m_u8ZWrite ? true : false, DepthStencilState::OnZWriteChange, pkDepthState);
    m_pkRight->AddProperty(1, tr("func"), s_kComparisonEnumStr, s_kComparisonEnum, pkDepthState->m_u8ZFunc, DepthStencilState::OnZFuncChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("enable"), pkDepthState->m_u8SEnable ? true : false, DepthStencilState::OnSEnableChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("read mask"), pkDepthState->m_u8SReadMask, 0, 255, DepthStencilState::OnSReadMaskChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("write mask"), pkDepthState->m_u8SWriteMask, 0, 255, DepthStencilState::OnSWriteMaskChange, pkDepthState);

    m_pkRight->AddProperty(2, tr("front failop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SFrontFailOp, DepthStencilState::OnSFrontFailOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("front zfailop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SFrontDepthFailOp, DepthStencilState::OnSFrontDepthFailOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("front passop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SFrontPassOp, DepthStencilState::OnSFrontPassOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("front func"), s_kComparisonEnumStr, s_kComparisonEnum, pkDepthState->m_u8SFrontFunc, DepthStencilState::OnSFrontFuncChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("back failop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SBackFailOp, DepthStencilState::OnSBackFailOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("back zfailop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SBackDepthFailOp, DepthStencilState::OnSBackDepthFailOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("back passop"), s_kStencilOpEnumStr, s_kStencilOpEnum, pkDepthState->m_u8SBackPassOp, DepthStencilState::OnSBackPassOpChange, pkDepthState);
    m_pkRight->AddProperty(2, tr("back func"), s_kComparisonEnumStr, s_kComparisonEnum, pkDepthState->m_u8SBackFunc, DepthStencilState::OnSBackFuncChange, pkDepthState);
}

void MaterialDoc::UpdateRasterizerState(RasterizerState* pkRasterizerState)
{
    static QStringList s_kFillModeEnumStr;
    static QVector<int> s_kFillModeEnum;
    static QStringList s_kCullModeEnumStr;
    static QVector<int> s_kCullModeEnum;
    static QStringList s_kDepthBiasModeEnumStr;
    static QVector<int> s_kDepthBiasModeEnum;
    if(s_kFillModeEnumStr.empty())
    {
        s_kFillModeEnumStr.push_back("FILL_WIREFRAME");
        s_kFillModeEnumStr.push_back("FILL_SOLID");
        s_kFillModeEnum.push_back(RasterizerState::FILL_WIREFRAME);
        s_kFillModeEnum.push_back(RasterizerState::FILL_SOLID);
        s_kCullModeEnumStr.push_back("CULL_NONE");
        s_kCullModeEnumStr.push_back("CULL_FRONT");
        s_kCullModeEnumStr.push_back("CULL_BACK");
        s_kCullModeEnum.push_back(RasterizerState::CULL_NONE);
        s_kCullModeEnum.push_back(RasterizerState::CULL_FRONT);
        s_kCullModeEnum.push_back(RasterizerState::CULL_BACK);
        s_kDepthBiasModeEnumStr.push_back("DBIAS_NONE");
        s_kDepthBiasModeEnum.push_back(RasterizerState::DBIAS_NONE);
    }

    m_pkRight->AddProperty(0, tr("name"), pkRasterizerState->m_kName, RasterizerState::OnNameChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("fill mode"), s_kFillModeEnumStr, s_kFillModeEnum, pkRasterizerState->m_u8FillMode, RasterizerState::OnFillModeChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("cull mode"), s_kCullModeEnumStr, s_kCullModeEnum, pkRasterizerState->m_u8CullMode, RasterizerState::OnCullModeChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("front ccw"), pkRasterizerState->m_u8FrontCCW ? true : false, RasterizerState::OnFrontCCWChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("depth bias"), s_kDepthBiasModeEnumStr, s_kDepthBiasModeEnum, pkRasterizerState->m_u8DepthBias, RasterizerState::OnDepthBiasChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("depth clip"), pkRasterizerState->m_u8DepthClipEnable ? true : false, RasterizerState::OnDepthClipEnableChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("scissor"), pkRasterizerState->m_u8ScissorEnable ? true : false, RasterizerState::OnScissorEnableChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("multisample"), pkRasterizerState->m_u8MultisampleEnable ? true : false, RasterizerState::OnMultisampleEnableChange, pkRasterizerState);
    m_pkRight->AddProperty(0, tr("antialiased line"), pkRasterizerState->m_u8AntialiasedLineEnable ? true : false, RasterizerState::OnAntialiasedLineEnableChange, pkRasterizerState);
}

void MaterialDoc::UpdateSamplerState(SamplerState* pkSamplerState)
{
    static QStringList s_kComparisonEnumStr;
    static QVector<int> s_kComparisonEnum;
    static QStringList s_kFilterEnumStr;
    static QVector<int> s_kFilterEnum;
    static QStringList s_kAddressModeEnumStr;
    static QVector<int> s_kAddressModeEnum;
    if(s_kComparisonEnumStr.empty())
    {
        s_kComparisonEnumStr.push_back("COMPARISON_NEVER");
        s_kComparisonEnumStr.push_back("COMPARISON_LESS");
        s_kComparisonEnumStr.push_back("COMPARISON_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_LESS_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_GREATER");
        s_kComparisonEnumStr.push_back("COMPARISON_NOT_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_GREATER_EQUAL");
        s_kComparisonEnumStr.push_back("COMPARISON_ALWAYS");
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_NEVER);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_LESS);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_LESS_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_GREATER);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_NOT_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_GREATER_EQUAL);
        s_kComparisonEnum.push_back(DepthStencilState::COMPARISON_ALWAYS);

        s_kFilterEnumStr.push_back("FILTER_MIN_MAG_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_MIN_MAG_POINT_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_MIN_POINT_MAG_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_MIN_LINEAR_MAG_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_MIN_MAG_LINEAR_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_MIN_MAG_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_ANISOTROPIC");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_MAG_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_MIN_MAG_MIP_LINEAR");
        s_kFilterEnumStr.push_back("FILTER_COMPARISON_ANISOTROPIC");
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_MAG_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_MAG_POINT_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_POINT_MAG_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_LINEAR_MAG_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_MAG_LINEAR_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_MIN_MAG_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_ANISOTROPIC);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_MAG_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_MIN_MAG_MIP_LINEAR);
        s_kFilterEnum.push_back(SamplerState::FILTER_COMPARISON_ANISOTROPIC);

        s_kAddressModeEnumStr.push_back("TEXTURE_ADDRESS_WRAP");
        s_kAddressModeEnumStr.push_back("TEXTURE_ADDRESS_MIRROR");
        s_kAddressModeEnumStr.push_back("TEXTURE_ADDRESS_CLAMP");
        s_kAddressModeEnumStr.push_back("TEXTURE_ADDRESS_BORDER");
        s_kAddressModeEnumStr.push_back("TEXTURE_ADDRESS_MIRROR_ONCE");
        s_kAddressModeEnum.push_back(SamplerState::TEXTURE_ADDRESS_WRAP);
        s_kAddressModeEnum.push_back(SamplerState::TEXTURE_ADDRESS_MIRROR);
        s_kAddressModeEnum.push_back(SamplerState::TEXTURE_ADDRESS_CLAMP);
        s_kAddressModeEnum.push_back(SamplerState::TEXTURE_ADDRESS_BORDER);
        s_kAddressModeEnum.push_back(SamplerState::TEXTURE_ADDRESS_MIRROR_ONCE);
    }

    m_pkRight->AddProperty(0, tr("name"), pkSamplerState->m_kName, SamplerState::OnNameChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("filter"), s_kFilterEnumStr, s_kFilterEnum, pkSamplerState->m_u8Filter, SamplerState::OnFilterChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("adress u"), s_kAddressModeEnumStr, s_kAddressModeEnum, pkSamplerState->m_u8AddressU, SamplerState::OnAddressUChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("adress v"), s_kAddressModeEnumStr, s_kAddressModeEnum, pkSamplerState->m_u8AddressV, SamplerState::OnAddressVChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("adress w"), s_kAddressModeEnumStr, s_kAddressModeEnum, pkSamplerState->m_u8AddressW, SamplerState::OnAddressWChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("max anisotropy"), pkSamplerState->m_u16MaxAnisotropy, 1, 16, SamplerState::OnMaxAnisotropyChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("comparison"), s_kComparisonEnumStr, s_kComparisonEnum, pkSamplerState->m_u16ComparisonFunc, SamplerState::OnComparisonFuncChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("mip lod bias"), pkSamplerState->m_fMipLODBias, 0.0f, 16.0f, 1.0f, SamplerState::OnMipLODBiasChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("min lod"), pkSamplerState->m_fMinLOD, -16.0f, 16.0f, 1.0f, SamplerState::OnMinLODChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("max lod"), pkSamplerState->m_fMaxLOD, -16.0f, 16.0f, 1.0f, SamplerState::OnMaxLODChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("border red"), pkSamplerState->m_afBorderColor[0], 0.0f, 1.0f, 0.1f, SamplerState::OnBordeRedChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("border green"), pkSamplerState->m_afBorderColor[1], 0.0f, 1.0f, 0.1f, SamplerState::OnBordeGreenChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("border blue"), pkSamplerState->m_afBorderColor[2], 0.0f, 1.0f, 0.1f, SamplerState::OnBordeBlueChange, pkSamplerState);
    m_pkRight->AddProperty(0, tr("border alpha"), pkSamplerState->m_afBorderColor[3], 0.0f, 1.0f, 0.1f, SamplerState::OnBordeAlphaChange, pkSamplerState);
}

void MaterialDoc::UpdateInputLayoutElements(InputLayout* pkInputLayout)
{
    static QStringList s_kSemanticEnumStr;
    static QVector<int> s_kSemanticEnum;
    static QStringList s_kFormatEnumStr;
    static QVector<int> s_kFormatEnum;
    static QStringList s_kClassEnumStr;
    static QVector<int> s_kClassEnum;
    if(s_kSemanticEnumStr.empty())
    {
        s_kSemanticEnumStr.push_back("SE_POSITION");
        s_kSemanticEnumStr.push_back("SE_NORMAL");
        s_kSemanticEnumStr.push_back("SE_COLOR");
        s_kSemanticEnumStr.push_back("SE_TEXCOORD");
        s_kSemanticEnumStr.push_back("SE_TANGENT");
        s_kSemanticEnumStr.push_back("SE_BINORMAL");
        s_kSemanticEnumStr.push_back("SE_BLENDINDICES");
        s_kSemanticEnumStr.push_back("SE_BLENDWEIGHT");
        s_kSemanticEnum.push_back(InputLayout::SE_POSITION);
        s_kSemanticEnum.push_back(InputLayout::SE_NORMAL);
        s_kSemanticEnum.push_back(InputLayout::SE_COLOR);
        s_kSemanticEnum.push_back(InputLayout::SE_TEXCOORD);
        s_kSemanticEnum.push_back(InputLayout::SE_TANGENT);
        s_kSemanticEnum.push_back(InputLayout::SE_BINORMAL);
        s_kSemanticEnum.push_back(InputLayout::SE_BLENDINDICES);
        s_kSemanticEnum.push_back(InputLayout::SE_BLENDWEIGHT);

        s_kFormatEnumStr.push_back("FMT_R32_FLOAT");
        s_kFormatEnumStr.push_back("FMT_R32G32_FLOAT");
        s_kFormatEnumStr.push_back("FMT_R32G32B32_FLOAT");
        s_kFormatEnumStr.push_back("FMT_R32G32B32A32_FLOAT");
        s_kFormatEnumStr.push_back("FMT_R8G8B8A8_UNORM");
        s_kFormatEnum.push_back(InputLayout::FMT_R32_FLOAT);
        s_kFormatEnum.push_back(InputLayout::FMT_R32G32_FLOAT);
        s_kFormatEnum.push_back(InputLayout::FMT_R32G32B32_FLOAT);
        s_kFormatEnum.push_back(InputLayout::FMT_R32G32B32A32_FLOAT);
        s_kFormatEnum.push_back(InputLayout::FMT_R8G8B8A8_UNORM);

        s_kClassEnumStr.push_back("PER_VERTEX_DATA");
        s_kClassEnumStr.push_back("PER_INSTANCE_DATA");
        s_kClassEnum.push_back(InputLayout::PER_VERTEX_DATA);
        s_kClassEnum.push_back(InputLayout::PER_INSTANCE_DATA);
    }

    while(m_pkRight->topLevelItemCount() > 1)
    {
        m_pkRight->DelType(1);
    }

    for(quint16 i(0); i < pkInputLayout->m_u32NumElements; ++i)
    {
        Q_ASSERT(i < pkInputLayout->m_kElementArray.size());
        InputLayout::Element& kElement = pkInputLayout->m_kElementArray[i];
        m_pkRight->AddType(QString("Element%1").arg(i));
        m_pkRight->AddProperty(i + 1, tr("semantic type"), s_kSemanticEnumStr, s_kSemanticEnum, kElement.m_u8SemanticType, InputLayout::OnSemanticTypeChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("semantic index"), kElement.m_u8SemanticIndex, 0, 7, InputLayout::OnSemanticIndexChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("format"), s_kFormatEnumStr, s_kFormatEnum, kElement.m_u8Format, InputLayout::OnFormatChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("input slot"), kElement.m_u8InputSlot, 0, 15, InputLayout::OnInputSlotChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("aligned byte offset"), kElement.m_u8AlignedByteOffset, 0, 255, InputLayout::OnAlignedByteOffsetChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("input slot class"), s_kClassEnumStr, s_kClassEnum, kElement.m_u8InputSlotClass, InputLayout::OnInputSlotClassChange, &kElement);
        m_pkRight->AddProperty(i + 1, tr("instance step rate"), kElement.m_u16InstanceStepRate, 0, 255, InputLayout::OnInstanceStepRateChange, &kElement);
    }
}

void MaterialDoc::UpdateMaterial(Material* pkMaterial)
{
    while(m_pkRight->topLevelItemCount() > 1)
    {
        m_pkRight->DelType(1);
    }
    for(int i(0); i < pkMaterial->m_kNodeList.size(); ++i)
    {
        m_pkRight->AddType(QString("Node%1").arg(i));
        m_pkRight->AddProperty(i + 1, tr("name"), pkMaterial->m_kNodeList[i], Material::OnNodeNameChange, &(pkMaterial->m_kNodeList[i]));
    }
}

void MaterialDoc::CreatePlatform(bool bWin, bool bLin, bool bMac, bool bIOS, bool bArd, bool bSim)
{
    int iCount = m_pkLeft->topLevelItemCount();
    QTreeWidgetItem* pkRoot = m_pkLeft->topLevelItem(0);
    QTreeWidgetItem* pkPlatform = new QTreeWidgetItem(pkRoot);
    pkPlatform->setText(0, tr("Platform"));
    pkPlatform->setExpanded(true);
    MaterialDoc::LeftItemData kPlatformData = {MaterialDoc::LTYPE_PLATFORM, iCount, NULL};
    MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkPlatform, kPlatformData).value();
    kData.m_pkData = new MaterialDoc::Platform(bWin, bLin, bMac, bIOS, bArd, bSim);

    QTreeWidgetItem* pkRenderObject = new QTreeWidgetItem(pkPlatform);
    pkRenderObject->setText(0, tr("RenderObject"));
    pkRenderObject->setExpanded(true);
    MaterialDoc::LeftItemData kRenderObjectData = {MaterialDoc::LTYPE_RENDEROBJ_ROOT, iCount, NULL};
    m_kLeftItemMap.insert(pkRenderObject, kRenderObjectData);

    QTreeWidgetItem* pkNodeData = new QTreeWidgetItem(pkPlatform);
    pkNodeData->setText(0, tr("NodeData"));
    pkNodeData->setExpanded(true);
    MaterialDoc::LeftItemData kNodeDataData = {MaterialDoc::LTYPE_NODEDATA_ROOT, iCount, NULL};
    m_kLeftItemMap.insert(pkNodeData, kNodeDataData);

    QTreeWidgetItem* pkNode = new QTreeWidgetItem(pkPlatform);
    pkNode->setText(0, tr("Node"));
    pkNode->setExpanded(true);
    MaterialDoc::LeftItemData kNodeData = {MaterialDoc::LTYPE_NODE_ROOT, iCount, NULL};
    m_kLeftItemMap.insert(pkNode, kNodeData);

    QTreeWidgetItem* pkMaterial = new QTreeWidgetItem(pkPlatform);
    pkMaterial->setText(0, tr("Material"));
    pkMaterial->setExpanded(true);
    MaterialDoc::LeftItemData kMaterialData = {MaterialDoc::LTYPE_MATERIAL_ROOT, iCount, NULL};
    m_kLeftItemMap.insert(pkMaterial, kMaterialData);
}

void MaterialDoc::SaveToStream(QDataStream& kStream)
{
    kStream << ('V' | 'M' << 8 | 'A' << 16 | 'T' << 24);
    QTreeWidgetItem* pkRoot = m_pkLeft->topLevelItem(0);
    LeftItemData& kRootData = m_kLeftItemMap[pkRoot];
    Q_ASSERT(kRootData.m_eType == LTYPE_ROOT);
    kStream << pkRoot->childCount();
    for(int i(0); i < pkRoot->childCount(); ++i)
    {
        QTreeWidgetItem* pkItem = pkRoot->child(i);
        QByteArray kCache;
        QDataStream kCacheStream(&kCache, QIODevice::WriteOnly);
        kCacheStream.setByteOrder(QDataStream::LittleEndian);
        kStream << SavePlatformToStream(pkItem, kCacheStream);
        kStream.writeBytes(kCache.data(), kCache.size());
    }


    //QByteArray kPlatformCache;
    //QDataStream kPlatformStream(&kPlatformCache, QIODevice::WriteOnly);

    //kTemp << 4;

    //qDebug() << kData.size();
}

quint32 MaterialDoc::SavePlatformToStream(QTreeWidgetItem* pkPlatform, QDataStream& kStream)
{
    LeftItemData& kData = m_kLeftItemMap[pkPlatform];
    Q_ASSERT(kData.m_eType == LTYPE_PLATFORM);
    QTreeWidgetItem* pkRenderObject = pkPlatform->child(0);
    kStream << pkRenderObject->childCount();
    if(pkRenderObject->childCount())
    {
        SaveRenderObjectToStream(pkRenderObject, kStream);
    }

    QTreeWidgetItem* pkNodeData = pkPlatform->child(1);
    kStream << pkNodeData->childCount();
    if(pkNodeData->childCount())
    {
        SaveNodeDataToStream(pkNodeData, kStream);
    }

    QTreeWidgetItem* pkNode = pkPlatform->child(2);
    kStream << pkNode->childCount();
    if(pkNode->childCount())
    {
        SaveNodeToStream(pkNode, kStream);
    }

    QTreeWidgetItem* pkMaterial = pkPlatform->child(3);
    kStream << pkMaterial->childCount();
    if(pkMaterial->childCount())
    {
        SaveMaterialToStream(pkMaterial, kStream);
    }

    quint32 u32Res = 0;
    if(kData.m_pkData)
    {
        Platform* pkPlatformData = (Platform*)kData.m_pkData;
        if(pkPlatformData->m_bWindows)
        {
            u32Res |= Platform::TYPE_WINDOWS;
        }
        if(pkPlatformData->m_bLinux)
        {
            u32Res |= Platform::TYPE_LINUX;
        }
        if(pkPlatformData->m_bMacosx)
        {
            u32Res |= Platform::TYPE_MACOSX;
        }
        if(pkPlatformData->m_bWinMobSim)
        {
            u32Res |= Platform::TYPE_WINMOBSIM;
        }
        if(pkPlatformData->m_bIOS)
        {
            u32Res |= Platform::TYPE_IOS;
        }
        if(pkPlatformData->m_bAndroid)
        {
            u32Res |= Platform::TYPE_ANDROID;
        }
    }
    else
    {
        u32Res = 0xffffffff;
    }

    return u32Res;
}

class EnumOutput
{
public:
    enum RenderObjectType
    {
        TYPE_BLEND_STATE,
        TYPE_COUNTER,
        TYPE_DEPTH_STENCIL_STATE,
        TYPE_INPUT_LAYOUT,
        TYPE_PREDICATE,
        TYPE_QUERY,
        TYPE_RASTERIZE_STATE,
        TYPE_SAMPLER_STATE,

        TYPE_BUFFER,
        TYPE_DEPTH_STENCIL_VIEW,
        TYPE_RENDER_TARGET_VIEW,
        TYPE_SHADER_RESOURCE_VIEW,
        TYPE_TEXTURE_1D,
        TYPE_TEXTURE_2D,
        TYPE_TEXTURE_3D,
        TYPE_UNORDERED_ACCESS_VIEW,

        TYPE_CLASS_LINKAGE,
        TYPE_COMPUTE_SHADER,
        TYPE_DOMAIN_SHADER,
        TYPE_GEOMETRY_SHADER,
        TYPE_HULL_SHADER,
        TYPE_PIXEL_SHADER,
        TYPE_VERTEX_SHADER,

        TYPE_MAX
    };

    enum RenderTickType
    {
        IA_INDEX_BUFFER,
        IA_INPUT_LAYOUT,
        IA_PRIMITIVE_TOPOLOGY,
        IA_VERTEX_BUFFER,

        VS_CONSTANT_BUFFER,
        VS_SAMPLER,
        VS_SHADER,
        VS_SHADER_RESOURCE,

        HS_CONSTANT_BUFFER,
        HS_SAMPLER,
        HS_SHADER,
        HS_SHADER_RESOURCE,

        DS_CONSTANT_BUFFER,
        DS_SAMPLER,
        DS_SHADER,
        DS_SHADER_RESOURCE,
        GS_CONSTANT_BUFFER,
        GS_SAMPLER,
        GS_SHADER,
        GS_SHADER_RESOURCE,

        SO_TARGET,

        RS_SCISSOR_RECT,
        RS_STATE,
        RS_VIEWPORT,

        PS_CONSTANT_BUFFER,
        PS_SAMPLER,
        PS_SHADER,
        PS_SHADER_RESOURCE,

        OM_BLEND_STATE,
        OM_DEPTH_STENCIL_STATE,
        OM_RENDER_TARGET_VIEW,
        OM_DEPTH_STENCIL_VIEW,
        OM_UNORDERED_ACCESS_VIEW
    };
};

void WriteString(QDataStream& kStream, QString& kString)
{
    quint32 u32Temp(0);
    int iLength = kString.length();
    if(iLength >= 255)
    {
        kStream << quint8(0xff);
        kStream << quint8(iLength);
        kStream << quint8(iLength >> 8);
        kStream << quint8(iLength >> 16);
        u32Temp += 4;
    }
    else
    {
        kStream << quint8(iLength);
        u32Temp += 1;
    }
    for(int i(0); i < iLength; ++i)
    {
        kStream << quint8(kString.at(i).toAscii());
    }
    u32Temp += iLength;
    u32Temp = ((u32Temp + 3) & 0xfffffffc) - u32Temp;
    if(u32Temp)
    {
        quint32 u32Zero = 0;
        kStream.writeRawData((const char*)&u32Zero, u32Temp);
    }
}

void MaterialDoc::SaveRenderObjectToStream(QTreeWidgetItem* pkRenderObject, QDataStream& kStream)
{
    for(int i(0); i < pkRenderObject->childCount(); ++i)
    {
        QTreeWidgetItem* pkItem = pkRenderObject->child(i);
        LeftItemData& kData = m_kLeftItemMap[pkItem];
        switch(kData.m_uiTypeSec)
        {
        case AddRenderObjectDialog::TYPE_BLEND_STATE:
            {
                kStream << quint32(EnumOutput::TYPE_BLEND_STATE);
                BlendState* pkBlendState = (BlendState*)kData.m_pkData;
                WriteString(kStream, pkBlendState->m_kName);
                kStream << pkBlendState->m_u16AlphaToCoverageEnable;
                kStream << pkBlendState->m_u16NumRTDesc;
                for(int j(0); j < pkBlendState->m_kStateArray.size(); ++j)
                {
                    BlendState::State& kState = pkBlendState->m_kStateArray[j];
                    kStream << kState.m_u8Enable;
                    kStream << kState.m_u8SrcBlend;
                    kStream << kState.m_u8DstBlend;
                    kStream << kState.m_u8BlendOp;
                    kStream << kState.m_u8SrcBlendAlpha;
                    kStream << kState.m_u8DstBlendAlpha;
                    kStream << kState.m_u8BlendOpAlpha;
                    kStream << kState.m_u8WriteMask;
                }
            }
            break;
        case AddRenderObjectDialog::TYPE_DEPTH_STENCIL_STATE:
            {
                kStream << quint32(EnumOutput::TYPE_DEPTH_STENCIL_STATE);
                DepthStencilState* pkDepthState = (DepthStencilState*)kData.m_pkData;
                WriteString(kStream, pkDepthState->m_kName);
                kStream << pkDepthState->m_u8ZEnable;
                kStream << pkDepthState->m_u8ZWrite;
                kStream << pkDepthState->m_u8ZFunc;
                kStream << pkDepthState->m_u8SEnable;
                if(pkDepthState->m_u8SEnable)
                {
                    kStream << pkDepthState->m_u8SReadMask;
                    kStream << pkDepthState->m_u8SWriteMask;
                    kStream << pkDepthState->m_u8SFrontFailOp;
                    kStream << pkDepthState->m_u8SFrontDepthFailOp;
                    kStream << pkDepthState->m_u8SFrontPassOp;
                    kStream << pkDepthState->m_u8SFrontFunc;
                    kStream << pkDepthState->m_u8SBackFailOp;
                    kStream << pkDepthState->m_u8SBackDepthFailOp;
                    kStream << pkDepthState->m_u8SBackPassOp;
                    kStream << pkDepthState->m_u8SBackFunc;
                    kStream << quint16(0);
                }
            }
            break;
        case AddRenderObjectDialog::TYPE_RASTERIZE_STATE:
            {
                kStream << quint32(EnumOutput::TYPE_RASTERIZE_STATE);
                RasterizerState* pkRasterizerState = (RasterizerState*)kData.m_pkData;
                WriteString(kStream, pkRasterizerState->m_kName);
                kStream << pkRasterizerState->m_u8FillMode;
                kStream << pkRasterizerState->m_u8CullMode;
                kStream << pkRasterizerState->m_u8FrontCCW;
                kStream << pkRasterizerState->m_u8DepthBias;
                kStream << pkRasterizerState->m_u8DepthClipEnable;
                kStream << pkRasterizerState->m_u8ScissorEnable;
                kStream << pkRasterizerState->m_u8MultisampleEnable;
                kStream << pkRasterizerState->m_u8AntialiasedLineEnable;
            }
            break;
        case AddRenderObjectDialog::TYPE_SAMPLER_STATE:
            {
                kStream << quint32(EnumOutput::TYPE_SAMPLER_STATE);
                SamplerState* pkSamplerState = (SamplerState*)kData.m_pkData;
                WriteString(kStream, pkSamplerState->m_kName);
                kStream << pkSamplerState->m_u8Filter;
                kStream << pkSamplerState->m_u8AddressU;
                kStream << pkSamplerState->m_u8AddressV;
                kStream << pkSamplerState->m_u8AddressW;
                kStream << pkSamplerState->m_u16MaxAnisotropy;
                kStream << pkSamplerState->m_u16ComparisonFunc;
                kStream << *(quint32*)&(pkSamplerState->m_fMipLODBias);
                kStream << *(quint32*)&(pkSamplerState->m_fMinLOD);
                kStream << *(quint32*)&(pkSamplerState->m_fMaxLOD);
                kStream << *(quint32*)&(pkSamplerState->m_afBorderColor[0]);
                kStream << *(quint32*)&(pkSamplerState->m_afBorderColor[1]);
                kStream << *(quint32*)&(pkSamplerState->m_afBorderColor[2]);
                kStream << *(quint32*)&(pkSamplerState->m_afBorderColor[3]);
            }
            break;
        case AddRenderObjectDialog::TYPE_VERTEX_SHADER:
            {
                kStream << quint32(EnumOutput::TYPE_VERTEX_SHADER);
                VertexShader* pkVertexShader = (VertexShader*)kData.m_pkData;
                WriteString(kStream, pkVertexShader->m_kName);
            }
            break;
        case AddRenderObjectDialog::TYPE_PIXEL_SHADER:
            {
                kStream << quint32(EnumOutput::TYPE_PIXEL_SHADER);
                PixelShader* pkPixelShader = (PixelShader*)kData.m_pkData;
                WriteString(kStream, pkPixelShader->m_kName);
            }
            break;
        case AddRenderObjectDialog::TYPE_INPUT_LAYOUT:
            {
                kStream << quint32(EnumOutput::TYPE_INPUT_LAYOUT);
                InputLayout* pkInputLayout = (InputLayout*)kData.m_pkData;
                WriteString(kStream, pkInputLayout->m_kName);
                WriteString(kStream, pkInputLayout->m_kVertexShader);
                kStream << quint32(pkInputLayout->m_u32NumElements);
                Q_ASSERT(pkInputLayout->m_u32NumElements == pkInputLayout->m_kElementArray.size());
                for(quint32 j(0); j < pkInputLayout->m_u32NumElements; ++j)
                {
                    InputLayout::Element& kElement = pkInputLayout->m_kElementArray[j];
                    kStream << kElement.m_u8SemanticType;
                    kStream << kElement.m_u8SemanticIndex;
                    kStream << kElement.m_u8Format;
                    kStream << kElement.m_u8InputSlot;
                    kStream << kElement.m_u8AlignedByteOffset;
                    kStream << kElement.m_u8InputSlotClass;
                    kStream << kElement.m_u16InstanceStepRate;
                }
            }
            break;
        default:
            break;
        }

    }
}

void MaterialDoc::SaveNodeDataToStream(QTreeWidgetItem* pkNodeData, QDataStream& kStream)
{
    for(int i(0); i < pkNodeData->childCount(); ++i)
    {
        QTreeWidgetItem* pkItem = pkNodeData->child(i);
        LeftItemData& kData = m_kLeftItemMap[pkItem];
        NodeData* pkNodeData = (NodeData*)kData.m_pkData;
        WriteString(kStream, pkNodeData->m_kName);
        kStream << quint32(pkNodeData->m_kRenderTickArray.size());

        for(int j(0); j < pkNodeData->m_kRenderTickArray.size(); ++j)
        {
            NodeData::RenderTick* pkTick = pkNodeData->m_kRenderTickArray[j];
            switch(pkTick->m_eRenderTick)
            {
            case MaterialDoc::NodeData::IA_INDEX_BUFFER:
                kStream << quint32(EnumOutput::IA_INDEX_BUFFER);
                WriteString(kStream, ((NodeData::IndexBuffer*)pkTick)->m_kName);
                switch(((NodeData::IndexBuffer*)pkTick)->m_eFormat)
                {
                case NodeData::IndexBuffer::R32_UINT:
                    kStream << quint32(42);
                    break;
                default:
                    kStream << quint32(57);
                    break;

                }
                break;
            case MaterialDoc::NodeData::IA_INPUT_LAYOUT:
                kStream << quint32(EnumOutput::IA_INPUT_LAYOUT);
                WriteString(kStream, ((NodeData::InputLayout*)pkTick)->m_kName);
                break;
            case MaterialDoc::NodeData::IA_PRIMITIVE_TOPOLOGY:
                kStream << quint32(EnumOutput::IA_PRIMITIVE_TOPOLOGY);
                kStream << quint32(((NodeData::PrimitiveTopology*)pkTick)->m_eTopology);
                break;
            case MaterialDoc::NodeData::IA_VERTEX_BUFFER:
                kStream << quint32(EnumOutput::IA_VERTEX_BUFFER);
                WriteString(kStream, ((NodeData::VertexBuffer*)pkTick)->m_kName);
                kStream << ((NodeData::VertexBuffer*)pkTick)->m_u16Slot;
                kStream << ((NodeData::VertexBuffer*)pkTick)->m_u16Stride;
                break;
            case MaterialDoc::NodeData::VS_CONSTANT_BUFFER:
                kStream << quint32(EnumOutput::VS_CONSTANT_BUFFER);
                WriteString(kStream, ((NodeData::ConstantBufferVS*)pkTick)->m_kName);
                kStream << ((NodeData::ConstantBufferVS*)pkTick)->m_u32Slot;
                break;
            case MaterialDoc::NodeData::VS_SHADER:
                kStream << quint32(EnumOutput::VS_SHADER);
                WriteString(kStream, ((NodeData::ShaderVS*)pkTick)->m_kName);
                break;
            case MaterialDoc::NodeData::RS_SCISSOR_RECT:
                kStream << quint32(EnumOutput::RS_SCISSOR_RECT);
                kStream << ((NodeData::ScissorRect*)pkTick)->m_u32Slot;
                kStream << ((NodeData::ScissorRect*)pkTick)->x;
                kStream << ((NodeData::ScissorRect*)pkTick)->y;
                kStream << ((NodeData::ScissorRect*)pkTick)->w;
                kStream << ((NodeData::ScissorRect*)pkTick)->h;
                break;
            case MaterialDoc::NodeData::RS_STATE:
                kStream << quint32(EnumOutput::RS_STATE);
                WriteString(kStream, ((NodeData::RasterizerState*)pkTick)->m_kName);
                break;
            case MaterialDoc::NodeData::RS_VIEWPORT:
                kStream << quint32(EnumOutput::RS_VIEWPORT);
                kStream << ((NodeData::ViewPort*)pkTick)->m_u32Slot;
                kStream << *(quint32*)&(((NodeData::ViewPort*)pkTick)->x);
                kStream << *(quint32*)&(((NodeData::ViewPort*)pkTick)->y);
                kStream << *(quint32*)&(((NodeData::ViewPort*)pkTick)->w);
                kStream << *(quint32*)&(((NodeData::ViewPort*)pkTick)->h);
                break;
            case MaterialDoc::NodeData::PS_SAMPLER:
                kStream << quint32(EnumOutput::PS_SAMPLER);
                WriteString(kStream, ((NodeData::SamplerPS*)pkTick)->m_kName);
                kStream << ((NodeData::SamplerPS*)pkTick)->m_u32Slot;
                break;
            case MaterialDoc::NodeData::PS_SHADER:
                kStream << quint32(EnumOutput::PS_SHADER);
                WriteString(kStream, ((NodeData::ShaderPS*)pkTick)->m_kName);
                break;
            case MaterialDoc::NodeData::PS_SHADER_RESOURCE:
                kStream << quint32(EnumOutput::PS_SHADER_RESOURCE);
                WriteString(kStream, ((NodeData::ShaderResPS*)pkTick)->m_kName);
                kStream << ((NodeData::ShaderResPS*)pkTick)->m_u32Slot;
                break;
            case MaterialDoc::NodeData::OM_BLEND_STATE:
                kStream << quint32(EnumOutput::OM_BLEND_STATE);
                WriteString(kStream, ((NodeData::BlendState*)pkTick)->m_kName);
                kStream << *(quint32*)&(((NodeData::BlendState*)pkTick)->m_fFactorR);
                kStream << *(quint32*)&(((NodeData::BlendState*)pkTick)->m_fFactorG);
                kStream << *(quint32*)&(((NodeData::BlendState*)pkTick)->m_fFactorB);
                kStream << *(quint32*)&(((NodeData::BlendState*)pkTick)->m_fFactorA);
                kStream << ((NodeData::BlendState*)pkTick)->m_u32SampleMask;
                break;
            case MaterialDoc::NodeData::OM_DEPTH_STENCIL_STATE:
                kStream << quint32(EnumOutput::OM_DEPTH_STENCIL_STATE);
                WriteString(kStream, ((NodeData::DepthStencilState*)pkTick)->m_kName);
                kStream << ((NodeData::DepthStencilState*)pkTick)->m_u32StencilRef;
                break;
            case MaterialDoc::NodeData::OM_RENDER_TARGET_VIEW:
                kStream << quint32(EnumOutput::OM_RENDER_TARGET_VIEW);
                WriteString(kStream, ((NodeData::RenderTargetView*)pkTick)->m_kName);
                kStream << ((NodeData::RenderTargetView*)pkTick)->m_u32Slot;
                break;
            case MaterialDoc::NodeData::OM_DEPTH_STENCIL_VIEW:
                kStream << quint32(EnumOutput::OM_DEPTH_STENCIL_VIEW);
                WriteString(kStream, ((NodeData::DepthStencilView*)pkTick)->m_kName);
                break;
            default:
                break;
            }
        }
        kStream << 0;
    }
}

void MaterialDoc::SaveNodeToStream(QTreeWidgetItem* pkNode, QDataStream& kStream)
{
    for(int i(0); i < pkNode->childCount(); ++i)
    {
        QTreeWidgetItem* pkItem = pkNode->child(i);
        LeftItemData& kData = m_kLeftItemMap[pkItem];
        Node* pkNode = (Node*)kData.m_pkData;
        WriteString(kStream, pkNode->m_kName);
        WriteString(kStream, pkNode->m_kDataName);
        WriteString(kStream, pkNode->m_kParent);
    }
}

void MaterialDoc::SaveMaterialToStream(QTreeWidgetItem* pkMaterial, QDataStream& kStream)
{
    for(int i(0); i < pkMaterial->childCount(); ++i)
    {
        QTreeWidgetItem* pkItem = pkMaterial->child(i);
        LeftItemData& kData = m_kLeftItemMap[pkItem];
        Material* pkMat = (Material*)kData.m_pkData;
        WriteString(kStream, pkMat->m_kName);
        kStream << pkMat->m_kNodeList.size();
        for(int j(0); j < pkMat->m_kNodeList.size(); ++j)
        {
            WriteString(kStream, pkMat->m_kNodeList[j]);
        }
    }
}

void MaterialDoc::LoadFromStream(QDataStream& kStream)
{
    QTreeWidgetItem* pkRoot = m_pkLeft->topLevelItem(0);
    quint32 u32PlatformCount;
    kStream >> u32PlatformCount;

    for(quint32 i(0); i < u32PlatformCount; ++i)
    {
        QTreeWidgetItem* pkPlatform = pkRoot->child(i);
        quint32 u32Support;
        kStream >> u32Support;
        if(i)
        {
            bool bWin = (u32Support & Platform::TYPE_WINDOWS) ? true : false;
            bool bLin = (u32Support & Platform::TYPE_LINUX) ? true : false;
            bool bMac = (u32Support & Platform::TYPE_MACOSX) ? true : false;
            bool bIOS = (u32Support & Platform::TYPE_IOS) ? true : false;
            bool bArd = (u32Support & Platform::TYPE_ANDROID) ? true : false;
            bool bSim = (u32Support & Platform::TYPE_WINMOBSIM) ? true : false;
            CreatePlatform(bWin, bLin, bMac, bIOS, bArd, bSim);
        }
        LoadPlatformFromStream(kStream, pkPlatform);
    }
}

void MaterialDoc::LoadPlatformFromStream(QDataStream& kStream, QTreeWidgetItem* pkPlatform)
{
    quint32 u32DataSize;
    kStream >> u32DataSize;
    quint32 u32RenderObjCount;
    kStream >> u32RenderObjCount;
    for(quint32 i(0); i < u32RenderObjCount; ++i)
    {
        LoadRenderObject(kStream, pkPlatform->child(0));
    }
    quint32 u32NodeDataCount;
    kStream >> u32NodeDataCount;
    for(quint32 i(0); i < u32NodeDataCount; ++i)
    {
        LoadNodeData(kStream, pkPlatform->child(1));
    }
    quint32 u32NodeCount;
    kStream >> u32NodeCount;
    for(quint32 i(0); i < u32NodeCount; ++i)
    {
        LoadNode(kStream, pkPlatform->child(2));
    }
    quint32 u32MaterialCount;
    kStream >> u32MaterialCount;
    for(quint32 i(0); i < u32MaterialCount; ++i)
    {
        LoadMaterial(kStream, pkPlatform->child(3));
    }
}

quint32 ReadLength(QDataStream& kStream)
{
    quint8 u8Len;
    kStream >> u8Len;
    quint32 u32Value = u8Len;
    if(u32Value == 0xFF)
    {
        u32Value = 0;
        kStream >> u8Len;
        u32Value |= u8Len;
        kStream >> u8Len;
        u32Value |= u8Len << 8;
        kStream >> u8Len;
        u32Value |= u8Len << 16;
    }
    return u32Value;
}

QString ReadString(QDataStream& kStream)
{
    quint32 u32Len = ReadLength(kStream);
    char acBuffer[1024];
    if(u32Len)
    {
        kStream.readRawData(acBuffer, u32Len);
        acBuffer[u32Len] = 0;
    }
    else
    {
        acBuffer[0] = 0;
    }
    quint32 u32Temp = (u32Len >= 255) ? 4 : 1;
    u32Temp += u32Len;
    u32Temp = ((u32Temp + 3) & 0xfffffffc) - u32Temp;
    if(u32Temp)
    {
        kStream.skipRawData(u32Temp);
    }
    return acBuffer;
}

void MaterialDoc::LoadRenderObject(QDataStream& kStream, QTreeWidgetItem* pkRenderObjectRoot)
{
    quint32 u32Type;
    kStream >> u32Type;
    QString kName = ReadString(kStream);
    QTreeWidgetItem* pkRenderObj = new QTreeWidgetItem(pkRenderObjectRoot);
    switch(u32Type)
    {
    case EnumOutput::TYPE_BLEND_STATE:
        {
            LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, AddRenderObjectDialog::TYPE_BLEND_STATE, NULL};
            MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            BlendState* pkState = new BlendState(kName);
            kData.m_pkData = pkState;
            kStream >> pkState->m_u16AlphaToCoverageEnable;
            kStream >> pkState->m_u16NumRTDesc;
            pkState->m_kStateArray.resize(pkState->m_u16NumRTDesc);
            for(int i(0); i < pkState->m_kStateArray.size(); ++i)
            {
                kStream >> pkState->m_kStateArray[i].m_u8Enable;
                kStream >> pkState->m_kStateArray[i].m_u8SrcBlend;
                kStream >> pkState->m_kStateArray[i].m_u8DstBlend;
                kStream >> pkState->m_kStateArray[i].m_u8BlendOp;
                kStream >> pkState->m_kStateArray[i].m_u8SrcBlendAlpha;
                kStream >> pkState->m_kStateArray[i].m_u8DstBlendAlpha;
                kStream >> pkState->m_kStateArray[i].m_u8BlendOpAlpha;
                kStream >> pkState->m_kStateArray[i].m_u8WriteMask;
            }
            pkRenderObj->setText(0, tr("BlendState") + tr("(") + pkState->m_kName + tr(")"));
        }
        break;
    case EnumOutput::TYPE_DEPTH_STENCIL_STATE:
        {
            LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, AddRenderObjectDialog::TYPE_DEPTH_STENCIL_STATE, NULL};
            MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            DepthStencilState* pkState = new DepthStencilState(kName);
            kData.m_pkData = pkState;
            kStream >> pkState->m_u8ZEnable;
            kStream >> pkState->m_u8ZWrite;
            kStream >> pkState->m_u8ZFunc;
            kStream >> pkState->m_u8SEnable;
            if(pkState->m_u8SEnable)
            {
                kStream >> pkState->m_u8SReadMask;
                kStream >> pkState->m_u8SWriteMask;
                kStream >> pkState->m_u8SFrontFailOp;
                kStream >> pkState->m_u8SFrontDepthFailOp;
                kStream >> pkState->m_u8SFrontPassOp;
                kStream >> pkState->m_u8SFrontFunc;
                kStream >> pkState->m_u8SBackFailOp;
                kStream >> pkState->m_u8SBackDepthFailOp;
                kStream >> pkState->m_u8SBackPassOp;
                kStream >> pkState->m_u8SBackFunc;
                quint16 u16Align;
                kStream >> u16Align;
            }
            pkRenderObj->setText(0, tr("DepthStencilState") + tr("(") + pkState->m_kName + tr(")"));
        }
        break;
    case EnumOutput::TYPE_RASTERIZE_STATE:
        {
            LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, AddRenderObjectDialog::TYPE_RASTERIZE_STATE, NULL};
            MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            RasterizerState* pkState = new RasterizerState(kName);
            kData.m_pkData = pkState;
            kStream >> pkState->m_u8FillMode;
            kStream >> pkState->m_u8CullMode;
            kStream >> pkState->m_u8FrontCCW;
            kStream >> pkState->m_u8DepthBias;
            kStream >> pkState->m_u8DepthClipEnable;
            kStream >> pkState->m_u8ScissorEnable;
            kStream >> pkState->m_u8MultisampleEnable;
            kStream >> pkState->m_u8AntialiasedLineEnable;
            pkRenderObj->setText(0, tr("RasterizerState") + tr("(") + pkState->m_kName + tr(")"));
        }
        break;
    case EnumOutput::TYPE_SAMPLER_STATE:
        {
            LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, AddRenderObjectDialog::TYPE_SAMPLER_STATE, NULL};
            MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            SamplerState* pkState = new SamplerState(kName);
            kData.m_pkData = pkState;
            kStream >> pkState->m_u8Filter;
            kStream >> pkState->m_u8AddressU;
            kStream >> pkState->m_u8AddressV;
            kStream >> pkState->m_u8AddressW;
            kStream >> pkState->m_u16MaxAnisotropy;
            kStream >> pkState->m_u16ComparisonFunc;
            kStream >> *(quint32*)&(pkState->m_fMipLODBias);
            kStream >> *(quint32*)&(pkState->m_fMinLOD);
            kStream >> *(quint32*)&(pkState->m_fMaxLOD);
            kStream >> *(quint32*)&(pkState->m_afBorderColor[0]);
            kStream >> *(quint32*)&(pkState->m_afBorderColor[1]);
            kStream >> *(quint32*)&(pkState->m_afBorderColor[2]);
            kStream >> *(quint32*)&(pkState->m_afBorderColor[3]);
            pkRenderObj->setText(0, tr("SamplerState") + tr("(") + pkState->m_kName + tr(")"));
        }
        break;
    case EnumOutput::TYPE_INPUT_LAYOUT:
        {
            LeftItemData kDataInit = {MaterialDoc::LTYPE_RENDEROBJ, AddRenderObjectDialog::TYPE_INPUT_LAYOUT, NULL};
            LeftItemData& kData = m_kLeftItemMap.insert(pkRenderObj, kDataInit).value();
            InputLayout* pkState = new InputLayout(kName);
            kData.m_pkData = pkState;
            pkState->m_kVertexShader = ReadString(kStream);
            kStream >> pkState->m_u32NumElements;
            kStream << quint32(pkState->m_u32NumElements);
            pkState->m_kElementArray.resize(pkState->m_u32NumElements);
            for(quint32 j(0); j < pkState->m_u32NumElements; ++j)
            {
                kStream >> pkState->m_kElementArray[j].m_u8SemanticType;
                kStream >> pkState->m_kElementArray[j].m_u8SemanticIndex;
                kStream >> pkState->m_kElementArray[j].m_u8Format;
                kStream >> pkState->m_kElementArray[j].m_u8InputSlot;
                kStream >> pkState->m_kElementArray[j].m_u8AlignedByteOffset;
                kStream >> pkState->m_kElementArray[j].m_u8InputSlotClass;
                kStream >> pkState->m_kElementArray[j].m_u16InstanceStepRate;
            }
            pkRenderObj->setText(0, tr("InputLayout") + tr("(") + pkState->m_kName + tr(")"));
        }
        break;
    default:
        break;
    }
}

void MaterialDoc::LoadNodeData(QDataStream& kStream, QTreeWidgetItem* pkNodeDataRoot)
{
    QString kName = ReadString(kStream);
    QTreeWidgetItem* pkNodeData = new QTreeWidgetItem(pkNodeDataRoot);    
    MaterialDoc::LeftItemData kDataInit = {LTYPE_NODEDATA, 0, NULL};
    MaterialDoc::LeftItemData& kData = m_kLeftItemMap.insert(pkNodeData, kDataInit).value();
    NodeData* pkData = new NodeData(kName);
    kData.m_pkData = pkData;
    quint32 u32NumTick;
    kStream >> u32NumTick;
    for(quint32 i(0); i < u32NumTick; ++i)
    {
        quint32 u32Type;
        kStream >> u32Type;
        switch(u32Type)
        {
        case EnumOutput::IA_INDEX_BUFFER:
            {
                NodeData::IndexBuffer* pkTick = new NodeData::IndexBuffer(ReadString(kStream));
                quint32 u32Format;
                kStream >> u32Format;
                if(u32Format == 42)
                {
                    pkTick->m_eFormat = NodeData::IndexBuffer::R32_UINT;
                }
                else
                {
                    pkTick->m_eFormat = NodeData::IndexBuffer::R16_UINT;
                }
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::IA_INPUT_LAYOUT:
            pkData->m_kRenderTickArray.push_back(new NodeData::InputLayout(ReadString(kStream)));
            break;
        case EnumOutput::IA_PRIMITIVE_TOPOLOGY:
            {
                NodeData::PrimitiveTopology* pkTick = new NodeData::PrimitiveTopology();
                quint32 u32Topology;
                kStream >> u32Topology;
                pkTick->m_eTopology = (NodeData::PrimitiveTopology::Topology)u32Topology;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::IA_VERTEX_BUFFER:
            {
                NodeData::VertexBuffer* pkTick = new NodeData::VertexBuffer(ReadString(kStream));
                kStream >> pkTick->m_u16Slot;
                kStream >> pkTick->m_u16Stride;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::VS_CONSTANT_BUFFER:
            {
                NodeData::ConstantBufferVS* pkTick = new NodeData::ConstantBufferVS(ReadString(kStream));
                kStream >> pkTick->m_u32Slot;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::VS_SHADER:
            {
                NodeData::ShaderVS* pkTick = new NodeData::ShaderVS(ReadString(kStream));
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::RS_SCISSOR_RECT:
            {
                NodeData::ScissorRect* pkTick = new NodeData::ScissorRect();
                kStream >> pkTick->m_u32Slot;
                kStream >> pkTick->x;
                kStream >> pkTick->y;
                kStream >> pkTick->w;
                kStream >> pkTick->h;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::RS_STATE:
            {
                NodeData::RasterizerState* pkTick = new NodeData::RasterizerState(ReadString(kStream));
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::RS_VIEWPORT:
            {
                NodeData::ViewPort* pkTick = new NodeData::ViewPort();
                kStream >> pkTick->m_u32Slot;
                kStream >> *(quint32*)&(pkTick->x);
                kStream >> *(quint32*)&(pkTick->y);
                kStream >> *(quint32*)&(pkTick->w);
                kStream >> *(quint32*)&(pkTick->h);
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::PS_SAMPLER:
            {
                NodeData::SamplerPS* pkTick = new NodeData::SamplerPS(ReadString(kStream));
                kStream >> pkTick->m_u32Slot;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::PS_SHADER:
            {
                NodeData::ShaderPS* pkTick = new NodeData::ShaderPS(ReadString(kStream));
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::PS_SHADER_RESOURCE:
            {
                NodeData::ShaderResPS* pkTick = new NodeData::ShaderResPS(ReadString(kStream));
                kStream >> pkTick->m_u32Slot;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::OM_BLEND_STATE:
            {
                NodeData::BlendState* pkTick = new NodeData::BlendState(ReadString(kStream));
                kStream >> *(quint32*)&(pkTick->m_fFactorR);
                kStream >> *(quint32*)&(pkTick->m_fFactorG);
                kStream >> *(quint32*)&(pkTick->m_fFactorB);
                kStream >> *(quint32*)&(pkTick->m_fFactorA);
                kStream >> pkTick->m_u32SampleMask;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::OM_DEPTH_STENCIL_STATE:
            {
                NodeData::DepthStencilState* pkTick = new NodeData::DepthStencilState(ReadString(kStream));
                kStream >> pkTick->m_u32StencilRef;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::OM_RENDER_TARGET_VIEW:
            {
                NodeData::RenderTargetView* pkTick = new NodeData::RenderTargetView(ReadString(kStream));
                kStream >> pkTick->m_u32Slot;
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        case EnumOutput::OM_DEPTH_STENCIL_VIEW:
            {
                NodeData::DepthStencilView* pkTick = new NodeData::DepthStencilView(ReadString(kStream));
                pkData->m_kRenderTickArray.push_back(pkTick);
            }
            break;
        default:
            break;
        }
    }
    quint32 u32NumCall;
    kStream >> u32NumCall;
    pkNodeData->setText(0, tr("NodeData") + tr("(") + kName + tr(")"));
}

void MaterialDoc::LoadNode(QDataStream& kStream, QTreeWidgetItem* pkNodeRoot)
{
    QTreeWidgetItem* pkNode = new QTreeWidgetItem(pkNodeRoot);
    LeftItemData kDataInit = {MaterialDoc::LTYPE_NODE, 0, NULL};
    LeftItemData& kData = m_kLeftItemMap.insert(pkNode, kDataInit).value();
    Node* pkData = new Node();
    pkData->m_kName = ReadString(kStream);
    pkData->m_kDataName = ReadString(kStream);
    pkData->m_kParent = ReadString(kStream);
    kData.m_pkData = pkData;
    pkNode->setText(0, tr("Node") + tr("(") + pkData->m_kName + tr(")"));
}

void MaterialDoc::LoadMaterial(QDataStream& kStream, QTreeWidgetItem* pkMatRoot)
{
    QTreeWidgetItem* pkMaterial = new QTreeWidgetItem(pkMatRoot);
    LeftItemData kDataInit = {LTYPE_MATERIAL, 0, NULL};
    LeftItemData& kData = m_kLeftItemMap.insert(pkMaterial, kDataInit).value();
    Material* pkMat = new Material();
    pkMat->m_kName = ReadString(kStream);
    quint32 u32Count;
    kStream >> u32Count;
    for(quint32 i(0); i < u32Count; ++i)
    {
        pkMat->m_kNodeList.push_back(ReadString(kStream));
    }
    kData.m_pkData = pkMat;
    pkMaterial->setText(0, tr("Material") + tr("(") + pkMat->m_kName + tr(")"));
}

extern MainWindow* g_pkWindow;

void MaterialDoc::UpdateName()
{
    int iIndex = g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->indexOf(this);
    if(m_bEdited)
    {
        g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->setTabText(iIndex, QString("%1%2").arg(m_kName).arg("*"));
    }
    else
    {
        g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->setTabText(iIndex, m_kName);
    }
    if(iIndex == g_pkWindow->m_pkMaterialEditor->m_iCurTable)
    {
        g_pkWindow->OnMaterialChanged(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->tabText(iIndex));
    }
}

void MaterialDoc::BlendState::OnNameChange(const QString& kValue, void* pvData)
{
    BlendState* pkBlendState = (BlendState*)pvData;
    pkBlendState->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("BlendState") + tr("(") + pkBlendState->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnAlphaToCoverageEnableChange(bool bValue, void* pvData)
{
    BlendState* pkBlendState = (BlendState*)pvData;
    pkBlendState->m_u16AlphaToCoverageEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnNumRTDescChange(int iValue, void* pvData)
{
    BlendState* pkBlendState = (BlendState*)pvData;
    pkBlendState->SetNumRTDesc(iValue);
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->UpdateBlendState(pkBlendState);
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnBlendEnableChange(bool bValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8Enable = bValue ? true : false;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnSrcBlendChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8SrcBlend = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnDstBlendChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8DstBlend = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnBlendOpChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8BlendOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnSrcBlendAlphaChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8SrcBlendAlpha = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnDstBlendAlphaChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8DstBlendAlpha = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnBlendOpAlphaChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8BlendOpAlpha = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::BlendState::OnWriteMaskChange(int iValue, void* pvData)
{
    BlendState::State* pkState = (BlendState::State*)pvData;
    pkState->m_u8WriteMask = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnNameChange(const QString& kValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("DepthStencilState") + tr("(") + pkDepthState->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnZEnableChange(bool bValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8ZEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnZWriteChange(bool bValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8ZWrite = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnZFuncChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8ZFunc = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSEnableChange(bool bValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSReadMaskChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SReadMask = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSWriteMaskChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SWriteMask = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSFrontFailOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SFrontFailOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSFrontDepthFailOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SFrontDepthFailOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSFrontPassOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SFrontPassOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSFrontFuncChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SFrontFunc = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSBackFailOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SBackFailOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSBackDepthFailOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SBackDepthFailOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSBackPassOpChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SBackPassOp = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::DepthStencilState::OnSBackFuncChange(int iValue, void* pvData)
{
    DepthStencilState* pkDepthState = (DepthStencilState*)pvData;
    pkDepthState->m_u8SBackFunc = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnNameChange(const QString& kValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("RasterizerState") + tr("(") + pkRasterizerState->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnFillModeChange(int iValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8FillMode = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnCullModeChange(int iValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8CullMode = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnFrontCCWChange(bool bValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8FrontCCW = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnDepthBiasChange(int iValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8DepthBias = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnDepthClipEnableChange(bool bValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8DepthClipEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnScissorEnableChange(bool bValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8ScissorEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnMultisampleEnableChange(bool bValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8MultisampleEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::RasterizerState::OnAntialiasedLineEnableChange(bool bValue, void* pvData)
{
    RasterizerState* pkRasterizerState = (RasterizerState*)pvData;
    pkRasterizerState->m_u8AntialiasedLineEnable = bValue ? 1 : 0;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnNameChange(const QString& kValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("SamplerState") + tr("(") + pkSamplerState->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnFilterChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u8Filter = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnAddressUChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u8AddressU = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnAddressVChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u8AddressV = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnAddressWChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u8AddressW = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnMaxAnisotropyChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u16MaxAnisotropy = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnComparisonFuncChange(int iValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_u16ComparisonFunc = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnMipLODBiasChange(float fValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_fMipLODBias = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnMinLODChange(float fValue, void* pvData)
{
    if(fValue == 16.0f) fValue = FLT_MAX;
    if(fValue == -16.0f) fValue = -FLT_MAX;
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_fMinLOD = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnMaxLODChange(float fValue, void* pvData)
{
    if(fValue == 16.0f) fValue = FLT_MAX;
    if(fValue == -16.0f) fValue = -FLT_MAX;
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_fMaxLOD = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnBordeRedChange(float fValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_afBorderColor[0] = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnBordeGreenChange(float fValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_afBorderColor[1] = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnBordeBlueChange(float fValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_afBorderColor[2] = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::SamplerState::OnBordeAlphaChange(float fValue, void* pvData)
{
    SamplerState* pkSamplerState = (SamplerState*)pvData;
    pkSamplerState->m_afBorderColor[3] = fValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::VertexShader::OnNameChange(const QString& kValue, void* pvData)
{
    VertexShader* pkShader = (VertexShader*)pvData;
    pkShader->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("VertexShader") + tr("(") + pkShader->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::PixelShader::OnNameChange(const QString& kValue, void* pvData)
{
    PixelShader* pkShader = (PixelShader*)pvData;
    pkShader->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("PixelShader") + tr("(") + pkShader->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnNameChange(const QString& kValue, void* pvData)
{
    InputLayout* pkLayout = (InputLayout*)pvData;
    pkLayout->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("InputLayout") + tr("(") + pkLayout->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnVertexShaderChange(const QString& kValue, void* pvData)
{
    InputLayout* pkLayout = (InputLayout*)pvData;
    pkLayout->m_kVertexShader = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnNumElementsChange(int iValue, void* pvData)
{
    InputLayout* pkLayout = (InputLayout*)pvData;
    pkLayout->m_u32NumElements = iValue;
    pkLayout->m_kElementArray.resize(iValue);
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->UpdateInputLayoutElements(pkLayout);
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnSemanticTypeChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8SemanticType = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnSemanticIndexChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8SemanticIndex = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnFormatChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8Format = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnInputSlotChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8InputSlot = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnAlignedByteOffsetChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8AlignedByteOffset = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnInputSlotClassChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u8InputSlotClass = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::InputLayout::OnInstanceStepRateChange(int iValue, void* pvData)
{
    InputLayout::Element* pkElement = (InputLayout::Element*)pvData;
    pkElement->m_u16InstanceStepRate = iValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::NodeData::OnNameChange(const QString& kValue, void* pvData)
{
    NodeData* pkNodeData = (NodeData*)pvData;
    pkNodeData->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("NodeData") + tr("(") + pkNodeData->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::NodeData::OnRenderTickNameChange(const QString& kValue, void* pvData)
{
    RenderTick* pkTick = (RenderTick*)pvData;
    *(QString*)((&pkTick->m_eRenderTick) + 1) = kValue;
}

void MaterialDoc::NodeData::OnIndexFormatChange(int iValue, void* pvData)
{
    IndexBuffer* pkTick = (IndexBuffer*)pvData;
    pkTick->m_eFormat = (IndexBuffer::Format)iValue;
}

void MaterialDoc::NodeData::OnTopologyChange(int iValue, void* pvData)
{
    PrimitiveTopology* pkTick = (PrimitiveTopology*)pvData;
    pkTick->m_eTopology = (PrimitiveTopology::Topology)iValue;
}

void MaterialDoc::NodeData::OnVertexBufferSlotChange(int iValue, void* pvData)
{
    VertexBuffer* pkTick = (VertexBuffer*)pvData;
    pkTick->m_u16Slot = iValue;
}

void MaterialDoc::NodeData::OnVertexBufferStrideChange(int iValue, void* pvData)
{
    VertexBuffer* pkTick = (VertexBuffer*)pvData;
    pkTick->m_u16Stride = iValue;
}

void MaterialDoc::NodeData::OnContantBufferSlotChange(int iValue, void* pvData)
{
    ConstantBufferVS* pkTick = (ConstantBufferVS*)pvData;
    pkTick->m_u32Slot = iValue;
}

void MaterialDoc::NodeData::OnScissorSlotChange(int iValue, void* pvData)
{
    ScissorRect* pkTick = (ScissorRect*)pvData;
    pkTick->m_u32Slot = iValue;
}

void MaterialDoc::NodeData::OnScissorxChange(int iValue, void* pvData)
{
    ScissorRect* pkTick = (ScissorRect*)pvData;
    pkTick->x = iValue;
}

void MaterialDoc::NodeData::OnScissoryChange(int iValue, void* pvData)
{
    ScissorRect* pkTick = (ScissorRect*)pvData;
    pkTick->y = iValue;
}

void MaterialDoc::NodeData::OnScissorwChange(int iValue, void* pvData)
{
    ScissorRect* pkTick = (ScissorRect*)pvData;
    pkTick->w = iValue;
}

void MaterialDoc::NodeData::OnScissorhChange(int iValue, void* pvData)
{
    ScissorRect* pkTick = (ScissorRect*)pvData;
    pkTick->h = iValue;
}

void MaterialDoc::NodeData::OnViewportSlotChange(int iValue, void* pvData)
{
    ViewPort* pkTick = (ViewPort*)pvData;
    pkTick->m_u32Slot = iValue;
}

void MaterialDoc::NodeData::OnViewportxChange(float fValue, void* pvData)
{
    ViewPort* pkTick = (ViewPort*)pvData;
    pkTick->x = fValue;
}

void MaterialDoc::NodeData::OnViewportyChange(float fValue, void* pvData)
{
    ViewPort* pkTick = (ViewPort*)pvData;
    pkTick->y = fValue;
}

void MaterialDoc::NodeData::OnViewportwChange(float fValue, void* pvData)
{
    ViewPort* pkTick = (ViewPort*)pvData;
    pkTick->w = fValue;
}

void MaterialDoc::NodeData::OnViewporthChange(float fValue, void* pvData)
{
    ViewPort* pkTick = (ViewPort*)pvData;
    pkTick->h = fValue;
}

void MaterialDoc::NodeData::OnSamplerSlotChange(int iValue, void* pvData)
{
    SamplerPS* pkTick = (SamplerPS*)pvData;
    pkTick->m_u32Slot = iValue;
}

void MaterialDoc::NodeData::OnBlendFactorRChange(float fValue, void* pvData)
{
    BlendState* pkTick = (BlendState*)pvData;
    pkTick->m_fFactorR = fValue;
}

void MaterialDoc::NodeData::OnBlendFactorGChange(float fValue, void* pvData)
{
    BlendState* pkTick = (BlendState*)pvData;
    pkTick->m_fFactorG = fValue;
}

void MaterialDoc::NodeData::OnBlendFactorBChange(float fValue, void* pvData)
{
    BlendState* pkTick = (BlendState*)pvData;
    pkTick->m_fFactorB = fValue;
}

void MaterialDoc::NodeData::OnBlendFactorAChange(float fValue, void* pvData)
{
    BlendState* pkTick = (BlendState*)pvData;
    pkTick->m_fFactorA = fValue;
}

void MaterialDoc::NodeData::OnSampleMaskChange(int iValue, void* pvData)
{
    BlendState* pkTick = (BlendState*)pvData;
    pkTick->m_u32SampleMask = iValue;
}

void MaterialDoc::NodeData::OnStencilRefChange(int iValue, void* pvData)
{
    DepthStencilState* pkTick = (DepthStencilState*)pvData;
    pkTick->m_u32StencilRef = iValue;
}

void MaterialDoc::NodeData::OnRTVSlotChange(int iValue, void* pvData)
{
    RenderTargetView* pkTick = (RenderTargetView*)pvData;
    pkTick->m_u32Slot = iValue;
}

void MaterialDoc::Node::OnNameChange(const QString& kValue, void* pvData)
{
    Node* pkNode = (Node*)pvData;
    pkNode->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("Node") + tr("(") + pkNode->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::Node::OnDataNameChange(const QString& kValue, void* pvData)
{
    Node* pkNode = (Node*)pvData;
    pkNode->m_kDataName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Node::OnParentNameChange(const QString& kValue, void* pvData)
{
    Node* pkNode = (Node*)pvData;
    pkNode->m_kParent = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Material::OnNameChange(const QString& kValue, void* pvData)
{
    Material* pkMaterial = (Material*)pvData;
    pkMaterial->m_kName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->m_pkCurrentOnProcess->setText(0, tr("Material") + tr("(") + pkMaterial->m_kName + tr(")"));
    pkDoc->Edit();
}

void MaterialDoc::Material::OnSchemeNumChange(int iValue, void* pvData)
{
    Material* pkMaterial = (Material*)pvData;
    pkMaterial->m_kNodeList.resize(iValue);
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->UpdateMaterial(pkMaterial);
    pkDoc->Edit();
}

void MaterialDoc::Material::OnNodeNameChange(const QString& kValue, void* pvData)
{
    QString* pkName = (QString*)pvData;
    *pkName = kValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnWindowsChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bWindows = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnLinuxChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bLinux = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnMacosxChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bMacosx = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnIOSChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bIOS = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnAndroidChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bAndroid = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}

void MaterialDoc::Platform::OnWinMobSimChange(bool bValue, void* pvData)
{
    Platform* pkPlatform = (Platform*)pvData;
    pkPlatform->m_bWinMobSim = bValue;
    MaterialDoc* pkDoc = (MaterialDoc*)(g_pkWindow->m_pkMaterialEditor->m_pkTabWidget->widget(g_pkWindow->m_pkMaterialEditor->m_iCurTable));
    pkDoc->Edit();
}
