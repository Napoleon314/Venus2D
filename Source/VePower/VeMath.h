////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMath.h
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#if defined(VE_ENABLE_SSE)
#	include <xmmintrin.h>
#endif

#define VE_MAXFLOAT_F			(3.402823466e+38F)
#define VE_MINFLOAT_F			(0.00000001F)
#define VE_MATH_E_F				(2.7182818284590452354f)
#define VE_MATH_LOG2E_F			(1.4426950408889634074f)
#define VE_MATH_LOG10E_F		(0.43429448190325182765f)
#define VE_MATH_LN2_F			(0.69314718055994530942f)
#define VE_MATH_LN10_F			(2.30258509299404568402f)
#define VE_MATH_PI_F			(3.14159265358979323846f)
#define VE_MATH_2PI_F			(6.28318530717958647692f)
#define VE_MATH_3PI_F			(9.42477796076937971538f)
#define VE_MATH_PI_2_F			(1.57079632679489661923f)
#define VE_MATH_PI_4_F			(0.78539816339744830962f)
#define VE_MATH_3PI_4_F			(2.3561944901923448370E0f)
#define VE_MATH_SQRTPI_F		(1.77245385090551602792981f)
#define VE_MATH_1_PI_F			(0.31830988618379067154f)
#define VE_MATH_2_PI_F			(0.63661977236758134308f)
#define VE_MATH_2_SQRTPI_F		(1.12837916709551257390f)
#define VE_MATH_SQRT2_F			(1.41421356237309504880f)
#define VE_MATH_SQRT1_2_F		(0.70710678118654752440f)
#define VE_MATH_LN2LO_F			(1.9082149292705877000E-10f)
#define VE_MATH_LN2HI_F			(6.9314718036912381649E-1f)
#define VE_MATH_SQRT3_F		   	(1.73205080756887719000f)
#define VE_MATH_IVLN10_F		(0.43429448190325182765f)
#define VE_MATH_LOG2_E_F		(0.693147180559945309417f)
#define VE_MATH_INVLN2_F		(1.4426950408889633870E0f)
#define VE_MATH_EPSILON_F		(0.0004f)

#define VeAtanf atanf
#define VeCosf cosf
#define VeSinf sinf
#define VeTanf tanf
#define VeTanhf tanhf
#define VeFrexpf frexpf
#define VeModff modff
#define VeCeilf ceilf
#define VeFabsf fabsf
#define VeFloorf floorf

#define VeAcosf acosf
#define VeAsinf asinf
#define VeAtan2f atan2f
#define VeCoshf coshf
#define VeSinhf sinhf
#define VeExpf expf
#define VeLdexpf ldexpf
#define VeLogf logf
#define VeLog10f log10f
#define VePowf powf
#define VeFmodf fmodf

#define VeAtan atan
#define VeCos cos
#define VeSin sin
#define VeTan tan
#define VeTanh tanh
#define VeFrexp frexp
#define VeModf modf
#define VeCeil ceil
#define VeFabs fabs
#define VeFloor floor

#define VeAcos acos
#define VeAsin asin
#define VeAtan2 atan2
#define VeCosh cosh
#define VeSinh sinh
#define VeExp exp
#define VeLdexp ldexp
#define VeLog log
#define VeLog10 log10
#define VePow pow
#define VeFmod fmod

#define VeDegreeToRadiantf(D)	((D) * 0.01745329251994329576923690768f)
#define VeRadiantToDegreef(R)	((R) * 57.2957795130823208767981548f)
#define VeFracf(number)			((number)-(VeFloat32)((VeInt32)(number)))

#define VeClampEx(min,val,max)	((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))
#define VeClamp(mag,val)		(VeClampEx(-(mag),(val),(mag)))

VE_FORCE_INLINE VeFloat32 VeSignf(VeFloat32 f32Value)
{
	return f32Value > 0 ? 1.0f : (f32Value < 0 ? -1.0f : 0.0f);
}

#define VeIntervalMapping(x,src_a,src_b,dst_a,dst_b) \
	(((dst_b) - (dst_a)) * ((x) - (src_a)) / ((src_b) - (src_a)) + dst_a)

#define VeLerp(t,a,b) ((a) + ((b) - (a)) * (t))

template <class T>
T VeTLerp(VeFloat32 t, const T& a, const T& b)
{
	return VeLerp(t, a, b);
}

template <typename T>
T VeTAbs(T a)
{
	return a > T(0) ? a : -a;
}

#define VeExchangeXor(a,b) \
	(a) = (a) ^ (b); \
	(b) = (a) ^ (b); \
	(a) = (a) ^ (b)

#define VeExchangeClass(a,b,class) \
	{ \
		class t((a)); \
		(a) = (b); \
		(b) = t; \
	}

#define VeExchangeBuffer(a,b,t) \
	t = (a); \
	(a) = (b); \
	(b) = t

#ifdef VE_USE_FAST_SQRT

#define VeSqrtf VeFastSqrtf
#define VeInvSqrtf VeFastInvSqrtf

#else

#define VeSqrtf sqrtf
#define VeInvSqrtf(v) (1.0f / sqrtf((v)))

#endif

#define VE_FLOAT_EQUAL(Value1, Value2) (VeFabsf(Value1 - Value2) < VE_MATH_EPSILON_F)

VE_POWER_INLINE bool VeAlmostEqual(const VeFloat32 f1, const VeFloat32 f2, const VeFloat32 f32Epsilon = VE_MATH_EPSILON_F);

VE_POWER_INLINE bool VeAlmostEqual(const VeFloat64 f1, const VeFloat64 f2, const VeFloat64 f64Epsilon = VE_MATH_EPSILON_F);

VE_POWER_INLINE bool VeAlmostZero(const VeFloat32 f, const VeFloat32 f32Epsilon = VE_MATH_EPSILON_F);

VE_POWER_INLINE bool VeAlmostZero(const VeFloat64 f, const VeFloat64 f64Epsilon = VE_MATH_EPSILON_F);

#define VE_FLOAT_POINT(p) ((VeFloat32*)p)
#define VE_FLOAT_POINT_CONST(p) ((const VeFloat32*)p)
#define VE_FLOAT_POINT_THIS ((VeFloat32*)this)

enum VeOutcode
{
	VE_OUTCODE_NULL		= 0x0,
	VE_OUTCODE_LEFT		= 0x1,
	VE_OUTCODE_RIGHT	= 0x2,
	VE_OUTCODE_BOTTOM	= 0x4,
	VE_OUTCODE_TOP		= 0x8,
	VE_OUTCODE_NEAR		= 0x10,
	VE_OUTCODE_FAR		= 0x20,
	VE_OUTCODE_MASK		= 0x3F
};

extern "C"
{
	VE_POWER_INLINE bool VeIsValid(VeFloat32 f32Value);

	VE_POWER_INLINE void VeSinCosf(VeFloat32* pf32Sin, VeFloat32* pf32Cos, VeFloat32 f32Radians);

	VE_POWER_INLINE VeFloat32 VeRoundf(VeFloat32 f32Value);
	VE_POWER_INLINE VeInt32 VeRoundfToInt(VeFloat32 f32Value);
	VE_POWER_INLINE VeFloat64 VeRound(VeFloat64 f64Value);
	VE_POWER_INLINE VeInt32 VeRoundToInt(VeFloat64 f64Value);

	VE_POWER_INLINE VE_BOOL VePowerOfTwo(VeUInt32 u32Number);

	VE_POWER_INLINE VeFloat32 VeDecayf(VeFloat32 f32SrcValue, VeFloat32 f32DstValue, VeFloat32 f32HalfLife, VeFloat32 f32DeltaTime);
	VE_POWER_INLINE VeFloat64 VeDecay(VeFloat64 f64SrcValue, VeFloat64 f64DstValue, VeFloat64 f64HalfLife, VeFloat64 f64DeltaTime);

	VE_POWER_INLINE void VeSrand(VeUInt32 u32Seed);
	VE_POWER_INLINE VeInt32 VeRand();
	VE_POWER_INLINE VeFloat32 VeSymmetricRandomf();
	VE_POWER_INLINE VeFloat32 VeUnitRandomf();
	VE_POWER_INLINE VeFloat32 VeRangeRandomf(VeFloat32 f32Min, VeFloat32 f32Max);

	VE_POWER_INLINE VeFloat32 VeFastInvSqrtf(VeFloat32 f32Value);
	VE_POWER_INLINE VeFloat32 VeFastSqrtf(VeFloat32 f32Value);

	VE_POWER_INLINE VeFloat32 VeNormaliseAnglef(VeFloat32 f32Aangle);
	VE_POWER_INLINE VeFloat32 VeSameSignAnglef(VeFloat32 f32Aangle, VeFloat32 f32Closest);
	VE_POWER_INLINE VeFloat32 VeTurnRangeAnglef(VeFloat32 f32From, VeFloat32 f32To);

#if defined(VE_ENABLE_SSE)

	VE_POWER_INLINE __m128 VeVector3DotSSE(__m128 v0, __m128 v1);
	VE_POWER_INLINE __m128 VeVector3CrossSSE(__m128 v0, __m128 v1);
	VE_POWER_INLINE __m128 VeVector3TransformM3SSE(__m128 v, __m128& c0, __m128& c1, __m128& c2);

	VE_POWER_INLINE __m128 VeVector4DotSSE(__m128 v0, __m128 v1);
	VE_POWER_INLINE __m128 VeVector4LerpSSE(__m128 t, __m128 a, __m128 b);
	VE_POWER_INLINE __m128 VeVector4PosNormalizeSSE(__m128 v);
	VE_POWER_INLINE __m128 VeVector4TransformM4SSE(__m128 v, __m128& c0, __m128& c1, __m128& c2, __m128& c3);

	VE_POWER_INLINE void VeMatrix3TransposeSSE(__m128& c0, __m128& c1, __m128& c2);

#endif

	VE_POWER_INLINE void VeZero2f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero3f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero4f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero6f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero16f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero4A16f(VeFloat32* pf32Dst);
	VE_POWER_INLINE void VeZero16A16f(VeFloat32* pf32Dst);

	VE_POWER_INLINE void VeSet2f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1);
	VE_POWER_INLINE void VeSet3f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1, VeFloat32 v2);
	VE_POWER_INLINE void VeSet4f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1, VeFloat32 v2, VeFloat32 v3);
	VE_POWER_INLINE void VeSet6f(VeFloat32* pf32Dst, VeFloat32 t00, VeFloat32 t01, VeFloat32 t10, VeFloat32 t11, VeFloat32 t20, VeFloat32 t21);
	VE_POWER_INLINE void VeSet16f(VeFloat32* pf32Dst
		, VeFloat32 m00, VeFloat32 m01, VeFloat32 m02, VeFloat32 m03
		, VeFloat32 m10, VeFloat32 m11, VeFloat32 m12, VeFloat32 m13
		, VeFloat32 m20, VeFloat32 m21, VeFloat32 m22, VeFloat32 m23
		, VeFloat32 m30, VeFloat32 m31, VeFloat32 m32, VeFloat32 m33);
	VE_POWER_INLINE void VeSet4A16f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1, VeFloat32 v2, VeFloat32 v3);
	VE_POWER_INLINE void VeSet16A16f(VeFloat32* pf32Dst
		, VeFloat32 m00, VeFloat32 m01, VeFloat32 m02, VeFloat32 m03
		, VeFloat32 m10, VeFloat32 m11, VeFloat32 m12, VeFloat32 m13
		, VeFloat32 m20, VeFloat32 m21, VeFloat32 m22, VeFloat32 m23
		, VeFloat32 m30, VeFloat32 m31, VeFloat32 m32, VeFloat32 m33);

	VE_POWER_INLINE void VeSet2f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet3f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet4f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet6f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet4A16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);
	VE_POWER_INLINE void VeSet16A16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar);

	VE_POWER_INLINE void VeCopy2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy6f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeCopy16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);

	VE_POWER_INLINE void VeAdd2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeAdd3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeAdd4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeAdd16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeAdd4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeAdd16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);

	VE_POWER_INLINE void VeSub2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeSub3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeSub4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeSub16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeSub4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeSub16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);

	VE_POWER_INLINE void VeMul2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeMul3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeMul4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeMul16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeMul4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeMul16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);

	VE_POWER_INLINE void VeDiv2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeDiv3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeDiv4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeDiv16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeDiv4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE void VeDiv16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);

	VE_POWER_INLINE void VeScale2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);
	VE_POWER_INLINE void VeScale3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);
	VE_POWER_INLINE void VeScale4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);
	VE_POWER_INLINE void VeScale16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);
	VE_POWER_INLINE void VeScale4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);
	VE_POWER_INLINE void VeScale16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src, VeFloat32 f32Scale);

	VE_POWER_INLINE VeFloat32 VeLengthSqr2f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLengthSqr3f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLengthSqr4f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLengthSqr3A16f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLengthSqr4A16f(const VeFloat32* pf32Src);

	VE_POWER_INLINE VeFloat32 VeLength2f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLength3f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLength4f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLength3A16f(const VeFloat32* pf32Src);
	VE_POWER_INLINE VeFloat32 VeLength4A16f(const VeFloat32* pf32Src);

	VE_POWER_INLINE void VeNormalize2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeNormalize3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeNormalize4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeNormalize3A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);
	VE_POWER_INLINE void VeNormalize4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src);

	VE_POWER_INLINE VeFloat32 VeDot2f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE VeFloat32 VeDot3f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE VeFloat32 VeDot4f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE VeFloat32 VeDot3A16f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);
	VE_POWER_INLINE VeFloat32 VeDot4A16f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1);

	VE_POWER_INLINE void VeLerp2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1, VeFloat32 t);
	VE_POWER_INLINE void VeLerp3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1, VeFloat32 t);
	VE_POWER_INLINE void VeLerp4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1, VeFloat32 t);
	VE_POWER_INLINE void VeLerp3A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1, VeFloat32 t);
	VE_POWER_INLINE void VeLerp4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0, const VeFloat32* pf32Src1, VeFloat32 t);

	VE_POWER_INLINE VeFloat32 VeVector2Crossf(const VeFloat32* pf32Vec0, const VeFloat32* pf32Vec1);
	VE_POWER_INLINE void VeVector3Crossf(VeFloat32* pf32Out, const VeFloat32* pf32Vec0, const VeFloat32* pf32Vec1);
	VE_POWER_INLINE void VeVector3CrossA16f(VeFloat32* pf32Out, const VeFloat32* pf32Vec0, const VeFloat32* pf32Vec1);

	VE_POWER_INLINE void VeVector3TransformM4f(VeFloat32* pf32OutVec4, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector3TransformCoordM4f(VeFloat32* pf32OutVec3, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector3TransformNormalM4f(VeFloat32* pf32OutVec3, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector3TransformM4A16f(VeFloat32* pf32OutVec4, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector3TransformCoordM4A16f(VeFloat32* pf32OutVec3, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector3TransformNormalM4A16f(VeFloat32* pf32OutVec3, const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4);

	VE_POWER_INLINE void VeVector3SetPitchYawf(VeFloat32* pf32OutVec3, VeFloat32 f32PitchInRadians, VeFloat32 f32YawInRadians);
	VE_POWER_INLINE VeFloat32 VeVector3GetPitchf(VeFloat32* pf32Vec3);
	VE_POWER_INLINE VeFloat32 VeVector3GetYawf(VeFloat32* pf32Vec3);

	VE_POWER_INLINE void VeVector4Transformf(VeFloat32* pf32OutVec4, const VeFloat32* pf32Vec4, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeVector4TransformA16f(VeFloat32* pf32OutVec4, const VeFloat32* pf32Vec4, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE VeUInt32 VeVector4Outcode(const VeFloat32* pf32Vec4);

	VE_POWER_INLINE void VeMatrixIdenty4f(VeFloat32* pf32OutMat4x4);
	VE_POWER_INLINE VE_BOOL VeMatrixInverse4f(VeFloat32* pf32OutMat4x4, VeFloat32* pf32Determinant, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeMatrixTranspose4f(VeFloat32* pf32OutMat4x4, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeMatrixTranspose4A16f(VeFloat32* pf32OutMat4x4, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE VeFloat32 VeMatrixDeterminant4f(const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeMatrixMultiply4f(VeFloat32* pf32OutMat4x4, const VeFloat32* pf32Mat4x4Src0, const VeFloat32* pf32Mat4x4Src1);
	VE_POWER_INLINE void VeMatrixRotationX4f(VeFloat32* pf32OutMat4x4, VeFloat32 f32Angle);
	VE_POWER_INLINE void VeMatrixRotationY4f(VeFloat32* pf32OutMat4x4, VeFloat32 f32Angle);
	VE_POWER_INLINE void VeMatrixRotationZ4f(VeFloat32* pf32OutMat4x4, VeFloat32 f32Angle);
	VE_POWER_INLINE void VeMatrixScaling4f(VeFloat32* pf32OutMat4x4, VeFloat32 f32ScaleX, VeFloat32 f32ScaleY, VeFloat32 f32ScaleZ);
	VE_POWER_INLINE void VeMatrixTranslation4f(VeFloat32* pf32OutMat4x4, VeFloat32 x, VeFloat32 y, VeFloat32 z);
	VE_POWER_INLINE void VeMatrixRotationYawPitchRoll4f(VeFloat32* pf32OutMat4x4, VeFloat32 f32Yaw, VeFloat32 f32Pitch, VeFloat32 f32Roll);
	VE_POWER_INLINE void VeMatrixRotationQuaternion4f(VeFloat32* pf32OutMat4x4, const VeFloat32* pfQuat);
	VE_POWER_INLINE void VeMatrixDecomposeWorld4f(VeFloat32* pf32OutQuat, VeFloat32* pf32OutVec3Scale, VeFloat32* pf32OutVec3Trans, const VeFloat32* pf32Mat4x4);

	VE_POWER_INLINE void VeMatrixPerspectiveFovLH_DX(VeFloat32* pf32OutMat4x4, VeFloat32 fov, VeFloat32 aspect, VeFloat32 znear, VeFloat32 zfar);
	VE_POWER_INLINE void VeMatrixPerspectiveFovLH_GL(VeFloat32* pf32OutMat4x4, VeFloat32 fov, VeFloat32 aspect, VeFloat32 znear, VeFloat32 zfar);

	VE_POWER_INLINE void VeQuaternionRotationMatrixf(VeFloat32* pf32OutQuat, const VeFloat32* pf32Mat4x4);
	VE_POWER_INLINE void VeQuaternionRotationAxisf(VeFloat32* pf32OutQuat, const VeFloat32* pf32Vec3, VeFloat32 f32Angle);
	VE_POWER_INLINE void VeQuaternionMultiplyf(VeFloat32* pf32OutQuat, const VeFloat32* pf32Quat0, const VeFloat32* pf32Quat1);
	VE_POWER_INLINE void VeQuaternionInversef(VeFloat32* p32OutQuat, const VeFloat32* pf32Quat);

	VE_POWER_INLINE void VeTransformIdenty6f(VeFloat32* pf32Dst);

}

#ifndef VE_NO_INLINE
#	include "VeMath.inl"
#endif

#include "VeAngle.h"
#include "VeColor.h"
#include "VeVector2D.h"
#include "VeVector3D.h"
#include "VeVector4D.h"
#include "VeLine2D.h"
#include "VeQuaternion.h"
#include "VeMatrix.h"
#include "VeBoundingBox.h"
#include "VeTransform.h"
