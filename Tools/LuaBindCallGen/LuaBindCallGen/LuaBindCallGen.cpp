#include <VePowerPCH.h>
#include <time.h>

VeStringA MakeSingleCall(VeUInt32 u32ParamsNum)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<class Ret";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class I";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tRet Call(const VeChar8* pcName";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", I";
		kRes += VeStringA::From(i + 1);
		kRes += " i";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ", lua_State* pkState = g_pLua->GetLua())\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tlua_State* pkThread = MakeFuncThread(pkState, pcName);\r\n";
	kRes += "\t\tif(!pkThread) return Default(ParamType<Ret>());\r\n";
	kRes += "\t\tStackHolder kHoldMain(pkState);\r\n";
	kRes += "\t\tStackHolder kHoldThread(pkThread);\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\tif(RetParam(pkThread, i" + VeStringA::From(i + 1) + ") < 0) return Default(ParamType<Ret>());\r\n";
	}
	kRes += "\t\tif(CallFuncThread(pkState, pkThread, " + VeStringA::From(u32ParamsNum) + ") != 1) return Default(ParamType<Ret>());\r\n";
	kRes += "\t\treturn GetParam(ParamType<Ret>(), pkThread, -1);\r\n";
	kRes += "\t}\r\n";
	return kRes;
}

VeStringA MakeMutipleCall(VeUInt32 u32RetNum, VeUInt32 u32ParamsNum)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<";
	for(VeUInt32 i(0); i < u32RetNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "class O";
		kRes += VeStringA::From(i + 1);
	}
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(u32RetNum || i) kRes += ", ";
		kRes += "class I";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tvoid Call(";
	for(VeUInt32 i(0); i < u32RetNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "O";
		kRes += VeStringA::From(i + 1);
		kRes += "& o";
		kRes += VeStringA::From(i + 1);
	}
	if(u32RetNum) kRes += ", ";
	kRes += "const VeChar8* pcName";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", I";
		kRes += VeStringA::From(i + 1);
		kRes += " i";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ", lua_State* pkState = g_pLua->GetLua())\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tlua_State* pkThread = MakeFuncThread(pkState, pcName);\r\n";
	kRes += "\t\tif(!pkThread) return;\r\n";
	kRes += "\t\tStackHolder kHoldMain(pkState);\r\n";
	kRes += "\t\tStackHolder kHoldThread(pkThread);\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\tif(RetParam(pkThread, i" + VeStringA::From(i + 1) + ") < 0) return;\r\n";
	}
	kRes += "\t\tif(CallFuncThread(pkState, pkThread, " + VeStringA::From(u32ParamsNum) + ") != 1) return;\r\n";
	for(VeUInt32 i(0); i < u32RetNum; ++i)
	{
		kRes += "\t\to" + VeStringA::From(i + 1) + " = GetParam(ParamType<O" + VeStringA::From(i + 1) + ">(), pkThread, -" + VeStringA::From(u32RetNum - i) + ");\r\n";
	}
	kRes += "\t}\r\n";
	return kRes;
}

VeStringA MakeInvoke(VeUInt32 u32ParamsNum)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<class Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, void (*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += "))\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0)";
	if(u32ParamsNum) kRes += ", i32Call(0), i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\tpfuncCall(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class Policies, class Ret";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, VeInt32 i32Bias, Policies kPolicies, Ret (*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += "))\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0), i32Call(0)";
	if(u32ParamsNum) kRes += ", i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\tRet tRet = pfuncCall(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	kRes += "\t\t\ti32Call = Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "::NEXT";
	}
	kRes += "::TYPE::RetCall(pkState, tRet);\r\n";
	kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
	kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class C, class Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += "))\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0)";
	if(u32ParamsNum) kRes += ", i32Call(0), i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\t(((C*)pvSelf)->*pfuncCall)(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class C, class Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, void (C::*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ") const)\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0)";
	if(u32ParamsNum) kRes += ", i32Call(0), i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\t(((C*)pvSelf)->*pfuncCall)(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class C, class Policies, class Ret";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += "))\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0), i32Call(0)";
	if(u32ParamsNum) kRes += ", i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\tRet tRet = (((C*)pvSelf)->*pfuncCall)(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	kRes += "\t\t\ti32Call = Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "::NEXT";
	}
	kRes += "::TYPE::RetCall(pkState, tRet);\r\n";
	kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
	kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class C, class Policies, class Ret";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tVeInt32 Invoke(lua_State* pkState, Policies kPolicies, void* pvSelf, VeInt32 i32Bias, Ret (C::*pfuncCall) (";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ") const)\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tVeInt32 i32ParamNum(0), i32Call(0)";
	if(u32ParamsNum) kRes += ", i32Index(0)";
	kRes += ";\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\ti32Index = i32ParamNum + i32Bias;\r\n";
		kRes += "\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::TestCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tif(i32Call < 0) return i32Call;\r\n";
		kRes += "\t\tP";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
		kRes += " = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::GetCall(ParamType<P" + VeStringA::From(i + 1) + ">(), pkState, i32Index);\r\n";
		kRes += "\t\tPolicies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::FillCall(pkState, i32Index, p" + VeStringA::From(i + 1) + ");\r\n";
		kRes += "\t\ti32ParamNum += i32Call;\r\n";
	}
	kRes += "\t\tif(VeLua::GetTop(pkState) == (i32ParamNum + i32Bias - 1))\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\tRet tRet = (((C*)pvSelf)->*pfuncCall)(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\t\tVeInt32 i32RetNum(0);\r\n";
	kRes += "\t\t\ti32Call = Policies";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "::NEXT";
	}
	kRes += "::TYPE::RetCall(pkState, tRet);\r\n";
	kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
	kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += "\t\t\ti32Call = Policies";
		for(VeUInt32 j(0); j < (u32ParamsNum - i - 1); ++j)
		{
			kRes += "::NEXT";
		}
		kRes += "::TYPE::PostCall(pkState, p";
		kRes += VeStringA::From(i + 1);
		kRes += ");\r\n";
		kRes += "\t\t\tVE_ASSERT(i32Call >= 0);\r\n";
		kRes += "\t\t\ti32RetNum += i32Call;\r\n";
	}
	kRes += "\t\t\treturn i32RetNum;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t\telse\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn -1;\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t}\r\n";
	return kRes;
}

VeStringA MakeCreateObject(VeUInt32 u32ParamsNum)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<class T";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tT* NewObject(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ")\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\treturn VE_NEW T(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t}\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<class T";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", class P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">\r\n";
	kRes += "\tlua_State* ToObject(lua_State* pkState";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ", ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
		kRes += " p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ")\r\n";
	kRes += "\t{\r\n";
	kRes += "\t\tnew (CreateLuaMemObject<T>(pkState)) T(";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "p";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ");\r\n";
	kRes += "\t\treturn pkState;\r\n";
	kRes += "\t}\r\n";
	
	return kRes;
}

VeStringA MakeConstructor(VeUInt32 u32ParamsNum, VeUInt32 u32Max)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "class ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
		if(u32ParamsNum == u32Max)
		{
			kRes += " = void";
		}
	}
	kRes += ">\r\n";
	kRes += "\tclass ConstructorNew";
	if(u32ParamsNum < u32Max)
	{
		kRes += "<";
		for(VeUInt32 i(0); i < u32ParamsNum; ++i)
		{
			if(i) kRes += ", ";
			kRes += "P";
			kRes += VeStringA::From(i + 1);
		}
		for(VeUInt32 i(u32ParamsNum); i < u32Max; ++i)
		{
			kRes += ", void";
		}
		kRes += ">";
	}
	kRes += "\r\n\t{\r\n";
	kRes += "\tpublic:\r\n";
	kRes += "\t\ttemplate<class T, class Policies>\r\n";
	kRes += "\t\tRegistPtr MakeRegist(T* pkType, Policies kPolicies)\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn MakeConstructorRegist(&NewObject<T";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ",P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">, kPolicies);\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t};\r\n";

	kRes += "\r\n";
	kRes += "\ttemplate<";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "class ";
		kRes += "P";
		kRes += VeStringA::From(i + 1);
		if(u32ParamsNum == u32Max)
		{
			kRes += " = void";
		}
	}
	kRes += ">\r\n";
	kRes += "\tclass Constructor";
	if(u32ParamsNum < u32Max)
	{
		kRes += "<";
		for(VeUInt32 i(0); i < u32ParamsNum; ++i)
		{
			if(i) kRes += ", ";
			kRes += "P";
			kRes += VeStringA::From(i + 1);
		}
		for(VeUInt32 i(u32ParamsNum); i < u32Max; ++i)
		{
			kRes += ", void";
		}
		kRes += ">";
	}
	kRes += "\r\n\t{\r\n";
	kRes += "\tpublic:\r\n";
	kRes += "\t\ttemplate<class T, class Policies>\r\n";
	kRes += "\t\tRegistPtr MakeRegist(T* pkType, Policies kPolicies)\r\n";
	kRes += "\t\t{\r\n";
	kRes += "\t\t\treturn MakeConstructorRegist(&ToObject<T";
	for(VeUInt32 i(0); i < u32ParamsNum; ++i)
	{
		kRes += ",P";
		kRes += VeStringA::From(i + 1);
	}
	kRes += ">, kPolicies);\r\n";
	kRes += "\t\t}\r\n";
	kRes += "\t};\r\n";

	return kRes;
}

VeStringA MakeBaseClass(VeUInt32 u32ClassNum, VeUInt32 u32Max)
{
	VeStringA kRes;
	kRes += "\r\n";
	kRes += "\ttemplate<";
	for(VeUInt32 i(0); i < u32ClassNum; ++i)
	{
		if(i) kRes += ", ";
		kRes += "class ";
		kRes += "B";
		kRes += VeStringA::From(i + 1);
		if(u32ClassNum == u32Max)
		{
			kRes += " = void";
		}
	}
	kRes += ">\r\n";
	kRes += "\tclass Base";
	if(u32ClassNum < u32Max)
	{
		kRes += "<";
		for(VeUInt32 i(0); i < u32ClassNum; ++i)
		{
			if(i) kRes += ", ";
			kRes += "B";
			kRes += VeStringA::From(i + 1);
		}
		for(VeUInt32 i(u32ClassNum); i < u32Max; ++i)
		{
			kRes += ", void";
		}
		kRes += ">";
	}
	kRes += "\r\n\t{\r\n";
	kRes += "\tpublic:\r\n";
	kRes += "\t\ttemplate<class C>\r\n";
	kRes += "\t\tstatic void GetClassContentList(C* pkNull, VeVector< VePair<const ClassContentPointer*,VeSizeT> >& kList)\r\n";
	kRes += "\t\t{\r\n";
	for(VeUInt32 i(0); i < u32ClassNum; ++i)
	{
		kRes += "\t\t\tkList.PushBack(VeMakePair(&B";
		kRes += VeStringA::From(i + 1);
		kRes += "::GetLuaBindClass(), BaseClassBias<C,B" + VeStringA::From(i + 1) + ">()));\r\n";
	}
	kRes += "\t\t}\r\n";
	kRes += "\t};\r\n";

	return kRes;
}

void main(VeInt16 i16Argc, VeChar8* apcArgv[])
{
	VeUInt32 u32MaxParam(0);
	VeUInt32 u32MaxRet(0);
	VeUInt32 u32MaxBase(0);
	for(VeInt16 i(1); i < i16Argc; ++i)
	{
		VeChar8* pcParam = apcArgv[i];
		if(*(pcParam++) == '-')
		{
			switch(*(pcParam++))
			{
			case 'o':
				u32MaxRet = VeAtoi(pcParam);
				break;
			case 'i':
				u32MaxParam = VeAtoi(pcParam);
				break;
			case 'b':
				u32MaxBase = VeAtoi(pcParam);
				break;
			}
		}
	}
	time_t kNow;
	tm kTm;
	time(&kNow);
	localtime_s(&kTm, &kNow);
	VeStringA kDate = VeStringA::From(kTm.tm_mday) + "/" + VeStringA::From(kTm.tm_mon + 1) + "/" + VeStringA::From(kTm.tm_year + 1900);
	VeStringA kData;
	kData += "////////////////////////////////////////////////////////////////////////////\r\n";
	kData += "//\r\n";
	kData += "//  Venus Engine Header File.\r\n";
	kData += "//  Copyright (C), Venus Interactive Entertainment.2012\r\n";
	kData += "// -------------------------------------------------------------------------\r\n";
	kData += "//  File name:   VeLuaBindCall.h\r\n";
	kData += "//  Version:     v1.00\r\n";
	kData += "//  Created:     " + kDate + " by Code Generator\r\n";
	kData += "//  Compilers:   Visual Studio.NET\r\n";
	kData += "//  Description: \r\n";
	kData += "// -------------------------------------------------------------------------\r\n";
	kData += "//  History:\r\n";
	kData += "//  http://www.venusie.com\r\n";
	kData += "////////////////////////////////////////////////////////////////////////////\r\n";
	kData += "\r\n";
	kData += "#pragma once\r\n";
	kData += "\r\n";
	kData += "namespace VeLuaBind\r\n";
	kData += "{";
	for(VeUInt32 i(0); i <= u32MaxParam; ++i)
	{
		kData += MakeSingleCall(i);
		for(VeUInt32 j(1); j <= u32MaxRet; ++j)
		{
			kData += MakeMutipleCall(j, i);
		}
	}
	for(VeUInt32 i(0); i <= (u32MaxParam + u32MaxRet - 1); ++i)
	{
		kData += MakeInvoke(i);
	}
	for(VeUInt32 i(0); i <= u32MaxParam; ++i)
	{
		kData += MakeCreateObject(i);
	}
	for(VeUInt32 i(u32MaxParam); i > 0; --i)
	{
		kData += MakeConstructor(i, u32MaxParam);
	}

	for(VeUInt32 i(u32MaxBase); i > 0; --i)
	{
		kData += MakeBaseClass(i, u32MaxBase);
	}
	kData += "};\r\n";

	FILE* pkFile(NULL);
	VE_ASSERT_EQ(fopen_s(&pkFile, "VeLuaBindCall.h", "wb"), VE_S_OK);
	fwrite((const VeChar8*)kData, 1, kData.Length(), pkFile);
	VE_ASSERT_EQ(fclose(pkFile), VE_S_OK);

}
