cbuffer cbSprite0 : register(b0)
{
	float4 cb_v4ScreenParams;
};

cbuffer cbSprite1 : register(b1)
{
	float4 cb_v4TexParams;
};

struct SpriteParam
{
	float4 m_v4Texcoord;
	float4 m_v4Transform0;
	float4 m_v4Transform1;
	float4 m_v4MulColor;
	float4 m_v4AddColor;
};

cbuffer cbSprite2 : register(b2)
{
	SpriteParam m_akParam[50];
};

struct InputVS
{
	float2 m_v2Pos : POSITION0;
};

struct OutputVS
{
	float4 m_v4Pos : SV_POSITION;
	float2 m_v2Tex : TEXCOORD0;
	float4 m_v4TexRange : TEXCOORD1;
	half4 m_v4MulColor : COLOR0;
	half4 m_v4AddColor : COLOR1;
};

OutputVS VeMainVS(InputVS kIn, uint uIndex : SV_InstanceID)
{
	OutputVS kOut = (OutputVS)0;
	float2 v2PosInPixel = kIn.m_v2Pos * m_akParam[uIndex].m_v4Texcoord.xy;
	float2 v2Pos = float2(dot(v2PosInPixel, m_akParam[uIndex].m_v4Transform0.xz), dot(v2PosInPixel, m_akParam[uIndex].m_v4Transform0.yw)) + m_akParam[uIndex].m_v4Transform1.xy;
	kOut.m_v4Pos = float4(v2Pos * cb_v4ScreenParams.xy * float2(2.0,-2.0) - float2(1.0,-1.0), 0.0, 1.0);
	kOut.m_v2Tex = (v2PosInPixel + m_akParam[uIndex].m_v4Texcoord.zw) * cb_v4TexParams.xy;
	kOut.m_v4TexRange = (float4(m_akParam[uIndex].m_v4Texcoord.zw, m_akParam[uIndex].m_v4Texcoord.zw + m_akParam[uIndex].m_v4Texcoord.xy) + float4(0.5,0.5,-0.5,-0.5)) * cb_v4TexParams.xyxy;
	kOut.m_v4MulColor = m_akParam[uIndex].m_v4MulColor;
	kOut.m_v4AddColor = m_akParam[uIndex].m_v4AddColor;
	return kOut;
}

Texture2D tex0 : register(t0);
SamplerState samp0 : register(s0);

struct InputPS
{
	float4 m_v4Pos : SV_POSITION;
	float2 m_v2Tex : TEXCOORD0;
	float4 m_v4TexRange : TEXCOORD1;
	half4 m_v4MulColor : COLOR0;
	half4 m_v4AddColor : COLOR1;
};

struct OutputPS
{
	float4 m_v4Color : SV_TARGET;
};

OutputPS VeMainPS(InputPS kIn)
{
	OutputPS kOut = (OutputPS)0;
	float2 v2Tex = float2(clamp(kIn.m_v2Tex.x, kIn.m_v4TexRange.x, kIn.m_v4TexRange.z),clamp(kIn.m_v2Tex.y, kIn.m_v4TexRange.y, kIn.m_v4TexRange.w));
	kOut.m_v4Color = tex0.Sample(samp0, v2Tex) * kIn.m_v4MulColor + kIn.m_v4AddColor;
	return kOut;
}
