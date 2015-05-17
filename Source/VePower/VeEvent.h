////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeEvent.h
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_DEFINE(name) name
#define VE_TEMPLATE template<typename A1 = void, typename A2 = void, typename A3 = void>
#define VE_TEMPLATE_T template<typename T, typename A1 = void, typename A2 = void, typename A3 = void>
#define VE_TEMPLATE_NO_DEFAULT template<typename A1, typename A2, typename A3>
#define VE_TEMPLATE_T_NO_DEFAULT template<typename T, typename A1, typename A2, typename A3>
#define VE_TEMPLATE_PARAM <A1, A2, A3>
#define VE_TEMPLATE_T_PARAM <T, A1, A2, A3>
#define VE_TEMPLATE_SPECIALIZATION
#define VE_TEMPLATE_T_SPECIALIZATION
#define VE_FUNCTION_PARAM A1 a1, A2 a2, A3 a3
#define VE_FUNCTION_PARAM_CUSTOM(type,val) A1 a1, A2 a2, A3 a3, type val
#define VE_FUNCTION_VALUE a1, a2, a3

#include "VeEventSub.h"

#define VE_DEFINE(name) name
#define VE_TEMPLATE template<typename A1, typename A2>
#define VE_TEMPLATE_T template<typename T, typename A1, typename A2>
#define VE_TEMPLATE_NO_DEFAULT VE_TEMPLATE
#define VE_TEMPLATE_T_NO_DEFAULT VE_TEMPLATE_T
#define VE_TEMPLATE_PARAM <A1, A2>
#define VE_TEMPLATE_T_PARAM <T, A1, A2>
#define VE_TEMPLATE_SPECIALIZATION <A1, A2, void>
#define VE_TEMPLATE_T_SPECIALIZATION <T, A1, A2, void>
#define VE_FUNCTION_PARAM A1 a1, A2 a2
#define VE_FUNCTION_PARAM_CUSTOM(type,val) A1 a1, A2 a2, type val
#define VE_FUNCTION_VALUE a1, a2

#include "VeEventSub.h"

#define VE_DEFINE(name) name
#define VE_TEMPLATE template<typename A1>
#define VE_TEMPLATE_T template<typename T, typename A1>
#define VE_TEMPLATE_NO_DEFAULT VE_TEMPLATE
#define VE_TEMPLATE_T_NO_DEFAULT VE_TEMPLATE_T
#define VE_TEMPLATE_PARAM <A1>
#define VE_TEMPLATE_T_PARAM <T, A1>
#define VE_TEMPLATE_SPECIALIZATION <A1, void, void>
#define VE_TEMPLATE_T_SPECIALIZATION <T, A1, void, void>
#define VE_FUNCTION_PARAM A1 a1
#define VE_FUNCTION_PARAM_CUSTOM(type,val) A1 a1, type val
#define VE_FUNCTION_VALUE a1

#include "VeEventSub.h"

#define VE_DEFINE(name) name
#define VE_TEMPLATE template<>
#define VE_TEMPLATE_T template<typename T>
#define VE_TEMPLATE_NO_DEFAULT inline
#define VE_TEMPLATE_T_NO_DEFAULT VE_TEMPLATE_T
#define VE_TEMPLATE_PARAM <>
#define VE_TEMPLATE_T_PARAM <T>
#define VE_TEMPLATE_SPECIALIZATION <void, void, void>
#define VE_TEMPLATE_T_SPECIALIZATION <T, void, void, void>
#define VE_FUNCTION_PARAM
#define VE_FUNCTION_PARAM_CUSTOM(type,val) type val
#define VE_FUNCTION_VALUE

#include "VeEventSub.h"


#define VeInitDelegate(class,name) \
	m_k##name.Set(this,&class::name)

#define VeDelegate(name) (m_k##name)
