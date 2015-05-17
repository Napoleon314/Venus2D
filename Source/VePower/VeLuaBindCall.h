////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLuaBindCall.h
//  Version:     v1.00
//  Created:     28/2/2014 by Code Generator
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace VeLuaBind
{
	template<class Ret>
	Ret Call(const VeChar8* pcName, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(CallFuncThread(pkState, pkThread, 0) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1>
	void Call(O1& o1, const VeChar8* pcName, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(CallFuncThread(pkState, pkThread, 0) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(CallFuncThread(pkState, pkThread, 0) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(CallFuncThread(pkState, pkThread, 0) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(CallFuncThread(pkState, pkThread, 0) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1>
	Ret Call(const VeChar8* pcName, I1 i1, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 1) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(CallFuncThread(pkState, pkThread, 1) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(CallFuncThread(pkState, pkThread, 1) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(CallFuncThread(pkState, pkThread, 1) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(CallFuncThread(pkState, pkThread, 1) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 2) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(CallFuncThread(pkState, pkThread, 2) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(CallFuncThread(pkState, pkThread, 2) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(CallFuncThread(pkState, pkThread, 2) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(CallFuncThread(pkState, pkThread, 2) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 3) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(CallFuncThread(pkState, pkThread, 3) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(CallFuncThread(pkState, pkThread, 3) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(CallFuncThread(pkState, pkThread, 3) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(CallFuncThread(pkState, pkThread, 3) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3, class I4>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i4) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 4) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3, class I4>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(CallFuncThread(pkState, pkThread, 4) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3, class I4>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(CallFuncThread(pkState, pkThread, 4) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3, class I4>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(CallFuncThread(pkState, pkThread, 4) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3, class I4>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(CallFuncThread(pkState, pkThread, 4) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3, class I4, class I5>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i4) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i5) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 5) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3, class I4, class I5>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(CallFuncThread(pkState, pkThread, 5) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3, class I4, class I5>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(CallFuncThread(pkState, pkThread, 5) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3, class I4, class I5>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(CallFuncThread(pkState, pkThread, 5) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3, class I4, class I5>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(CallFuncThread(pkState, pkThread, 5) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3, class I4, class I5, class I6>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i4) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i5) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i6) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 6) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3, class I4, class I5, class I6>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(CallFuncThread(pkState, pkThread, 6) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3, class I4, class I5, class I6>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(CallFuncThread(pkState, pkThread, 6) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3, class I4, class I5, class I6>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(CallFuncThread(pkState, pkThread, 6) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3, class I4, class I5, class I6>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(CallFuncThread(pkState, pkThread, 6) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3, class I4, class I5, class I6, class I7>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i4) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i5) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i6) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i7) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 7) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3, class I4, class I5, class I6, class I7>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(CallFuncThread(pkState, pkThread, 7) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3, class I4, class I5, class I6, class I7>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(CallFuncThread(pkState, pkThread, 7) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3, class I4, class I5, class I6, class I7>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(CallFuncThread(pkState, pkThread, 7) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3, class I4, class I5, class I6, class I7>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(CallFuncThread(pkState, pkThread, 7) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Ret, class I1, class I2, class I3, class I4, class I5, class I6, class I7, class I8>
	Ret Call(const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, I8 i8, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return Default(ParamType<Ret>());
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i2) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i3) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i4) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i5) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i6) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i7) < 0) return Default(ParamType<Ret>());
		if(RetParam(pkThread, i8) < 0) return Default(ParamType<Ret>());
		if(CallFuncThread(pkState, pkThread, 8) != 1) return Default(ParamType<Ret>());
		return GetParam(ParamType<Ret>(), pkThread, -1);
	}

	template<class O1, class I1, class I2, class I3, class I4, class I5, class I6, class I7, class I8>
	void Call(O1& o1, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, I8 i8, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(RetParam(pkThread, i8) < 0) return;
		if(CallFuncThread(pkState, pkThread, 8) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -1);
	}

	template<class O1, class O2, class I1, class I2, class I3, class I4, class I5, class I6, class I7, class I8>
	void Call(O1& o1, O2& o2, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, I8 i8, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(RetParam(pkThread, i8) < 0) return;
		if(CallFuncThread(pkState, pkThread, 8) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -2);
		o2 = GetParam(ParamType<O2>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class I1, class I2, class I3, class I4, class I5, class I6, class I7, class I8>
	void Call(O1& o1, O2& o2, O3& o3, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, I8 i8, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(RetParam(pkThread, i8) < 0) return;
		if(CallFuncThread(pkState, pkThread, 8) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -3);
		o2 = GetParam(ParamType<O2>(), pkThread, -2);
		o3 = GetParam(ParamType<O3>(), pkThread, -1);
	}

	template<class O1, class O2, class O3, class O4, class I1, class I2, class I3, class I4, class I5, class I6, class I7, class I8>
	void Call(O1& o1, O2& o2, O3& o3, O4& o4, const VeChar8* pcName, I1 i1, I2 i2, I3 i3, I4 i4, I5 i5, I6 i6, I7 i7, I8 i8, lua_State* pkState = g_pLua->GetLua())
	{
		lua_State* pkThread = MakeFuncThread(pkState, pcName);
		if(!pkThread) return;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		if(RetParam(pkThread, i1) < 0) return;
		if(RetParam(pkThread, i2) < 0) return;
		if(RetParam(pkThread, i3) < 0) return;
		if(RetParam(pkThread, i4) < 0) return;
		if(RetParam(pkThread, i5) < 0) return;
		if(RetParam(pkThread, i6) < 0) return;
		if(RetParam(pkThread, i7) < 0) return;
		if(RetParam(pkThread, i8) < 0) return;
		if(CallFuncThread(pkState, pkThread, 8) != 1) return;
		o1 = GetParam(ParamType<O1>(), pkThread, -4);
		o2 = GetParam(ParamType<O2>(), pkThread, -3);
		o3 = GetParam(ParamType<O3>(), pkThread, -2);
		o4 = GetParam(ParamType<O4>(), pkThread, -1);
	}

	template<class Policies>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) ())
	{
		VeInt32 i32ParamNum(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall();
			VeInt32 i32RetNum(0);
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) ())
	{
		VeInt32 i32ParamNum(0), i32Call(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall();
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) ())
	{
		VeInt32 i32ParamNum(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)();
			VeInt32 i32RetNum(0);
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) () const)
	{
		VeInt32 i32ParamNum(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)();
			VeInt32 i32RetNum(0);
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) ())
	{
		VeInt32 i32ParamNum(0), i32Call(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)();
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) () const)
	{
		VeInt32 i32ParamNum(0), i32Call(0);
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)();
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = pfuncCall(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			(((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class C, class Policies, class Ret, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>
	VeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) const)
	{
		VeInt32 i32ParamNum(0), i32Call(0), i32Index(0);
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P1>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P1 p1 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P1>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p1);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P2>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P2 p2 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P2>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p2);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P3>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P3 p3 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P3>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p3);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P4>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P4 p4 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P4>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p4);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P5>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P5 p5 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P5>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p5);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P6>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P6 p6 = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P6>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p6);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P7>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P7 p7 = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P7>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p7);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::NEXT::TYPE::TestCall(ParamType<P8>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P8 p8 = Policies::NEXT::NEXT::NEXT::TYPE::GetCall(ParamType<P8>(), pkState, i32Index);
		Policies::NEXT::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p8);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::NEXT::TYPE::TestCall(ParamType<P9>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P9 p9 = Policies::NEXT::NEXT::TYPE::GetCall(ParamType<P9>(), pkState, i32Index);
		Policies::NEXT::NEXT::TYPE::FillCall(pkState, i32Index, p9);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::NEXT::TYPE::TestCall(ParamType<P10>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P10 p10 = Policies::NEXT::TYPE::GetCall(ParamType<P10>(), pkState, i32Index);
		Policies::NEXT::TYPE::FillCall(pkState, i32Index, p10);
		i32ParamNum += i32Call;
		i32Index = i32ParamNum + i32Bias;
		i32Call = Policies::TYPE::TestCall(ParamType<P11>(), pkState, i32Index);
		if(i32Call < 0) return i32Call;
		P11 p11 = Policies::TYPE::GetCall(ParamType<P11>(), pkState, i32Index);
		Policies::TYPE::FillCall(pkState, i32Index, p11);
		i32ParamNum += i32Call;
		if(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))
		{
			Ret tRet = (((C*)pvSelf)->*pfuncCall)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			VeInt32 i32RetNum(0);
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::RetCall(pkState, tRet);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p1);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p2);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p3);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p4);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p5);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p6);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p7);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::NEXT::TYPE::PostCall(pkState, p8);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::NEXT::TYPE::PostCall(pkState, p9);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::NEXT::TYPE::PostCall(pkState, p10);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			i32Call = Policies::TYPE::PostCall(pkState, p11);
			VE_ASSERT(i32Call >= 0);
			i32RetNum += i32Call;
			return i32RetNum;
		}
		else
		{
			return -1;
		}
	}

	template<class T>
	T* NewObject()
	{
		return VE_NEW T();
	}

	template<class T>
	lua_State* ToObject(lua_State* pkState)
	{
		new (CreateLuaMemObject<T>(pkState)) T();
		return pkState;
	}

	template<class T, class P1>
	T* NewObject(P1 p1)
	{
		return VE_NEW T(p1);
	}

	template<class T, class P1>
	lua_State* ToObject(lua_State* pkState, P1 p1)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1);
		return pkState;
	}

	template<class T, class P1, class P2>
	T* NewObject(P1 p1, P2 p2)
	{
		return VE_NEW T(p1, p2);
	}

	template<class T, class P1, class P2>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2);
		return pkState;
	}

	template<class T, class P1, class P2, class P3>
	T* NewObject(P1 p1, P2 p2, P3 p3)
	{
		return VE_NEW T(p1, p2, p3);
	}

	template<class T, class P1, class P2, class P3>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3);
		return pkState;
	}

	template<class T, class P1, class P2, class P3, class P4>
	T* NewObject(P1 p1, P2 p2, P3 p3, P4 p4)
	{
		return VE_NEW T(p1, p2, p3, p4);
	}

	template<class T, class P1, class P2, class P3, class P4>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3, P4 p4)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3, p4);
		return pkState;
	}

	template<class T, class P1, class P2, class P3, class P4, class P5>
	T* NewObject(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		return VE_NEW T(p1, p2, p3, p4, p5);
	}

	template<class T, class P1, class P2, class P3, class P4, class P5>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3, p4, p5);
		return pkState;
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6>
	T* NewObject(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
	{
		return VE_NEW T(p1, p2, p3, p4, p5, p6);
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3, p4, p5, p6);
		return pkState;
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	T* NewObject(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
	{
		return VE_NEW T(p1, p2, p3, p4, p5, p6, p7);
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3, p4, p5, p6, p7);
		return pkState;
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	T* NewObject(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	{
		return VE_NEW T(p1, p2, p3, p4, p5, p6, p7, p8);
	}

	template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	lua_State* ToObject(lua_State* pkState, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	{
		new (CreateLuaMemObject<T>(pkState)) T(p1, p2, p3, p4, p5, p6, p7, p8);
		return pkState;
	}

	template<class P1 = void, class P2 = void, class P3 = void, class P4 = void, class P5 = void, class P6 = void, class P7 = void, class P8 = void>
	class ConstructorNew
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3,P4,P5,P6,P7,P8>, kPolicies);
		}
	};

	template<class P1 = void, class P2 = void, class P3 = void, class P4 = void, class P5 = void, class P6 = void, class P7 = void, class P8 = void>
	class Constructor
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3,P4,P5,P6,P7,P8>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	class ConstructorNew<P1, P2, P3, P4, P5, P6, P7, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3,P4,P5,P6,P7>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	class Constructor<P1, P2, P3, P4, P5, P6, P7, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3,P4,P5,P6,P7>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6>
	class ConstructorNew<P1, P2, P3, P4, P5, P6, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3,P4,P5,P6>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6>
	class Constructor<P1, P2, P3, P4, P5, P6, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3,P4,P5,P6>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5>
	class ConstructorNew<P1, P2, P3, P4, P5, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3,P4,P5>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4, class P5>
	class Constructor<P1, P2, P3, P4, P5, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3,P4,P5>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4>
	class ConstructorNew<P1, P2, P3, P4, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3,P4>, kPolicies);
		}
	};

	template<class P1, class P2, class P3, class P4>
	class Constructor<P1, P2, P3, P4, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3,P4>, kPolicies);
		}
	};

	template<class P1, class P2, class P3>
	class ConstructorNew<P1, P2, P3, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2,P3>, kPolicies);
		}
	};

	template<class P1, class P2, class P3>
	class Constructor<P1, P2, P3, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2,P3>, kPolicies);
		}
	};

	template<class P1, class P2>
	class ConstructorNew<P1, P2, void, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1,P2>, kPolicies);
		}
	};

	template<class P1, class P2>
	class Constructor<P1, P2, void, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1,P2>, kPolicies);
		}
	};

	template<class P1>
	class ConstructorNew<P1, void, void, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&NewObject<T,P1>, kPolicies);
		}
	};

	template<class P1>
	class Constructor<P1, void, void, void, void, void, void, void>
	{
	public:
		template<class T, class Policies>
		RegistPtr MakeRegist(T* pkType, Policies kPolicies)
		{
			return MakeConstructorRegist(&ToObject<T,P1>, kPolicies);
		}
	};

	template<class B1 = void, class B2 = void, class B3 = void, class B4 = void>
	class Base
	{
	public:
		template<class C>
		static void GetClassContentList(C* pkNull, VeVector< VePair<const ClassContentPointer*,VeSizeT> >& kList)
		{
			kList.PushBack(VeMakePair(&B1::GetLuaBindClass(), BaseClassBias<C,B1>()));
			kList.PushBack(VeMakePair(&B2::GetLuaBindClass(), BaseClassBias<C,B2>()));
			kList.PushBack(VeMakePair(&B3::GetLuaBindClass(), BaseClassBias<C,B3>()));
			kList.PushBack(VeMakePair(&B4::GetLuaBindClass(), BaseClassBias<C,B4>()));
		}
	};

	template<class B1, class B2, class B3>
	class Base<B1, B2, B3, void>
	{
	public:
		template<class C>
		static void GetClassContentList(C* pkNull, VeVector< VePair<const ClassContentPointer*,VeSizeT> >& kList)
		{
			kList.PushBack(VeMakePair(&B1::GetLuaBindClass(), BaseClassBias<C,B1>()));
			kList.PushBack(VeMakePair(&B2::GetLuaBindClass(), BaseClassBias<C,B2>()));
			kList.PushBack(VeMakePair(&B3::GetLuaBindClass(), BaseClassBias<C,B3>()));
		}
	};

	template<class B1, class B2>
	class Base<B1, B2, void, void>
	{
	public:
		template<class C>
		static void GetClassContentList(C* pkNull, VeVector< VePair<const ClassContentPointer*,VeSizeT> >& kList)
		{
			kList.PushBack(VeMakePair(&B1::GetLuaBindClass(), BaseClassBias<C,B1>()));
			kList.PushBack(VeMakePair(&B2::GetLuaBindClass(), BaseClassBias<C,B2>()));
		}
	};

	template<class B1>
	class Base<B1, void, void, void>
	{
	public:
		template<class C>
		static void GetClassContentList(C* pkNull, VeVector< VePair<const ClassContentPointer*,VeSizeT> >& kList)
		{
			kList.PushBack(VeMakePair(&B1::GetLuaBindClass(), BaseClassBias<C,B1>()));
		}
	};
};
