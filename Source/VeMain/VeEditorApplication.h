////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeEditorApplication.h
//  Version:     v1.00
//  Created:     12/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeEditorLogger : public VeLogger
{
public:
    typedef void (*LogFunc)(const VeChar8*);
    
    VeEditorLogger(LogFunc pfuncLog);
    
    void SetLogFunc(LogFunc pfuncLog);
    
    virtual void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, va_list kArgs);
    
protected:
    LogFunc m_pfuncLog;
    
};

VeSmartPointer(VeEditorLogger);

class VE_MAIN_API VeEditorApplication : public VeApplication
{
public:
    typedef void (*FPSFunc)(const VeChar8*);
    
    VeEditorApplication();
 
    ~VeEditorApplication();
 
    virtual void OnInit();
 
    virtual void OnTerm();
 
    virtual void OnUpdate();
 
    virtual void Update();
 
    virtual void Render();
    
    void SetFPSFunc(FPSFunc pfuncSetFPS);
    
protected:
    FPSFunc m_pfuncSetFPS;
 
};
