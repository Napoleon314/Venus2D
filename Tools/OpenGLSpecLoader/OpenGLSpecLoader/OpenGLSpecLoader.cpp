////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Tools Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   OpenGLSpecLoader.cpp
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <direct.h>
#include <assert.h>
#include <hash_map>
#include <hash_set>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>
#include "Stringmap.h"

using namespace std;

char* OpenFile(const char* pcName, size_t& stLen)
{
	assert(_access(pcName, 4) == 0);
	FILE* pkFile(NULL);
	fopen_s(&pkFile, pcName, "r");
	assert(pkFile);
	fseek(pkFile, 0, SEEK_END);
	size_t len = ftell(pkFile);
	char* pcBuffer = (char*)malloc(len + 1);
	fseek(pkFile, 0, SEEK_SET);
	fread(pcBuffer, 1, len, pkFile);
	pcBuffer[len] = 0;
	stLen = len;
	fclose(pkFile);
	return pcBuffer;
}

void CloseFile(char* pcBuffer)
{
	free(pcBuffer);
}

hash_set<char> tm_sep;

hash_set<char> normal_sep;

enum SpecType
{
	SPEC_DEFINE,
	SPEC_ENUM,
	SPEC_PASSTHRU,
	SPEC_FUNC,
	SPEC_TYPE_MAX
};

enum FuncType
{
	FUNC_RETURN,
	FUNC_PARAM
};

StringHashMap<SpecType> spec_Type;

StringHashMap<FuncType> func_Type;

StringHashMap<string> trans;

StringHashMap<int> funcName;

bool GetLine(const char** pcBuffer, char* pcLine)
{
	int i(0);
	while((**pcBuffer) != '\n' && (**pcBuffer) != '\0')
	{
		*pcLine = **pcBuffer;
		++pcLine;
		++(*pcBuffer);
		++i;
		assert(i < 2000);
	}
	*pcLine = '\0';
	if((**pcBuffer) == '\n')
	{
		++(*pcBuffer);
		return true;
	}
	else
	{
		return false;
	}
}

void GetTmWorld(const char* pcBuffer, char* pcLeft, char* pcRight)
{
	while(*pcBuffer != '\0')
	{
		if(tm_sep.find(*pcBuffer) == tm_sep.end() || ((*pcBuffer) == ' '))
		{
			*pcLeft = *pcBuffer;
			++pcLeft;
			++pcBuffer;
		}
		else
		{
			break;
		}
	}
	*pcLeft = '\0';

	while(tm_sep.find(*pcBuffer) != tm_sep.end())
	{
		++pcBuffer;
	}

	while(*pcBuffer != '\0')
	{
		if(tm_sep.find(*pcBuffer) == tm_sep.end() || ((*pcBuffer) == ' ') || ((*pcBuffer) == '*'))
		{
			*pcRight = *pcBuffer;
			++pcRight;
			++pcBuffer;
		}
		else
		{
			break;
		}
	}
	*pcRight = '\0';
}

void Load_tm(const char* pcBuffer, size_t stLen, StringHashMap<string>& kTypeMap)
{
	const char* pcStart = pcBuffer;
	char acLineBuffer[2048];
	while(GetLine(&pcStart, acLineBuffer))
	{
		if(acLineBuffer[0] < 0x30 || acLineBuffer[0] > 0x7A)
		{
			continue;
		}
		char acLeft[1024], acRight[1024];
		GetTmWorld(acLineBuffer, acLeft, acRight);
		kTypeMap[acLeft] = acRight;
	}
}

const char* GetSpecType(const char* pcLine, char* pcTemp)
{
	char* pcTempPointer = pcTemp;
	while(*pcLine)
	{
		*pcTempPointer = *pcLine;
		if((*pcTempPointer) == ':')
		{
			++pcLine;
			++pcTempPointer;
			break;
		}
		else if((*pcTempPointer) == ' ' || (*pcTempPointer) == '\t')
		{
			++pcLine;
			pcTempPointer = pcTemp;
			continue;
		}
		++pcLine;
		++pcTempPointer;		
	}
	*pcTempPointer = 0;
	return pcLine;
}

void GetDefine(const char* pcLine, char* pcMacro, char* pcValue)
{
	while(*pcLine)
	{
		if(*pcLine == ' ' || *pcLine == '\t')
		{
			++pcLine;
			continue;
		}
		else
		{
			break;
		}
	}

	while(*pcLine)
	{
		if(*pcLine == ' ' || *pcLine == '\t')
		{
			break;
		}
		else
		{
			*pcMacro = *pcLine;
			++pcMacro;
			++pcLine;
		}
	}
	*pcMacro = 0;

	while(*pcLine)
	{
		if(*pcLine == '=')
		{
			++pcLine;
			break;
		}
		++pcLine;
	}

	while(*pcLine)
	{
		if(*pcLine == ' ' || *pcLine == '\t')
		{
			++pcLine;
			continue;
		}
		else
		{
			break;
		}
	}

	while(*pcLine)
	{
		if(*pcLine == ' ' || *pcLine == '\t')
		{
			break;
		}
		else
		{
			*pcValue = *pcLine;
			++pcValue;
			++pcLine;
		}
	}
	*pcValue = 0;
}

string smallPre;
string bigPre;
string LoadContext;
string UnloadContext;
string macro;

void Load_spec(const char* pcBuffer, size_t stLen, StringHashMap<string>& kTypeMap, string& outHeader, string& outSource)
{
	const char* pcStart = pcBuffer;
	char acLineBuffer[2048];

	SpecType eState = SPEC_TYPE_MAX;
	SpecType eLastState = SPEC_TYPE_MAX;

	string func_name;
	string return_name;
	vector<string> params;
	StringHashMap<pair<string,bool>> paramsType;

	int i(0);

	while(GetLine(&pcStart, acLineBuffer))
	{
		++i;
		switch(eState)
		{
		case SPEC_ENUM:
			if(eState == SPEC_ENUM)
			{
				if(acLineBuffer[0] == '\t')
				{
					char acMacro[1024], acValue[1024];
					GetDefine(acLineBuffer, acMacro, acValue);
					if(strcmp(acMacro, "use") != 0)
					{
						outHeader += "#ifndef ";
						outHeader += bigPre;
						outHeader += acMacro;
						outHeader += "\n#define ";
						outHeader += bigPre;
						outHeader += acMacro;
						outHeader += " ";
						outHeader += acValue;
						outHeader += "\n#endif\n\n";
					}
					break;
				}
				else
				{
					eState = SPEC_TYPE_MAX;
					eLastState = SPEC_ENUM;
				}
			}
		case SPEC_DEFINE:
			if(eState == SPEC_DEFINE)
			{
				if(acLineBuffer[0] == '\t')
				{
					char acMacro[1024], acValue[1024];
					GetDefine(acLineBuffer, acMacro, acValue);
					if(strcmp(acMacro, "use") != 0)
					{
						outHeader += "#ifndef ";
						outHeader += bigPre;
						outHeader += acMacro;
						outHeader += "\n#define ";
						outHeader += bigPre;
						outHeader += acMacro;
						outHeader += " ";
						outHeader += acValue;
						outHeader += "\n#endif\n\n";
					}
					break;
				}
				else
				{
					eState = SPEC_TYPE_MAX;
					eLastState = SPEC_DEFINE;
				}
			}
		case SPEC_FUNC:
			if(eState == SPEC_FUNC)
			{
				if(acLineBuffer[0] == '\t')
				{
					char acWord0[128], acWord1[128], acWord2[128];
					char* pcSrc;
					char* pcDst;
					{
						pcSrc = acLineBuffer;
						pcDst = acWord0;
						while(*pcSrc == ' ' || *pcSrc == '\t')
						{
							++pcSrc;
						}
						while(*pcSrc != ' ' && *pcSrc != '\t' && *pcSrc != '\0')
						{
							*pcDst = *pcSrc;
							++pcDst;
							++pcSrc;
						}
						*pcDst = 0;
					}
					StringHashMap<FuncType>::iterator it = func_Type.find(acWord0);
					if(it != func_Type.end())
					{
						switch(it->second)
						{
						case FUNC_RETURN:
							{
								pcDst = acWord1;
								while(*pcSrc == ' ' || *pcSrc == '\t')
								{
									++pcSrc;
								}
								while(*pcSrc != ' ' && *pcSrc != '\t' && *pcSrc != '\0')
								{
									*pcDst = *pcSrc;
									++pcDst;
									++pcSrc;
								}
								*pcDst = 0;
								return_name = acWord1;
							}
							break;
						case FUNC_PARAM:
							{
								pcDst = acWord1;
								while(*pcSrc == ' ' || *pcSrc == '\t')
								{
									++pcSrc;
								}
								while(*pcSrc != ' ' && *pcSrc != '\t' && *pcSrc != '\0')
								{
									*pcDst = *pcSrc;
									++pcDst;
									++pcSrc;
								}
								*pcDst = 0;
								
								pcDst = acWord2;
								while(*pcSrc == ' ' || *pcSrc == '\t')
								{
									++pcSrc;
								}
								while(*pcSrc != ' ' && *pcSrc != '\t' && *pcSrc != '\0')
								{
									*pcDst = *pcSrc;
									++pcDst;
									++pcSrc;
								}
								*pcDst = 0;
								if(strstr(pcSrc, "value"))
								{
									paramsType[acWord1] = make_pair(string(acWord2), false);
								}
								else
								{
									paramsType[acWord1] = make_pair(string(acWord2), true);
								}
							}
							break;
						}
					}

					break;
				}
				else
				{
					if(funcName.find(func_name.c_str()) == funcName.end())
					{
						string strTemp;

						outHeader += "typedef ";
						strTemp = kTypeMap[return_name];
						if(strTemp == "") strTemp = "void";
						outHeader += strTemp;
						outHeader += " (APIENTRY *";
						outHeader += func_name;
						outHeader += "Func)(";
						for(size_t i(0); i < params.size(); ++i)
						{
							strTemp = paramsType[params[i]].first;
							strTemp = kTypeMap[strTemp];
							if(strTemp == "")
							{
								strTemp = "void";
							}
							if(paramsType[params[i]].second)
							{
								strTemp += "*";
							}
							outHeader += strTemp;
							outHeader += " ";

							StringHashMap<string>::iterator it = trans.find(params[i]);
							if(it != trans.end())
							{
								outHeader += it->second;
							}
							else
							{
								outHeader += params[i];
							}
							if(i < (params.size() - 1))
							{
								outHeader += ", ";
							}
						}
						outHeader += ");\n";
						outHeader += "extern ";
						outHeader += func_name;
						outHeader += "Func _";
						outHeader += func_name;
						outHeader += ";\n";

						outHeader += "#define ";
						outHeader += func_name;
						if(return_name == "void")
						{
							outHeader += " VE_ASSERT(_";
							outHeader += func_name;
							outHeader += ");_";
						}
						else
						{
							outHeader += " _";
						}
						outHeader += func_name;
						outHeader += "\n";

						outSource += "#ifdef ";
						outSource += func_name;
						outSource += "\n";
						outSource += func_name;
						outSource += "Func _";
						outSource += func_name;
						outSource += " = NULL;\n";
						outSource += "#endif\n";

						LoadContext += "#\tifdef ";
						LoadContext += func_name;
						LoadContext += "\n";
						LoadContext += "\t_";
						LoadContext += func_name;
						LoadContext += " = (";
						LoadContext += func_name;
						LoadContext += "Func)";
						LoadContext += smallPre;
						LoadContext += "GetFunction(\"";
						LoadContext += func_name;
						LoadContext += "\");\n";
						LoadContext += "#\tendif\n";

						UnloadContext += "#\tifdef ";
						UnloadContext += func_name;
						UnloadContext += "\n";
						UnloadContext += "\t_";
						UnloadContext += func_name;
						UnloadContext += " = NULL;\n";
						UnloadContext += "#\tendif\n";

						funcName[func_name] = 1;
					}

					eState = SPEC_TYPE_MAX;
					eLastState = SPEC_TYPE_MAX;
				}
				
			}
		case SPEC_TYPE_MAX:
			if(eState == SPEC_TYPE_MAX)
			{
				if(acLineBuffer[0] < 0x30 || acLineBuffer[0] > 0x7A)
				{
					continue;
				}
				char acTemp[1024];
				const char* pcNext = GetSpecType(acLineBuffer, acTemp);
				{
					bool bFunc = false;
					{
						const char* pcTempPointer = acTemp;
						while(*pcTempPointer)
						{
							if(*pcTempPointer == ')')
							{
								bFunc = true;
							}
							++pcTempPointer;
						}
					}
					if(bFunc)
					{
						char acTempBuffer[128];
						char* pcDst = acTempBuffer;
						char* pcSrc = acLineBuffer;
						while(*pcSrc)
						{
							*pcDst = *pcSrc;
							if(*pcDst == '(')
							{
								++pcSrc;
								break;
							}
							++pcDst;
							++pcSrc;
						}
						*pcDst = 0;
						func_name = smallPre + acTempBuffer;
						return_name = "";
						params.clear();
						paramsType.clear();
						while(*pcSrc)
						{
							pcDst = acTempBuffer;
							while(*pcSrc)
							{
								*pcDst = *pcSrc;
								if(*pcSrc == ')')
								{
									break;
								}
								else if(*pcSrc == ' ' || *pcSrc == '\t' || *pcSrc == ',')
								{
									++pcSrc;
									break;
								}
								++pcSrc;
								++pcDst;
							}
							*pcDst = 0;

							if(strlen(acTempBuffer))
							{
								params.push_back(acTempBuffer);
							}

							while(*pcSrc == ' ' || *pcSrc == '\t' || *pcSrc == ',')
							{
								++pcSrc;
							}

							if(*pcSrc == ')')
							{
								break;
							}
						}

						eState = SPEC_FUNC;
					}
					else
					{
						StringHashMap<SpecType>::iterator it = spec_Type.find(acTemp);
						if(it != spec_Type.end())
						{
							if(it->second == SPEC_PASSTHRU)
							{
								while(*pcNext == ' ' || *pcNext == '\t')
								{
									++pcNext;
								}
								outHeader += pcNext;
								outHeader += "\n";
								eState = eLastState;
							}
							else
							{
								eState = it->second;
							}
						}
						else
						{
							eState = SPEC_ENUM;
						}
					}
				}
			}
			break;
		}
		

	}
}

char g_acBuffer[2048], g_acLoad[2048], g_acSave[2048];

StringHashMap<string> g_kTypeMap;

void Generate(const char* pcName, const vector<const char*>& kNameList)
{
	funcName.clear();
	funcName["glXCreateContext"] = 1;
	funcName["glXMakeCurrent"] = 1;
	funcName["glXSwapBuffers"] = 1;
	funcName["glXGetProcAddressARB"] = 1;
	funcName["wglGetProcAddress"] = 1;
	funcName["wglCreateContext"] = 1;
	funcName["wglMakeCurrent"] = 1;
	funcName["wglDeleteContext"] = 1;
	LoadContext = "";
	UnloadContext = "";
	smallPre = pcName;
	bigPre = pcName;
	int i(0);
	while(pcName[i])
	{
		if(pcName[i] >= 'a' && pcName[i] <= 'z')
			bigPre[i] = pcName[i] - 0x20;
		else
			bigPre[i] = pcName[i];
		++i;
	}

	macro = "VE_";
	macro += bigPre;

	bigPre += "_";
	if(bigPre == "WGL_") bigPre = "";

	size_t stLen;

	char acBuffer[1024];
	sprintf_s(acBuffer, "%s.tm", pcName);

	char* pcFile = OpenFile(acBuffer, stLen);
	
	Load_tm(pcFile, stLen, g_kTypeMap);
	CloseFile(pcFile);

	string kGlHeader;
	string kGlSource;

	kGlHeader +=
		"////////////////////////////////////////////////////////////////////////////\n" \
		"//\n" \
		"//  Venus Engine Header File.\n" \
		"//  Copyright (C), Venus Interactive Entertainment.2012\n" \
		"// -------------------------------------------------------------------------\n" \
		"//  File name:   ";
	kGlHeader += pcName;
	kGlHeader += ".h\n";
	kGlHeader +=
		"//  Version:     v1.00\n" \
		"//  Created:     by GlSpecLoader\n" \
		"//  Compilers:   Visual Studio.NET\n" \
		"//  Description: \n" \
		"// -------------------------------------------------------------------------\n" \
		"//  History:\n" \
		"//  http://www.venusie.com\n" \
		"////////////////////////////////////////////////////////////////////////////\n\n";
	kGlHeader += "#pragma once\n\n" \
		"#ifdef ";
	kGlHeader += macro;
	kGlHeader += "\n\n" \
		"extern \"C\"\n" \
		"{\n\n";

	kGlSource +=
		"////////////////////////////////////////////////////////////////////////////\n" \
		"//\n" \
		"//  Venus Engine Source File.\n" \
		"//  Copyright (C), Venus Interactive Entertainment.2012\n" \
		"// -------------------------------------------------------------------------\n" \
		"//  File name:   ";
	kGlSource += pcName;
	kGlSource += ".cpp\n";
	kGlSource +=
		"//  Version:     v1.00\n" \
		"//  Created:     by GlSpecLoader\n" \
		"//  Compilers:   Visual Studio.NET\n" \
		"//  Description: \n" \
		"// -------------------------------------------------------------------------\n" \
		"//  History:\n" \
		"//  http://www.venusie.com\n" \
		"////////////////////////////////////////////////////////////////////////////\n\n";
	kGlSource +=
		"#include \"VeMainPCH.h\"\n" \
		"#include \"_VeGlLoader.h\"\n\n";

	kGlSource += "#ifdef ";
	kGlSource += macro;
	kGlSource += "\n\n";

	for(size_t i(0); i < kNameList.size(); ++i)
	{
		pcFile = OpenFile(kNameList[i], stLen);

		Load_spec(pcFile, stLen, g_kTypeMap, kGlHeader, kGlSource);

		CloseFile(pcFile);
	}

	kGlHeader += "\nvoid ";
	kGlHeader += smallPre;
	kGlHeader += "Funcload();\n";

	kGlHeader += "\nvoid ";
	kGlHeader += smallPre;
	kGlHeader += "FuncUnload();\n\n";

	kGlHeader += "}\n\n";
	kGlHeader += "#endif\n";

	kGlSource += "\nvoid ";
	kGlSource += smallPre;
	kGlSource += "Funcload()\n{\n";
	kGlSource += LoadContext;
	kGlSource += "}\n";

	kGlSource += "\nvoid ";
	kGlSource += smallPre;
	kGlSource += "FuncUnload()\n{\n";
	kGlSource += UnloadContext;
	kGlSource += "}\n\n";
	kGlSource += "#endif\n";

	_chdir(g_acSave);
	FILE* pfHeaderFile;
	sprintf_s(acBuffer, "%s.h", pcName);
	fopen_s(&pfHeaderFile, acBuffer, "w");
	fwrite(kGlHeader.c_str(), 1, kGlHeader.length(), pfHeaderFile);
	fclose(pfHeaderFile);
	FILE* pfSourceFile;
	sprintf_s(acBuffer, "%s.cpp", pcName);
	fopen_s(&pfSourceFile, acBuffer, "w");
	fwrite(kGlSource.c_str(), 1, kGlSource.length(), pfSourceFile);
	fclose(pfSourceFile);
	_chdir(g_acLoad);
}

int main(int iArgc, char* apcArgv[])
{
	assert(iArgc >= 3);

	{
		_getcwd(g_acBuffer, 2048);
		_chdir(apcArgv[2]);
		_getcwd(g_acSave, 2048);
		_chdir(g_acBuffer);
		_chdir(apcArgv[1]);
		_getcwd(g_acLoad, 2048);

		char acBuffer[2048];
		_getcwd(acBuffer, 2048);
		printf_s("Working directory is: %s\n", acBuffer);
	}

	tm_sep.insert('*');
	tm_sep.insert(',');
	tm_sep.insert(' ');
	tm_sep.insert('\t');

	func_Type["return"] = FUNC_RETURN;
	func_Type["param"] = FUNC_PARAM;

	spec_Type["define:"] = SPEC_DEFINE;
	spec_Type["enum:"] = SPEC_ENUM;
	spec_Type["passthru:"] = SPEC_PASSTHRU;
	spec_Type["passend:"] = SPEC_PASSTHRU;

	trans["class"] = "class1";

	g_kTypeMap["LPCSTR"] = "LPCSTR";

	vector<const char*> kNameList;

	kNameList.clear();
	kNameList.push_back("enum.spec");
	kNameList.push_back("enumext.spec");
	kNameList.push_back("gl.spec");
	Generate("gl", kNameList);
	kNameList.clear();
	kNameList.push_back("glxenum.spec");
	kNameList.push_back("glxenumext.spec");
	kNameList.push_back("glxext.spec");
	kNameList.push_back("glx.spec");
	Generate("glX", kNameList);
	kNameList.clear();
	kNameList.push_back("wglenum.spec");
	kNameList.push_back("wglenumext.spec");
	kNameList.push_back("wgl.spec");
	kNameList.push_back("wglext.spec");
	Generate("wgl", kNameList);
	
	return 0;
}
