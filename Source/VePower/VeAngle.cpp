////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAngle.cpp
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAngle.inl"
#endif

//--------------------------------------------------------------------------
const VeAngle VeAngle::ZERO;
const VeAngle VeAngle::HALF_CYCLE(VE_MATH_PI_F);
//--------------------------------------------------------------------------
VeAngle::VeAngle() : m_f32Angle(0)
{

}
//--------------------------------------------------------------------------
VeAngle::VeAngle(const VeAngle& kAngle)
	: m_f32Angle(kAngle.m_f32Angle)

{

}
//--------------------------------------------------------------------------
VeAngle::VeAngle(VeFloat32 f32ValueInRadians)
	: m_f32Angle(f32ValueInRadians)
{
	Normalise();
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeAngle)
{
	Module() [
		Class<VeAngle>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32>()).
			Def(Constructor<const VeAngle&>()).
			Def("GetAngle", &VeAngle::GetAngle).
			Def("ClampBetween", &VeAngle::ClampBetween).
			Def("IsBetween", &VeAngle::IsBetween).
			Def("Lerp", &VeAngle::Lerp).
			Def("Normalise", (void (VeAngle::*)())&VeAngle::Normalise).
			OpAdd(&OpFuncAdd<VeAngle,VeAngle,VeAngle>).
			OpSub(&OpFuncSub<VeAngle,VeAngle,VeAngle>).
			OpUnm(&OpFuncUnm<VeAngle,VeAngle>).
			OpLt(&OpFuncLt<VeAngle,VeAngle>).
			OpLe(&OpFuncLe<VeAngle,VeAngle>).
			OpToStr(&VeAngle::ToString) [
				Def("Add", &OpFuncAdd<VeAngle,VeAngle,VeAngle>),
				Def("Sub", &OpFuncSub<VeAngle,VeAngle,VeAngle>),
				Def("Eq", &OpFuncEq<VeAngle,VeAngle>),
				Def("Normalise", (VeFloat32 (*)(VeFloat32))&VeAngle::Normalise),
				Def("Decay", &VeAngle::Decay),
				Def("SameSignAngle", &VeAngle::SameSignAngle),
				Def("TurnRange", &VeAngle::TurnRange),
				DefRead("ZERO", VeAngle::ZERO),
				DefRead("HALF_CYCLE", VeAngle::HALF_CYCLE)
			]
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeAngle::ToString(VeAngle kAngle)
{
	VeSprintf(g_acPrintBuffer, "angle(%.2f)", kAngle.m_f32Angle);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
