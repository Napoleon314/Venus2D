////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Tools Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   HLSLCompiler.cpp
//  Version:     v1.00
//  Created:     4/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <VeMainPCH.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>

void Init()
{
	VE_NEW VeGlobalStringTable();
	VE_NEW VeAllocatorManager();
	//VE_NEW VeStringParser();
	VeLogger::SetLog(VeLogger::OUTPUT_DEBUGOUTPUT);
	VE_NEW VeResourceManager();
}

void Term()
{
	VeResourceManager::Destory();
	VeLogger::SetLog(VeLogger::OUTPUT_MAX);
	//VeStringParser::Destory();
	VeAllocatorManager::Destory();
	VeGlobalStringTable::Destory();
#ifdef VE_MEM_DEBUG
	_VeMemoryExit();
#endif
}

VeDirectory::WriteFuncDelegate g_kWriteDelegate(NULL);

void Compile(VeChar8* pcFileName, VeChar8* pcDstDir)
{
	VeChar8* pcFile = VeStrrchr(pcFileName, '/');
	VeSizeT stNum = pcFile - pcFileName;
	VeChar8 acBuffer[2048];
	VeMemcpy(acBuffer, pcFileName, stNum);
	acBuffer[stNum] = 0;
	++pcFile;
	VeFileDir kFile(acBuffer);
	VeChar8* pcContent;
	VeChar8* pcTemp = VeStrtok(pcDstDir, "/", &pcContent);
	VE_ASSERT(pcTemp && *pcTemp);
	VeFileDir kDstFile(pcTemp);
	pcTemp = VeStrtok(NULL, "/", &pcContent);
	while(pcTemp && *pcTemp)
	{
		kDstFile.Change(pcTemp);
		pcTemp = VeStrtok(NULL, "/", &pcContent);
	}
	

	VeBinaryIStreamPtr spStream = kFile.OpenSync(pcFile);
	VE_ASSERT(spStream);
	VeXMLDocument kDoc;
	(*spStream) >> kDoc;
	VE_ASSERT(!kDoc.Error());
	VeXMLElement* pkRoot = kDoc.RootElement();
	VeXMLElement* pkGroup = pkRoot->FirstChildElement("Group");
	while(pkGroup)
	{
		VeXMLElement* pkShader = pkGroup->FirstChildElement();
		while(pkShader)
		{
			const VeChar8* pcName = pkShader->Value();
			const VeChar8* pcSrc = pkShader->GetAttribute("src");
			const VeChar8* pcEntry = pkShader->GetAttribute("entry");
			VeString kFile(acBuffer);
			kFile += '/';
			kFile += pcSrc;
			VeVector<const VeChar8*> kProfileList;
			VeXMLElement* pkProfile = pkShader->FirstChildElement("Profile");
			while(pkProfile)
			{
				const VeChar8* pcProfile = pkProfile->GetAttribute("value");
				kProfileList.PushBack(pcProfile);
				pkProfile = pkProfile->NextSiblingElement("Profile");
			}
			VeVector<D3D_SHADER_MACRO> kMacroList;
			VeXMLElement* pkMacro = pkShader->FirstChildElement("Macro");
			while(pkMacro)
			{
				D3D_SHADER_MACRO kMac;
				kMac.Name = pkMacro->GetAttribute("name");
				kMac.Definition = pkMacro->GetAttribute("define");
				kMacroList.PushBack(kMac);
				pkMacro = pkMacro->NextSiblingElement("Macro");
			}
			D3D_SHADER_MACRO kLast = {NULL, NULL};
			kMacroList.PushBack(kLast);
			for(VeVector<const VeChar8*>::iterator it = kProfileList.Begin(); it != kProfileList.End(); ++it)
			{
				HRESULT hRes = S_OK;
				ID3DBlob* pkOut;
				ID3DBlob* pkErrorBlob;
				hRes = D3DX11CompileFromFile(kFile, kMacroList.Begin(), NULL, pcEntry, *it, 
					D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3 | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR,
					0, NULL, &pkOut, &pkErrorBlob, NULL);
				if(VE_FAILED(hRes))
				{
					if(pkErrorBlob)
					{
						VE_LOG_E("HLSLComplier", (VeChar8*)pkErrorBlob->GetBufferPointer());
					}
				}
				else
				{
					VeString kOutputName(pcName);
					kOutputName += '.';
					kOutputName += *it;
					VeMemoryOStreamPtr spOutputStream = VE_NEW VeMemoryOStream();
					spOutputStream->AddBlob(pkOut->GetBufferPointer(), pkOut->GetBufferSize());
					kDstFile.WriteAsync(kOutputName, spOutputStream, g_kWriteDelegate);
				}
				VE_SAFE_RELEASE(pkOut);
				VE_SAFE_RELEASE(pkErrorBlob);
			}
			pkShader = pkShader->NextSiblingElement();
		}
		pkGroup = pkGroup->NextSiblingElement("Group");
	}
}

VeInt32 main(VeInt32 i32Argc, VeChar8* apcArgv[])
{
	VE_ASSERT(i32Argc > 1);
	Init();
	{
		VeChar8* pcPointer = apcArgv[1];
		while(*pcPointer)
		{
			if(*pcPointer == '\\')
			{
				*pcPointer = '/';
			}
			++pcPointer;
		}
	}
	if(i32Argc == 2)
	{
		Compile(apcArgv[1], ".");
	}
	else
	{
		VeChar8* pcPointer = apcArgv[2];
		while(*pcPointer)
		{
			if(*pcPointer == '\\')
			{
				*pcPointer = '/';
			}
			++pcPointer;
		}
		Compile(apcArgv[1], apcArgv[2]);
	}
	
	
	Term();
	printf_s("Succeed\n");
	return 0;
}
