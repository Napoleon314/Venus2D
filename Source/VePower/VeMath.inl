////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMath.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostEqual(const VeFloat32 f1, const VeFloat32 f2,
	const VeFloat32 f32Epsilon)
{
	return VeFabsf(f1 - f2) < f32Epsilon;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostEqual(const VeFloat64 f1, const VeFloat64 f2,
	const VeFloat64 f64Epsilon)
{
	return VeFabs(f1 - f2) < f64Epsilon;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostZero(const VeFloat32 f, const VeFloat32 f32Epsilon)
{
	return f < f32Epsilon && f > -f32Epsilon;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostZero(const VeFloat64 f, const VeFloat64 f64Epsilon)
{
	return f < f64Epsilon && f > -f64Epsilon;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeIsValid(VeFloat32 f32Value)
{
	VeUInt32 u32Value = *(VeUInt32*)&f32Value;
	return (u32Value & 0x7f800000) != 0x7f800000;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSinCosf(VeFloat32* pf32Sin, VeFloat32* pf32Cos,
	VeFloat32 f32Radians)
{
	*pf32Sin = VeSinf(f32Radians);
	*pf32Cos = VeCosf(f32Radians);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRoundf(VeFloat32 f32Value)
{
	return VeFloorf(f32Value + 0.5f);
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeRoundfToInt(VeFloat32 f32Value)
{
	return (VeInt32)VeRoundf(f32Value);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeRound(VeFloat64 f64Value)
{
	return VeFloor(f64Value + 0.5);
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeRoundToInt(VeFloat64 f64Value)
{
	return (VeInt32)VeRound(f64Value);
}
//--------------------------------------------------------------------------
VE_INLINE VE_BOOL VePowerOfTwo(VeUInt32 u32Number)
{
	return u32Number ? ((u32Number & (- (int)u32Number)) == u32Number)
		: VE_FALSE;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDecayf(VeFloat32 f32SrcValue, VeFloat32 f32DstValue,
	VeFloat32 f32HalfLife, VeFloat32 f32DeltaTime)
{
	if(f32HalfLife <= 0.0f)
	{
		return f32DstValue;
	}
	else
	{
		return f32DstValue + VePowf(0.5f, f32DeltaTime / f32HalfLife)
			* (f32SrcValue - f32DstValue);
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeDecay(VeFloat64 f64SrcValue, VeFloat64 f64DstValue,
	VeFloat64 f64HalfLife, VeFloat64 f64DeltaTime)
{
	if(f64HalfLife <= 0.0)
	{
		return f64DstValue;
	}
	else
	{
		return f64DstValue + VePow(0.5, f64DeltaTime / f64HalfLife)
			* (f64SrcValue - f64DstValue);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeSrand(VeUInt32 u32Seed)
{
	srand(u32Seed);
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeRand()
{
	return rand();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSymmetricRandomf()
{
	return -1.0f + ((VeFloat32)VeRand()) * (2.0f / ((VeFloat32)RAND_MAX));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUnitRandomf()
{
	return ((VeFloat32)VeRand()) * (1.0f / ((VeFloat32)RAND_MAX));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRangeRandomf(VeFloat32 f32Min, VeFloat32 f32Max)
{
	return f32Min + VeUnitRandomf() * (f32Max - f32Min);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeFastInvSqrtf(VeFloat32 f32Value)
{
	union VeFloatBin
	{
		VeFloat32 f;
		VeInt32 i;
	};
	VeFloat32 f32Half = 0.5f * f32Value;
	VeFloatBin kValue;
	kValue.f = f32Value;
	kValue.i = 0x5f3759df - (kValue.i >> 1);				//What the fuck!
	f32Value = kValue.f;
	f32Value = f32Value * (1.5f - f32Half * f32Value * f32Value);
	return f32Value;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeFastSqrtf(VeFloat32 f32Value)
{
	return VeFastInvSqrtf(f32Value) * f32Value;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeNormaliseAnglef(VeFloat32 f32Aangle)
{
	if(f32Aangle > VE_MATH_PI_F)
	{
		if (f32Aangle > VE_MATH_3PI_F)
		{
			return f32Aangle - VeFloorf((f32Aangle + VE_MATH_PI_F)
				/ VE_MATH_2PI_F) * VE_MATH_2PI_F;
		}
		else
		{
			return f32Aangle - VE_MATH_2PI_F;
		}
	}
	else if (f32Aangle <= -VE_MATH_PI_F)
	{
		if (f32Aangle <= -VE_MATH_3PI_F)
		{
			return f32Aangle - VeFloorf((f32Aangle + VE_MATH_PI_F)
				/ VE_MATH_2PI_F) * VE_MATH_2PI_F;
		}
		else
		{
			return f32Aangle + VE_MATH_2PI_F;
		}
	}
	else
	{
		return f32Aangle;
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSameSignAnglef(VeFloat32 f32Aangle,
	VeFloat32 f32Closest)
{
	if(f32Closest > f32Aangle + VE_MATH_PI_F)
	{
		return f32Closest - 2.0f * VE_MATH_PI_F;
	}
	else if(f32Closest < f32Aangle - VE_MATH_PI_F)
	{
		return f32Closest + 2.0f * VE_MATH_PI_F;
	}
	else
	{
		return f32Closest;
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeTurnRangeAnglef(VeFloat32 f32From, VeFloat32 f32To)
{
	VeFloat32 f32Diff = f32To - f32From;
	return (f32Diff < 0.0f) ? f32Diff + VE_MATH_2PI_F : f32Diff;
}
//--------------------------------------------------------------------------
#if defined(VE_ENABLE_SSE)
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector3DotSSE(__m128 v0, __m128 v1)
{
	v0 = _mm_mul_ps(v0, v1);
	v1 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(2,1,2,1));
	v0 = _mm_add_ss(v0, v1);
	v1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(1,1,1,1));
	return _mm_add_ss(v0, v1);
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector3CrossSSE(__m128 v0, __m128 v1)
{
	v0 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(3,0,2,1));
	v1 = _mm_shuffle_ps(v1,v1,_MM_SHUFFLE(3,1,0,2));
	__m128 vRes = _mm_mul_ps(v0, v1);

	v0 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(3,0,2,1));
	v1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3,1,0,2));
	v0 = _mm_mul_ps(v0, v1);
	vRes = _mm_sub_ps(vRes, v0);
	return vRes;
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector3TransformM3SSE(__m128 v, __m128& c0,
	__m128& c1, __m128& c2)
{
	c0 = _mm_mul_ps(v, c0);
	c1 = _mm_mul_ps(v, c1);
	c2 = _mm_mul_ps(v, c2);
	VeMatrix3TransposeSSE(c0, c1, c2);
	return _mm_add_ps(_mm_add_ps(c0, c1), c2);
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector4DotSSE(__m128 v0, __m128 v1)
{
	v0 = _mm_mul_ps(v0, v1);
	v1 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(0,0,3,2));
	v0 = _mm_add_ps(v0, v1);
	v1 = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(0,0,0,1));
	return _mm_add_ps(v0, v1);
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector4LerpSSE(__m128 t, __m128 a, __m128 b)
{
	b = _mm_sub_ps(b, a);
	b = _mm_mul_ps(b, t);
	return _mm_add_ps(a, b);
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector4PosNormalizeSSE(__m128 v)
{
	__m128 t = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3,3,3,3));
	t = _mm_rcp_ps(t);
	return _mm_mul_ps(v, t);
}
//--------------------------------------------------------------------------
VE_INLINE __m128 VeVector4TransformM4SSE(__m128 v, __m128& c0,
	__m128& c1, __m128& c2, __m128& c3)
{
	c0 = _mm_mul_ps(v, c0);
	c1 = _mm_mul_ps(v, c1);
	c2 = _mm_mul_ps(v, c2);
	c3 = _mm_mul_ps(v, c3);
	_MM_TRANSPOSE4_PS(c0, c1, c2, c3);
	v = _mm_add_ps(_mm_add_ps(c0, c1), _mm_add_ps(c2, c3));
	return v;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix3TransposeSSE(__m128& c0, __m128& c1, __m128& c2)
{
	__m128 t0 = _mm_shuffle_ps(c0, c1,_MM_SHUFFLE(1,0,1,0));
	__m128 t1 = _mm_shuffle_ps(c0, c1,_MM_SHUFFLE(3,2,3,2));
	c0 = _mm_shuffle_ps(t0, c2, _MM_SHUFFLE(3,0,2,0));
	c1 = _mm_shuffle_ps(t0, c2, _MM_SHUFFLE(3,1,3,1));
	c2 = _mm_shuffle_ps(t1, c2, _MM_SHUFFLE(3,2,2,0));
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VE_INLINE void VeZero2f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst);
	*(VeUInt64*)pf32Dst = 0;
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero3f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst);
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 3);
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero4f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_setzero_ps());
#	else
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero6f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst);
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 6);
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero16f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_setzero_ps());
	_mm_storeu_ps(pf32Dst + 4, _mm_setzero_ps());
	_mm_storeu_ps(pf32Dst + 8, _mm_setzero_ps());
	_mm_storeu_ps(pf32Dst + 12, _mm_setzero_ps());
#	else
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 16);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero4A16f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_setzero_ps());
#	else
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeZero16A16f(VeFloat32* pf32Dst)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_setzero_ps());
	_mm_store_ps(pf32Dst + 4, _mm_setzero_ps());
	_mm_store_ps(pf32Dst + 8, _mm_setzero_ps());
	_mm_store_ps(pf32Dst + 12, _mm_setzero_ps());
#	else
	VeZeroMemoryEx(pf32Dst, sizeof(VeFloat32), 16);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet2f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1)
{
	VE_ASSERT(pf32Dst);
	pf32Dst[0] = v0;
	pf32Dst[1] = v1;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet3f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1,
	VeFloat32 v2)
{
	VE_ASSERT(pf32Dst);
	pf32Dst[0] = v0;
	pf32Dst[1] = v1;
	pf32Dst[2] = v2;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet4f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1
	, VeFloat32 v2, VeFloat32 v3)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_set_ps(v3, v2, v1, v0));
#	else
	pf32Dst[0] = v0;
	pf32Dst[1] = v1;
	pf32Dst[2] = v2;
	pf32Dst[3] = v3;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet6f(VeFloat32* pf32Dst, VeFloat32 t00, VeFloat32 t01,
	VeFloat32 t10, VeFloat32 t11, VeFloat32 t20, VeFloat32 t21)
{
	VeSet4f(pf32Dst, t00, t01, t10, t11);
	VeSet2f(pf32Dst + 4, t20, t21);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet16f(VeFloat32* pf32Dst
	, VeFloat32 m00, VeFloat32 m01, VeFloat32 m02, VeFloat32 m03
	, VeFloat32 m10, VeFloat32 m11, VeFloat32 m12, VeFloat32 m13
	, VeFloat32 m20, VeFloat32 m21, VeFloat32 m22, VeFloat32 m23
	, VeFloat32 m30, VeFloat32 m31, VeFloat32 m32, VeFloat32 m33)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_set_ps(m03, m02, m01, m00));
	_mm_storeu_ps(pf32Dst + 4, _mm_set_ps(m13, m12, m11, m10));
	_mm_storeu_ps(pf32Dst + 8, _mm_set_ps(m23, m22, m21, m20));
	_mm_storeu_ps(pf32Dst + 12, _mm_set_ps(m33, m32, m31, m30));
#	else
	pf32Dst[0] = m00;
	pf32Dst[1] = m01;
	pf32Dst[2] = m02;
	pf32Dst[3] = m03;
	pf32Dst[4] = m10;
	pf32Dst[5] = m11;
	pf32Dst[6] = m12;
	pf32Dst[7] = m13;
	pf32Dst[8] = m20;
	pf32Dst[9] = m21;
	pf32Dst[10] = m22;
	pf32Dst[11] = m23;
	pf32Dst[12] = m30;
	pf32Dst[13] = m31;
	pf32Dst[14] = m32;
	pf32Dst[15] = m33;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet4A16f(VeFloat32* pf32Dst, VeFloat32 v0, VeFloat32 v1
	, VeFloat32 v2, VeFloat32 v3)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_set_ps(v3, v2, v1, v0));
#	else
	pf32Dst[0] = v0;
	pf32Dst[1] = v1;
	pf32Dst[2] = v2;
	pf32Dst[3] = v3;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet16A16f(VeFloat32* pf32Dst
	, VeFloat32 m00, VeFloat32 m01, VeFloat32 m02, VeFloat32 m03
	, VeFloat32 m10, VeFloat32 m11, VeFloat32 m12, VeFloat32 m13
	, VeFloat32 m20, VeFloat32 m21, VeFloat32 m22, VeFloat32 m23
	, VeFloat32 m30, VeFloat32 m31, VeFloat32 m32, VeFloat32 m33)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_set_ps(m03, m02, m01, m00));
	_mm_store_ps(pf32Dst + 4, _mm_set_ps(m13, m12, m11, m10));
	_mm_store_ps(pf32Dst + 8, _mm_set_ps(m23, m22, m21, m20));
	_mm_store_ps(pf32Dst + 12, _mm_set_ps(m33, m32, m31, m30));
#	else
	pf32Dst[0] = m00;
	pf32Dst[1] = m01;
	pf32Dst[2] = m02;
	pf32Dst[3] = m03;
	pf32Dst[4] = m10;
	pf32Dst[5] = m11;
	pf32Dst[6] = m12;
	pf32Dst[7] = m13;
	pf32Dst[8] = m20;
	pf32Dst[9] = m21;
	pf32Dst[10] = m22;
	pf32Dst[11] = m23;
	pf32Dst[12] = m30;
	pf32Dst[13] = m31;
	pf32Dst[14] = m32;
	pf32Dst[15] = m33;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet2f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst);
	pf32Dst[0] = pf32Dst[1] = f32Scalar;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet3f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst);
	pf32Dst[0] = pf32Dst[1] = pf32Dst[2] = f32Scalar;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet4f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_set_ps1(f32Scalar));
#	else
	pf32Dst[0] = pf32Dst[1] = pf32Dst[2] = pf32Dst[3] = f32Scalar;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet6f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VeSet4f1(pf32Dst, f32Scalar);
	VeSet2f1(pf32Dst + 4, f32Scalar);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_set_ps1(f32Scalar));
	_mm_storeu_ps(pf32Dst + 16, _mm_set_ps1(f32Scalar));
	_mm_storeu_ps(pf32Dst + 32, _mm_set_ps1(f32Scalar));
	_mm_storeu_ps(pf32Dst + 48, _mm_set_ps1(f32Scalar));
#	else
	pf32Dst[0] = pf32Dst[1] = pf32Dst[2] = pf32Dst[3] = f32Scalar;
	pf32Dst[4] = pf32Dst[5] = pf32Dst[6] = pf32Dst[7] = f32Scalar;
	pf32Dst[8] = pf32Dst[9] = pf32Dst[10] = pf32Dst[11] = f32Scalar;
	pf32Dst[12] = pf32Dst[13] = pf32Dst[14] = pf32Dst[15] = f32Scalar;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet4A16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_set_ps1(f32Scalar));
#	else
	pf32Dst[0] = pf32Dst[1] = pf32Dst[2] = pf32Dst[3] = f32Scalar;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSet16A16f1(VeFloat32* pf32Dst, VeFloat32 f32Scalar)
{
	VE_ASSERT(pf32Dst && ((VeSizeT(pf32Dst) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_set_ps1(f32Scalar));
	_mm_store_ps(pf32Dst + 4, _mm_set_ps1(f32Scalar));
	_mm_store_ps(pf32Dst + 8, _mm_set_ps1(f32Scalar));
	_mm_store_ps(pf32Dst + 12, _mm_set_ps1(f32Scalar));
#	else
	pf32Dst[0] = pf32Dst[1] = pf32Dst[2] = pf32Dst[3] = f32Scalar;
	pf32Dst[4] = pf32Dst[5] = pf32Dst[6] = pf32Dst[7] = f32Scalar;
	pf32Dst[8] = pf32Dst[9] = pf32Dst[10] = pf32Dst[11] = f32Scalar;
	pf32Dst[12] = pf32Dst[13] = pf32Dst[14] = pf32Dst[15] = f32Scalar;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 2);
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 3);
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_loadu_ps(pf32Src));
#	else
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy6f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 6);
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_loadu_ps(pf32Src));
	_mm_storeu_ps(pf32Dst + 4, _mm_loadu_ps(pf32Src + 4));
	_mm_storeu_ps(pf32Dst + 8, _mm_loadu_ps(pf32Src + 8));
	_mm_storeu_ps(pf32Dst + 12, _mm_loadu_ps(pf32Src + 12));
#	else
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 16);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_load_ps(pf32Src));
#	else
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeCopy16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_load_ps(pf32Src));
	_mm_store_ps(pf32Dst + 4, _mm_load_ps(pf32Src + 4));
	_mm_store_ps(pf32Dst + 8, _mm_load_ps(pf32Src + 8));
	_mm_store_ps(pf32Dst + 12, _mm_load_ps(pf32Src + 12));
#	else
	VeCrazyCopyEx(pf32Dst, pf32Src, sizeof(VeFloat32), 16);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] + pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] + pf32Src1[1];
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] + pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] + pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] + pf32Src1[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_add_ps(_mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	pf32Dst[0] = pf32Src0[0] + pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] + pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] + pf32Src1[2];
	pf32Dst[3] = pf32Src0[3] + pf32Src1[3];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VeAdd4f(pf32Dst, pf32Src0, pf32Src1);
	VeAdd4f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeAdd4f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeAdd4f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_add_ps(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeAdd4f(pf32Dst, pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeAdd16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
	VeAdd4A16f(pf32Dst, pf32Src0, pf32Src1);
	VeAdd4A16f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeAdd4A16f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeAdd4A16f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] - pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] - pf32Src1[1];
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] - pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] - pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] - pf32Src1[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_sub_ps(_mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	pf32Dst[0] = pf32Src0[0] - pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] - pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] - pf32Src1[2];
	pf32Dst[3] = pf32Src0[3] - pf32Src1[3];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VeSub4f(pf32Dst, pf32Src0, pf32Src1);
	VeSub4f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeSub4f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeSub4f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_sub_ps(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeSub4f(pf32Dst, pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeSub16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
	VeSub4A16f(pf32Dst, pf32Src0, pf32Src1);
	VeSub4A16f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeSub4A16f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeSub4A16f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] * pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] * pf32Src1[1];
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] * pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] * pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] * pf32Src1[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_mul_ps(_mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	pf32Dst[0] = pf32Src0[0] * pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] * pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] * pf32Src1[2];
	pf32Dst[3] = pf32Src0[3] * pf32Src1[3];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VeMul4f(pf32Dst, pf32Src0, pf32Src1);
	VeMul4f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeMul4f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeMul4f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_mul_ps(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeMul4f(pf32Dst, pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeMul16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
	VeMul4A16f(pf32Dst, pf32Src0, pf32Src1);
	VeMul4A16f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeMul4A16f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeMul4A16f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] / pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] / pf32Src1[1];
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = pf32Src0[0] / pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] / pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] / pf32Src1[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_div_ps(_mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	pf32Dst[0] = pf32Src0[0] / pf32Src1[0];
	pf32Dst[1] = pf32Src0[1] / pf32Src1[1];
	pf32Dst[2] = pf32Src0[2] / pf32Src1[2];
	pf32Dst[3] = pf32Src0[3] / pf32Src1[3];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VeDiv4f(pf32Dst, pf32Src0, pf32Src1);
	VeDiv4f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeDiv4f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeDiv4f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_div_ps(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeDiv4f(pf32Dst, pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeDiv16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
	VeDiv4A16f(pf32Dst, pf32Src0, pf32Src1);
	VeDiv4A16f(pf32Dst + 4, pf32Src0 + 4, pf32Src1 + 4);
	VeDiv4A16f(pf32Dst + 8, pf32Src0 + 8, pf32Src1 + 8);
	VeDiv4A16f(pf32Dst + 12, pf32Src0 + 12, pf32Src1 + 12);
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
	pf32Dst[0] = pf32Src[0] * f32Scale;
	pf32Dst[1] = pf32Src[1] * f32Scale;
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
	pf32Dst[0] = pf32Src[0] * f32Scale;
	pf32Dst[1] = pf32Src[1] * f32Scale;
	pf32Dst[2] = pf32Src[2] * f32Scale;
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, _mm_mul_ps(_mm_loadu_ps(pf32Src), _mm_set_ps1(f32Scale)));
#	else
	pf32Dst[0] = pf32Src[0] * f32Scale;
	pf32Dst[1] = pf32Src[1] * f32Scale;
	pf32Dst[2] = pf32Src[2] * f32Scale;
	pf32Dst[3] = pf32Src[3] * f32Scale;
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VeScale4f(pf32Dst, pf32Src, f32Scale);
	VeScale4f(pf32Dst + 4, pf32Src + 4, f32Scale);
	VeScale4f(pf32Dst + 8, pf32Src + 8, f32Scale);
	VeScale4f(pf32Dst + 12, pf32Src + 12, f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, _mm_sub_ps(_mm_load_ps(pf32Src), _mm_set_ps1(f32Scale)));
#	else
	VeScale4f(pf32Dst, pf32Src, f32Scale);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeScale16A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src,
	VeFloat32 f32Scale)
{
	VE_ASSERT(pf32Dst && pf32Src);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src) & 0xf) == 0));
	VeScale4A16f(pf32Dst, pf32Src, f32Scale);
	VeScale4A16f(pf32Dst + 4, pf32Src + 4, f32Scale);
	VeScale4A16f(pf32Dst + 8, pf32Src + 8, f32Scale);
	VeScale4A16f(pf32Dst + 12, pf32Src + 12, f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLengthSqr2f(const VeFloat32* pf32Src)
{
	return VeDot2f(pf32Src, pf32Src);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLengthSqr3f(const VeFloat32* pf32Src)
{
	return VeDot3f(pf32Src, pf32Src);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLengthSqr4f(const VeFloat32* pf32Src)
{
	return VeDot4f(pf32Src, pf32Src);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLengthSqr3A16f(const VeFloat32* pf32Src)
{
	return VeDot3A16f(pf32Src, pf32Src);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLengthSqr4A16f(const VeFloat32* pf32Src)
{
	return VeDot4A16f(pf32Src, pf32Src);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLength2f(const VeFloat32* pf32Src)
{
	return VeSqrtf(VeLengthSqr2f(pf32Src));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLength3f(const VeFloat32* pf32Src)
{
	return VeSqrtf(VeLengthSqr3f(pf32Src));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLength4f(const VeFloat32* pf32Src)
{
	return VeSqrtf(VeLengthSqr4f(pf32Src));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLength3A16f(const VeFloat32* pf32Src)
{
	return VeSqrtf(VeLengthSqr3A16f(pf32Src));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLength4A16f(const VeFloat32* pf32Src)
{
	return VeSqrtf(VeLengthSqr4A16f(pf32Src));
}
//--------------------------------------------------------------------------
VE_INLINE void VeNormalize2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VeScale2f(pf32Dst, pf32Src, VeInvSqrtf(VeLengthSqr2f(pf32Src)));
}
//--------------------------------------------------------------------------
VE_INLINE void VeNormalize3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VeScale3f(pf32Dst, pf32Src, VeInvSqrtf(VeLengthSqr3f(pf32Src)));
}
//--------------------------------------------------------------------------
VE_INLINE void VeNormalize4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src)
{
	VeScale4f(pf32Dst, pf32Src, VeInvSqrtf(VeLengthSqr4f(pf32Src)));
}
//--------------------------------------------------------------------------
VE_INLINE void VeNormalize3A16f(VeFloat32* pf32Dst,
	const VeFloat32* pf32Src)
{
	VeScale4A16f(pf32Dst, pf32Src, VeInvSqrtf(VeLengthSqr3A16f(pf32Src)));
}
//--------------------------------------------------------------------------
VE_INLINE void VeNormalize4A16f(VeFloat32* pf32Dst,
	const VeFloat32* pf32Src)
{
	VeScale4A16f(pf32Dst, pf32Src, VeInvSqrtf(VeLengthSqr4A16f(pf32Src)));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDot2f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Src0 && pf32Src1);
	return pf32Src0[0] * pf32Src1[0] + pf32Src0[1] * pf32Src1[1];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDot3f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Src0 && pf32Src1);
	return pf32Src0[0] * pf32Src1[0] + pf32Src0[1] * pf32Src1[1] + pf32Src0[2] * pf32Src1[2];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDot4f(const VeFloat32* pf32Src0, const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	return _mm_cvtss_f32(VeVector4DotSSE(_mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	return pf32Src0[0] * pf32Src1[0] + pf32Src0[1] * pf32Src1[1] + pf32Src0[2] * pf32Src1[2] + pf32Src0[3] * pf32Src1[3];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDot3A16f(const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	return _mm_cvtss_f32(VeVector3DotSSE(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	return VeDot3f(pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDot4A16f(const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1)
{
	VE_ASSERT(pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));

#	if defined(VE_ENABLE_SSE)
	return _mm_cvtss_f32(VeVector4DotSSE(_mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	return VeDot4f(pf32Src0, pf32Src1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeLerp2f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1, VeFloat32 t)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = VeLerp(t, pf32Src0[0], pf32Src1[0]);
	pf32Dst[1] = VeLerp(t, pf32Src0[1], pf32Src1[1]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeLerp3f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1, VeFloat32 t)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	pf32Dst[0] = VeLerp(t, pf32Src0[0], pf32Src1[0]);
	pf32Dst[1] = VeLerp(t, pf32Src0[1], pf32Src1[1]);
	pf32Dst[2] = VeLerp(t, pf32Src0[2], pf32Src1[2]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeLerp4f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1, VeFloat32 t)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32Dst, VeVector4LerpSSE(_mm_set_ps1(t), _mm_loadu_ps(pf32Src0), _mm_loadu_ps(pf32Src1)));
#	else
	pf32Dst[0] = VeLerp(t, pf32Src0[0], pf32Src1[0]);
	pf32Dst[1] = VeLerp(t, pf32Src0[1], pf32Src1[1]);
	pf32Dst[2] = VeLerp(t, pf32Src0[2], pf32Src1[2]);
	pf32Dst[3] = VeLerp(t, pf32Src0[3], pf32Src1[3]);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeLerp3A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1, VeFloat32 t)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, VeVector4LerpSSE(_mm_set_ps1(t), _mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeLerp3f(pf32Dst, pf32Src0, pf32Src1, t);
#	endif

}
//--------------------------------------------------------------------------
VE_INLINE void VeLerp4A16f(VeFloat32* pf32Dst, const VeFloat32* pf32Src0,
	const VeFloat32* pf32Src1, VeFloat32 t)
{
	VE_ASSERT(pf32Dst && pf32Src0 && pf32Src1);
	VE_ASSERT(((VeSizeT(pf32Dst) & 0xf) == 0)
		&& ((VeSizeT(pf32Src0) & 0xf) == 0)
		&& ((VeSizeT(pf32Src1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Dst, VeVector4LerpSSE(_mm_set_ps1(t), _mm_load_ps(pf32Src0), _mm_load_ps(pf32Src1)));
#	else
	VeLerp4f(pf32Dst, pf32Src0, pf32Src1, t);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2Crossf(const VeFloat32* pf32Vec0,
	const VeFloat32* pf32Vec1)
{
	return pf32Vec0[0] * pf32Vec1[1] - pf32Vec0[1] * pf32Vec1[0];
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3Crossf(VeFloat32* pf32Out, const VeFloat32* pf32Vec0,
	const VeFloat32* pf32Vec1)
{
	VeFloat32 af32Vec0[3];
	VeFloat32 af32Vec1[3];

	VE_ASSERT(pf32Out && pf32Vec0 && pf32Vec1);

	VeCopy3f(af32Vec0, pf32Vec0);
	VeCopy3f(af32Vec1, pf32Vec1);

	pf32Out[0] = (af32Vec0[1] * af32Vec1[2]) - (af32Vec0[2] * af32Vec1[1]);
	pf32Out[1] = (af32Vec0[2] * af32Vec1[0]) - (af32Vec0[0] * af32Vec1[2]);
	pf32Out[2] = (af32Vec0[0] * af32Vec1[1]) - (af32Vec0[1] * af32Vec1[0]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3CrossA16f(VeFloat32* pf32Out,
	const VeFloat32* pf32Vec0, const VeFloat32* pf32Vec1)
{
	VE_ASSERT(pf32Out && pf32Vec0 && pf32Vec1);
	VE_ASSERT(((VeSizeT(pf32Out) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec0) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec1) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32Out, VeVector3CrossSSE(_mm_load_ps(pf32Vec0), _mm_load_ps(pf32Vec1)));
#	else
	VeVector3Crossf(pf32Out, pf32Vec0, pf32Vec1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformM4f(VeFloat32* pf32OutVec4,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VeFloat32 af32Vec3[3];
	VeFloat32 af32Mat4x4[16];

	VE_ASSERT(pf32OutVec4 && pf32Vec3 && pf32Mat4x4);

	VeCopy3f(af32Vec3, pf32Vec3);
	VeCopy16f(af32Mat4x4, pf32Mat4x4);

	pf32OutVec4[0] = af32Vec3[0] * af32Mat4x4[0] + af32Vec3[1] * af32Mat4x4[1] + af32Vec3[2] * af32Mat4x4[2] + af32Mat4x4[3];
	pf32OutVec4[1] = af32Vec3[0] * af32Mat4x4[4] + af32Vec3[1] * af32Mat4x4[5] + af32Vec3[2] * af32Mat4x4[6] + af32Mat4x4[7];
	pf32OutVec4[2] = af32Vec3[0] * af32Mat4x4[8] + af32Vec3[1] * af32Mat4x4[9] + af32Vec3[2] * af32Mat4x4[10] + af32Mat4x4[11];
	pf32OutVec4[3] = af32Vec3[0] * af32Mat4x4[12] + af32Vec3[1] * af32Mat4x4[13] + af32Vec3[2] * af32Mat4x4[14] + af32Mat4x4[15];
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformCoordM4f(VeFloat32* pf32OutVec3,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VeFloat32 af32Vec3[3];
	VeFloat32 af32Mat4x4[16];
	VeFloat32 f32Invw;

	VE_ASSERT(pf32OutVec3 && pf32Vec3 && pf32Mat4x4);

	VeCopy3f(af32Vec3, pf32Vec3);
	VeCopy16f(af32Mat4x4, pf32Mat4x4);

	f32Invw = 1.0f / (af32Vec3[0] * af32Mat4x4[12] + af32Vec3[1] * af32Mat4x4[13] + af32Vec3[2] * af32Mat4x4[14] + af32Mat4x4[15]);

	pf32OutVec3[0] = pf32OutVec3[1] = pf32OutVec3[2] = f32Invw;

	pf32OutVec3[0] *= af32Vec3[0] * af32Mat4x4[0] + af32Vec3[1] * af32Mat4x4[1] + af32Vec3[2] * af32Mat4x4[2] + af32Mat4x4[3];
	pf32OutVec3[1] *= af32Vec3[0] * af32Mat4x4[4] + af32Vec3[1] * af32Mat4x4[5] + af32Vec3[2] * af32Mat4x4[6] + af32Mat4x4[7];
	pf32OutVec3[2] *= af32Vec3[0] * af32Mat4x4[8] + af32Vec3[1] * af32Mat4x4[9] + af32Vec3[2] * af32Mat4x4[10] + af32Mat4x4[11];
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformNormalM4f(VeFloat32* pf32OutVec3,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VeFloat32 af32Vec3[3];
	VeFloat32 af32Mat4x4[16];

	VE_ASSERT(pf32OutVec3 && pf32Vec3 && pf32Mat4x4);

	VeCopy3f(af32Vec3, pf32Vec3);
	VeCopy16f(af32Mat4x4, pf32Mat4x4);

	pf32OutVec3[0] = af32Vec3[0] * af32Mat4x4[0] + af32Vec3[1] * af32Mat4x4[1] + af32Vec3[2] * af32Mat4x4[2];
	pf32OutVec3[1] = af32Vec3[0] * af32Mat4x4[4] + af32Vec3[1] * af32Mat4x4[5] + af32Vec3[2] * af32Mat4x4[6];
	pf32OutVec3[2] = af32Vec3[0] * af32Mat4x4[8] + af32Vec3[1] * af32Mat4x4[9] + af32Vec3[2] * af32Mat4x4[10];
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformM4A16f(VeFloat32* pf32OutVec4,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutVec4 && pf32Vec3 && pf32Mat4x4);
	VE_ASSERT(((VeSizeT(pf32OutVec4) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec3) & 0xf) == 0)
		&& ((VeSizeT(pf32Mat4x4) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	((VeFloat32*)(void*)pf32Vec3)[3] = 1.0f;
	_mm_store_ps(pf32OutVec4, VeVector4TransformM4SSE(_mm_load_ps(pf32Vec3),
		_mm_load_ps(pf32Mat4x4), _mm_load_ps(pf32Mat4x4 + 4),
		_mm_load_ps(pf32Mat4x4 + 8), _mm_load_ps(pf32Mat4x4 + 12)));
#	else
	VeVector3TransformM4f(pf32OutVec4, pf32Vec3, pf32Mat4x4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformCoordM4A16f(VeFloat32* pf32OutVec3,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutVec3 && pf32Vec3 && pf32Mat4x4);
	VE_ASSERT(((VeSizeT(pf32OutVec3) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec3) & 0xf) == 0)
		&& ((VeSizeT(pf32Mat4x4) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	((VeFloat32*)(void*)pf32Vec3)[3] = 1.0f;
	__m128 temp = VeVector4TransformM4SSE(_mm_load_ps(pf32Vec3),
		_mm_load_ps(pf32Mat4x4), _mm_load_ps(pf32Mat4x4 + 4),
		_mm_load_ps(pf32Mat4x4 + 8), _mm_load_ps(pf32Mat4x4 + 12));
	_mm_store_ps(pf32OutVec3, VeVector4PosNormalizeSSE(temp));
#	else
	VeVector3TransformCoordM4f(pf32OutVec3, pf32Vec3, pf32Mat4x4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3TransformNormalM4A16f(VeFloat32* pf32OutVec3,
	const VeFloat32* pf32Vec3, const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutVec3 && pf32Vec3 && pf32Mat4x4);
	VE_ASSERT(((VeSizeT(pf32OutVec3) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec3) & 0xf) == 0)
		&& ((VeSizeT(pf32Mat4x4) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32OutVec3, VeVector3TransformM3SSE(_mm_load_ps(pf32Vec3),
		_mm_load_ps(pf32Mat4x4), _mm_load_ps(pf32Mat4x4 + 4),
		_mm_load_ps(pf32Mat4x4 + 8)));
#	else
	VeVector3TransformNormalM4f(pf32OutVec3, pf32Vec3, pf32Mat4x4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3SetPitchYawf(VeFloat32* pf32OutVec3,
	VeFloat32 f32PitchInRadians, VeFloat32 f32YawInRadians)
{
	VeFloat32 f32CosPitch = VeCosf(f32PitchInRadians);
	VeFloat32 f32SinPitch = VeSinf(-f32PitchInRadians);

	VeFloat32 f32CosYaw = VeCosf(f32YawInRadians);
	VeFloat32 f32SinYaw = VeSinf(f32YawInRadians);

	pf32OutVec3[0] = f32CosPitch * f32SinYaw;
	pf32OutVec3[1] = f32CosPitch * f32CosYaw;
	pf32OutVec3[2] = f32SinPitch;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3GetPitchf(VeFloat32* pf32Vec3)
{
	return -VeAtan2f(pf32Vec3[2], VeSqrtf(pf32Vec3[0] * pf32Vec3[0] + pf32Vec3[1] * pf32Vec3[1]));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3GetYawf(VeFloat32* pf32Vec3)
{
	return VeAtan2f(pf32Vec3[0], pf32Vec3[1]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4Transformf(VeFloat32* pf32OutVec4,
	const VeFloat32* pf32Vec4, const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutVec4 && pf32Vec4 && pf32Mat4x4);
#	if defined(VE_ENABLE_SSE)
	_mm_storeu_ps(pf32OutVec4, VeVector4TransformM4SSE(_mm_loadu_ps(pf32Vec4),
		_mm_loadu_ps(pf32Mat4x4), _mm_loadu_ps(pf32Mat4x4 + 4),
		_mm_loadu_ps(pf32Mat4x4 + 8), _mm_loadu_ps(pf32Mat4x4 + 12)));
#	else
	VeFloat32 afVec4[4];
	VeFloat32 afMat4x4[16];
	VeCopy4f(afVec4, pf32Vec4);
	VeCopy16f(afMat4x4, pf32Mat4x4);
	pf32OutVec4[0] = afVec4[0] * afMat4x4[0] + afVec4[1] * afMat4x4[1] +
		afVec4[2] * afMat4x4[2] + afVec4[3] * afMat4x4[3];
	pf32OutVec4[1] = afVec4[0] * afMat4x4[4] + afVec4[1] * afMat4x4[5] +
		afVec4[2] * afMat4x4[6] + afVec4[3] * afMat4x4[7];
	pf32OutVec4[2] = afVec4[0] * afMat4x4[8] + afVec4[1] * afMat4x4[9] +
		afVec4[2] * afMat4x4[10] + afVec4[3] * afMat4x4[11];
	pf32OutVec4[3] = afVec4[0] * afMat4x4[12] + afVec4[1] * afMat4x4[13] +
		afVec4[2] * afMat4x4[14] + afVec4[3] * afMat4x4[15];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4TransformA16f(VeFloat32* pf32OutVec4,
	const VeFloat32* pf32Vec4, const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutVec4 && pf32Vec4 && pf32Mat4x4);
	VE_ASSERT(((VeSizeT(pf32OutVec4) & 0xf) == 0)
		&& ((VeSizeT(pf32Vec4) & 0xf) == 0)
		&& ((VeSizeT(pf32Mat4x4) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	_mm_store_ps(pf32OutVec4, VeVector4TransformM4SSE(_mm_load_ps(pf32Vec4),
		_mm_load_ps(pf32Mat4x4), _mm_load_ps(pf32Mat4x4 + 4),
		_mm_load_ps(pf32Mat4x4 + 8), _mm_load_ps(pf32Mat4x4 + 12)));
#	else
	VeVector4Transformf(pf32OutVec4, pf32Vec4, pf32Mat4x4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeVector4Outcode(const VeFloat32* pf32Vec4)
{
	VeUInt32 u32Code = VE_OUTCODE_NULL;
	if(pf32Vec4[0] < (-pf32Vec4[3]))
		u32Code |= VE_OUTCODE_LEFT;
	if(pf32Vec4[0] > pf32Vec4[3])
		u32Code |= VE_OUTCODE_RIGHT;
	if(pf32Vec4[1] < (-pf32Vec4[3]))
		u32Code |= VE_OUTCODE_BOTTOM;
	if(pf32Vec4[1] > pf32Vec4[3])
		u32Code |= VE_OUTCODE_TOP;
	if(pf32Vec4[2] < 0)
		u32Code |= VE_OUTCODE_NEAR;
	if(pf32Vec4[2] > pf32Vec4[3])
		u32Code |= VE_OUTCODE_FAR;
	return u32Code;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixIdenty4f(VeFloat32* pf32OutMat4x4)
{
	VE_ASSERT(pf32OutMat4x4);
	pf32OutMat4x4[1] = pf32OutMat4x4[2] =pf32OutMat4x4[3] =
		pf32OutMat4x4[4] = pf32OutMat4x4[6] = pf32OutMat4x4[7] =
		pf32OutMat4x4[8] = pf32OutMat4x4[9] = pf32OutMat4x4[11] =
		pf32OutMat4x4[12] = pf32OutMat4x4[13] = pf32OutMat4x4[14] = 0;
	pf32OutMat4x4[0] = pf32OutMat4x4[5] = pf32OutMat4x4[10] =
		pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE VE_BOOL VeMatrixInverse4f(VeFloat32* pf32OutMat4x4,
	VeFloat32* pf32Determinant, const VeFloat32* pf32Mat4x4)
{
	VeFloat32 afMat4x4[16];
	VeFloat32 v0, v1, v2, v3, v4, v5;
	VeFloat32 t00, t10, t20, t30;
	VeFloat32 fDet, fInvDet;

	VE_ASSERT(pf32Mat4x4);
	VE_ASSERT(pf32OutMat4x4);

	VeCopy16f(afMat4x4, pf32Mat4x4);

	v0 = afMat4x4[8] * afMat4x4[13] - afMat4x4[9] * afMat4x4[12];
	v1 = afMat4x4[8] * afMat4x4[14] - afMat4x4[10] * afMat4x4[12];
	v2 = afMat4x4[8] * afMat4x4[15] - afMat4x4[11] * afMat4x4[12];
	v3 = afMat4x4[9] * afMat4x4[14] - afMat4x4[10] * afMat4x4[13];
	v4 = afMat4x4[9] * afMat4x4[15] - afMat4x4[11] * afMat4x4[13];
	v5 = afMat4x4[10] * afMat4x4[15] - afMat4x4[11] * afMat4x4[14];

	t00 = + (v5 * afMat4x4[5] - v4 * afMat4x4[6] + v3 * afMat4x4[7]);
	t10 = - (v5 * afMat4x4[4] - v2 * afMat4x4[6] + v1 * afMat4x4[7]);
	t20 = + (v4 * afMat4x4[4] - v2 * afMat4x4[5] + v0 * afMat4x4[7]);
	t30 = - (v3 * afMat4x4[4] - v1 * afMat4x4[5] + v0 * afMat4x4[6]);

	fDet = (t00 * afMat4x4[0] + t10 * afMat4x4[1] + t20 * afMat4x4[2] +
		t30 * afMat4x4[3]);

	if(pf32Determinant)
		*pf32Determinant = fDet;

	if(fDet == 0) return VE_FALSE;

	fInvDet = 1.0f / fDet;

	pf32OutMat4x4[0] = t00 * fInvDet;
	pf32OutMat4x4[4] = t10 * fInvDet;
	pf32OutMat4x4[8] = t20 * fInvDet;
	pf32OutMat4x4[12] = t30 * fInvDet;

	pf32OutMat4x4[1] = - (v5 * afMat4x4[1] - v4 * afMat4x4[2] + v3 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[5] = + (v5 * afMat4x4[0] - v2 * afMat4x4[2] + v1 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[9] = - (v4 * afMat4x4[0] - v2 * afMat4x4[1] + v0 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[13] = + (v3 * afMat4x4[0] - v1 * afMat4x4[1] + v0 *
		afMat4x4[2]) * fInvDet;

	v0 = afMat4x4[4] * afMat4x4[13] - afMat4x4[5] * afMat4x4[12];
	v1 = afMat4x4[4] * afMat4x4[14] - afMat4x4[6] * afMat4x4[12];
	v2 = afMat4x4[4] * afMat4x4[15] - afMat4x4[7] * afMat4x4[12];
	v3 = afMat4x4[5] * afMat4x4[14] - afMat4x4[6] * afMat4x4[13];
	v4 = afMat4x4[5] * afMat4x4[15] - afMat4x4[7] * afMat4x4[13];
	v5 = afMat4x4[6] * afMat4x4[15] - afMat4x4[7] * afMat4x4[14];

	pf32OutMat4x4[2] = + (v5 * afMat4x4[1] - v4 * afMat4x4[2] + v3 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[6] = - (v5 * afMat4x4[0] - v2 * afMat4x4[2] + v1 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[10] = + (v4 * afMat4x4[0] - v2 * afMat4x4[1] + v0 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[14] = - (v3 * afMat4x4[0] - v1 * afMat4x4[1] + v0 *
		afMat4x4[2]) * fInvDet;

	v0 = afMat4x4[9] * afMat4x4[4] - afMat4x4[8] * afMat4x4[5];
	v1 = afMat4x4[10] * afMat4x4[4] - afMat4x4[8] * afMat4x4[6];
	v2 = afMat4x4[11] * afMat4x4[4] - afMat4x4[8] * afMat4x4[7];
	v3 = afMat4x4[10] * afMat4x4[5] - afMat4x4[9] * afMat4x4[6];
	v4 = afMat4x4[11] * afMat4x4[5] - afMat4x4[9] * afMat4x4[7];
	v5 = afMat4x4[11] * afMat4x4[6] - afMat4x4[10] * afMat4x4[7];

	pf32OutMat4x4[3] = - (v5 * afMat4x4[1] - v4 * afMat4x4[2] + v3 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[7] = + (v5 * afMat4x4[0] - v2 * afMat4x4[2] + v1 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[11] = - (v4 * afMat4x4[0] - v2 * afMat4x4[1] + v0 *
		afMat4x4[3]) * fInvDet;
	pf32OutMat4x4[15] = + (v3 * afMat4x4[0] - v1 * afMat4x4[1] + v0 *
		afMat4x4[2]) * fInvDet;

	return VE_TRUE;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixTranspose4f(VeFloat32* pf32OutMat4x4,
	const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutMat4x4 && pf32Mat4x4);
#	if defined(VE_ENABLE_SSE)
	__m128 c0 = _mm_loadu_ps(pf32Mat4x4);
	__m128 c1 = _mm_loadu_ps(pf32Mat4x4 + 4);
	__m128 c2 = _mm_loadu_ps(pf32Mat4x4 + 8);
	__m128 c3 = _mm_loadu_ps(pf32Mat4x4 + 12);
	_MM_TRANSPOSE4_PS(c0, c1, c2, c3);
	_mm_storeu_ps(pf32OutMat4x4, c0);
	_mm_storeu_ps(pf32OutMat4x4 + 4, c1);
	_mm_storeu_ps(pf32OutMat4x4 + 8, c2);
	_mm_storeu_ps(pf32OutMat4x4 + 12, c3);
#	else
	VeFloat32 afMat4x4[16];
	VeCopy16f(afMat4x4, pf32Mat4x4);
	pf32OutMat4x4[0] = afMat4x4[0];
	pf32OutMat4x4[1] = afMat4x4[4];
	pf32OutMat4x4[2] = afMat4x4[8];
	pf32OutMat4x4[3] = afMat4x4[12];

	pf32OutMat4x4[4] = afMat4x4[1];
	pf32OutMat4x4[5] = afMat4x4[5];
	pf32OutMat4x4[6] = afMat4x4[9];
	pf32OutMat4x4[7] = afMat4x4[13];

	pf32OutMat4x4[8] = afMat4x4[2];
	pf32OutMat4x4[9] = afMat4x4[6];
	pf32OutMat4x4[10] = afMat4x4[10];
	pf32OutMat4x4[11] = afMat4x4[14];

	pf32OutMat4x4[12] = afMat4x4[3];
	pf32OutMat4x4[13] = afMat4x4[7];
	pf32OutMat4x4[14] = afMat4x4[11];
	pf32OutMat4x4[15] = afMat4x4[15];
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixTranspose4A16f(VeFloat32* pf32OutMat4x4,
	const VeFloat32* pf32Mat4x4)
{
	VE_ASSERT(pf32OutMat4x4 && pf32Mat4x4);
	VE_ASSERT(((VeSizeT(pf32OutMat4x4) & 0xf) == 0)
		&& ((VeSizeT(pf32Mat4x4) & 0xf) == 0));
#	if defined(VE_ENABLE_SSE)
	__m128 c0 = _mm_load_ps(pf32Mat4x4);
	__m128 c1 = _mm_load_ps(pf32Mat4x4 + 4);
	__m128 c2 = _mm_load_ps(pf32Mat4x4 + 8);
	__m128 c3 = _mm_load_ps(pf32Mat4x4 + 12);
	_MM_TRANSPOSE4_PS(c0, c1, c2, c3);
	_mm_store_ps(pf32OutMat4x4, c0);
	_mm_store_ps(pf32OutMat4x4 + 4, c1);
	_mm_store_ps(pf32OutMat4x4 + 8, c2);
	_mm_store_ps(pf32OutMat4x4 + 12, c3);
#	else
	VeMatrixTranspose4f(pf32OutMat4x4, pf32Mat4x4);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeMatrixDeterminant4f(const VeFloat32* pf32Mat4x4)
{
	VeFloat32 v0, v1, v2, v3, v4, v5;
	VeFloat32 t00, t10, t20, t30;

	VE_ASSERT(pf32Mat4x4);

	v0 = pf32Mat4x4[8] * pf32Mat4x4[13] - pf32Mat4x4[9] * pf32Mat4x4[12];
	v1 = pf32Mat4x4[8] * pf32Mat4x4[14] - pf32Mat4x4[10] * pf32Mat4x4[12];
	v2 = pf32Mat4x4[8] * pf32Mat4x4[15] - pf32Mat4x4[11] * pf32Mat4x4[12];
	v3 = pf32Mat4x4[9] * pf32Mat4x4[14] - pf32Mat4x4[10] * pf32Mat4x4[13];
	v4 = pf32Mat4x4[9] * pf32Mat4x4[15] - pf32Mat4x4[11] * pf32Mat4x4[13];
	v5 = pf32Mat4x4[10] * pf32Mat4x4[15] - pf32Mat4x4[11] * pf32Mat4x4[14];

	t00 = + (v5 * pf32Mat4x4[5] - v4 * pf32Mat4x4[6] + v3 * pf32Mat4x4[7]);
	t10 = - (v5 * pf32Mat4x4[4] - v2 * pf32Mat4x4[6] + v1 * pf32Mat4x4[7]);
	t20 = + (v4 * pf32Mat4x4[4] - v2 * pf32Mat4x4[5] + v0 * pf32Mat4x4[7]);
	t30 = - (v3 * pf32Mat4x4[4] - v1 * pf32Mat4x4[5] + v0 * pf32Mat4x4[6]);

	return (t00 * pf32Mat4x4[0] + t10 * pf32Mat4x4[1] + t20 * pf32Mat4x4[2] +
		t30 * pf32Mat4x4[3]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixMultiply4f(VeFloat32* pf32OutMat4x4,
	const VeFloat32* pf32Mat4x4Src0, const VeFloat32* pf32Mat4x4Src1)
{
	VeFloat32 afMat4x4Src0[16];
	VeFloat32 afMat4x4Src1[16];

	VE_ASSERT(pf32Mat4x4Src1);
	VE_ASSERT(pf32Mat4x4Src0);
	VE_ASSERT(pf32OutMat4x4);

	VeCopy16f(afMat4x4Src0, pf32Mat4x4Src0);
	VeCopy16f(afMat4x4Src1, pf32Mat4x4Src1);

	pf32OutMat4x4[0] = afMat4x4Src0[0] * afMat4x4Src1[0] + afMat4x4Src0[1] *
		afMat4x4Src1[4] + afMat4x4Src0[2] * afMat4x4Src1[8] +
		afMat4x4Src0[3] * afMat4x4Src1[12];
	pf32OutMat4x4[1] = afMat4x4Src0[0] * afMat4x4Src1[1] + afMat4x4Src0[1] *
		afMat4x4Src1[5]	+ afMat4x4Src0[2] * afMat4x4Src1[9] +
		afMat4x4Src0[3] * afMat4x4Src1[13];
	pf32OutMat4x4[2] = afMat4x4Src0[0] * afMat4x4Src1[2] + afMat4x4Src0[1] *
		afMat4x4Src1[6] + afMat4x4Src0[2] * afMat4x4Src1[10] +
		afMat4x4Src0[3] * afMat4x4Src1[14];
	pf32OutMat4x4[3] = afMat4x4Src0[0] * afMat4x4Src1[3] + afMat4x4Src0[1] *
		afMat4x4Src1[7]	+ afMat4x4Src0[2] * afMat4x4Src1[11] +
		afMat4x4Src0[3] * afMat4x4Src1[15];

	pf32OutMat4x4[4] = afMat4x4Src0[4] * afMat4x4Src1[0] + afMat4x4Src0[5] *
		afMat4x4Src1[4]	+ afMat4x4Src0[6] * afMat4x4Src1[8] +
		afMat4x4Src0[7] * afMat4x4Src1[12];
	pf32OutMat4x4[5] = afMat4x4Src0[4] * afMat4x4Src1[1] + afMat4x4Src0[5] *
		afMat4x4Src1[5]	+ afMat4x4Src0[6] * afMat4x4Src1[9] +
		afMat4x4Src0[7] * afMat4x4Src1[13];
	pf32OutMat4x4[6] = afMat4x4Src0[4] * afMat4x4Src1[2] + afMat4x4Src0[5] *
		afMat4x4Src1[6]	+ afMat4x4Src0[6] * afMat4x4Src1[10] +
		afMat4x4Src0[7] * afMat4x4Src1[14];
	pf32OutMat4x4[7] = afMat4x4Src0[4] * afMat4x4Src1[3] + afMat4x4Src0[5] *
		afMat4x4Src1[7]	+ afMat4x4Src0[6] * afMat4x4Src1[11] +
		afMat4x4Src0[7] * afMat4x4Src1[15];

	pf32OutMat4x4[8] = afMat4x4Src0[8] * afMat4x4Src1[0] + afMat4x4Src0[9] *
		afMat4x4Src1[4]	+ afMat4x4Src0[10] * afMat4x4Src1[8] +
		afMat4x4Src0[11] * afMat4x4Src1[12];
	pf32OutMat4x4[9] = afMat4x4Src0[8] * afMat4x4Src1[1] + afMat4x4Src0[9] *
		afMat4x4Src1[5]	+ afMat4x4Src0[10] * afMat4x4Src1[9] +
		afMat4x4Src0[11] * afMat4x4Src1[13];
	pf32OutMat4x4[10] = afMat4x4Src0[8] * afMat4x4Src1[2] + afMat4x4Src0[9] *
		afMat4x4Src1[6]	+ afMat4x4Src0[10] * afMat4x4Src1[10] +
		afMat4x4Src0[11] * afMat4x4Src1[14];
	pf32OutMat4x4[11] = afMat4x4Src0[8] * afMat4x4Src1[3] + afMat4x4Src0[9] *
		afMat4x4Src1[7]	+ afMat4x4Src0[10] * afMat4x4Src1[11] +
		afMat4x4Src0[11] * afMat4x4Src1[15];

	pf32OutMat4x4[12] = afMat4x4Src0[12] * afMat4x4Src1[0] + afMat4x4Src0[13] *
		afMat4x4Src1[4]	+ afMat4x4Src0[14] * afMat4x4Src1[8] +
		afMat4x4Src0[15] * afMat4x4Src1[12];
	pf32OutMat4x4[13] = afMat4x4Src0[12] * afMat4x4Src1[1] + afMat4x4Src0[13] *
		afMat4x4Src1[5]	+ afMat4x4Src0[14] * afMat4x4Src1[9] +
		afMat4x4Src0[15] * afMat4x4Src1[13];
	pf32OutMat4x4[14] = afMat4x4Src0[12] * afMat4x4Src1[2] + afMat4x4Src0[13] *
		afMat4x4Src1[6]	+ afMat4x4Src0[14] * afMat4x4Src1[10] +
		afMat4x4Src0[15] * afMat4x4Src1[14];
	pf32OutMat4x4[15] = afMat4x4Src0[12] * afMat4x4Src1[3] + afMat4x4Src0[13] *
		afMat4x4Src1[7]	+ afMat4x4Src0[14] * afMat4x4Src1[11] +
		afMat4x4Src0[15] * afMat4x4Src1[15];
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixRotationX4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 f32Angle)
{
	VeFloat32 fSin, fCos;
	VE_ASSERT(pf32OutMat4x4);
	VeSinCosf(&fSin, &fCos, f32Angle);
	pf32OutMat4x4[0] = 1.0f;
	pf32OutMat4x4[1] = 0.0f;
	pf32OutMat4x4[2] = 0.0f;
	pf32OutMat4x4[3] = 0.0f;
	pf32OutMat4x4[4] = 0.0f;
	pf32OutMat4x4[5] = fCos;
	pf32OutMat4x4[6] = -fSin;
	pf32OutMat4x4[7] = 0.0f;
	pf32OutMat4x4[8] = 0.0f;
	pf32OutMat4x4[9] = fSin;
	pf32OutMat4x4[10] = fCos;
	pf32OutMat4x4[11] = 0.0f;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixRotationY4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 f32Angle)
{
	VeFloat32 fSin, fCos;
	VE_ASSERT(pf32OutMat4x4);
	VeSinCosf(&fSin, &fCos, f32Angle);
	pf32OutMat4x4[0] = fCos;
	pf32OutMat4x4[1] = 0.0f;
	pf32OutMat4x4[2] = fSin;
	pf32OutMat4x4[3] = 0.0f;
	pf32OutMat4x4[4] = 0.0f;
	pf32OutMat4x4[5] = 1.0f;
	pf32OutMat4x4[6] = 0.0f;
	pf32OutMat4x4[7] = 0.0f;
	pf32OutMat4x4[8] = -fSin;
	pf32OutMat4x4[9] = 0.0f;
	pf32OutMat4x4[10] = fCos;
	pf32OutMat4x4[11] = 0.0f;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixRotationZ4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 f32Angle)
{
	VeFloat32 fSin, fCos;
	VE_ASSERT(pf32OutMat4x4);
	VeSinCosf(&fSin, &fCos, f32Angle);
	pf32OutMat4x4[0] = fCos;
	pf32OutMat4x4[1] = -fSin;
	pf32OutMat4x4[2] = 0.0f;
	pf32OutMat4x4[3] = 0.0f;
	pf32OutMat4x4[4] = fSin;
	pf32OutMat4x4[5] = fCos;
	pf32OutMat4x4[6] = 0.0f;
	pf32OutMat4x4[7] = 0.0f;
	pf32OutMat4x4[8] = 0.0f;
	pf32OutMat4x4[9] = 0.0f;
	pf32OutMat4x4[10] = 1.0f;
	pf32OutMat4x4[11] = 0.0f;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixScaling4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 f32ScaleX, VeFloat32 f32ScaleY, VeFloat32 f32ScaleZ)
{
	VE_ASSERT(pf32OutMat4x4);
	pf32OutMat4x4[0] = f32ScaleX;
	pf32OutMat4x4[1] = 0.0f;
	pf32OutMat4x4[2] = 0.0f;
	pf32OutMat4x4[3] = 0.0f;
	pf32OutMat4x4[4] = 0.0f;
	pf32OutMat4x4[5] = f32ScaleY;
	pf32OutMat4x4[6] = 0.0f;
	pf32OutMat4x4[7] = 0.0f;
	pf32OutMat4x4[8] = 0.0f;
	pf32OutMat4x4[9] = 0.0f;
	pf32OutMat4x4[10] = f32ScaleZ;
	pf32OutMat4x4[11] = 0.0f;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixTranslation4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 x, VeFloat32 y, VeFloat32 z)
{
	VE_ASSERT(pf32OutMat4x4);
	pf32OutMat4x4[0] = 1.0f;
	pf32OutMat4x4[1] = 0.0f;
	pf32OutMat4x4[2] = 0.0f;
	pf32OutMat4x4[3] = x;
	pf32OutMat4x4[4] = 0.0f;
	pf32OutMat4x4[5] = 1.0f;
	pf32OutMat4x4[6] = 0.0f;
	pf32OutMat4x4[7] = y;
	pf32OutMat4x4[8] = 0.0f;
	pf32OutMat4x4[9] = 0.0f;
	pf32OutMat4x4[10] = 1.0f;
	pf32OutMat4x4[11] = z;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixRotationYawPitchRoll4f(VeFloat32* pf32OutMat4x4,
	VeFloat32 f32Yaw, VeFloat32 f32Pitch, VeFloat32 f32Roll)
{
	VeFloat32 afMat4x4Temp[16];
	VE_ASSERT(pf32OutMat4x4);
	VeMatrixRotationZ4f(pf32OutMat4x4, f32Roll);
	VeMatrixRotationX4f(afMat4x4Temp, f32Pitch);
	VeMatrixMultiply4f(pf32OutMat4x4, pf32OutMat4x4, afMat4x4Temp);
	VeMatrixRotationY4f(afMat4x4Temp, f32Yaw);
	VeMatrixMultiply4f(pf32OutMat4x4, pf32OutMat4x4, afMat4x4Temp);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixRotationQuaternion4f(VeFloat32* pf32OutMat4x4,
	const VeFloat32* pfQuat)
{
	const VeFloat32 fTx  = 2.0f * pfQuat[0];
	const VeFloat32 fTy  = 2.0f * pfQuat[1];
	const VeFloat32 fTz  = 2.0f * pfQuat[2];
	const VeFloat32 fTwx = fTx * pfQuat[3];
	const VeFloat32 fTwy = fTy * pfQuat[3];
	const VeFloat32 fTwz = fTz * pfQuat[3];
	const VeFloat32 fTxx = fTx * pfQuat[0];
	const VeFloat32 fTxy = fTy * pfQuat[0];
	const VeFloat32 fTxz = fTz * pfQuat[0];
	const VeFloat32 fTyy = fTy * pfQuat[1];
	const VeFloat32 fTyz = fTz * pfQuat[1];
	const VeFloat32 fTzz = fTz * pfQuat[2];
	pf32OutMat4x4[0] = 1.0f - (fTyy + fTzz);
	pf32OutMat4x4[1] = fTxy + fTwz;
	pf32OutMat4x4[2] = fTxz - fTwy;
	pf32OutMat4x4[3] = 0.0f;
	pf32OutMat4x4[4] = fTxy - fTwz;
	pf32OutMat4x4[5] = 1.0f - (fTxx + fTzz);
	pf32OutMat4x4[6] = fTyz + fTwx;
	pf32OutMat4x4[7] = 0.0f;
	pf32OutMat4x4[8] = fTxz + fTwy;
	pf32OutMat4x4[9] = fTyz - fTwx;
	pf32OutMat4x4[10] = 1.0f - (fTxx + fTyy);
	pf32OutMat4x4[11] = 0.0f;
	pf32OutMat4x4[12] = 0.0f;
	pf32OutMat4x4[13] = 0.0f;
	pf32OutMat4x4[14] = 0.0f;
	pf32OutMat4x4[15] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixDecomposeWorld4f(
	VeFloat32* pf32OutQuat, VeFloat32* pf32OutVec3Scale,
	VeFloat32* pf32OutVec3Trans, const VeFloat32* pf32Mat4x4)
{
	VeFloat32 afMat4x4[16];
	VeFloat32 fScaleX;
	VeFloat32 fScaleY;
	VeFloat32 fScaleZ;

	VE_ASSERT(pf32Mat4x4[3] == 0.0f && pf32Mat4x4[7] == 0.0f &&
		pf32Mat4x4[11] == 0.0f && pf32Mat4x4[15] == 1.0f);

	VE_ASSERT(pf32Mat4x4);
	VE_ASSERT(pf32OutVec3Trans);
	VE_ASSERT(pf32OutVec3Scale);
	VE_ASSERT(pf32OutQuat);

	VeCopy16f(afMat4x4, pf32Mat4x4);

	pf32OutVec3Trans[0] = afMat4x4[12];
	pf32OutVec3Trans[1] = afMat4x4[13];
	pf32OutVec3Trans[2] = afMat4x4[14];

	fScaleX = VeLength3f(&afMat4x4[0]);
	fScaleY = VeLength3f(&afMat4x4[4]);
	fScaleZ = VeLength3f(&afMat4x4[8]);

	VeScale3f(&afMat4x4[0], &afMat4x4[0], 1.0f / fScaleX);
	VeScale3f(&afMat4x4[4], &afMat4x4[4], 1.0f / fScaleY);
	VeScale3f(&afMat4x4[8], &afMat4x4[8], 1.0f / fScaleZ);

	VeQuaternionRotationMatrixf(pf32OutQuat, afMat4x4);

	pf32OutVec3Scale[0] = fScaleX;
	pf32OutVec3Scale[1] = fScaleY;
	pf32OutVec3Scale[2] = fScaleZ;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrixPerspectiveFovLH_DX(VeFloat32* pf32OutMat4x4,
	VeFloat32 fov, VeFloat32 aspect, VeFloat32 znear, VeFloat32 zfar)
{
	VE_ASSERT(pf32OutMat4x4);
	VeFloat32 yScale = 1.0f / VeTanf(fov * 0.5f);
	VeFloat32 xScale = yScale * aspect;
	pf32OutMat4x4[0] = xScale;
	pf32OutMat4x4[1] = 0;
	pf32OutMat4x4[2] = 0;
	pf32OutMat4x4[3] = 0;
	pf32OutMat4x4[4] = 0;
	pf32OutMat4x4[5] = yScale;
	pf32OutMat4x4[6] = 0;
	pf32OutMat4x4[7] = 0;
	pf32OutMat4x4[8] = 0;
	pf32OutMat4x4[9] = 0;
	pf32OutMat4x4[10] = zfar / (zfar - znear);
	pf32OutMat4x4[11] = pf32OutMat4x4[10] * (-znear);
	pf32OutMat4x4[12] = 0;
	pf32OutMat4x4[13] = 0;
	pf32OutMat4x4[14] = 1;
	pf32OutMat4x4[15] = 0;
}
//--------------------------------------------------------------------------
VE_POWER_INLINE void VeMatrixPerspectiveFovLH_GL(VeFloat32* pf32OutMat4x4,
	VeFloat32 fov, VeFloat32 aspect, VeFloat32 znear, VeFloat32 zfar)
{
	VE_ASSERT(pf32OutMat4x4);
	VeFloat32 yScale = 1.0f / VeTanf(fov * 0.5f);
	VeFloat32 xScale = yScale * aspect;
	VeFloat32 zInvDelta = 1.0f / (zfar - znear);
	pf32OutMat4x4[0] = xScale;
	pf32OutMat4x4[1] = 0;
	pf32OutMat4x4[2] = 0;
	pf32OutMat4x4[3] = 0;
	pf32OutMat4x4[4] = 0;
	pf32OutMat4x4[5] = yScale;
	pf32OutMat4x4[6] = 0;
	pf32OutMat4x4[7] = 0;
	pf32OutMat4x4[8] = 0;
	pf32OutMat4x4[9] = 0;
	pf32OutMat4x4[10] = zInvDelta * (zfar + znear);
	pf32OutMat4x4[11] = zInvDelta * (-znear) * 2.0f * zfar;
	pf32OutMat4x4[12] = 0;
	pf32OutMat4x4[13] = 0;
	pf32OutMat4x4[14] = 1;
	pf32OutMat4x4[15] = 0;
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternionRotationMatrixf(VeFloat32* pf32OutQuat,
	const VeFloat32* pf32Mat4x4)
{
	static VeUInt32 s_uiNext[3] = {1, 2, 0};
	VeFloat32 fTrace = pf32Mat4x4[0] + pf32Mat4x4[5] + pf32Mat4x4[10];
	VeFloat32 fRoot;
	VeUInt32 i,j,k;

	if (fTrace > 0.0f)
	{
		fRoot = VeSqrtf(fTrace + 1.0f);
		pf32OutQuat[3] = 0.5f * fRoot;
		fRoot = 0.5f / fRoot;
		pf32OutQuat[0] = (pf32Mat4x4[6] - pf32Mat4x4[9]) * fRoot;
		pf32OutQuat[1] = (pf32Mat4x4[8] - pf32Mat4x4[2]) * fRoot;
		pf32OutQuat[2] = (pf32Mat4x4[1] - pf32Mat4x4[4]) * fRoot;
	}
	else
	{

		i = 0;
		if (pf32Mat4x4[5] > pf32Mat4x4[0])
			i = 1;
		if (pf32Mat4x4[10] > pf32Mat4x4[0])
			i = 2;
		j = s_uiNext[i];
		k = s_uiNext[j];

		fRoot = VeSqrtf(pf32Mat4x4[i*4+i] - pf32Mat4x4[j*4+j] -
			pf32Mat4x4[k*4+k] + 1.0f);
		pf32OutQuat[i] = 0.5f * fRoot;
		fRoot = 0.5f / fRoot;
		pf32OutQuat[3] = (pf32Mat4x4[j*4+k] - pf32Mat4x4[k*4+j]) * fRoot;
		pf32OutQuat[j] = (pf32Mat4x4[i*4+j] + pf32Mat4x4[j*4+i]) * fRoot;
		pf32OutQuat[k] = (pf32Mat4x4[i*4+k] + pf32Mat4x4[k*4+i]) * fRoot;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternionRotationAxisf(VeFloat32* pf32OutQuat,
	const VeFloat32* pf32Vec3, VeFloat32 f32Angle)
{
	VeFloat32 fSin, fCos;
	VeSinCosf(&fSin, &fCos, 0.5f * f32Angle);
	pf32OutQuat[0] = fSin * pf32Vec3[0];
	pf32OutQuat[1] = fSin * pf32Vec3[1];
	pf32OutQuat[2] = fSin * pf32Vec3[2];
	pf32OutQuat[3] = fCos;
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternionMultiplyf(VeFloat32* pf32OutQuat,
	const VeFloat32* pf32Quat0, const VeFloat32* pf32Quat1)
{
	pf32OutQuat[0] = pf32Quat0[3] * pf32Quat1[0] + pf32Quat0[0] * pf32Quat1[3] -
		pf32Quat0[1] * pf32Quat1[2] + pf32Quat0[2] * pf32Quat1[1];
	pf32OutQuat[1] = pf32Quat0[3] * pf32Quat1[1] + pf32Quat0[1] * pf32Quat1[3] -
		pf32Quat0[2] * pf32Quat1[0] + pf32Quat0[0] * pf32Quat1[2];
	pf32OutQuat[2] = pf32Quat0[3] * pf32Quat1[2] + pf32Quat0[2] * pf32Quat1[3] -
		pf32Quat0[0] * pf32Quat1[1] + pf32Quat0[1] * pf32Quat1[0];
	pf32OutQuat[3] = pf32Quat0[3] * pf32Quat1[3] - pf32Quat0[0] * pf32Quat1[0] -
		pf32Quat0[1] * pf32Quat1[1] - pf32Quat0[2] * pf32Quat1[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternionInversef(VeFloat32* p32OutQuat,
	const VeFloat32* pf32Quat)
{
	VeFloat32 fNorm = VeLengthSqr4f(pf32Quat);
	if(fNorm > 0)
	{
		VeFloat32 fInvNorm = 1.0f / fNorm;
		p32OutQuat[0] = -fInvNorm * pf32Quat[0];
		p32OutQuat[1] = -fInvNorm * pf32Quat[1];
		p32OutQuat[2] = -fInvNorm * pf32Quat[2];
		p32OutQuat[3] = fInvNorm * pf32Quat[3];
	}
	else
	{
		p32OutQuat[0] = 0;
		p32OutQuat[1] = 0;
		p32OutQuat[2] = 0;
		p32OutQuat[3] = 0;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransformIdenty6f(VeFloat32* pf32Dst)
{
	pf32Dst[0] = 1.0f;
	pf32Dst[1] = 0.0f;
	pf32Dst[2] = 0.0f;
	pf32Dst[3] = 1.0f;
	pf32Dst[4] = 0.0f;
	pf32Dst[5] = 0.0f;
}
//--------------------------------------------------------------------------
