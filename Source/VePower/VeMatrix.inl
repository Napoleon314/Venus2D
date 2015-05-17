////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMatrix.inl
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeMatrix::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32& VeMatrix::operator () (VeUInt32 u32Row,
	VeUInt32 u32Col)
{
	return m[u32Row][u32Col];
}
//--------------------------------------------------------------------------
VE_INLINE const VeFloat32& VeMatrix::operator () (VeUInt32 u32Row,
	VeUInt32 u32Col) const
{
	return m[u32Row][u32Col];
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix& VeMatrix::operator *= (const VeMatrix& kMatrix)
{
	VeMatrixMultiply4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kMatrix);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix& VeMatrix::operator += (const VeMatrix& kMatrix)
{
	VeAdd16f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kMatrix);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix& VeMatrix::operator -= (const VeMatrix& kMatrix)
{
	VeSub16f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kMatrix);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix& VeMatrix::operator *= (VeFloat32 f32Scale)
{
	VeScale16f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix& VeMatrix::operator /= (VeFloat32 f32Scale)
{
	VeScale16f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator + () const
{
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator - () const
{
	return (*this) * -1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator * (const VeMatrix& kMatrix) const
{
	VeMatrix kRes;
	VeMatrixMultiply4f(kRes, VE_FLOAT_POINT_THIS, kMatrix);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator + (const VeMatrix& kMatrix) const
{
	VeMatrix kRes;
	VeAdd16f(kRes, VE_FLOAT_POINT_THIS, kMatrix);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator - (const VeMatrix& kMatrix) const
{
	VeMatrix kRes;
	VeSub16f(kRes, VE_FLOAT_POINT_THIS, kMatrix);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator * (VeFloat32 f32Scale) const
{
	VeMatrix kRes;
	VeScale16f(kRes, VE_FLOAT_POINT_THIS, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix VeMatrix::operator / (VeFloat32 f32Scale) const
{
	VeMatrix kRes;
	VeScale16f(kRes, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeMatrix operator * (VeFloat32 f32Scale, const VeMatrix& kMatrix)
{
	VeMatrix kRes;
	VeScale16f(kRes, kMatrix, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeMatrix::operator == (const VeMatrix& kMatrix) const
{
	return (_11 == kMatrix._11) && (_12 == kMatrix._12) &&
		(_13 == kMatrix._13) && (_14 == kMatrix._14) &&
		(_21 == kMatrix._21) && (_22 == kMatrix._22) &&
		(_23 == kMatrix._23) && (_24 == kMatrix._24) &&
		(_31 == kMatrix._31) && (_32 == kMatrix._32) &&
		(_33 == kMatrix._33) && (_34 == kMatrix._34) &&
		(_41 == kMatrix._41) && (_42 == kMatrix._42) &&
		(_43 == kMatrix._43) && (_44 == kMatrix._44);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeMatrix::operator != (const VeMatrix& kMatrix) const
{
	return (_11 != kMatrix._11) || (_12 != kMatrix._12) ||
		(_13 != kMatrix._13) || (_14 != kMatrix._14) ||
		(_21 != kMatrix._21) || (_22 != kMatrix._22) ||
		(_23 != kMatrix._23) || (_24 != kMatrix._24) ||
		(_31 != kMatrix._31) || (_32 != kMatrix._32) ||
		(_33 != kMatrix._33) || (_34 != kMatrix._34) ||
		(_41 != kMatrix._41) || (_42 != kMatrix._42) ||
		(_43 != kMatrix._43) || (_44 != kMatrix._44);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeMatrix::operator [] (VeUInt32 i)
{
	return *(VeVector4D*)(&m[i]);
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector4D& VeMatrix::operator [] (VeUInt32 i) const
{
	return *(const VeVector4D*)(&m[i]);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeMatrix::Row(VeUInt32 i)
{
	VE_ASSERT(0 <= i && i < 4);
	return *(VeVector4D*)(&m[i]);
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector4D& VeMatrix::Row(VeUInt32 i) const
{
	VE_ASSERT(0 <= i && i < 4);
	return *(const VeVector4D*)(&m[i]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::Row(VeUInt32 i, const VeVector4D& kVec)
{
	Row(i) = kVec;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeMatrix::Col(VeUInt32 i) const
{
	VE_ASSERT(0 <= i && i < 4);
	return VeVector4D(m[0][i],  m[1][i], m[2][i], m[3][i]);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::Col(VeUInt32 i, const VeVector4D& kVec)
{
	VE_ASSERT(0 <= i && i < 4);
	m[0][i] = kVec.x;
	m[1][i] = kVec.y;
	m[2][i] = kVec.z;
	m[3][i] = kVec.w;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetZero()
{
	*this = ZERO;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetIdentity()
{
	*this = IDENTITY;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetScale(VeFloat32 x, VeFloat32 y, VeFloat32 z)
{
	VeMatrixScaling4f(VE_FLOAT_POINT_THIS, x, y, z);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetScale(const VeVector3D& kScale)
{
	SetScale(kScale.x, kScale.y, kScale.z);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetTranslate(VeFloat32 x, VeFloat32 y, VeFloat32 z)
{
	VeMatrixTranslation4f(VE_FLOAT_POINT_THIS, x, y, z);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetTranslate(const VeVector3D& kPos)
{
	SetTranslate(kPos.x, kPos.y, kPos.z);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotateX(VeFloat32 f32Angle)
{
	VeMatrixRotationX4f(VE_FLOAT_POINT_THIS, f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotateY(VeFloat32 f32Angle)
{
	VeMatrixRotationY4f(VE_FLOAT_POINT_THIS, f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotateZ(VeFloat32 f32Angle)
{
	VeMatrixRotationY4f(VE_FLOAT_POINT_THIS, f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotate(const VeQuaternion& kQuat)
{
	VeMatrixRotationQuaternion4f(VE_FLOAT_POINT_THIS, kQuat);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotate(VeFloat32 f32Yaw, VeFloat32 f32Pitch,
	VeFloat32 f32Roll)
{
	VeMatrixRotationYawPitchRoll4f(VE_FLOAT_POINT_THIS,
		f32Yaw, f32Pitch, f32Roll);
}
//--------------------------------------------------------------------------
VE_INLINE static bool IsValidAngle(VeFloat32 f32Angle)
{
	return (-100.0f < f32Angle) && (f32Angle < 100.0f);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::SetRotateInverse(VeFloat32 f32Yaw,
	VeFloat32 f32Pitch, VeFloat32 f32Roll)
{
	VE_ASSERT(IsValidAngle(f32Yaw));
	VE_ASSERT(IsValidAngle(f32Pitch));
	VE_ASSERT(IsValidAngle(f32Roll));

	VeFloat32 sya, cya;
	VeFloat32 sxa, cxa;
	VeFloat32 sza, cza;

	VeSinCosf(&sya, &cya, f32Yaw);
	VeSinCosf(&sxa, &cxa, f32Pitch);
	VeSinCosf(&sza, &cza, f32Roll);

	m[0][0] = cya * cza;
	m[0][1] = -cya * sza;
	m[0][2] = sya * cxa;
	m[0][3] =  0.0f;

	m[1][0] = cxa * sza;
	m[1][1] = cxa * cza;
	m[1][2] = -sxa;
	m[1][3] =  0.0f;

	m[2][0] = -sya * cza + cya * sza * sxa;
	m[2][1] = sya * sza + cya * cza * sxa;
	m[2][2] = cxa * cya;
	m[2][3] =  0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::Multiply(const VeMatrix& kMat0,
	const VeMatrix& kMat1)
{
	VeMatrixMultiply4f(VE_FLOAT_POINT_THIS, kMat0, kMat1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::PreMultiply(const VeMatrix& kMat)
{
	VeMatrixMultiply4f(VE_FLOAT_POINT_THIS, kMat, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::PostMultiply(const VeMatrix& kMat)
{
	VeMatrixMultiply4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kMat);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::InvertOrthonormal(const VeMatrix& kMat)
{
	m[0][0] = kMat.m[0][0];
	m[0][1] = kMat.m[1][0];
	m[0][2] = kMat.m[2][0];
	m[0][3] = 0.0f;

	m[1][0] = kMat.m[0][1];
	m[1][1] = kMat.m[1][1];
	m[1][2] = kMat.m[2][1];
	m[1][3] = 0.0f;

	m[2][0] = kMat.m[0][2];
	m[2][1] = kMat.m[1][2];
	m[2][2] = kMat.m[2][2];
	m[2][3] = 0.0f;

	m[3][0] = -(kMat.m[3][0] * m[0][0] + kMat.m[3][1] * m[1][0] + kMat.m[3][2] * m[2][0]);
	m[3][1] = -(kMat.m[3][0] * m[0][1] + kMat.m[3][1] * m[1][1] + kMat.m[3][2] * m[2][1]);
	m[3][2] = -(kMat.m[3][0] * m[0][2] + kMat.m[3][1] * m[1][2] + kMat.m[3][2] * m[2][2]);
	m[3][3] = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::InvertOrthonormal()
{
	const VeMatrix kMat(*this);
	InvertOrthonormal(kMat);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeMatrix::Invert(const VeMatrix& kMat)
{
	return VeMatrixInverse4f(VE_FLOAT_POINT_THIS, NULL, kMat) ? true : false;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeMatrix::Invert()
{
	return Invert(*this);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeMatrix::GetDeterminant() const
{
	return VeMatrixDeterminant4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::Transpose(const VeMatrix& kMat)
{
	VeMatrixTranspose4f(VE_FLOAT_POINT_THIS, kMat);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::Transpose()
{
	VeMatrixTranspose4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::LookAt(const VeVector3D& kPosition,
	const VeVector3D& kDirection, const VeVector3D& kUp)
{
	VE_ASSERT(!"Can't use!");
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeMatrix::ApplyPoint(const VeVector3D& kVec) const
{
	VeVector3D kRes;
	VeVector3TransformCoordM4f(kRes, kVec, VE_FLOAT_POINT_THIS);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::ApplyPoint(VeVector3D& kVec0,
	const VeVector3D& kVec1) const
{
	VeVector3TransformCoordM4f(kVec0, kVec1, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::ApplyPoint(VeVector4D& kVec0,
	const VeVector3D& kVec1) const
{
	VeVector3TransformM4f(kVec0, kVec1, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::ApplyPoint(VeVector4D& kVec0,
	const VeVector4D& kVec1) const
{
	VeVector4Transformf(kVec0, kVec1, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeMatrix::ApplyVector(const VeVector3D& kVec) const
{
	VeVector3D kRes;
	VeVector3TransformNormalM4f(kRes, kVec, VE_FLOAT_POINT_THIS);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMatrix::ApplyVector(VeVector3D& kVec0,
	const VeVector3D& kVec1) const
{
	VeVector3TransformNormalM4f(kVec0, kVec1, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector3D& VeMatrix::ApplyToUnitAxisVector(
	VeUInt32 u32Axis) const
{
	return *(const VeVector3D*)m[u32Axis];
}
//--------------------------------------------------------------------------
