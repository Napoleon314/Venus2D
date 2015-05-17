cbuffer cbCamera : register(b0)
{
	matrix ViewProj;
};

cbuffer cbWorld : register(b1)
{
	float4 Rotate;
	float4 TranslateScale;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	half4 Color : COLOR;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	half4 Color : COLOR;
};

PS_INPUT VeMainVS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	float4 pos = input.Pos;
	pos.xyz *= TranslateScale.w;
	float3 uv = cross(Rotate.xyz, pos.xyz);
	float3 uuv = cross(Rotate.xyz, uv) * 2.0;
	uv *= (2.0 * Rotate.w);
	pos.xyz += uv + uuv;
	pos.xyz += TranslateScale.xyz;
	
	output.Pos = mul(pos, ViewProj);
  output.Color = input.Color;
	return output;
}

float4 VeMainPS(PS_INPUT input) : SV_Target
{
	return input.Color;
}

Texture2D tex0 : register(t0);
SamplerState samp0 : register(s0);

struct VS_QUAD_INPUT
{
	float4 Pos : POSITION;
};

struct PS_QUAD_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

PS_QUAD_INPUT VeQuadVS(VS_QUAD_INPUT input)
{
	PS_QUAD_INPUT output = (PS_QUAD_INPUT)0;
	output.Pos = input.Pos;
  output.Tex = input.Pos.xy * float2(0.5, -0.5) + 0.5;
	return output;
}

float4 VeQuadPS(PS_QUAD_INPUT input) : SV_Target
{
	return tex0.Sample(samp0, input.Tex);
}
