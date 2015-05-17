////////////////////////////////////////////////////////////////////////////
//
//  Olympus Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   MaterialDoc.h
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

class PropertyList;

class MaterialDoc : public QWidget
{
    Q_OBJECT
public:
    enum LeftItemType
    {
        LTYPE_ROOT,
        LTYPE_PLATFORM,
        LTYPE_RENDEROBJ_ROOT,
        LTYPE_NODEDATA_ROOT,
        LTYPE_NODE_ROOT,
        LTYPE_MATERIAL_ROOT,
        LTYPE_RENDEROBJ,
        LTYPE_NODEDATA,
        LTYPE_NODE,
        LTYPE_MATERIAL,
        LTYPE_MAX
    };

    class LeftItemSubData
    {
    public:
        virtual ~LeftItemSubData() {}
    };

    class BlendState : public LeftItemSubData
    {
    public:
        enum Blend
        {
            BLEND_ZERO               = 1,
            BLEND_ONE                = 2,
            BLEND_SRC_COLOR          = 3,
            BLEND_INV_SRC_COLOR      = 4,
            BLEND_SRC_ALPHA          = 5,
            BLEND_INV_SRC_ALPHA      = 6,
            BLEND_DEST_ALPHA         = 7,
            BLEND_INV_DEST_ALPHA     = 8,
            BLEND_DEST_COLOR         = 9,
            BLEND_INV_DEST_COLOR     = 10,
            BLEND_SRC_ALPHA_SAT      = 11,
            BLEND_BLEND_FACTOR       = 14,
            BLEND_INV_BLEND_FACTOR   = 15,
            BLEND_SRC1_COLOR         = 16,
            BLEND_INV_SRC1_COLOR     = 17,
            BLEND_SRC1_ALPHA         = 18,
            BLEND_INV_SRC1_ALPHA     = 19
        };

        enum BlendOp
        {
            BLEND_OP_ADD            = 1,
            BLEND_OP_SUBTRACT       = 2,
            BLEND_OP_REV_SUBTRACT   = 3,
            BLEND_OP_MIN            = 4,
            BLEND_OP_MAX            = 5
        };

        enum ColorWriteEnable
        {
            COLOR_WRITE_ENABLE_RED     = 1,
            COLOR_WRITE_ENABLE_GREEN   = 2,
            COLOR_WRITE_ENABLE_BLUE    = 4,
            COLOR_WRITE_ENABLE_ALPHA   = 8,
            COLOR_WRITE_ENABLE_ALL     = (COLOR_WRITE_ENABLE_RED | COLOR_WRITE_ENABLE_GREEN |  COLOR_WRITE_ENABLE_BLUE | COLOR_WRITE_ENABLE_ALPHA)
        };

        struct State
        {
            State()
            {
                m_pkBlendState = NULL;
                m_u8Enable = 0;
                m_u8SrcBlend = BLEND_ONE;
                m_u8DstBlend = BLEND_ZERO;
                m_u8BlendOp = BLEND_OP_ADD;
                m_u8SrcBlendAlpha = BLEND_ONE;
                m_u8DstBlendAlpha = BLEND_ZERO;
                m_u8BlendOpAlpha = BLEND_OP_ADD;
                m_u8WriteMask = COLOR_WRITE_ENABLE_ALL;
            }

            BlendState* m_pkBlendState;
            quint8 m_u8Enable;
            quint8 m_u8SrcBlend;
            quint8 m_u8DstBlend;
            quint8 m_u8BlendOp;
            quint8 m_u8SrcBlendAlpha;
            quint8 m_u8DstBlendAlpha;
            quint8 m_u8BlendOpAlpha;
            quint8 m_u8WriteMask;
        };

        BlendState(QString& kName) : m_kName(kName)
        {
            m_u16AlphaToCoverageEnable = 0;
            m_u16NumRTDesc = 0;
            SetNumRTDesc(1);
        }

        void SetNumRTDesc(int iNum)
        {
            m_kStateArray.resize(iNum);
            if(m_u16NumRTDesc && m_u16NumRTDesc < iNum)
            {
                for(int i(m_u16NumRTDesc); i < iNum; ++i)
                {
                    m_kStateArray[i] = m_kStateArray[m_u16NumRTDesc - 1];
                }
            }
            m_u16NumRTDesc = iNum;

            for(quint16 i(0); i < m_u16NumRTDesc; ++i)
            {
                m_kStateArray[i].m_pkBlendState = this;
            }
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnAlphaToCoverageEnableChange(bool bValue, void* pvData);

        static void OnNumRTDescChange(int iValue, void* pvData);

        static void OnBlendEnableChange(bool bValue, void* pvData);

        static void OnSrcBlendChange(int iValue, void* pvData);

        static void OnDstBlendChange(int iValue, void* pvData);

        static void OnBlendOpChange(int iValue, void* pvData);

        static void OnSrcBlendAlphaChange(int iValue, void* pvData);

        static void OnDstBlendAlphaChange(int iValue, void* pvData);

        static void OnBlendOpAlphaChange(int iValue, void* pvData);

        static void OnWriteMaskChange(int iValue, void* pvData);

        QString m_kName;
        quint16 m_u16AlphaToCoverageEnable;
        quint16 m_u16NumRTDesc;
        QVector<State> m_kStateArray;

    };

    class DepthStencilState : public LeftItemSubData
    {
    public:
        enum ComparisonFunc
        {
            COMPARISON_NEVER           = 1,
            COMPARISON_LESS            = 2,
            COMPARISON_EQUAL           = 3,
            COMPARISON_LESS_EQUAL      = 4,
            COMPARISON_GREATER         = 5,
            COMPARISON_NOT_EQUAL       = 6,
            COMPARISON_GREATER_EQUAL   = 7,
            COMPARISON_ALWAYS          = 8
        };

        enum StencilOp
        {
            STENCIL_OP_KEEP       = 1,
            STENCIL_OP_ZERO       = 2,
            STENCIL_OP_REPLACE    = 3,
            STENCIL_OP_INCR_SAT   = 4,
            STENCIL_OP_DECR_SAT   = 5,
            STENCIL_OP_INVERT     = 6,
            STENCIL_OP_INCR       = 7,
            STENCIL_OP_DECR       = 8
        };

        DepthStencilState(QString& kName) : m_kName(kName)
        {
            m_u8ZEnable = 1;
            m_u8ZWrite = 1;
            m_u8ZFunc = COMPARISON_LESS;
            m_u8SEnable = 0;
            m_u8SReadMask = 0xff;
            m_u8SWriteMask = 0xff;
            m_u8SFrontFailOp = STENCIL_OP_KEEP;
            m_u8SFrontDepthFailOp = STENCIL_OP_KEEP;
            m_u8SFrontPassOp = STENCIL_OP_KEEP;
            m_u8SFrontFunc = COMPARISON_ALWAYS;
            m_u8SBackFailOp = STENCIL_OP_KEEP;
            m_u8SBackDepthFailOp = STENCIL_OP_KEEP;
            m_u8SBackPassOp = STENCIL_OP_KEEP;
            m_u8SBackFunc = COMPARISON_ALWAYS;
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnZEnableChange(bool bValue, void* pvData);

        static void OnZWriteChange(bool bValue, void* pvData);

        static void OnZFuncChange(int iValue, void* pvData);

        static void OnSEnableChange(bool bValue, void* pvData);

        static void OnSReadMaskChange(int iValue, void* pvData);

        static void OnSWriteMaskChange(int iValue, void* pvData);

        static void OnSFrontFailOpChange(int iValue, void* pvData);

        static void OnSFrontDepthFailOpChange(int iValue, void* pvData);

        static void OnSFrontPassOpChange(int iValue, void* pvData);

        static void OnSFrontFuncChange(int iValue, void* pvData);

        static void OnSBackFailOpChange(int iValue, void* pvData);

        static void OnSBackDepthFailOpChange(int iValue, void* pvData);

        static void OnSBackPassOpChange(int iValue, void* pvData);

        static void OnSBackFuncChange(int iValue, void* pvData);

        QString m_kName;
        quint8 m_u8ZEnable;
        quint8 m_u8ZWrite;
        quint8 m_u8ZFunc;
        quint8 m_u8SEnable;
        quint8 m_u8SReadMask;
        quint8 m_u8SWriteMask;
        quint8 m_u8SFrontFailOp;
        quint8 m_u8SFrontDepthFailOp;
        quint8 m_u8SFrontPassOp;
        quint8 m_u8SFrontFunc;
        quint8 m_u8SBackFailOp;
        quint8 m_u8SBackDepthFailOp;
        quint8 m_u8SBackPassOp;
        quint8 m_u8SBackFunc;

    };

    class RasterizerState : public LeftItemSubData
    {
    public:
        enum FillMode
        {
            FILL_WIREFRAME   = 2,
            FILL_SOLID       = 3
        };

        enum CullMode
        {
            CULL_NONE    = 1,
            CULL_FRONT   = 2,
            CULL_BACK    = 3
        };

        enum DepthBiasMode
        {
            DBIAS_NONE
        };

        RasterizerState(QString& kName) : m_kName(kName)
        {
            m_u8FillMode = FILL_SOLID;
            m_u8CullMode = CULL_BACK;
            m_u8FrontCCW = 0;
            m_u8DepthBias = DBIAS_NONE;
            m_u8DepthClipEnable = 1;
            m_u8ScissorEnable = 0;
            m_u8MultisampleEnable = 0;
            m_u8AntialiasedLineEnable = 0;
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnFillModeChange(int iValue, void* pvData);

        static void OnCullModeChange(int iValue, void* pvData);

        static void OnFrontCCWChange(bool bValue, void* pvData);

        static void OnDepthBiasChange(int iValue, void* pvData);

        static void OnDepthClipEnableChange(bool bValue, void* pvData);

        static void OnScissorEnableChange(bool bValue, void* pvData);

        static void OnMultisampleEnableChange(bool bValue, void* pvData);

        static void OnAntialiasedLineEnableChange(bool bValue, void* pvData);

        QString m_kName;
        quint8 m_u8FillMode;
        quint8 m_u8CullMode;
        quint8 m_u8FrontCCW;
        quint8 m_u8DepthBias;
        quint8 m_u8DepthClipEnable;
        quint8 m_u8ScissorEnable;
        quint8 m_u8MultisampleEnable;
        quint8 m_u8AntialiasedLineEnable;

    };

    class SamplerState : public LeftItemSubData
    {
    public:
        enum Filter
        {
            FILTER_MIN_MAG_MIP_POINT                            = 0,
            FILTER_MIN_MAG_POINT_MIP_LINEAR                     = 0x1,
            FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT               = 0x4,
            FILTER_MIN_POINT_MAG_MIP_LINEAR                     = 0x5,
            FILTER_MIN_LINEAR_MAG_MIP_POINT                     = 0x10,
            FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR              = 0x11,
            FILTER_MIN_MAG_LINEAR_MIP_POINT                     = 0x14,
            FILTER_MIN_MAG_MIP_LINEAR                           = 0x15,
            FILTER_ANISOTROPIC                                  = 0x55,
            FILTER_COMPARISON_MIN_MAG_MIP_POINT                 = 0x80,
            FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR          = 0x81,
            FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT    = 0x84,
            FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR          = 0x85,
            FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT          = 0x90,
            FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR   = 0x91,
            FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT          = 0x94,
            FILTER_COMPARISON_MIN_MAG_MIP_LINEAR                = 0x95,
            FILTER_COMPARISON_ANISOTROPIC                       = 0xd5
        };

        enum TextureAddressMode
        {
            TEXTURE_ADDRESS_WRAP          = 1,
            TEXTURE_ADDRESS_MIRROR        = 2,
            TEXTURE_ADDRESS_CLAMP         = 3,
            TEXTURE_ADDRESS_BORDER        = 4,
            TEXTURE_ADDRESS_MIRROR_ONCE   = 5
        };

        SamplerState(QString& kName) : m_kName(kName)
        {
            m_u8Filter = FILTER_MIN_MAG_MIP_LINEAR;
            m_u8AddressU = TEXTURE_ADDRESS_CLAMP;
            m_u8AddressV = TEXTURE_ADDRESS_CLAMP;
            m_u8AddressW = TEXTURE_ADDRESS_CLAMP;
            m_u16MaxAnisotropy = 16;
            m_u16ComparisonFunc = DepthStencilState::COMPARISON_NEVER;
            m_fMipLODBias = 0;
            m_fMinLOD = -FLT_MAX;
            m_fMaxLOD = FLT_MAX;
            m_afBorderColor[0] = 0;
            m_afBorderColor[1] = 0;
            m_afBorderColor[2] = 0;
            m_afBorderColor[3] = 0;
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnFilterChange(int iValue, void* pvData);

        static void OnAddressUChange(int iValue, void* pvData);

        static void OnAddressVChange(int iValue, void* pvData);

        static void OnAddressWChange(int iValue, void* pvData);

        static void OnMaxAnisotropyChange(int iValue, void* pvData);

        static void OnComparisonFuncChange(int iValue, void* pvData);

        static void OnMipLODBiasChange(float fValue, void* pvData);

        static void OnMinLODChange(float fValue, void* pvData);

        static void OnMaxLODChange(float fValue, void* pvData);

        static void OnBordeRedChange(float fValue, void* pvData);

        static void OnBordeGreenChange(float fValue, void* pvData);

        static void OnBordeBlueChange(float fValue, void* pvData);

        static void OnBordeAlphaChange(float fValue, void* pvData);

        QString m_kName;
        quint8 m_u8Filter;
        quint8 m_u8AddressU;
        quint8 m_u8AddressV;
        quint8 m_u8AddressW;
        quint16 m_u16MaxAnisotropy;
        quint16 m_u16ComparisonFunc;
        float m_fMipLODBias;
        float m_fMinLOD;
        float m_fMaxLOD;
        float m_afBorderColor[4];

    };

    class VertexShader : public LeftItemSubData
    {
    public:
        VertexShader(QString& kName) : m_kName(kName)
        {

        }

        static void OnNameChange(const QString& kValue, void* pvData);

        QString m_kName;
    };

    class PixelShader : public LeftItemSubData
    {
    public:
        PixelShader(QString& kName) : m_kName(kName)
        {

        }

        static void OnNameChange(const QString& kValue, void* pvData);

        QString m_kName;
    };

    class InputLayout : public LeftItemSubData
    {
    public:
        enum Semantic
        {
            SE_POSITION,
            SE_NORMAL,
            SE_COLOR,
            SE_TEXCOORD,
            SE_TANGENT,
            SE_BINORMAL,
            SE_BLENDINDICES,
            SE_BLENDWEIGHT,
            SEMANTIC_NUM
        };

        enum Format
        {
            FMT_UNKNOWN                      = 0,
            FMT_R32G32B32A32_TYPELESS        = 1,
            FMT_R32G32B32A32_FLOAT           = 2,
            FMT_R32G32B32A32_UINT            = 3,
            FMT_R32G32B32A32_SINT            = 4,
            FMT_R32G32B32_TYPELESS           = 5,
            FMT_R32G32B32_FLOAT              = 6,
            FMT_R32G32B32_UINT               = 7,
            FMT_R32G32B32_SINT               = 8,
            FMT_R16G16B16A16_TYPELESS        = 9,
            FMT_R16G16B16A16_FLOAT           = 10,
            FMT_R16G16B16A16_UNORM           = 11,
            FMT_R16G16B16A16_UINT            = 12,
            FMT_R16G16B16A16_SNORM           = 13,
            FMT_R16G16B16A16_SINT            = 14,
            FMT_R32G32_TYPELESS              = 15,
            FMT_R32G32_FLOAT                 = 16,
            FMT_R32G32_UINT                  = 17,
            FMT_R32G32_SINT                  = 18,
            FMT_R32G8X24_TYPELESS            = 19,
            FMT_D32_FLOAT_S8X24_UINT         = 20,
            FMT_R32_FLOAT_X8X24_TYPELESS     = 21,
            FMT_X32_TYPELESS_G8X24_UINT      = 22,
            FMT_R10G10B10A2_TYPELESS         = 23,
            FMT_R10G10B10A2_UNORM            = 24,
            FMT_R10G10B10A2_UINT             = 25,
            FMT_R11G11B10_FLOAT              = 26,
            FMT_R8G8B8A8_TYPELESS            = 27,
            FMT_R8G8B8A8_UNORM               = 28,
            FMT_R8G8B8A8_UNORM_SRGB          = 29,
            FMT_R8G8B8A8_UINT                = 30,
            FMT_R8G8B8A8_SNORM               = 31,
            FMT_R8G8B8A8_SINT                = 32,
            FMT_R16G16_TYPELESS              = 33,
            FMT_R16G16_FLOAT                 = 34,
            FMT_R16G16_UNORM                 = 35,
            FMT_R16G16_UINT                  = 36,
            FMT_R16G16_SNORM                 = 37,
            FMT_R16G16_SINT                  = 38,
            FMT_R32_TYPELESS                 = 39,
            FMT_D32_FLOAT                    = 40,
            FMT_R32_FLOAT                    = 41,
            FMT_R32_UINT                     = 42,
            FMT_R32_SINT                     = 43,
            FMT_R24G8_TYPELESS               = 44,
            FMT_D24_UNORM_S8_UINT            = 45,
            FMT_R24_UNORM_X8_TYPELESS        = 46,
            FMT_X24_TYPELESS_G8_UINT         = 47,
            FMT_R8G8_TYPELESS                = 48,
            FMT_R8G8_UNORM                   = 49,
            FMT_R8G8_UINT                    = 50,
            FMT_R8G8_SNORM                   = 51,
            FMT_R8G8_SINT                    = 52,
            FMT_R16_TYPELESS                 = 53,
            FMT_R16_FLOAT                    = 54,
            FMT_D16_UNORM                    = 55,
            FMT_R16_UNORM                    = 56,
            FMT_R16_UINT                     = 57,
            FMT_R16_SNORM                    = 58,
            FMT_R16_SINT                     = 59,
            FMT_R8_TYPELESS                  = 60,
            FMT_R8_UNORM                     = 61,
            FMT_R8_UINT                      = 62,
            FMT_R8_SNORM                     = 63,
            FMT_R8_SINT                      = 64,
            FMT_A8_UNORM                     = 65,
            FMT_R1_UNORM                     = 66,
            FMT_R9G9B9E5_SHAREDEXP           = 67,
            FMT_R8G8_B8G8_UNORM              = 68,
            FMT_G8R8_G8B8_UNORM              = 69,
            FMT_BC1_TYPELESS                 = 70,
            FMT_BC1_UNORM                    = 71,
            FMT_BC1_UNORM_SRGB               = 72,
            FMT_BC2_TYPELESS                 = 73,
            FMT_BC2_UNORM                    = 74,
            FMT_BC2_UNORM_SRGB               = 75,
            FMT_BC3_TYPELESS                 = 76,
            FMT_BC3_UNORM                    = 77,
            FMT_BC3_UNORM_SRGB               = 78,
            FMT_BC4_TYPELESS                 = 79,
            FMT_BC4_UNORM                    = 80,
            FMT_BC4_SNORM                    = 81,
            FMT_BC5_TYPELESS                 = 82,
            FMT_BC5_UNORM                    = 83,
            FMT_BC5_SNORM                    = 84,
            FMT_B5G6R5_UNORM                 = 85,
            FMT_B5G5R5A1_UNORM               = 86,
            FMT_B8G8R8A8_UNORM               = 87,
            FMT_B8G8R8X8_UNORM               = 88,
            FMT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
            FMT_B8G8R8A8_TYPELESS            = 90,
            FMT_B8G8R8A8_UNORM_SRGB          = 91,
            FMT_B8G8R8X8_TYPELESS            = 92,
            FMT_B8G8R8X8_UNORM_SRGB          = 93,
            FMT_BC6H_TYPELESS                = 94,
            FMT_BC6H_UF16                    = 95,
            FMT_BC6H_SF16                    = 96,
            FMT_BC7_TYPELESS                 = 97,
            FMT_BC7_UNORM                    = 98,
            FMT_BC7_UNORM_SRGB               = 99
        };

        enum InputClassification
        {
            PER_VERTEX_DATA     = 0,
            PER_INSTANCE_DATA   = 1
        };

        struct Element
        {
            Element()
            {
                m_u8SemanticType = SE_POSITION;
                m_u8SemanticIndex = 0;
                m_u8Format = FMT_R32G32B32_FLOAT;
                m_u8InputSlot = 0;
                m_u8AlignedByteOffset = 0;
                m_u8InputSlotClass = PER_VERTEX_DATA;
                m_u16InstanceStepRate = 0;
            }

            quint8 m_u8SemanticType;
            quint8 m_u8SemanticIndex;
            quint8 m_u8Format;
            quint8 m_u8InputSlot;
            quint8 m_u8AlignedByteOffset;
            quint8 m_u8InputSlotClass;
            quint16 m_u16InstanceStepRate;
        };

        InputLayout(QString& kName) : m_kName(kName), m_kVertexShader(kName)
        {
            m_u32NumElements = 1;
            m_kElementArray.resize(1);
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnVertexShaderChange(const QString& kValue, void* pvData);

        static void OnNumElementsChange(int iValue, void* pvData);

        static void OnSemanticTypeChange(int iValue, void* pvData);

        static void OnSemanticIndexChange(int iValue, void* pvData);

        static void OnFormatChange(int iValue, void* pvData);

        static void OnInputSlotChange(int iValue, void* pvData);

        static void OnAlignedByteOffsetChange(int iValue, void* pvData);

        static void OnInputSlotClassChange(int iValue, void* pvData);

        static void OnInstanceStepRateChange(int iValue, void* pvData);

        QString m_kName;
        QString m_kVertexShader;
        quint32 m_u32NumElements;
        QVector<Element> m_kElementArray;

    };

    class NodeData : public LeftItemSubData
    {
    public:
        enum RenderTickEnum
        {
            IA_INDEX_BUFFER,
            IA_INPUT_LAYOUT,
            IA_PRIMITIVE_TOPOLOGY,
            IA_VERTEX_BUFFER,
            VS_CONSTANT_BUFFER,
            VS_SHADER,
            RS_SCISSOR_RECT,
            RS_STATE,
            RS_VIEWPORT,
            PS_SAMPLER,
            PS_SHADER,
            PS_SHADER_RESOURCE,
            OM_BLEND_STATE,
            OM_DEPTH_STENCIL_STATE,
            OM_RENDER_TARGET_VIEW,
            OM_DEPTH_STENCIL_VIEW,
            TYPE_MAX
        };

        class RenderTick
        {
        public:
            RenderTick(RenderTickEnum eTick) : m_eRenderTick(eTick) {}

            virtual ~RenderTick() {}

            RenderTickEnum m_eRenderTick;
        };

        class IndexBuffer : public RenderTick
        {
        public:
            enum Format
            {
                R16_UINT = 57,
                R32_UINT = 42
            };

            IndexBuffer(const QString& kName) : RenderTick(IA_INDEX_BUFFER)
            {
                m_kName = kName;
                m_eFormat = R16_UINT;
            }

            QString m_kName;
            Format m_eFormat;

        };

        class InputLayout : public RenderTick
        {
        public:
            InputLayout(const QString& kName) : RenderTick(IA_INPUT_LAYOUT)
            {
                m_kName = kName;
            }

            QString m_kName;
        };

        class PrimitiveTopology : public RenderTick
        {
        public:
            enum Topology
            {
                TOPOLOGY_UNDEFINED                    = 0,
                TOPOLOGY_POINTLIST                    = 1,
                TOPOLOGY_LINELIST                     = 2,
                TOPOLOGY_LINESTRIP                    = 3,
                TOPOLOGY_TRIANGLELIST                 = 4,
                TOPOLOGY_TRIANGLESTRIP                = 5,
                TOPOLOGY_LINELIST_ADJ                 = 10,
                TOPOLOGY_LINESTRIP_ADJ                = 11,
                TOPOLOGY_TRIANGLELIST_ADJ             = 12,
                TOPOLOGY_TRIANGLESTRIP_ADJ            = 13,
                TOPOLOGY_1_CONTROL_POINT_PATCHLIST    = 33,
                TOPOLOGY_2_CONTROL_POINT_PATCHLIST    = 34,
                TOPOLOGY_3_CONTROL_POINT_PATCHLIST    = 35,
                TOPOLOGY_4_CONTROL_POINT_PATCHLIST    = 36,
                TOPOLOGY_5_CONTROL_POINT_PATCHLIST    = 37,
                TOPOLOGY_6_CONTROL_POINT_PATCHLIST    = 38,
                TOPOLOGY_7_CONTROL_POINT_PATCHLIST    = 39,
                TOPOLOGY_8_CONTROL_POINT_PATCHLIST    = 40,
                TOPOLOGY_9_CONTROL_POINT_PATCHLIST    = 41,
                TOPOLOGY_10_CONTROL_POINT_PATCHLIST   = 42,
                TOPOLOGY_11_CONTROL_POINT_PATCHLIST   = 43,
                TOPOLOGY_12_CONTROL_POINT_PATCHLIST   = 44,
                TOPOLOGY_13_CONTROL_POINT_PATCHLIST   = 45,
                TOPOLOGY_14_CONTROL_POINT_PATCHLIST   = 46,
                TOPOLOGY_15_CONTROL_POINT_PATCHLIST   = 47,
                TOPOLOGY_16_CONTROL_POINT_PATCHLIST   = 48,
                TOPOLOGY_17_CONTROL_POINT_PATCHLIST   = 49,
                TOPOLOGY_18_CONTROL_POINT_PATCHLIST   = 50,
                TOPOLOGY_19_CONTROL_POINT_PATCHLIST   = 51,
                TOPOLOGY_20_CONTROL_POINT_PATCHLIST   = 52,
                TOPOLOGY_21_CONTROL_POINT_PATCHLIST   = 53,
                TOPOLOGY_22_CONTROL_POINT_PATCHLIST   = 54,
                TOPOLOGY_23_CONTROL_POINT_PATCHLIST   = 55,
                TOPOLOGY_24_CONTROL_POINT_PATCHLIST   = 56,
                TOPOLOGY_25_CONTROL_POINT_PATCHLIST   = 57,
                TOPOLOGY_26_CONTROL_POINT_PATCHLIST   = 58,
                TOPOLOGY_27_CONTROL_POINT_PATCHLIST   = 59,
                TOPOLOGY_28_CONTROL_POINT_PATCHLIST   = 60,
                TOPOLOGY_29_CONTROL_POINT_PATCHLIST   = 61,
                TOPOLOGY_30_CONTROL_POINT_PATCHLIST   = 62,
                TOPOLOGY_31_CONTROL_POINT_PATCHLIST   = 63,
                TOPOLOGY_32_CONTROL_POINT_PATCHLIST   = 64
            };

            PrimitiveTopology() : RenderTick(IA_PRIMITIVE_TOPOLOGY)
            {
                m_eTopology = TOPOLOGY_TRIANGLELIST;
            }

            Topology m_eTopology;
        };

        class VertexBuffer : public RenderTick
        {
        public:
            VertexBuffer(const QString& kName) : RenderTick(IA_VERTEX_BUFFER)
            {
                m_kName = kName;
                m_u16Slot = 0;
                m_u16Stride = 0;
            }

            QString m_kName;
            quint16 m_u16Slot;
            quint16 m_u16Stride;
        };

        class ConstantBufferVS : public RenderTick
        {
        public:
            ConstantBufferVS(const QString& kName) : RenderTick(VS_CONSTANT_BUFFER)
            {
                m_kName = kName;
                m_u32Slot = 0;
            }

            QString m_kName;
            quint32 m_u32Slot;

        };

        class ShaderVS : public RenderTick
        {
        public:
            ShaderVS(const QString& kName) : RenderTick(VS_SHADER)
            {
                m_kName = kName;
            }

            QString m_kName;
        };

        class ScissorRect : public RenderTick
        {
        public:
            ScissorRect() : RenderTick(RS_SCISSOR_RECT)
            {
                m_u32Slot = 0;
                x = y = w = h = 0;
            }

            quint32 m_u32Slot;
            quint16 x;
            quint16 y;
            quint16 w;
            quint16 h;

        };

        class RasterizerState : public RenderTick
        {
        public:
            RasterizerState(const QString& kName) : RenderTick(RS_STATE)
            {
                m_kName = kName;
            }

            QString m_kName;
        };

        class ViewPort : public RenderTick
        {
        public:
            ViewPort() : RenderTick(RS_VIEWPORT)
            {
                m_u32Slot = 0;
                x = y = w = h = 0;
            }

            quint32 m_u32Slot;
            float x;
            float y;
            float w;
            float h;
        };

        class SamplerPS : public RenderTick
        {
        public:
            SamplerPS(const QString& kName) : RenderTick(PS_SAMPLER)
            {
                m_kName = kName;
                m_u32Slot = 0;
            }

            QString m_kName;
            quint32 m_u32Slot;

        };

        class ShaderPS : public RenderTick
        {
        public:
            ShaderPS(const QString& kName) : RenderTick(PS_SHADER)
            {
                m_kName = kName;
            }

            QString m_kName;
        };

        class ShaderResPS : public RenderTick
        {
        public:
            ShaderResPS(const QString& kName) : RenderTick(PS_SHADER_RESOURCE)
            {
                m_kName = kName;
                m_u32Slot = 0;
            }

            QString m_kName;
            quint32 m_u32Slot;

        };

        class BlendState : public RenderTick
        {
        public:
            BlendState(const QString& kName) : RenderTick(OM_BLEND_STATE)
            {
                m_kName = kName;
                m_fFactorR = 0.0;
                m_fFactorG = 0.0;
                m_fFactorB = 0.0;
                m_fFactorA = 0.0;
                m_u32SampleMask = 0xffffffff;
            }

            QString m_kName;
            float m_fFactorR;
            float m_fFactorG;
            float m_fFactorB;
            float m_fFactorA;
            quint32 m_u32SampleMask;

        };

        class DepthStencilState : public RenderTick
        {
        public:
            DepthStencilState(const QString& kName) : RenderTick(OM_DEPTH_STENCIL_STATE)
            {
                m_kName = kName;
                m_u32StencilRef = 0;
            }

            QString m_kName;
            quint32 m_u32StencilRef;

        };

        class RenderTargetView : public RenderTick
        {
        public:
            RenderTargetView(const QString& kName) : RenderTick(OM_RENDER_TARGET_VIEW)
            {
                m_kName = kName;
                m_u32Slot = 0;
            }

            QString m_kName;
            quint32 m_u32Slot;

        };

        class DepthStencilView : public RenderTick
        {
        public:
            DepthStencilView(const QString& kName) : RenderTick(OM_DEPTH_STENCIL_VIEW)
            {
                m_kName = kName;
            }

            QString m_kName;
        };

        NodeData(QString& kName) : m_kName(kName)
        {

        }

        ~NodeData()
        {
            for(int i(0); i < m_kRenderTickArray.size(); ++i)
            {
                delete m_kRenderTickArray[i];
            }
            m_kRenderTickArray.clear();
        }

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnRenderTickNameChange(const QString& kValue, void* pvData);

        static void OnIndexFormatChange(int iValue, void* pvData);

        static void OnTopologyChange(int iValue, void* pvData);

        static void OnVertexBufferSlotChange(int iValue, void* pvData);

        static void OnVertexBufferStrideChange(int iValue, void* pvData);

        static void OnContantBufferSlotChange(int iValue, void* pvData);

        static void OnScissorSlotChange(int iValue, void* pvData);

        static void OnScissorxChange(int iValue, void* pvData);

        static void OnScissoryChange(int iValue, void* pvData);

        static void OnScissorwChange(int iValue, void* pvData);

        static void OnScissorhChange(int iValue, void* pvData);

        static void OnViewportSlotChange(int iValue, void* pvData);

        static void OnViewportxChange(float fValue, void* pvData);

        static void OnViewportyChange(float fValue, void* pvData);

        static void OnViewportwChange(float fValue, void* pvData);

        static void OnViewporthChange(float fValue, void* pvData);

        static void OnSamplerSlotChange(int iValue, void* pvData);

        static void OnBlendFactorRChange(float fValue, void* pvData);

        static void OnBlendFactorGChange(float fValue, void* pvData);

        static void OnBlendFactorBChange(float fValue, void* pvData);

        static void OnBlendFactorAChange(float fValue, void* pvData);

        static void OnSampleMaskChange(int iValue, void* pvData);

        static void OnStencilRefChange(int iValue, void* pvData);

        static void OnRTVSlotChange(int iValue, void* pvData);

        QString m_kName;
        QVector<RenderTick*> m_kRenderTickArray;
    };

    class Node : public LeftItemSubData
    {
    public:
        QString m_kName;
        QString m_kDataName;
        QString m_kParent;

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnDataNameChange(const QString& kValue, void* pvData);

        static void OnParentNameChange(const QString& kValue, void* pvData);

    };

    class Material : public LeftItemSubData
    {
    public:
        QString m_kName;
        QVector<QString> m_kNodeList;

        static void OnNameChange(const QString& kValue, void* pvData);

        static void OnSchemeNumChange(int iValue, void* pvData);

        static void OnNodeNameChange(const QString& kValue, void* pvData);
    };

    class Platform : public LeftItemSubData
    {
    public:
        enum Type
        {
            TYPE_WINDOWS = 0x1,
            TYPE_LINUX = 0x2,
            TYPE_MACOSX = 0x4,
            TYPE_WINMOBSIM = 0x8,
            TYPE_IOS = 0x10,
            TYPE_ANDROID = 0x20
        };

        Platform(bool bWin = true, bool bLin = true, bool bMac = true, bool bIOS = true, bool bArd = true, bool bSim= true)
        {
            m_bWindows = bWin;
            m_bLinux = bLin;
            m_bMacosx = bMac;
            m_bIOS = bIOS;
            m_bAndroid = bArd;
            m_bWinMobSim = bSim;
        }

        static void OnWindowsChange(bool bValue, void* pvData);

        static void OnLinuxChange(bool bValue, void* pvData);

        static void OnMacosxChange(bool bValue, void* pvData);

        static void OnIOSChange(bool bValue, void* pvData);

        static void OnAndroidChange(bool bValue, void* pvData);

        static void OnWinMobSimChange(bool bValue, void* pvData);

        bool m_bWindows;
        bool m_bLinux;
        bool m_bMacosx;
        bool m_bIOS;
        bool m_bAndroid;
        bool m_bWinMobSim;
    };

    struct LeftItemData
    {
        ~LeftItemData()
        {
            if(m_pkData)
            {
                delete m_pkData;
                m_pkData = NULL;
            }
        }

        LeftItemType m_eType;
        unsigned int m_uiTypeSec;
        LeftItemSubData* m_pkData;
    };

    explicit MaterialDoc(const QString& kName, QWidget* pkParent = NULL);
    ~MaterialDoc();

    void Edit();

    void UpdateRight();

    void UpdateBlendState(BlendState* pkBlendState);

    void UpdateDepthStencilState(DepthStencilState* pkDepthState);

    void UpdateRasterizerState(RasterizerState* pkRasterizerState);

    void UpdateSamplerState(SamplerState* pkSamplerState);

    void UpdateInputLayoutElements(InputLayout* pkInputLayout);

    void UpdateMaterial(Material* pkMaterial);

    void CreatePlatform(bool bWin = true, bool bLin = true, bool bMac = true, bool bIOS = true, bool bArd = true, bool bSim= true);

    void SaveToStream(QDataStream& kStream);

    quint32 SavePlatformToStream(QTreeWidgetItem* pkPlatform, QDataStream& kStream);

    void SaveRenderObjectToStream(QTreeWidgetItem* pkRenderObject, QDataStream& kStream);

    void SaveNodeDataToStream(QTreeWidgetItem* pkNodeData, QDataStream& kStream);

    void SaveNodeToStream(QTreeWidgetItem* pkNode, QDataStream& kStream);

    void SaveMaterialToStream(QTreeWidgetItem* pkMaterial, QDataStream& kStream);

    void LoadFromStream(QDataStream& kStream);

    void LoadPlatformFromStream(QDataStream& kStream, QTreeWidgetItem* pkPlatform);

    void LoadRenderObject(QDataStream& kStream, QTreeWidgetItem* pkRenderObjectRoot);

    void LoadNodeData(QDataStream& kStream, QTreeWidgetItem* pkNodeDataRoot);

    void LoadNode(QDataStream& kStream, QTreeWidgetItem* pkNodeRoot);

    void LoadMaterial(QDataStream& kStream, QTreeWidgetItem* pkMatRoot);
    
    QString m_kName;
    QTreeWidget* m_pkLeft;
    PropertyList* m_pkRight;
    QMap<QTreeWidgetItem*, LeftItemData> m_kLeftItemMap;
    QTreeWidgetItem* m_pkCurrentOnProcess;
    bool m_bEdited;

private:
    void InitLeft();

    void InitRight();

    void UpdateName();

private slots:
    void ShowLeftTreeContextMenu(const QPoint& kPos);

    void CleanLeft();

};
