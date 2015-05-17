////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSingleton.h
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class T>
class VeSingleton : public VeMemObject
{
public:
	VeSingleton()
	{
		VE_ASSERT(!ms_pSingleton);
		ms_pSingleton = static_cast<T*>(this);
	}

	virtual ~VeSingleton()
	{
		VE_ASSERT(ms_pSingleton);
		ms_pSingleton = NULL;
	}

	static void Destory()
	{
		VE_SAFE_DELETE(ms_pSingleton);
	}

	static T& GetSingleton()
	{
		VE_ASSERT(ms_pSingleton);
		return (*ms_pSingleton);
	}

	static T* GetSingletonPtr()
	{
		return ms_pSingleton;
	}

protected:
	static T* ms_pSingleton;

};

template<class T> T* VeSingleton<T>::ms_pSingleton = NULL;
