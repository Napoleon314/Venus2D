cbuffer cbSprite0 : register(b0)
{
	float4 cb_v4ScreenParams;
};

struct ShapeParam
{
	float4 m_v4Transform0;
	float4 m_v4Transform1;
	float4 m_v4Color;
};

cbuffer cbSprite1 : register(b1)
{
	ShapeParam m_akParam[50];
};

struct InputVS
{
	float2 m_v2Pos : POSITION0;
};

struct OutputVS
{
	float4 m_v4Pos : SV_POSITION;
	half4 m_v4Color : COLOR0;
};

OutputVS VeMainVS(InputVS kIn, uint uIndex : SV_InstanceID)
{
	OutputVS kOut = (OutputVS)0;
	float2 v2Pos = kIn.m_v2Pos * m_akParam[uIndex].m_v4Transform1.zw;
	v2Pos = float2(dot(v2Pos, m_akParam[uIndex].m_v4Transform0.xz), dot(v2Pos, m_akParam[uIndex].m_v4Transform0.yw)) + m_akParam[uIndex].m_v4Transform1.xy;
	kOut.m_v4Pos = float4(v2Pos * cb_v4ScreenParams.xy * float2(2.0,-2.0) - float2(1.0,-1.0), 0.0, 1.0);
	kOut.m_v4Color = m_akParam[uIndex].m_v4Color;
	return kOut;
}

struct InputPS
{
	float4 m_v4Pos : SV_POSITION;
	half4 m_v4Color : COLOR0;
};

struct OutputPS
{
	float4 m_v4Color : SV_TARGET;
};

OutputPS VeMainPS(InputPS kIn)
{
	OutputPS kOut = (OutputPS)0;
	kOut.m_v4Color = kIn.m_v4Color;
	return kOut;
}
