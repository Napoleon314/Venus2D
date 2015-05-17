////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAction.cpp
//  Version:     v1.00
//  Created:     8/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAction.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRootRTTI(VeAction);
//--------------------------------------------------------------------------
VeAction::VeAction() : m_pkTarget(NULL), m_f64StartTime(0), m_i32Tag(-1)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeAction::~VeAction()
{

}
//--------------------------------------------------------------------------
bool VeAction::IsDone()
{
	return true;
}
//--------------------------------------------------------------------------
void VeAction::Stop()
{
	if(m_pkTarget && m_kNode.IsAttach())
	{
		m_pkTarget->StopAction(this);
	}
	else
	{
		m_pkTarget = NULL;
		m_f64StartTime = 0;
	}
}
//--------------------------------------------------------------------------
void VeAction::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	m_pkTarget = pkTarget;
	m_f64StartTime = f64Time;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeAction)
{
	Module() [
		Class<VeAction>().
			Def("SetTag", &VeAction::SetTag).
			Def("GetTag", &VeAction::GetTag).
			Def("GetStartTime", &VeAction::GetStartTime).
			Def("IsDone", &VeAction::IsDone).
			Def("Stop", &VeAction::Stop).
			Def("Start", &VeAction::Start).
			Def("Update", &VeAction::Update).
			Def("SetPos", &VeAction::SetPos)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeFiniteTimeAction, VeAction);
//--------------------------------------------------------------------------
VeFiniteTimeAction::VeFiniteTimeAction()
	: m_f32Duration(0.0f), m_f32InvDuration(0.0f)
{

}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeFiniteTimeAction::Reverse()
{
	return NULL;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeFiniteTimeAction)
{
	Module() [
		Class< VeFiniteTimeAction, Base<VeAction> >().
			Def("SetDuration", &VeFiniteTimeAction::SetDuration).
			Def("GetDuration", &VeFiniteTimeAction::GetDuration).
			Def("Reverse", (VeFiniteTimeAction* (VeFiniteTimeAction::*)()) &VeFiniteTimeAction::Reverse)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeActionInterval, VeFiniteTimeAction);
//--------------------------------------------------------------------------
VeActionInterval::VeActionInterval() : m_f64CurTime(0)
{

}
//--------------------------------------------------------------------------
bool VeActionInterval::IsDone()
{
	return (m_f64CurTime - m_f64StartTime) >= m_f32Duration;
}
//--------------------------------------------------------------------------
void VeActionInterval::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeFiniteTimeAction::Start(pkTarget, f64Time);
	m_f64CurTime = f64Time;
}
//--------------------------------------------------------------------------
void VeActionInterval::Update(VeFloat64 f64Time)
{
	m_f64CurTime = f64Time;
	VeFloat32 f32Pos = (m_f32InvDuration == 0) ?
		1.0f : VE_SAT(VeFloat32(m_f64CurTime - m_f64StartTime) * m_f32InvDuration);
	SetPos(f32Pos);
}
//--------------------------------------------------------------------------
void VeActionInterval::InitWithDuration(VeFloat32 f32Duration)
{
	SetDuration(f32Duration);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeActionInterval)
{
	Module() [
		Class< VeActionInterval, Base<VeFiniteTimeAction> >().
			Def("GetCurTime", &VeActionInterval::GetCurTime)
	];
}
//--------------------------------------------------------------------------
VeSmartPointer(ExtraAction);
//--------------------------------------------------------------------------
class ExtraAction : public VeFiniteTimeAction
{
	VeDeclareRTTI;
public:
	static ExtraAction* Create()
	{
		return VE_NEW ExtraAction;
	}

	virtual VeFiniteTimeAction* Reverse()
	{
		return ExtraAction::Create();
	}

	virtual void Update(VeFloat64 f64Time) {}

	virtual void SetPos(VeFloat32 f32Pos) {}

};
//--------------------------------------------------------------------------
VeImplementRTTI(ExtraAction, VeActionInterval);
//--------------------------------------------------------------------------
VeImplementRTTI(VeSequence, VeActionInterval);
//--------------------------------------------------------------------------
VeSequence::VeSequence() : m_f32Split(0), m_i32Last(-1)
{

}
//--------------------------------------------------------------------------
void VeSequence::Stop()
{
	if(m_i32Last != -1)
	{
		m_aspActions[m_i32Last]->Stop();
	}
	VeActionInterval::Stop();
}
//--------------------------------------------------------------------------
void VeSequence::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	m_f32Split = m_aspActions[0]->GetDuration() * m_f32InvDuration;
	m_i32Last = -1;
}
//--------------------------------------------------------------------------
void VeSequence::SetPos(VeFloat32 f32Pos)
{
	VeInt32 i32Found(0);
	VeFloat32 f32NewPos(0.0f);
	if(f32Pos < m_f32Split)
	{
		i32Found = 0;
		f32NewPos = (m_f32Split != 0.0f) ? (f32Pos / m_f32Split) : 1.0f;
	}
	else
	{
		i32Found = 1;
		f32NewPos = (m_f32Split != 1.0f) ? ((f32Pos - m_f32Split) / (1.0f - m_f32Split)) : 1.0f;
	}

	if(i32Found == 1)
	{
		if(m_i32Last == -1)
		{
			m_aspActions[0]->Start(m_pkTarget, 0);
			m_aspActions[0]->SetPos(1.0f);
			m_aspActions[0]->Stop();
		}
		else if(m_i32Last == 0)
		{
			m_aspActions[0]->SetPos(1.0f);
			m_aspActions[0]->Stop();
		}
	}
	else if(i32Found == 0 && m_i32Last == 1)
	{
		m_aspActions[1]->SetPos(0.0f);
		m_aspActions[1]->Stop();
	}
	if(i32Found == m_i32Last && m_aspActions[i32Found]->IsDone())
	{
		return;
	}
	if(i32Found != m_i32Last)
	{
		m_aspActions[i32Found]->Start(m_pkTarget, 0);
	}
	m_aspActions[i32Found]->SetPos(f32NewPos);
	m_i32Last = i32Found;
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeSequence::Reverse()
{
	return NULL;
}
//--------------------------------------------------------------------------
void VeSequence::InitWithTwoActions(
	VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1)
{
	VE_ASSERT(pkAction0 && pkAction1);
	VeActionInterval::InitWithDuration(pkAction0->GetDuration() + pkAction1->GetDuration());
	m_aspActions[0] = pkAction0;
	m_aspActions[1] = pkAction1;
}
//--------------------------------------------------------------------------
VeSequence* VeSequence::Create(VeFiniteTimeAction* pkAction, ...)
{
	VeSequence* pkRes;
	va_list kArgs;
	va_start(kArgs, pkAction);
	pkRes = VeSequence::CreateWithVariableList(pkAction, kArgs);
	va_end(kArgs);
	return pkRes;
}
//--------------------------------------------------------------------------
VeSequence* VeSequence::CreateWithVariableList(
	VeFiniteTimeAction* pkAction, va_list kArgs)
{
	VeFiniteTimeAction* pkNow;
	VeFiniteTimeAction* pkPrev = pkAction;
	bool bOneAction(true);
	while(pkAction)
	{
		pkNow = va_arg(kArgs, VeFiniteTimeAction*);
		if(pkNow)
		{
			pkPrev = CreateWithTwoActions(pkPrev, pkNow);
			bOneAction = false;
		}
		else
		{
			if(bOneAction)
			{
				pkPrev = CreateWithTwoActions(pkPrev, ExtraAction::Create());
			}
			break;
		}
	}
	return VeDynamicCast(VeSequence, pkPrev);
}
//--------------------------------------------------------------------------
VeSequence* VeSequence::CreateWithTwoActions(
	VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1)
{
	VeSequence* pkSequence = VE_NEW VeSequence;
	pkSequence->InitWithTwoActions(pkAction0, pkAction1);
	return pkSequence;
}
//--------------------------------------------------------------------------
static VeInt32 CreateSequence(lua_State* pkState)
{
	VeInt32 i32ParamNum = VeLua::GetTop(pkState);
	if(i32ParamNum)
	{
		VeInt32 i32Index(1);
		if(TestParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index) == 1)
		{
			VeFiniteTimeAction* pkNow;
			VeFiniteTimeAction* pkPrev = GetParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index);
			bool bOneAction(true);
			while((++i32Index) <= i32ParamNum)
			{
				if(TestParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index) == 1)
				{
					pkNow = GetParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index);
				}
				else
				{
					pkNow = NULL;
				}
				if(pkNow)
				{
					pkPrev = VeSequence::CreateWithTwoActions(pkPrev, pkNow);
					bOneAction = false;
				}
				else
				{
					if(bOneAction)
					{
						pkPrev = VeSequence::CreateWithTwoActions(pkPrev, ExtraAction::Create());
					}
					break;
				}
			}
			return RetParam(pkState, pkPrev);
		}
	}
	return -1;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSequence)
{
	Module() [
		Class< VeSequence, Base<VeActionInterval> >().
			Def("InitWithTwoActions", &VeSequence::InitWithTwoActions) [
				Def("CreateWithTwoActions", &VeSequence::CreateWithTwoActions),
				DefManualFunc("Create", &CreateSequence)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRepeat, VeActionInterval);
//--------------------------------------------------------------------------
bool VeRepeat::IsDone()
{
	return m_u32Total == m_u32Times;
}
//--------------------------------------------------------------------------
void VeRepeat::Stop()
{
	m_spInnerAction->Stop();
	VeActionInterval::Stop();
}
//--------------------------------------------------------------------------
void VeRepeat::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	m_u32Total = 0;
	m_f32Next = m_spInnerAction->GetDuration() * m_f32InvDuration;
	VeActionInterval::Start(pkTarget, f64Time);
	m_spInnerAction->Start(pkTarget, 0);
}
//--------------------------------------------------------------------------
void VeRepeat::SetPos(VeFloat32 f32Pos)
{
	if(f32Pos >= m_f32Next)
	{
		while(f32Pos > m_f32Next && m_u32Total < m_u32Times)
		{
			m_spInnerAction->Update(1.0f);
			++m_u32Total;
			m_spInnerAction->Stop();
			m_spInnerAction->Start(m_pkTarget, 0);
			m_f32Next += m_spInnerAction->GetDuration() * m_f32InvDuration;
		}

		if(f32Pos >= 1.0f && m_u32Total < m_u32Times) 
		{
			++m_u32Total;
		}

		if(!m_bActionInstant)
		{
			if(m_u32Total == m_u32Times)
			{
				m_spInnerAction->SetPos(1.0f);
				m_spInnerAction->Stop();
			}
			else
			{
				m_spInnerAction->SetPos(f32Pos - (m_f32Next - m_spInnerAction->GetDuration() * m_f32InvDuration));
			}
		}
	}
	else
	{
		m_spInnerAction->SetPos(VeFmodf(f32Pos * m_u32Times, 1.0f));
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeRepeat::Reverse()
{
	return VeRepeat::Create(m_spInnerAction->Reverse(), m_u32Times);
}
//--------------------------------------------------------------------------
void VeRepeat::InitWithAction(VeFiniteTimeAction* pkAction,
	VeUInt32 u32Times)
{
	VeActionInterval::InitWithDuration(pkAction->GetDuration() * u32Times);
	m_u32Times = u32Times;
	m_u32Total = 0;
	m_spInnerAction = pkAction;
	m_bActionInstant = VeDynamicCast(VeActionInstant, pkAction) ? true : false;
	if(m_bActionInstant) m_u32Times -= 1;
}
//--------------------------------------------------------------------------
VeRepeat* VeRepeat::Create(VeFiniteTimeAction* pkAction, VeUInt32 u32Times)
{
	VeRepeat* pkRepeat = VE_NEW VeRepeat;
	pkRepeat->InitWithAction(pkAction, u32Times);
	return pkRepeat;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeRepeat)
{
	Module() [
		Class< VeRepeat, Base<VeActionInterval> >().
			Def("InitWithAction", &VeRepeat::InitWithAction) [
				Def("Create", &VeRepeat::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRepeatForever, VeActionInterval);
//--------------------------------------------------------------------------
bool VeRepeatForever::IsDone()
{
	return false;
}
//--------------------------------------------------------------------------
void VeRepeatForever::Stop()
{
	m_spInnerAction->Stop();
	VeActionInterval::Stop();
}
//--------------------------------------------------------------------------
void VeRepeatForever::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	m_spInnerAction->Start(pkTarget, f64Time);
}
//--------------------------------------------------------------------------
void VeRepeatForever::Update(VeFloat64 f64Time)
{
	m_spInnerAction->Update(f64Time);
	if(m_spInnerAction->IsDone())
	{
		m_spInnerAction->Start(m_pkTarget, m_spInnerAction->GetStartTime() + m_spInnerAction->GetDuration());
		m_spInnerAction->Update(f64Time);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeRepeatForever::Reverse()
{
	return VeRepeatForever::Create(m_spInnerAction->Reverse());
}
//--------------------------------------------------------------------------
void VeRepeatForever::InitWithAction(VeFiniteTimeAction* pkAction)
{
	m_spInnerAction = pkAction;
}
//--------------------------------------------------------------------------
VeRepeatForever* VeRepeatForever::Create(VeFiniteTimeAction* pkAction)
{
	VeRepeatForever* pkRet = VE_NEW VeRepeatForever;
	pkRet->InitWithAction(pkAction);
	return pkRet;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeRepeatForever)
{
	Module() [
		Class< VeRepeatForever, Base<VeActionInterval> >().
			Def("InitWithAction", &VeRepeatForever::InitWithAction) [
				Def("Create", &VeRepeatForever::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSpawn, VeActionInterval);
//--------------------------------------------------------------------------
void VeSpawn::Stop()
{
	m_spFirst->Stop();
	m_spSecond->Stop();
	VeActionInterval::Stop();
}
//--------------------------------------------------------------------------
void VeSpawn::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	m_spFirst->Start(pkTarget, f64Time);
	m_spSecond->Start(pkTarget, f64Time);
}
//--------------------------------------------------------------------------
void VeSpawn::SetPos(VeFloat32 f32Pos)
{
	m_spFirst->SetPos(f32Pos);
	m_spSecond->SetPos(f32Pos);
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeSpawn::Reverse()
{
    return VeSpawn::CreateWithTwoActions(m_spFirst->Reverse(), m_spSecond->Reverse());
}
//--------------------------------------------------------------------------
void VeSpawn::InitWithTwoActions(VeFiniteTimeAction* pkAction0,
	VeFiniteTimeAction* pkAction1)
{
	VE_ASSERT(pkAction0 && pkAction1);
	VeFloat32 f32Dur0 = pkAction0->GetDuration();
	VeFloat32 f32Dur1 = pkAction1->GetDuration();
	VeActionInterval::InitWithDuration(VE_MAX(f32Dur0, f32Dur1));
	m_spFirst = pkAction0;
	m_spSecond = pkAction1;
	if(f32Dur0 > f32Dur1)
	{
		m_spSecond = VeSequence::CreateWithTwoActions(pkAction1, VeDelayTime::Create(f32Dur0 - f32Dur1));
	} 
	else if(f32Dur0 < f32Dur1)
	{
		m_spFirst = VeSequence::CreateWithTwoActions(pkAction0, VeDelayTime::Create(f32Dur1 - f32Dur0));
	}
}
//--------------------------------------------------------------------------
VeSpawn* VeSpawn::Create(VeFiniteTimeAction* pkAction, ...)
{
	VeSpawn* pkRes;
	va_list kArgs;
	va_start(kArgs, pkAction);
	pkRes = VeSpawn::CreateWithVariableList(pkAction, kArgs);
	va_end(kArgs);
	return pkRes;
}
//--------------------------------------------------------------------------
VeSpawn* VeSpawn::CreateWithVariableList(VeFiniteTimeAction* pkAction,
	va_list kArgs)
{
	VeFiniteTimeAction* pkNow;
	VeFiniteTimeAction* pkPrev = pkAction;
	bool bOneAction(true);
	while(pkAction)
	{
		pkNow = va_arg(kArgs, VeFiniteTimeAction*);
		if(pkNow)
		{
			pkPrev = CreateWithTwoActions(pkPrev, pkNow);
			bOneAction = false;
		}
		else
		{
			if(bOneAction)
			{
				pkPrev = CreateWithTwoActions(pkPrev, ExtraAction::Create());
			}
			break;
		}
	}
	return VeDynamicCast(VeSpawn, pkPrev);
}
//--------------------------------------------------------------------------
VeSpawn* VeSpawn::CreateWithTwoActions(VeFiniteTimeAction* pkAction0,
	VeFiniteTimeAction* pkAction1)
{
	VeSpawn* pkAction = VE_NEW VeSpawn;
	pkAction->InitWithTwoActions(pkAction0, pkAction1);
	return pkAction;
}
//--------------------------------------------------------------------------
static VeInt32 CreateSpawn(lua_State* pkState)
{
	VeInt32 i32ParamNum = VeLua::GetTop(pkState);
	if(i32ParamNum)
	{
		VeInt32 i32Index(1);
		if(TestParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index) == 1)
		{
			VeFiniteTimeAction* pkNow;
			VeFiniteTimeAction* pkPrev = GetParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index);
			bool bOneAction(true);
			while((++i32Index) <= i32ParamNum)
			{
				if(TestParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index) == 1)
				{
					pkNow = GetParam(VeLuaBind::ParamType<VeFiniteTimeAction*>(), pkState, i32Index);
				}
				else
				{
					pkNow = NULL;
				}
				if(pkNow)
				{
					pkPrev = VeSpawn::CreateWithTwoActions(pkPrev, pkNow);
					bOneAction = false;
				}
				else
				{
					if(bOneAction)
					{
						pkPrev = VeSpawn::CreateWithTwoActions(pkPrev, ExtraAction::Create());
					}
					break;
				}
			}
			return RetParam(pkState, pkPrev);
		}
	}
	return -1;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSpawn)
{
	Module() [
		Class< VeSpawn, Base<VeActionInterval> >().
			Def("InitWithTwoActions", &VeSpawn::InitWithTwoActions) [
				Def("CreateWithTwoActions", &VeSpawn::CreateWithTwoActions),
				DefManualFunc("Create", &CreateSpawn)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRotateTo2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeRotateTo2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartSkew = pkNode->GetSkew();
	}
}
//--------------------------------------------------------------------------
void VeRotateTo2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		pkNode->SetSkew(VeLerp(g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f), m_kStartSkew, m_kDstSkew));
	}
}
//--------------------------------------------------------------------------
void VeRotateTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32DstAngle)
{
	InitWithDuration(f32Duration, f32DstAngle, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeRotateTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY)
{
	InitWithDuration(f32Duration, f32SkewX, f32SkewY, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeRotateTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32DstAngle, VeTweenEasing::Type eType)
{
	InitWithDuration(f32Duration, f32DstAngle, f32DstAngle, eType);
}
//--------------------------------------------------------------------------
void VeRotateTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kDstSkew.x = f32SkewX;
	m_kDstSkew.y = f32SkewY;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeRotateTo2D* VeRotateTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32DstAngle)
{
	return Create(f32Duration, f32DstAngle, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeRotateTo2D* VeRotateTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY)
{
	return Create(f32Duration, f32SkewX, f32SkewY, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeRotateTo2D* VeRotateTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32DstAngle, VeTweenEasing::Type eType)
{
	return Create(f32Duration, f32DstAngle, f32DstAngle, eType);
}
//--------------------------------------------------------------------------
VeRotateTo2D* VeRotateTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType)
{
	VeRotateTo2D* pkAction = VE_NEW VeRotateTo2D;
	pkAction->InitWithDuration(f32Duration, f32SkewX, f32SkewY, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeRotateTo2D)
{
	Module() [
		Class< VeRotateTo2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeRotateTo2D::*)(VeFloat32,VeFloat32))&VeRotateTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateTo2D::*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateTo2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeRotateTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateTo2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateTo2D::InitWithDuration) [
				Def("Create", (VeRotateTo2D* (*)(VeFloat32,VeFloat32))&VeRotateTo2D::Create),
				Def("Create", (VeRotateTo2D* (*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateTo2D::Create),
				Def("Create", (VeRotateTo2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeRotateTo2D::Create),
				Def("Create", (VeRotateTo2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateTo2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRotateBy2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeRotateBy2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartSkew = pkNode->GetSkew();
		m_kPreSkew = m_kStartSkew;
	}
}
//--------------------------------------------------------------------------
void VeRotateBy2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartSkew += (pkNode->GetSkew() - m_kPreSkew);
		m_kPreSkew = m_kStartSkew + m_kAddSkew * g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f);
		pkNode->SetSkew(m_kPreSkew);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeRotateBy2D::Reverse()
{
	return VeRotateBy2D::Create(m_f32Duration, -m_kAddSkew.x, -m_kAddSkew.y, m_eType);
}
//--------------------------------------------------------------------------
void VeRotateBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Angle)
{
	InitWithDuration(f32Duration, f32Angle, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeRotateBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY)
{
	InitWithDuration(f32Duration, f32SkewX, f32SkewY, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeRotateBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Angle, VeTweenEasing::Type eType)
{
	InitWithDuration(f32Duration, f32Angle, f32Angle, eType);
}
//--------------------------------------------------------------------------
void VeRotateBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kAddSkew.x = f32SkewX;
	m_kAddSkew.y = f32SkewY;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeRotateBy2D* VeRotateBy2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32Angle)
{
	return Create(f32Duration, f32Angle, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeRotateBy2D* VeRotateBy2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY)
{
	return Create(f32Duration, f32SkewX, f32SkewY, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeRotateBy2D* VeRotateBy2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32Angle, VeTweenEasing::Type eType)
{
	return Create(f32Duration, f32Angle, f32Angle, eType);
}
//--------------------------------------------------------------------------
VeRotateBy2D* VeRotateBy2D::Create(VeFloat32 f32Duration,
	VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType)
{
	VeRotateBy2D* pkAction = VE_NEW VeRotateBy2D;
	pkAction->InitWithDuration(f32Duration, f32SkewX, f32SkewY, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeRotateBy2D)
{
	Module() [
		Class< VeRotateBy2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeRotateBy2D::*)(VeFloat32,VeFloat32))&VeRotateBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateBy2D::*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateBy2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeRotateBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeRotateBy2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateBy2D::InitWithDuration) [
				Def("Create", (VeRotateBy2D* (*)(VeFloat32,VeFloat32))&VeRotateBy2D::Create),
				Def("Create", (VeRotateBy2D* (*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateBy2D::Create),
				Def("Create", (VeRotateBy2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeRotateBy2D::Create),
				Def("Create", (VeRotateBy2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeRotateBy2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeMoveTo2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeMoveTo2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartPos = pkNode->GetPosition();
	}
}
//--------------------------------------------------------------------------
void VeMoveTo2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		pkNode->SetPosition(VeLerp(g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f), m_kStartPos, m_kDstPos));
	}
}
//--------------------------------------------------------------------------
void VeMoveTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 x, VeFloat32 y)
{
	InitWithDuration(f32Duration, x, y, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeMoveTo2D::InitWithDuration(VeFloat32 f32Duration, VeFloat32 x,
	VeFloat32 y, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kDstPos.x = x;
	m_kDstPos.y = y;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeMoveTo2D* VeMoveTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 x, VeFloat32 y)
{
	return Create(f32Duration, x, y, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeMoveTo2D* VeMoveTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType)
{
	VeMoveTo2D* pkAction = VE_NEW VeMoveTo2D;
	pkAction->InitWithDuration(f32Duration, x, y, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMoveTo2D)
{
	Module() [
		Class< VeMoveTo2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeMoveTo2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeMoveTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeMoveTo2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeMoveTo2D::InitWithDuration) [
				Def("Create", (VeMoveTo2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeMoveTo2D::Create),
				Def("Create", (VeMoveTo2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeMoveTo2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeMoveBy2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeMoveBy2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartPos = pkNode->GetPosition();
		m_kPrePos = m_kStartPos;
	}
}
//--------------------------------------------------------------------------
void VeMoveBy2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartPos += (pkNode->GetPosition() - m_kPrePos);
		m_kPrePos = m_kStartPos + m_kAddPos * g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f);
		pkNode->SetPosition(m_kPrePos);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeMoveBy2D::Reverse()
{
	return VeMoveBy2D::Create(m_f32Duration, -m_kAddPos.x, -m_kAddPos.y, m_eType);
}
//--------------------------------------------------------------------------
void VeMoveBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 x, VeFloat32 y)
{
	InitWithDuration(f32Duration, x, y, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeMoveBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kAddPos.x = x;
	m_kAddPos.y = y;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeMoveBy2D* VeMoveBy2D::Create(VeFloat32 f32Duration, VeFloat32 x,
	VeFloat32 y)
{
	return Create(f32Duration, x, y, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeMoveBy2D* VeMoveBy2D::Create(VeFloat32 f32Duration, VeFloat32 x,
	VeFloat32 y, VeTweenEasing::Type eType)
{
	VeMoveBy2D* pkAction = VE_NEW VeMoveBy2D;
	pkAction->InitWithDuration(f32Duration, x, y, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMoveBy2D)
{
	Module() [
		Class< VeMoveBy2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeMoveBy2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeMoveBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeMoveBy2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeMoveBy2D::InitWithDuration) [
				Def("Create", (VeMoveBy2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeMoveBy2D::Create),
				Def("Create", (VeMoveBy2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeMoveBy2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeScaleTo2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeScaleTo2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartScale = pkNode->GetScale();
	}
}
//--------------------------------------------------------------------------
void VeScaleTo2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		pkNode->SetScale(VeLerp(g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f), m_kStartScale, m_kDstScale));
	}
}
//--------------------------------------------------------------------------
void VeScaleTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Scale)
{
	InitWithDuration(f32Duration, f32Scale, f32Scale);
}
//--------------------------------------------------------------------------
void VeScaleTo2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Scale, VeTweenEasing::Type eType)
{
	InitWithDuration(f32Duration, f32Scale, f32Scale, eType);
}
//--------------------------------------------------------------------------
void VeScaleTo2D::InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx,
	VeFloat32 sy)
{
	InitWithDuration(f32Duration, sx, sy, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeScaleTo2D::InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx,
	VeFloat32 sy, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kDstScale.x = sx;
	m_kDstScale.y = sy;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeScaleTo2D* VeScaleTo2D::Create(VeFloat32 f32Duration, VeFloat32 f32Scale)
{
	return Create(f32Duration, f32Scale, f32Scale);
}
//--------------------------------------------------------------------------
VeScaleTo2D* VeScaleTo2D::Create(VeFloat32 f32Duration, VeFloat32 f32Scale,
	VeTweenEasing::Type eType)
{
	return Create(f32Duration, f32Scale, f32Scale, eType);
}
//--------------------------------------------------------------------------
VeScaleTo2D* VeScaleTo2D::Create(VeFloat32 f32Duration,
	VeFloat32 sx, VeFloat32 sy)
{
	return Create(f32Duration, sx, sy, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeScaleTo2D* VeScaleTo2D::Create(VeFloat32 f32Duration, VeFloat32 sx,
	VeFloat32 sy, VeTweenEasing::Type eType)
{
	VeScaleTo2D* pkAction = VE_NEW VeScaleTo2D;
	pkAction->InitWithDuration(f32Duration, sx, sy, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeScaleTo2D)
{
	Module() [
		Class< VeScaleTo2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeScaleTo2D::*)(VeFloat32,VeFloat32))&VeScaleTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleTo2D::*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleTo2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeScaleTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleTo2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleTo2D::InitWithDuration) [
				Def("Create", (VeScaleTo2D* (*)(VeFloat32,VeFloat32))&VeScaleTo2D::Create),
				Def("Create", (VeScaleTo2D* (*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleTo2D::Create),
				Def("Create", (VeScaleTo2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeScaleTo2D::Create),
				Def("Create", (VeScaleTo2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleTo2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeScaleBy2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeScaleBy2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartScale = pkNode->GetScale();
		m_kPreScale = m_kStartScale;
	}
}
//--------------------------------------------------------------------------
void VeScaleBy2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartScale += (pkNode->GetScale() - m_kPreScale);
		m_kPreScale = m_kStartScale + m_kAddScale * g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f);
		pkNode->SetPosition(m_kPreScale);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeScaleBy2D::Reverse()
{
	return VeScaleBy2D::Create(m_f32Duration, -m_kAddScale.x, -m_kAddScale.y, m_eType);
}
//--------------------------------------------------------------------------
void VeScaleBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Scale)
{
	InitWithDuration(f32Duration, f32Scale, f32Scale);
}
//--------------------------------------------------------------------------
void VeScaleBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 f32Scale, VeTweenEasing::Type eType)
{
	InitWithDuration(f32Duration, f32Scale, f32Scale, eType);
}
//--------------------------------------------------------------------------
void VeScaleBy2D::InitWithDuration(VeFloat32 f32Duration,
	VeFloat32 sx, VeFloat32 sy)
{
	InitWithDuration(f32Duration, sx, sy, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeScaleBy2D::InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx,
	VeFloat32 sy, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kAddScale.x = sx;
	m_kAddScale.y = sy;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeScaleBy2D* VeScaleBy2D::Create(VeFloat32 f32Duration, VeFloat32 f32Scale)
{
	return Create(f32Duration, f32Scale, f32Scale);
}
//--------------------------------------------------------------------------
VeScaleBy2D* VeScaleBy2D::Create(VeFloat32 f32Duration, VeFloat32 f32Scale,
	VeTweenEasing::Type eType)
{
	return Create(f32Duration, f32Scale, f32Scale, eType);
}
//--------------------------------------------------------------------------
VeScaleBy2D* VeScaleBy2D::Create(VeFloat32 f32Duration,
	VeFloat32 sx, VeFloat32 sy)
{
	return Create(f32Duration, sx, sy, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeScaleBy2D* VeScaleBy2D::Create(VeFloat32 f32Duration, VeFloat32 sx,
	VeFloat32 sy, VeTweenEasing::Type eType)
{
	VeScaleBy2D* pkAction = VE_NEW VeScaleBy2D;
	pkAction->InitWithDuration(f32Duration, sx, sy, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeScaleBy2D)
{
	Module() [
		Class< VeScaleBy2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeScaleBy2D::*)(VeFloat32,VeFloat32))&VeScaleBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleBy2D::*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleBy2D::*)(VeFloat32,VeFloat32,VeFloat32))&VeScaleBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeScaleBy2D::*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleBy2D::InitWithDuration) [
				Def("Create", (VeScaleBy2D* (*)(VeFloat32,VeFloat32))&VeScaleBy2D::Create),
				Def("Create", (VeScaleBy2D* (*)(VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleBy2D::Create),
				Def("Create", (VeScaleBy2D* (*)(VeFloat32,VeFloat32,VeFloat32))&VeScaleBy2D::Create),
				Def("Create", (VeScaleBy2D* (*)(VeFloat32,VeFloat32,VeFloat32,VeTweenEasing::Type))&VeScaleBy2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeMulColorTo2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeMulColorTo2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor = pkNode->GetMulColor();
	}
}
//--------------------------------------------------------------------------
void VeMulColorTo2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		pkNode->SetMulColor(VeLerp(g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f), m_kStartColor, m_kDstColor));
	}
}
//--------------------------------------------------------------------------
void VeMulColorTo2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	InitWithDuration(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeMulColorTo2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kDstColor = kColor;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeMulColorTo2D* VeMulColorTo2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	return Create(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeMulColorTo2D* VeMulColorTo2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeMulColorTo2D* pkAction = VE_NEW VeMulColorTo2D;
	pkAction->InitWithDuration(f32Duration, kColor, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMulColorTo2D)
{
	Module() [
		Class< VeMulColorTo2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeMulColorTo2D::*)(VeFloat32,const VeColor&))&VeMulColorTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeMulColorTo2D::*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeMulColorTo2D::InitWithDuration) [
				Def("Create", (VeMulColorTo2D* (*)(VeFloat32,const VeColor&))&VeMulColorTo2D::Create),
				Def("Create", (VeMulColorTo2D* (*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeMulColorTo2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeMulColorBy2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeMulColorBy2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor = pkNode->GetMulColor();
		m_kPreColor = m_kStartColor;
	}
}
//--------------------------------------------------------------------------
void VeMulColorBy2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor += (pkNode->GetMulColor() - m_kPreColor);
		m_kPreColor = m_kStartColor + m_kAddColor * g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f);
		pkNode->SetMulColor(m_kPreColor);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeMulColorBy2D::Reverse()
{
	return VeMulColorBy2D::Create(m_f32Duration, -m_kAddColor, m_eType);
}
//--------------------------------------------------------------------------
void VeMulColorBy2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	InitWithDuration(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeMulColorBy2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kAddColor = kColor;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeMulColorBy2D* VeMulColorBy2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	return Create(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeMulColorBy2D* VeMulColorBy2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeMulColorBy2D* pkAction = VE_NEW VeMulColorBy2D;
	pkAction->InitWithDuration(f32Duration, kColor, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMulColorBy2D)
{
	Module() [
		Class< VeMulColorBy2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeMulColorBy2D::*)(VeFloat32,const VeColor&))&VeMulColorBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeMulColorBy2D::*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeMulColorBy2D::InitWithDuration) [
				Def("Create", (VeMulColorBy2D* (*)(VeFloat32,const VeColor&))&VeMulColorBy2D::Create),
				Def("Create", (VeMulColorBy2D* (*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeMulColorBy2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeAddColorTo2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeAddColorTo2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor = pkNode->GetAddColor();
	}
}
//--------------------------------------------------------------------------
void VeAddColorTo2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		pkNode->SetAddColor(VeLerp(g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f), m_kStartColor, m_kDstColor));
	}
}
//--------------------------------------------------------------------------
void VeAddColorTo2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	InitWithDuration(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeAddColorTo2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kDstColor = kColor;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeAddColorTo2D* VeAddColorTo2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	return Create(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeAddColorTo2D* VeAddColorTo2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeAddColorTo2D* pkAction = VE_NEW VeAddColorTo2D;
	pkAction->InitWithDuration(f32Duration, kColor, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeAddColorTo2D)
{
	Module() [
		Class< VeAddColorTo2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeAddColorTo2D::*)(VeFloat32,const VeColor&))&VeAddColorTo2D::InitWithDuration).
			Def("InitWithDuration", (void (VeAddColorTo2D::*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeAddColorTo2D::InitWithDuration) [
				Def("Create", (VeAddColorTo2D* (*)(VeFloat32,const VeColor&))&VeAddColorTo2D::Create),
				Def("Create", (VeAddColorTo2D* (*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeAddColorTo2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeAddColorBy2D, VeActionInterval);
//--------------------------------------------------------------------------
void VeAddColorBy2D::Start(VeSceneNode* pkTarget, VeFloat64 f64Time)
{
	VeActionInterval::Start(pkTarget, f64Time);
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor = pkNode->GetAddColor();
		m_kPreColor = m_kStartColor;
	}
}
//--------------------------------------------------------------------------
void VeAddColorBy2D::SetPos(VeFloat32 f32Pos)
{
	VeSceneNode2D* pkNode = VeDynamicCast(VeSceneNode2D, m_pkTarget);
	if(pkNode)
	{
		m_kStartColor += (pkNode->GetAddColor() - m_kPreColor);
		m_kPreColor = m_kStartColor + m_kAddColor * g_pTweenEasing->Ease(m_eType, f32Pos, 1.0f);
		pkNode->SetAddColor(m_kPreColor);
	}
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeAddColorBy2D::Reverse()
{
	return VeAddColorBy2D::Create(m_f32Duration, -m_kAddColor, m_eType);
}
//--------------------------------------------------------------------------
void VeAddColorBy2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	InitWithDuration(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
void VeAddColorBy2D::InitWithDuration(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeActionInterval::InitWithDuration(f32Duration);
	m_kAddColor = kColor;
	m_eType = eType;
}
//--------------------------------------------------------------------------
VeAddColorBy2D* VeAddColorBy2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor)
{
	return Create(f32Duration, kColor, VeTweenEasing::TYPE_LINEAR);
}
//--------------------------------------------------------------------------
VeAddColorBy2D* VeAddColorBy2D::Create(VeFloat32 f32Duration,
	const VeColor& kColor, VeTweenEasing::Type eType)
{
	VeAddColorBy2D* pkAction = VE_NEW VeAddColorBy2D;
	pkAction->InitWithDuration(f32Duration, kColor, eType);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeAddColorBy2D)
{
	Module() [
		Class< VeAddColorBy2D, Base<VeActionInterval> >().
			Def("InitWithDuration", (void (VeAddColorBy2D::*)(VeFloat32,const VeColor&))&VeAddColorBy2D::InitWithDuration).
			Def("InitWithDuration", (void (VeAddColorBy2D::*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeAddColorBy2D::InitWithDuration) [
				Def("Create", (VeAddColorBy2D* (*)(VeFloat32,const VeColor&))&VeAddColorBy2D::Create),
				Def("Create", (VeAddColorBy2D* (*)(VeFloat32,const VeColor&,VeTweenEasing::Type))&VeAddColorBy2D::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeDelayTime, VeActionInterval);
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeDelayTime::Reverse()
{
	return VeDelayTime::Create(m_f32Duration);
}
//--------------------------------------------------------------------------
VeDelayTime* VeDelayTime::Create(VeFloat32 f32Duration)
{
	VeDelayTime* pkAction = VE_NEW VeDelayTime;
	pkAction->InitWithDuration(f32Duration);
	return pkAction;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeDelayTime)
{
	Module() [
		Class< VeDelayTime, Base<VeActionInterval> >() [
				Def("Create", &VeDelayTime::Create)
			]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeActionInstant, VeFiniteTimeAction);
//--------------------------------------------------------------------------
bool VeActionInstant::IsDone()
{
	return true;
}
//--------------------------------------------------------------------------
void VeActionInstant::Update(VeFloat64 f64Time)
{
	SetPos(1.0f);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeActionInstant)
{
	Module() [
		Class< VeActionInstant, Base<VeFiniteTimeAction> >()
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeChangeVisibleMask, VeActionInstant);
//--------------------------------------------------------------------------
VeChangeVisibleMask::VeChangeVisibleMask(VeUInt32 u32Mask)
	: m_u32VisibleMask(u32Mask)
{

}
//--------------------------------------------------------------------------
void VeChangeVisibleMask::SetPos(VeFloat32 f32Pos)
{
	m_pkTarget->SetVisibleMask(m_u32VisibleMask);
}
//--------------------------------------------------------------------------
VeFiniteTimeAction* VeChangeVisibleMask::Reverse()
{
	return VeChangeVisibleMask::Create(~m_u32VisibleMask);
}
//--------------------------------------------------------------------------
VeChangeVisibleMask* VeChangeVisibleMask::Create(VeUInt32 u32Mask)
{
	return VE_NEW VeChangeVisibleMask(u32Mask);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeChangeVisibleMask)
{
	Module() [
		Class< VeChangeVisibleMask, Base<VeActionInstant> >() [
			Def("Create", &VeChangeVisibleMask::Create)
		]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeToggleVisibility, VeActionInstant);
//--------------------------------------------------------------------------
void VeToggleVisibility::SetPos(VeFloat32 f32Pos)
{
	m_pkTarget->SetVisibleMask(~(m_pkTarget->GetVisibleMask()));
}
//--------------------------------------------------------------------------
VeToggleVisibility* VeToggleVisibility::Create()
{
	return VE_NEW VeToggleVisibility;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeToggleVisibility)
{
	Module() [
		Class< VeToggleVisibility, Base<VeActionInstant> >() [
			Def("Create", &VeToggleVisibility::Create)
		]
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeActionCall, VeActionInstant);
//--------------------------------------------------------------------------
VeActionCall::VeActionCall()
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
void VeActionCall::SetPos(VeFloat32 f32Pos)
{
	IncRefCount();
	g_pSceneManager->m_kActionCallList.AttachBack(m_kNode);
}
//--------------------------------------------------------------------------
VeActionCall* VeActionCall::Create(Delegate& kDelegate)
{
	VeActionCall* pkAction = VE_NEW VeActionCall;
	pkAction->m_kEvent.AddDelegate(kDelegate);
	return pkAction;
}
//--------------------------------------------------------------------------
