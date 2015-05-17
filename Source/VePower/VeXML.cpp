////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeXML.cpp
//  Version:     v1.00
//  Created:     19/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeXMLCursor::VeXMLCursor()
{
	Clear();
}
//--------------------------------------------------------------------------
void VeXMLCursor::Clear()
{
	m_i32Row = m_i32Col = -1;
}
//--------------------------------------------------------------------------
VeImplementRootRTTI(VeXMLBase);
//--------------------------------------------------------------------------
const unsigned char VE_XML_UTF_LEAD_0 = 0xefU;
const unsigned char VE_XML_UTF_LEAD_1 = 0xbbU;
const unsigned char VE_XML_UTF_LEAD_2 = 0xbfU;
//--------------------------------------------------------------------------
const VeByte VeXMLBase::ms_utf8ByteTable[256] = 
{
	//	0	1	2	3	4	5	6	7	8	9	a	b	c	d	e	f
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x00
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x10
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x20
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x30
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x40
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x50
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x60
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x70	End of ASCII range
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x80 0x80 to 0xc1 invalid
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0x90 
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xa0 
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	// 0xb0 
	1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xc0 0xc2 to 0xdf 2 byte
	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	// 0xd0
	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	// 0xe0 0xe0 to 0xef 3 byte
	4,	4,	4,	4,	4,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1	// 0xf0 0xf0 to 0xf4 4 byte, 0xf5 and higher invalid
};
//--------------------------------------------------------------------------
VeXMLBase::Entity VeXMLBase::ms_akEntity[VeXMLBase::NUM_ENTITY] =
{
	{ "&amp;",  5, '&' },
	{ "&lt;",   4, '<' },
	{ "&gt;",   4, '>' },
	{ "&quot;", 6, '\"' },
	{ "&apos;", 6, '\'' }
};
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::ms_pcErrorString[VeXMLBase::VE_XML_ERROR_STRING_COUNT] =
{
	"No error",
	"Error",
	"Failed to open file",
	"Error parsing Element.",
	"Failed to read Element name",
	"Error reading Element value.",
	"Error reading Attributes.",
	"Error: empty tag.",
	"Error reading end tag.",
	"Error parsing Unknown.",
	"Error parsing Comment.",
	"Error parsing Declaration.",
	"Error document empty.",
	"Error null (0) or unexpected EOF found in input stream.",
	"Error parsing CData.",
	"Error when VeXMLDocument added to document, because VeXMLDocument can only be at the root.",
};
//--------------------------------------------------------------------------
class VeXMLParsingData
{
	friend class VeXMLDocument;
public:
	void Stamp(const VeChar8* pcNow, VeXMLEncoding eEncoding)
	{
		VE_ASSERT( pcNow );
		if ( m_i32Tabsize < 1 )
		{
			return;
		}

		VeInt32 row = m_kCursor.m_i32Row;
		VeInt32 col = m_kCursor.m_i32Col;
		const VeChar8* pcContent = m_pcStamp;
		VE_ASSERT( pcContent );

		while ( pcContent < pcNow )
		{
			const VeUInt8* pU = (const VeUInt8*)pcContent;

			switch (*pU) {
			case 0:
				return;
			case '\r':
				++row;
				col = 0;				
				++pcContent;
				if (*pcContent == '\n') {
					++pcContent;
				}
				break;
			case '\n':
				++row;
				col = 0;
				++pcContent;
				if (*pcContent == '\r') {
					++pcContent;
				}
				break;
			case '\t':
				++pcContent;
				col = (col / m_i32Tabsize + 1) * m_i32Tabsize;
				break;
			case VE_XML_UTF_LEAD_0:
				if ( eEncoding == VE_XML_ENCODING_UTF8 )
				{
					if ( *(pcContent+1) && *(pcContent+2) )
					{
						if ( *(pU+1)==VE_XML_UTF_LEAD_1 && *(pU+2)==VE_XML_UTF_LEAD_2 )
							pcContent += 3;	
						else if ( *(pU+1)==0xbfU && *(pU+2)==0xbeU )
							pcContent += 3;	
						else if ( *(pU+1)==0xbfU && *(pU+2)==0xbfU )
							pcContent += 3;	
						else
						{ pcContent +=3; ++col; }
					}
				}
				else
				{
					++pcContent;
					++col;
				}
				break;
			default:
				if ( eEncoding == VE_XML_ENCODING_UTF8 )
				{
					VeInt32 step = VeXMLBase::ms_utf8ByteTable[*((const VeUInt8*)pcContent)];
					if ( step == 0 )
						step = 1;
					pcContent += step;
					++col;
				}
				else
				{
					++pcContent;
					++col;
				}
				break;
			}
		}
		m_kCursor.m_i32Row = row;
		m_kCursor.m_i32Col = col;
		VE_ASSERT( m_kCursor.m_i32Row >= -1 );
		VE_ASSERT( m_kCursor.m_i32Col >= -1 );
		m_pcStamp = pcContent;
		VE_ASSERT( m_pcStamp );
	}

	const VeXMLCursor& Cursor() const
	{
		return m_kCursor;
	}

private:
	VeXMLParsingData(const VeChar8* pcStart, VeInt32 i32Tabsize, VeInt32 i32Row, VeInt32 i32Col)
	{
		VE_ASSERT(pcStart);
		m_pcStamp = pcStart;
		m_i32Tabsize = i32Tabsize;
		m_kCursor.m_i32Row = i32Row;
		m_kCursor.m_i32Col = i32Col;
	}

	VeXMLCursor m_kCursor;
	const VeChar8* m_pcStamp;
	VeInt32 m_i32Tabsize;
};
//--------------------------------------------------------------------------
VeXMLBase::VeXMLBase()
{

}
//--------------------------------------------------------------------------
VeXMLBase::VeXMLBase(const VeXMLBase&)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
void VeXMLBase::operator = (const VeXMLBase&)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
VeXMLBase::~VeXMLBase()
{

}
//--------------------------------------------------------------------------
VeInt32 VeXMLBase::Row() const
{
	return m_kLocation.m_i32Row + 1;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLBase::Column() const
{
	return m_kLocation.m_i32Col + 1;
}
//--------------------------------------------------------------------------
void VeXMLBase::EncodeString(const VeString& kStr, VeString& kOut)
{
	VeInt32 i(0);
	while(i < (VeInt32)kStr.Length())
	{
		VeUInt8 c = (VeUInt8)kStr.GetAt(i);

		if (c == '&' && i < ((VeInt32)kStr.Length() - 2)
			 && kStr.GetAt(i+1) == '#'
			 && kStr.GetAt(i+2) == 'x' )
		{
			while(i < ((VeInt32)kStr.Length() - 1))
			{
				kOut += kStr.GetAt(i);
				++i;
				if (kStr.GetAt(i) == ';')
					break;
			}
		}
		else if (c == '&')
		{
			kOut += ms_akEntity[0].m_pcStr;
			++i;
		}
		else if ( c == '<' )
		{
			kOut += ms_akEntity[1].m_pcStr;
			++i;
		}
		else if ( c == '>' )
		{
			kOut += ms_akEntity[2].m_pcStr;
			++i;
		}
		else if ( c == '\"' )
		{
			kOut += ms_akEntity[3].m_pcStr;
			++i;
		}
		else if ( c == '\'' )
		{
			kOut += ms_akEntity[4].m_pcStr;
			++i;
		}
		else if(c < 32)
		{
			VeChar8 acBuf[32];
			VeSprintf(acBuf, "&#x%02X;", (unsigned)(c & 0xff));
			kOut += acBuf;
			++i;
		}
		else
		{
			kOut += (VeChar8)c;
			++i;
		}
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::SkipWhiteSpace(const VeChar8* pcStr, VeXMLEncoding eEncoding)
{
	if(!pcStr || !*pcStr)
	{
		return 0;
	}
	if(eEncoding == VE_XML_ENCODING_UTF8)
	{
		while (*pcStr)
		{
			const VeUInt8* pu8Str = (const VeUInt8*)pcStr;

			if (*(pu8Str+0) == VE_XML_UTF_LEAD_0
				&& *(pu8Str+1) == VE_XML_UTF_LEAD_1 
				&& *(pu8Str+2) == VE_XML_UTF_LEAD_2)
			{
				pcStr += 3;
				continue;
			}
			else if(*(pu8Str+0) == VE_XML_UTF_LEAD_0
				&& *(pu8Str+1) == 0xbfU
				&& *(pu8Str+2) == 0xbeU)
			{
				pcStr += 3;
				continue;
			}
			else if(*(pu8Str+0) == VE_XML_UTF_LEAD_0
				&& *(pu8Str+1) == 0xbfU
				&& *(pu8Str+2) == 0xbfU )
			{
				pcStr += 3;
				continue;
			}
			if(IsWhiteSpace(*pcStr))
				++pcStr;
			else
				break;
		}
	}
	else
	{
		while(*pcStr && IsWhiteSpace(*pcStr))
			++pcStr;
	}

	return pcStr;
}
//--------------------------------------------------------------------------
bool VeXMLBase::IsWhiteSpace(VeChar8 c)
{
	return (VeIsSpace((VeUInt8)c) || c == '\n' || c == '\r'); 
}
//--------------------------------------------------------------------------
bool VeXMLBase::IsWhiteSpace( VeInt32 c )
{
	if(c < 256)
		return IsWhiteSpace((VeChar8)c);
	return false;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::ReadName(const VeChar8* pcStr, VeString& kName, VeXMLEncoding eEncoding)
{
	kName = "";
	VE_ASSERT(pcStr);

	if (pcStr && *pcStr && (IsAlpha((VeUInt8)*pcStr, eEncoding) || *pcStr == '_' ))
	{
		const VeChar8* pcStart = pcStr;
		while(pcStr && *pcStr && (IsAlphaNum((VeUInt8)*pcStr, eEncoding) 
			|| *pcStr == '_' || *pcStr == '-'
			|| *pcStr == '.' || *pcStr == ':'))
		{
			++pcStr;
		}
		if(pcStr - pcStart > 0)
		{
			kName = VeString(pcStart, VeUInt32(pcStr - pcStart));
		}
		return pcStr;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLBase::IsAlpha(VeUInt8 u8AnyByte, VeXMLEncoding eEncoding)
{
	if (u8AnyByte < 127)
		return VeIsAlpha(u8AnyByte);
	else
		return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLBase::IsAlphaNum(VeUInt8 u8AnyByte, VeXMLEncoding eEncoding)
{
	if(u8AnyByte < 127)
		return VeIsAlnum(u8AnyByte);
	else
		return 1;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::ReadText(const VeChar8* pcStr, VeString& kText, bool bIgnoreWhiteSpace, const VeChar8* pcEndTag, bool bIgnoreCase, VeXMLEncoding eEncoding)
{
	kText = "";
	if(!bIgnoreWhiteSpace)
	{
		while(pcStr && *pcStr && !StringEqual(pcStr, pcEndTag, bIgnoreCase, eEncoding))
		{
			VeInt32 len;
			VeChar8 cArr[4] = { 0, 0, 0, 0 };
			pcStr = GetChar(pcStr, cArr, &len, eEncoding);
			kText += VeString(cArr, len);
		}
	}
	else
	{
		bool whitespace = false;
		pcStr = SkipWhiteSpace(pcStr, eEncoding);
		while(pcStr && *pcStr && !StringEqual(pcStr, pcEndTag, bIgnoreCase, eEncoding))
		{
			if (*pcStr == '\r' || *pcStr == '\n')
			{
				whitespace = true;
				++pcStr;
			}
			else if(IsWhiteSpace(*pcStr))
			{
				whitespace = true;
				++pcStr;
			}
			else
			{
				if(whitespace)
				{
					kText += ' ';
					whitespace = false;
				}
				VeInt32 len;
				VeChar8 cArr[4] = { 0, 0, 0, 0 };
				pcStr = GetChar(pcStr, cArr, &len, eEncoding);
				if(len == 1)
					kText += cArr[0];
				else
					kText += VeString(cArr, len);
			}
		}
	}
	if(pcStr && *pcStr)
		pcStr += VeStrlen(pcEndTag);
	return (pcStr && *pcStr) ? pcStr : 0;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::GetEntity(const VeChar8* pcStr, VeChar8* pcValue, VeInt32* pi32Length, VeXMLEncoding eEncoding)
{
	VeString ent;
	VeInt32 i;
	*pi32Length = 0;

	if ( *(pcStr+1) && *(pcStr+1) == '#' && *(pcStr+2) )
	{
		VeUInt32 ucs = 0;
		ptrdiff_t delta = 0;
		unsigned mult = 1;

		if ( *(pcStr+2) == 'x' )
		{
			if ( !*(pcStr+3) ) return 0;

			const char* q = pcStr+3;
			q = VeStrchr( q, ';' );

			if ( !q || !*q ) return 0;

			delta = q-pcStr;
			--q;

			while ( *q != 'x' )
			{
				if ( *q >= '0' && *q <= '9' )
					ucs += mult * (*q - '0');
				else if ( *q >= 'a' && *q <= 'f' )
					ucs += mult * (*q - 'a' + 10);
				else if ( *q >= 'A' && *q <= 'F' )
					ucs += mult * (*q - 'A' + 10 );
				else 
					return 0;
				mult *= 16;
				--q;
			}
		}
		else
		{
			if ( !*(pcStr+2) ) return 0;

			const char* q = pcStr+2;
			q = VeStrchr( q, ';' );

			if ( !q || !*q ) return 0;

			delta = q-pcStr;
			--q;

			while ( *q != '#' )
			{
				if ( *q >= '0' && *q <= '9' )
					ucs += mult * (*q - '0');
				else 
					return 0;
				mult *= 10;
				--q;
			}
		}
		if ( eEncoding == VE_XML_ENCODING_UTF8 )
		{
			ConvertUTF32ToUTF8(ucs, pcValue, pi32Length);
		}
		else
		{
			*pcValue = (char)ucs;
			*pi32Length = 1;
		}
		return pcStr + delta + 1;
	}

	for( i=0; i<NUM_ENTITY; ++i )
	{
		if (VeStrncmp(ms_akEntity[i].m_pcStr, pcStr, ms_akEntity[i].m_u32Length ) == 0 )
		{
			VE_ASSERT( VeStrlen( ms_akEntity[i].m_pcStr ) == ms_akEntity[i].m_u32Length );
			*pcValue = ms_akEntity[i].m_cChar;
			*pi32Length = 1;
			return ( pcStr + ms_akEntity[i].m_u32Length );
		}
	}

	*pcValue = *pcStr;
	return pcStr+1;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLBase::GetChar(const VeChar8* pcStr, VeChar8* pcValue, VeInt32* pi32Length, VeXMLEncoding eEncoding)
{
	VE_ASSERT(pcStr);
	if ( eEncoding == VE_XML_ENCODING_UTF8 )
	{
		*pi32Length = ms_utf8ByteTable[ *((const VeUInt8*)pcStr) ];
		VE_ASSERT( *pi32Length >= 0 && *pi32Length < 5 );
	}
	else
	{
		*pi32Length = 1;
	}

	if ( *pi32Length == 1 )
	{
		if ( *pcStr == '&' )
			return GetEntity( pcStr, pcValue, pi32Length, eEncoding );
		*pcValue = *pcStr;
		return pcStr+1;
	}
	else if ( *pi32Length )
	{
		for( int i=0; pcStr[i] && i<*pi32Length; ++i ) {
			pcValue[i] = pcStr[i];
		}
		return pcStr + (*pi32Length);
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
bool VeXMLBase::StringEqual(const VeChar8* pcStr, const VeChar8* pcEndTag, bool bIgnoreCase, VeXMLEncoding eEncoding)
{
	VE_ASSERT(pcStr);
	VE_ASSERT(pcEndTag);
	if (!pcStr || !*pcStr)
	{
		return false;
	}

	const VeChar8* q = pcStr;

	if(bIgnoreCase)
	{
		while(*q && *pcEndTag && ToLower(*q, eEncoding) == ToLower(*pcEndTag, eEncoding))
		{
			++q;
			++pcEndTag;
		}

		if(*pcEndTag == 0)
			return true;
	}
	else
	{
		while(*q && *pcEndTag && *q == *pcEndTag)
		{
			++q;
			++pcEndTag;
		}

		if(*pcEndTag == 0)
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLBase::ToLower(VeInt32 v, VeXMLEncoding eEncoding)
{
	if(eEncoding == VE_XML_ENCODING_UTF8)
	{
		if (v < 128) return VeToLower(v);
		return v;
	}
	else
	{
		return VeToLower(v);
	}
}
//--------------------------------------------------------------------------
void VeXMLBase::ConvertUTF32ToUTF8(VeUInt32 u32Input, VeChar8* pcOutput, VeInt32* pi32Length)
{
	const unsigned long BYTE_MASK = 0xBF;
	const unsigned long BYTE_MARK = 0x80;
	const unsigned long FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

	if (u32Input < 0x80) 
		*pi32Length = 1;
	else if ( u32Input < 0x800 )
		*pi32Length = 2;
	else if ( u32Input < 0x10000 )
		*pi32Length = 3;
	else if ( u32Input < 0x200000 )
		*pi32Length = 4;
	else
	{ *pi32Length = 0; return; }

	pcOutput += *pi32Length;

	switch (*pi32Length) 
	{
	case 4:
		--pcOutput; 
		*pcOutput = (char)((u32Input | BYTE_MARK) & BYTE_MASK); 
		u32Input >>= 6;
	case 3:
		--pcOutput; 
		*pcOutput = (char)((u32Input | BYTE_MARK) & BYTE_MASK); 
		u32Input >>= 6;
	case 2:
		--pcOutput; 
		*pcOutput = (char)((u32Input | BYTE_MARK) & BYTE_MASK); 
		u32Input >>= 6;
	case 1:
		--pcOutput; 
		*pcOutput = (char)(u32Input | FIRST_BYTE_MARK[*pi32Length]);
	default:
		break;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLNode, VeXMLBase);
//--------------------------------------------------------------------------
VeXMLNode::VeXMLNode(NodeType eType)
	: m_eType(eType), m_pkParent(NULL)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeXMLNode::VeXMLNode(const VeXMLNode&)
	: m_eType(VE_XML_TYPECOUNT), m_pkParent(NULL)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
void VeXMLNode::operator = (const VeXMLNode&)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
VeXMLNode::~VeXMLNode()
{
	Clear();
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLNode::Value() const
{
	return m_kValue;
}
//--------------------------------------------------------------------------
const VeString& VeXMLNode::ValueToStr() const
{
	return m_kValue;
}
//--------------------------------------------------------------------------
void VeXMLNode::SetValue(const VeChar8* pcValue)
{
	m_kValue = pcValue;
}
//--------------------------------------------------------------------------
void VeXMLNode::Clear()
{
	m_kChildren.BeginIterator();
	while(!m_kChildren.IsEnd())
	{
		VeXMLNode* pkNode = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Next();
		VE_ASSERT(pkNode);
		VE_DELETE(pkNode);
	}
	VE_ASSERT(m_kChildren.Empty());
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::Parent()
{
	return m_pkParent;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::Parent() const
{
	return m_pkParent;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::FirstChild()
{
	return m_kChildren.Size() ? m_kChildren.GetHeadNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::FirstChild() const
{
	return m_kChildren.Size() ? m_kChildren.GetHeadNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::FirstChild(const VeChar8* pcValue)
{
	VeRefList<VeXMLNode*>::iterator iter = m_kChildren.GetHeadNode();
	while(!VeRefList<VeXMLNode*>::IsEnd(iter))
	{
		VeXMLNode* pkNode = iter->m_tContent;
		iter = VeRefList<VeXMLNode*>::Next(iter);		
		VE_ASSERT(pkNode);
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::FirstChild(const VeChar8* pcValue) const
{
	VeRefList<VeXMLNode*>::iterator iter = m_kChildren.GetHeadNode();
	while(!VeRefList<VeXMLNode*>::IsEnd(iter))
	{
		VeXMLNode* pkNode = iter->m_tContent;
		VeRefList<VeXMLNode*>::Next(iter);		
		VE_ASSERT(pkNode);
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::LastChild()
{
	return m_kChildren.Size() ? m_kChildren.GetLastNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::LastChild() const
{
	return m_kChildren.Size() ? m_kChildren.GetLastNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::LastChild(const VeChar8* pcValue)
{
	VeRefList<VeXMLNode*>::iterator iter = m_kChildren.GetLastNode();
	while(!VeRefList<VeXMLNode*>::IsEnd(iter))
	{
		VeXMLNode* pkNode = iter->m_tContent;
		VeRefList<VeXMLNode*>::Pre(iter);		
		VE_ASSERT(pkNode);
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::LastChild(const VeChar8* pcValue) const
{
	VeRefList<VeXMLNode*>::iterator iter = m_kChildren.GetLastNode();
	while(!VeRefList<VeXMLNode*>::IsEnd(iter))
	{
		VeXMLNode* pkNode = iter->m_tContent;
		VeRefList<VeXMLNode*>::Pre(iter);		
		VE_ASSERT(pkNode);
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::IterateChildren(VeXMLNode* pkPrevious)
{
	if(!pkPrevious)
	{
		return FirstChild();
	}
	else
	{
		VE_ASSERT(pkPrevious->m_pkParent == this);
		return pkPrevious->NextSibling();
	}
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::IterateChildren(const VeXMLNode* pkPrevious) const
{
	if(!pkPrevious)
	{
		return FirstChild();
	}
	else
	{
		VE_ASSERT(pkPrevious->m_pkParent == this);
		return pkPrevious->NextSibling();
	}
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::IterateChildren(const VeChar8* pcValue, VeXMLNode* pkPrevious)
{
	if (!pkPrevious)
	{
		return FirstChild(pcValue);
	}
	else
	{
		VE_ASSERT(pkPrevious->m_pkParent == this);
		return pkPrevious->NextSibling(pcValue);
	}
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::IterateChildren(const VeChar8* pcValue, const VeXMLNode* pkPrevious) const
{
	if (!pkPrevious)
	{
		return FirstChild(pcValue);
	}
	else
	{
		VE_ASSERT(pkPrevious->m_pkParent == this);
		return pkPrevious->NextSibling(pcValue);
	}
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::PreviousSibling()
{
	return m_kNode.Pre() ? m_kNode.Pre()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::PreviousSibling() const
{
	return m_kNode.Pre() ? m_kNode.Pre()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::PreviousSibling(const VeChar8* pcValue)
{
	VeXMLNode* pkNode = this;
	while((pkNode = pkNode->PreviousSibling()))
	{
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::PreviousSibling(const VeChar8* pcValue) const
{
	const VeXMLNode* pkNode = this;
	while((pkNode = pkNode->PreviousSibling()))
	{
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::NextSibling()
{
	return m_kNode.Next() ? m_kNode.Next()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::NextSibling() const
{
	return m_kNode.Next() ? m_kNode.Next()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::NextSibling(const VeChar8* pcValue)
{
	VeXMLNode* pkNode = this;
	while((pkNode = pkNode->NextSibling()))
	{
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeXMLNode* VeXMLNode::NextSibling(const VeChar8* pcValue) const
{
	const VeXMLNode* pkNode = this;
	while((pkNode = pkNode->NextSibling()))
	{
		if(VeStrcmp(pkNode->Value(), pcValue) == 0)
			return pkNode;
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::InsertEndChild(const VeXMLNode& kAddThis)
{
	if (kAddThis.Type() == VeXMLNode::VE_XML_DOCUMENT)
	{
		if(GetDocument()) 
			GetDocument()->SetError(VE_XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}
	VeXMLNode* pkNode = kAddThis.Clone();
	if(!pkNode)
		return NULL;

	return LinkEndChild(pkNode);
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::LinkEndChild(VeXMLNode* pkAddThis)
{
	VE_ASSERT(pkAddThis->m_pkParent == NULL || pkAddThis->m_pkParent == this);
	VE_ASSERT(pkAddThis->GetDocument() == 0 || pkAddThis->GetDocument() == this->GetDocument());
	if(pkAddThis->Type() == VeXMLNode::VE_XML_DOCUMENT)
	{
		VE_DELETE(pkAddThis);
		if(GetDocument()) 
			GetDocument()->SetError(VE_XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}
	pkAddThis->m_pkParent = this;
	m_kChildren.AttachBack(pkAddThis->m_kNode);
	return pkAddThis;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::InsertBeforeChild(VeXMLNode* pkBeforeThis, const VeXMLNode& kAddThis)
{
	if (!pkBeforeThis || pkBeforeThis->m_pkParent != this)
	{
		return 0;
	}
	if(kAddThis.Type() == VeXMLNode::VE_XML_DOCUMENT)
	{
		if(GetDocument()) 
			GetDocument()->SetError(VE_XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}
	VeXMLNode* pkNode = kAddThis.Clone();
	if ( !pkNode )
		return 0;
	pkNode->m_pkParent = this;
	pkBeforeThis->m_kNode.InsertBefore(pkNode->m_kNode);
	return pkNode;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::InsertAfterChild(VeXMLNode* pkAfterThis, const VeXMLNode& kAddThis)
{
	if ( !pkAfterThis || pkAfterThis->m_pkParent != this )
	{
		return 0;
	}
	if ( kAddThis.Type() == VeXMLNode::VE_XML_DOCUMENT )
	{
		if(GetDocument()) 
			GetDocument()->SetError(VE_XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}
	VeXMLNode* pkNode = kAddThis.Clone();
	if(!pkNode) return NULL;
	pkNode->m_pkParent = this;
	pkAfterThis->m_kNode.InsertAfter(pkNode->m_kNode);
	return pkNode;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::ReplaceChild(VeXMLNode* pkReplaceThis, const VeXMLNode& kWithThis)
{
	if ( !pkReplaceThis )
		return 0;

	if ( pkReplaceThis->m_pkParent != this )
		return 0;

	if (kWithThis.ToDocument())
	{
		VeXMLDocument* pkDocument = GetDocument();
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_DOCUMENT_TOP_ONLY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return 0;
	}
	VeXMLNode* pkNode = kWithThis.Clone();
	if ( !pkNode )
		return 0;
	pkReplaceThis->m_kNode.InsertAfter(pkNode->m_kNode);
	VE_DELETE(pkReplaceThis);
	pkNode->m_pkParent = this;
	return pkNode;
}
//--------------------------------------------------------------------------
bool VeXMLNode::RemoveChild(VeXMLNode* pkRemoveThis)
{
	if ( !pkRemoveThis ) {
		return false;
	}

	if ( pkRemoveThis->m_pkParent != this )
	{	
		VE_ASSERT( 0 );
		return false;
	}

	VE_DELETE(pkRemoveThis);
	return true;
}
//--------------------------------------------------------------------------
VeXMLNode::NodeType VeXMLNode::Type() const
{
	return m_eType;
}
//--------------------------------------------------------------------------
bool VeXMLNode::NoChildren() const
{
	return m_kChildren.Empty();
}
//--------------------------------------------------------------------------
VeXMLDocument* VeXMLNode::GetDocument()
{
	for(VeXMLNode* pkNode = this; pkNode; pkNode = pkNode->m_pkParent)
	{
		if(pkNode->ToDocument())
			return pkNode->ToDocument();
	}
	return 0;
}
//--------------------------------------------------------------------------
const VeXMLDocument* VeXMLNode::GetDocument() const
{
	for(const VeXMLNode* pkNode = this; pkNode; pkNode = pkNode->m_pkParent)
	{
		if(pkNode->ToDocument())
			return pkNode->ToDocument();
	}
	return 0;
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLNode::FirstChildElement()
{
	VeXMLNode* pkNode;
	for(pkNode = FirstChild(); pkNode; pkNode = pkNode->NextSibling())
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return 0;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLNode::FirstChildElement() const
{
	const VeXMLNode* pkNode;
	for(pkNode = FirstChild(); pkNode; pkNode = pkNode->NextSibling())
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return 0;
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLNode::FirstChildElement(const VeChar8* pcValue)
{
	VeXMLNode* pkNode;
	for(pkNode = FirstChild(pcValue); pkNode; pkNode = pkNode->NextSibling(pcValue))
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return 0;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLNode::FirstChildElement(const VeChar8* pcValue) const
{
	const VeXMLNode* pkNode;
	for(pkNode = FirstChild(pcValue); pkNode; pkNode = pkNode->NextSibling(pcValue))
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return 0;
}
//--------------------------------------------------------------------------
void VeXMLNode::CopyTo(VeXMLNode* pkTarget) const
{
	pkTarget->SetValue(m_kValue); 
	pkTarget->m_kLocation = m_kLocation;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLNode::Identify(const VeChar8* pcStart, VeXMLEncoding eEncoding)
{
	VeXMLNode* pkReturnNode = 0;

	pcStart = SkipWhiteSpace(pcStart, eEncoding);
	if(!pcStart || !*pcStart || *pcStart != '<')
	{
		return 0;
	}

	pcStart = SkipWhiteSpace(pcStart, eEncoding);

	if(!pcStart || !*pcStart)
	{
		return 0;
	}

	const VeChar8* pcXmlHeader = { "<?xml" };
	const VeChar8* pcCommentHeader = { "<!--" };
	const VeChar8* pcDTDHeader = { "<!" };
	const VeChar8* pcCDataHeader = { "<![CDATA[" };

	if(StringEqual(pcStart, pcXmlHeader, true, eEncoding))
	{
		pkReturnNode = VE_NEW VeXMLDeclaration();
	}
	else if(StringEqual(pcStart, pcCommentHeader, false, eEncoding))
	{
		pkReturnNode = VE_NEW VeXMLComment();
	}
	else if(StringEqual(pcStart, pcCDataHeader, false, eEncoding))
	{
		VeXMLText* pkText = VE_NEW VeXMLText("");
		pkText->SetCData(true);
		pkReturnNode = pkText;
	}
	else if(StringEqual(pcStart, pcDTDHeader, false, eEncoding))
	{
		pkReturnNode = VE_NEW VeXMLUnknown();
	}
	else if(IsAlpha(*(pcStart+1), eEncoding) || *(pcStart+1) == '_')
	{
		pkReturnNode = VE_NEW VeXMLElement("");
	}
	else
	{
		pkReturnNode = VE_NEW VeXMLUnknown();
	}

	if(pkReturnNode)
	{
		pkReturnNode->m_pkParent = this;
	}
	return pkReturnNode;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLNode::NextSiblingElement() const
{
	for(const VeXMLNode* pkNode = NextSibling(); pkNode; pkNode = pkNode->NextSibling())
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLNode::NextSiblingElement()
{
	for(VeXMLNode* pkNode = NextSibling(); pkNode; pkNode = pkNode->NextSibling())
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLNode::NextSiblingElement(const VeChar8* pcValue) const
{
	for(const VeXMLNode* pkNode = NextSibling(pcValue); pkNode; pkNode = pkNode->NextSibling(pcValue))
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLNode::NextSiblingElement(const VeChar8* pcValue)
{
	for(VeXMLNode* pkNode = NextSibling(pcValue); pkNode; pkNode = pkNode->NextSibling(pcValue))
	{
		if(pkNode->ToElement())
			return pkNode->ToElement();
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLComment, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLComment::VeXMLComment() : VeXMLNode(VeXMLNode::VE_XML_COMMENT)
{

}
//--------------------------------------------------------------------------
VeXMLComment::VeXMLComment(const VeChar8* pcValue) : VeXMLNode(VeXMLNode::VE_XML_COMMENT)
{
	SetValue(pcValue);
}
//--------------------------------------------------------------------------
VeXMLComment::VeXMLComment(const VeXMLComment& kCopy) : VeXMLNode(VeXMLNode::VE_XML_COMMENT)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLComment& VeXMLComment::operator = (const VeXMLComment& kBase)
{
	Clear();
	kBase.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLComment::~VeXMLComment()
{

}
//--------------------------------------------------------------------------
void VeXMLComment::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	for(VeInt32 i(0); i < i32Depth; ++i)
	{
		kOutput += "\t";
	}
	kOutput += "<!--";
	kOutput += m_kValue;
	kOutput += "-->";
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLComment::Clone() const
{
	VeXMLComment* pkClone = VE_NEW VeXMLComment();
	if(!pkClone)
		return 0;
	CopyTo(pkClone);
	return pkClone;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLComment::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	VeXMLDocument* pkDocument = GetDocument();
	m_kValue = "";

	pcContent = SkipWhiteSpace(pcContent, eEncoding);

	if(pkData)
	{
		pkData->Stamp(pcContent, eEncoding);
		m_kLocation = pkData->Cursor();
	}
	const VeChar8* startTag = "<!--";
	const VeChar8* endTag   = "-->";

	if (!StringEqual(pcContent, startTag, false, eEncoding))
	{
		if (pkDocument)
			pkDocument->SetError(VE_XML_ERROR_PARSING_COMMENT, pcContent, pkData, eEncoding);
		return 0;
	}
	pcContent += VeStrlen(startTag);

    m_kValue = "";
	
	while(pcContent && *pcContent && !StringEqual( pcContent, endTag, false, eEncoding))
	{
		m_kValue += *pcContent;
		++pcContent;
	}
	if(pcContent && *pcContent) 
		pcContent += VeStrlen(endTag);

	return pcContent;
}
//--------------------------------------------------------------------------
VeXMLComment* VeXMLComment::ToComment()
{
	return this;
}
//--------------------------------------------------------------------------
const VeXMLComment* VeXMLComment::ToComment() const
{
	return this;
}
//--------------------------------------------------------------------------
void VeXMLComment::CopyTo(VeXMLComment* pkTarget) const
{
	VeXMLNode::CopyTo(pkTarget);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLUnknown, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLUnknown::VeXMLUnknown() : VeXMLNode(VeXMLNode::VE_XML_UNKNOWN)
{

}
//--------------------------------------------------------------------------
VeXMLUnknown::VeXMLUnknown(const VeXMLUnknown& kCopy) : VeXMLNode(VeXMLNode::VE_XML_UNKNOWN)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLUnknown::~VeXMLUnknown()
{

}
//--------------------------------------------------------------------------
VeXMLUnknown& VeXMLUnknown::operator = (const VeXMLUnknown& kCopy)
{
	kCopy.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLUnknown::Clone() const
{
	VeXMLUnknown* pkClone = VE_NEW VeXMLUnknown();

	if ( !pkClone )
		return 0;

	CopyTo( pkClone );
	return pkClone;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLUnknown::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	VeXMLDocument* pkDocument = GetDocument();
	pcContent = SkipWhiteSpace( pcContent, eEncoding );

	if ( pkData )
	{
		pkData->Stamp( pcContent, eEncoding );
		m_kLocation = pkData->Cursor();
	}
	if ( !pcContent || !*pcContent || *pcContent != '<' )
	{
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_PARSING_UNKNOWN, pcContent, pkData, eEncoding);
		return 0;
	}
	++pcContent;
	m_kValue = "";

	while ( pcContent && *pcContent && *pcContent != '>' )
	{
		m_kValue += *pcContent;
		++pcContent;
	}

	if ( !pcContent )
	{
		if(pkDocument)	
			pkDocument->SetError(VE_XML_ERROR_PARSING_UNKNOWN, 0, 0, eEncoding);
	}
	if ( pcContent && *pcContent == '>' )
		return pcContent+1;
	return pcContent;
}
//--------------------------------------------------------------------------
VeXMLUnknown* VeXMLUnknown::ToUnknown()
{
	return this;
}
//--------------------------------------------------------------------------
const VeXMLUnknown* VeXMLUnknown::ToUnknown() const
{
	return this;
}
//--------------------------------------------------------------------------
void VeXMLUnknown::CopyTo(VeXMLUnknown* pkTarget) const
{
	VeXMLNode::CopyTo(pkTarget);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLDeclaration, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLDeclaration::VeXMLDeclaration() : VeXMLNode(VeXMLNode::VE_XML_DECLARATION)
{

}
//--------------------------------------------------------------------------
VeXMLDeclaration::VeXMLDeclaration(const VeChar8* pcVersion, const VeChar8* pcEncoding, const VeChar8* pcStandalone)
	: VeXMLNode(VeXMLNode::VE_XML_DECLARATION)
{
	m_kVersion = pcVersion;
	m_kEncoding = pcEncoding;
	m_kStandalone = pcStandalone;
}
//--------------------------------------------------------------------------
VeXMLDeclaration::VeXMLDeclaration(const VeXMLDeclaration& kCopy) : VeXMLNode(VeXMLNode::VE_XML_DECLARATION)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLDeclaration& VeXMLDeclaration::operator = (const VeXMLDeclaration& kCopy)
{
	Clear();
	kCopy.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLDeclaration::~VeXMLDeclaration()
{

}
//--------------------------------------------------------------------------
void VeXMLDeclaration::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	kOutput += "<?xml ";
	if(m_kVersion.Length())
	{
		kOutput += "version=\"";
		kOutput += m_kVersion;
		kOutput += "\" ";
	}
	if(m_kEncoding.Length())
	{
		kOutput += "encoding=\"";
		kOutput += m_kEncoding;
		kOutput += "\" ";
	}
	if(m_kStandalone.Length())
	{
		kOutput += "standalone=\"";
		kOutput += m_kStandalone;
		kOutput += "\" ";
	}
	kOutput += "?>";
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDeclaration::Version() const
{
	return m_kVersion;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDeclaration::Encoding() const
{
	return m_kEncoding;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDeclaration::Standalone() const
{
	return m_kStandalone;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLDeclaration::Clone() const
{
	VeXMLDeclaration* pkClone = VE_NEW VeXMLDeclaration();

	if ( !pkClone )
		return 0;

	CopyTo( pkClone );
	return pkClone;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDeclaration::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	pcContent = SkipWhiteSpace( pcContent, eEncoding );
	VeXMLDocument* document = GetDocument();
	if ( !pcContent || !*pcContent || !StringEqual( pcContent, "<?xml", true, eEncoding ) )
	{
		if(document)
			document->SetError(VE_XML_ERROR_PARSING_DECLARATION, 0, 0, eEncoding);
		return 0;
	}
	if ( pkData )
	{
		pkData->Stamp( pcContent, eEncoding );
		m_kLocation = pkData->Cursor();
	}
	pcContent += 5;

	m_kVersion = "";
	m_kEncoding = "";
	m_kStandalone = "";

	while ( pcContent && *pcContent )
	{
		if ( *pcContent == '>' )
		{
			++pcContent;
			return pcContent;
		}

		pcContent = SkipWhiteSpace( pcContent, eEncoding );
		if ( StringEqual( pcContent, "version", true, eEncoding ) )
		{
			VeXMLAttribute kAttr;
			pcContent = kAttr.Parse( pcContent, pkData, eEncoding );		
			m_kVersion = kAttr.Value();
		}
		else if ( StringEqual( pcContent, "eEncoding", true, eEncoding ) )
		{
			VeXMLAttribute kAttr;
			pcContent = kAttr.Parse( pcContent, pkData, eEncoding );		
			m_kEncoding = kAttr.Value();
		}
		else if ( StringEqual( pcContent, "standalone", true, eEncoding ) )
		{
			VeXMLAttribute kAttr;
			pcContent = kAttr.Parse( pcContent, pkData, eEncoding );		
			m_kStandalone = kAttr.Value();
		}
		else
		{
			while( pcContent && *pcContent && *pcContent != '>' && !IsWhiteSpace( *pcContent ) )
				++pcContent;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeXMLDeclaration* VeXMLDeclaration::ToDeclaration()
{
	return this;
}
//--------------------------------------------------------------------------
const VeXMLDeclaration* VeXMLDeclaration::ToDeclaration() const
{
	return this;
}
//--------------------------------------------------------------------------
void VeXMLDeclaration::CopyTo(VeXMLDeclaration* pkTarget) const
{
	VeXMLNode::CopyTo( pkTarget );
	pkTarget->m_kVersion = m_kVersion;
	pkTarget->m_kEncoding = m_kEncoding;
	pkTarget->m_kStandalone = m_kStandalone;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLAttribute, VeXMLBase);
//--------------------------------------------------------------------------
VeXMLAttribute::VeXMLAttribute()
	: m_pkDocument(NULL)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeXMLAttribute::VeXMLAttribute(const VeChar8* pcName, const VeChar8* pcValue)
	: m_pkDocument(NULL), m_kName(pcName), m_kValue(pcValue)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
void VeXMLAttribute::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	VeString n, v;

	EncodeString(m_kName, n);
	EncodeString(m_kValue, v);

	if(m_kValue.Find ('\"') == VE_INFINITE)
	{
		kOutput += n;
		kOutput += "=\"";
		kOutput += v;
		kOutput += "\"";
	}
	else
	{
		kOutput += n;
		kOutput += "='";
		kOutput += v;
		kOutput += "'";
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLAttribute::Name() const
{
	return m_kName;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLAttribute::Value() const
{
	return m_kValue;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLAttribute::IntValue() const
{
	return VeAtoi(m_kValue);
}
//--------------------------------------------------------------------------
VeFloat32 VeXMLAttribute::FloatValue() const
{
	return (VeFloat32)VeAtof(m_kValue);
}
//--------------------------------------------------------------------------
const VeString& VeXMLAttribute::NameToStr() const
{
	return m_kName;
}
//--------------------------------------------------------------------------
bool VeXMLAttribute::QueryIntValue(VeInt32* pi32Value) const
{
	return m_kValue.ToInt(*pi32Value);
}
//--------------------------------------------------------------------------
bool VeXMLAttribute::QueryFloatValue(VeFloat32* pf32Value) const
{
	return m_kValue.ToFloat(*pf32Value);
}
//--------------------------------------------------------------------------
void VeXMLAttribute::SetName(const VeChar8* pcName)
{
	m_kName = pcName;
}
//--------------------------------------------------------------------------
void VeXMLAttribute::SetValue(const VeChar8* pcValue)
{
	m_kValue = pcValue;
}
//--------------------------------------------------------------------------
void VeXMLAttribute::SetIntValue(VeInt32 i32Value)
{
	m_kValue = VeString::FromInt(i32Value);
}
//--------------------------------------------------------------------------
void VeXMLAttribute::SetFloatValue(VeFloat32 f32Value)
{
	m_kValue = VeString::FromFloat(f32Value);
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLAttribute::Next() const
{
	return m_kNode.Next() ? m_kNode.Next()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttribute::Next()
{
	return m_kNode.Next() ? m_kNode.Next()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLAttribute::Previous() const
{
	return m_kNode.Pre() ? m_kNode.Pre()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttribute::Previous()
{
	return m_kNode.Pre() ? m_kNode.Pre()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
bool VeXMLAttribute::operator == (const VeXMLAttribute& kAttri) const
{
	return m_kName == kAttri.m_kName;
}
//--------------------------------------------------------------------------
bool VeXMLAttribute::operator < (const VeXMLAttribute& kAttri) const
{
	return m_kName < kAttri.m_kName;
}
//--------------------------------------------------------------------------
bool VeXMLAttribute::operator > (const VeXMLAttribute& kAttri) const
{
	return m_kName > kAttri.m_kName;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLAttribute::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	pcContent = SkipWhiteSpace(pcContent, eEncoding);
	if(!pcContent || !*pcContent)
		return 0;

	if(pkData)
	{
		pkData->Stamp(pcContent, eEncoding);
		m_kLocation = pkData->Cursor();
	}

	const VeChar8* pcErr = pcContent;
	pcContent = ReadName(pcContent, m_kName, eEncoding);
	if (!pcContent || !*pcContent)
	{
		if(m_pkDocument)
			m_pkDocument->SetError(VE_XML_ERROR_READING_ATTRIBUTES, pcErr, pkData, eEncoding);
		return 0;
	}
	pcContent = SkipWhiteSpace( pcContent, eEncoding );
	if (!pcContent || !*pcContent || *pcContent != '=')
	{
		if (m_pkDocument)
			m_pkDocument->SetError(VE_XML_ERROR_READING_ATTRIBUTES, pcContent, pkData, eEncoding);
		return 0;
	}

	++pcContent;
	pcContent = SkipWhiteSpace(pcContent, eEncoding);
	if (!pcContent || !*pcContent)
	{
		if(m_pkDocument)
			m_pkDocument->SetError(VE_XML_ERROR_READING_ATTRIBUTES, pcContent, pkData, eEncoding);
		return 0;
	}

	const VeChar8* pcEnd;
	const VeChar8 SINGLE_QUOTE = '\'';
	const VeChar8 DOUBLE_QUOTE = '\"';

	if(*pcContent == SINGLE_QUOTE)
	{
		++pcContent;
		pcEnd = "\'";
		pcContent = ReadText(pcContent, m_kValue, false, pcEnd, false, eEncoding);
	}
	else if(*pcContent == DOUBLE_QUOTE)
	{
		++pcContent;
		pcEnd = "\"";
		pcContent = ReadText( pcContent, m_kValue, false, pcEnd, false, eEncoding );
	}
	else
	{
		m_kValue = "";
		while(pcContent && *pcContent && !IsWhiteSpace(*pcContent) && *pcContent != '/' && *pcContent != '>')							// tag end
		{
			if(*pcContent == SINGLE_QUOTE || *pcContent == DOUBLE_QUOTE)
			{
				if(m_pkDocument)
					m_pkDocument->SetError(VE_XML_ERROR_READING_ATTRIBUTES, pcContent, pkData, eEncoding);
				return 0;
			}
			m_kValue += *pcContent;
			++pcContent;
		}
	}
	return pcContent;
}
//--------------------------------------------------------------------------
void VeXMLAttribute::SetDocument(VeXMLDocument* pkDoc)
{
	m_pkDocument = pkDoc;
}
//--------------------------------------------------------------------------
VeXMLAttributeSet::VeXMLAttributeSet()
{

}
//--------------------------------------------------------------------------
VeXMLAttributeSet::VeXMLAttributeSet(const VeXMLAttributeSet&)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
void VeXMLAttributeSet::operator = (const VeXMLAttributeSet&)
{
	VE_ASSERT(!"Error");
}
//--------------------------------------------------------------------------
VeXMLAttributeSet::~VeXMLAttributeSet()
{
	VE_ASSERT(m_kList.Empty());
}
//--------------------------------------------------------------------------
void VeXMLAttributeSet::Add(VeXMLAttribute* pkAttribute)
{
	VE_ASSERT(!Find(pkAttribute->Name()));
	m_kList.AttachBack(pkAttribute->m_kNode);
}
//--------------------------------------------------------------------------
void VeXMLAttributeSet::Remove(VeXMLAttribute* pkAttribute)
{
	VE_ASSERT(pkAttribute->m_kNode.IsAttach(m_kList));
	pkAttribute->m_kNode.Detach();
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLAttributeSet::First() const
{
	return m_kList.Size() ? m_kList.GetHeadNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttributeSet::First()
{
	return m_kList.Size() ? m_kList.GetHeadNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLAttributeSet::Last() const
{
	return m_kList.Size() ? m_kList.GetLastNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttributeSet::Last()
{
	return m_kList.Size() ? m_kList.GetLastNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttributeSet::Find(const VeChar8* pcName) const
{
	m_kList.BeginIterator();
	while(!m_kList.IsEnd())
	{
		VeXMLAttribute* pkAttr = m_kList.GetIterNode()->m_tContent;
		m_kList.Next();
		if(pkAttr->m_kName == pcName)
		{
			return pkAttr;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLAttributeSet::FindOrCreate(const VeChar8* pcName)
{
	VeXMLAttribute* pkAttr = Find(pcName);
	if(!pkAttr)
	{
		pkAttr = VE_NEW VeXMLAttribute();
		Add(pkAttr);
		pkAttr->SetName(pcName);
	}
	return pkAttr;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLText, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLText::VeXMLText(const VeChar8* pcValue) : VeXMLNode(VeXMLNode::VE_XML_TEXT), m_bCData(false)
{
	SetValue(pcValue);
}
//--------------------------------------------------------------------------
VeXMLText::VeXMLText(const VeXMLText& kCopy) : VeXMLNode(VeXMLNode::VE_XML_TEXT), m_bCData(false)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLText& VeXMLText::operator = (const VeXMLText& kBase)
{
	kBase.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLText::~VeXMLText()
{

}
//--------------------------------------------------------------------------
void VeXMLText::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	if(m_bCData)
	{
		kOutput += "\r\n";
		for(VeInt32 i(0); i < i32Depth; ++i)
		{
			kOutput += "\t";
		}
		kOutput += "<![CDATA[";
		kOutput += m_kValue;
		kOutput += "]]>\r\n";
	}
	else
	{
		VeString kBuffer;
		EncodeString(m_kValue, kBuffer);
		kOutput += kBuffer;
	}
}
//--------------------------------------------------------------------------
bool VeXMLText::GetCData() const
{
	return m_bCData;
}
//--------------------------------------------------------------------------
void VeXMLText::SetCData(bool bData)
{
	m_bCData = bData;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLText::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	m_kValue = "";
	VeXMLDocument* pkDocument = GetDocument();

	if(pkData)
	{
		pkData->Stamp(pcContent, eEncoding);
		m_kLocation = pkData->Cursor();
	}

	const VeChar8* const pcStartTag = "<![CDATA[";
	const VeChar8* const pcEndTag   = "]]>";

	if (m_bCData || StringEqual(pcContent, pcStartTag, false, eEncoding))
	{
		m_bCData = true;

		if(!StringEqual(pcContent, pcStartTag, false, eEncoding))
		{
			if(pkDocument)
				pkDocument->SetError(VE_XML_ERROR_PARSING_CDATA, pcContent, pkData, eEncoding);
			return 0;
		}
		pcContent += VeStrlen(pcStartTag);

		while(pcContent && *pcContent && !StringEqual(pcContent, pcEndTag, false, eEncoding))
		{
			m_kValue += *pcContent;
			++pcContent;
		}

		VeString kDummy; 
		pcContent = ReadText(pcContent, kDummy, false, pcEndTag, false, eEncoding);
		return pcContent;
	}
	else
	{
		bool bIgnoreWhite = true;
		const VeChar8* pcEnd = "<";
		pcContent = ReadText(pcContent, m_kValue, bIgnoreWhite, pcEnd, false, eEncoding);
		if(pcContent && *pcContent)
			return pcContent - 1;
		return 0;
	}
}
//--------------------------------------------------------------------------
const VeXMLText* VeXMLText::ToText() const
{
	return this;
}
//--------------------------------------------------------------------------
VeXMLText* VeXMLText::ToText()
{
	return this;
}
//--------------------------------------------------------------------------
VeXMLText* VeXMLText::Clone() const
{
	VeXMLText* pkClone = VE_NEW VeXMLText("");
	CopyTo(pkClone);
	return pkClone;
}
//--------------------------------------------------------------------------
void VeXMLText::CopyTo(VeXMLText* pkTarget) const
{
	VeXMLNode::CopyTo(pkTarget);
	pkTarget->m_bCData = m_bCData;
}
//--------------------------------------------------------------------------
bool VeXMLText::Blank() const
{
	for(VeUInt32 i(0); i < m_kValue.Length(); ++i)
		if(!IsWhiteSpace(m_kValue.GetAt(i)))
			return false;
	return true;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLElement, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLElement::VeXMLElement(const VeChar8* pcValue) : VeXMLNode(VeXMLNode::VE_XML_ELEMENT)
{

}
//--------------------------------------------------------------------------
VeXMLElement::VeXMLElement(const VeXMLElement& kCopy) : VeXMLNode(VeXMLNode::VE_XML_ELEMENT)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLElement& VeXMLElement::operator = (const VeXMLElement& kBase)
{
	ClearThis();
	kBase.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLElement::~VeXMLElement()
{
	ClearThis();
}
//--------------------------------------------------------------------------
void VeXMLElement::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	for(VeInt32 i(0); i < i32Depth; ++i)
	{
		kOutput += "\t";
	}

	kOutput += "<";
	kOutput += m_kValue;

	for(const VeXMLAttribute* pkAttrib = m_kAttributeSet.First(); pkAttrib; pkAttrib = pkAttrib->Next())
	{
		kOutput += " ";
		pkAttrib->Output(kOutput, i32Depth);
	}

	if(!FirstChild())
	{
		kOutput += " />";
	}
	else if(FirstChild() == LastChild() && FirstChild()->ToText())
	{
		kOutput += ">";
		FirstChild()->Output(kOutput, i32Depth + 1);
		kOutput += "</";
		kOutput += m_kValue;
		kOutput += ">";
	}
	else
	{
		kOutput += ">";

		for(VeXMLNode* pkNode = (m_kChildren.Size() ? m_kChildren.GetHeadNode()->m_tContent : NULL);
			pkNode; pkNode = pkNode->NextSibling())
		{
			if(!pkNode->ToText())
			{
				kOutput += "\r\n";
			}
			pkNode->Output(kOutput, i32Depth + 1);
		}
		kOutput += "\r\n";
		for(VeInt32 i(0); i < i32Depth; ++i)
		{
			kOutput += "\t";
		}
		kOutput += "</";
		kOutput += m_kValue;
		kOutput += ">";
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLElement::GetAttribute(const VeChar8* pcName) const
{
	const VeXMLAttribute* pkAttr = m_kAttributeSet.Find(pcName);
	return pkAttr ? pkAttr->Value() : NULL;
}
//--------------------------------------------------------------------------
void VeXMLElement::SetAttribute(const VeChar8* pcName, const VeChar8* pcValue)
{
	VeXMLAttribute* pkAttr = m_kAttributeSet.FindOrCreate(pcName);
	if (pkAttr)
	{
		pkAttr->SetValue(pcValue);
	}
}
//--------------------------------------------------------------------------
void VeXMLElement::RemoveAttribute(const VeChar8 * pcName)
{
	VeXMLAttribute* pkAttr = m_kAttributeSet.Find(pcName);
	if(pkAttr)
	{
		m_kAttributeSet.Remove(pkAttr);
		VE_DELETE(pkAttr);
	}
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLElement::FirstAttribute() const
{
	return m_kAttributeSet.First();
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLElement::FirstAttribute()
{
	return m_kAttributeSet.First();
}
//--------------------------------------------------------------------------
const VeXMLAttribute* VeXMLElement::LastAttribute() const
{
	return m_kAttributeSet.Last();
}
//--------------------------------------------------------------------------
VeXMLAttribute* VeXMLElement::LastAttribute()
{
	return m_kAttributeSet.Last();
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLElement::GetText() const
{
	const VeXMLNode* pkChild = FirstChild();
	if(pkChild)
	{
		const VeXMLText* pkChildText = pkChild->ToText();
		if(pkChildText)
		{
			return pkChildText->Value();
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLElement::Clone() const
{
	VeXMLElement* pcClone = VE_NEW VeXMLElement(Value());
	if(!pcClone) return NULL;
	CopyTo(pcClone);
	return pcClone;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLElement::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	pcContent = SkipWhiteSpace(pcContent, eEncoding);
	VeXMLDocument* pkDocument = GetDocument();

	if(!pcContent || !*pcContent)
	{
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_PARSING_ELEMENT, 0, 0, eEncoding);
		return NULL;
	}

	if(pkData)
	{
		pkData->Stamp(pcContent, eEncoding);
		m_kLocation = pkData->Cursor();
	}

	if(*pcContent != '<')
	{
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_PARSING_ELEMENT, pcContent, pkData, eEncoding);
		return NULL;
	}

	pcContent = SkipWhiteSpace(pcContent+1, eEncoding);

	const VeChar8* pcErr = pcContent;

	pcContent = ReadName(pcContent, m_kValue, eEncoding);
	if(!pcContent || !*pcContent)
	{
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_FAILED_TO_READ_ELEMENT_NAME, pcErr, pkData, eEncoding);
		return NULL;
	}

	VeString kEndTag("</");
	kEndTag += m_kValue;

	while(pcContent && *pcContent)
	{
		pcErr = pcContent;
		pcContent = SkipWhiteSpace(pcContent, eEncoding);
		if(!pcContent || !*pcContent)
		{
			if(pkDocument)
				pkDocument->SetError(VE_XML_ERROR_READING_ATTRIBUTES, pcErr, pkData, eEncoding);
			return NULL;
		}
		if(*pcContent == '/')
		{
			++pcContent;
			if(*pcContent  != '>')
			{
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_PARSING_EMPTY, pcContent, pkData, eEncoding);		
				return NULL;
			}
			return (pcContent + 1);
		}
		else if(*pcContent == '>')
		{
			++pcContent;
			pcContent = ReadValue(pcContent, pkData, eEncoding);
			if(!pcContent || !*pcContent)
			{
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_READING_END_TAG, pcContent, pkData, eEncoding);
				return NULL;
			}

			if(StringEqual(pcContent, kEndTag, false, eEncoding))
			{
				pcContent += kEndTag.Length();
				pcContent = SkipWhiteSpace(pcContent, eEncoding);
				if(pcContent && *pcContent && *pcContent == '>')
				{
					++pcContent;
					return pcContent;
				}
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_READING_END_TAG, pcContent, pkData, eEncoding);
				return NULL;
			}
			else
			{
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_READING_END_TAG, pcContent, pkData, eEncoding);
				return NULL;
			}
		}
		else
		{
			VeXMLAttribute* pkAttr = VE_NEW VeXMLAttribute();
			if (!pkAttr) return NULL;
			pkAttr->SetDocument(pkDocument);
			pcErr = pcContent;
			pcContent = pkAttr->Parse(pcContent, pkData, eEncoding);

			if(!pcContent || !*pcContent)
			{
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_PARSING_ELEMENT, pcErr, pkData, eEncoding);
				VE_DELETE(pkAttr);
				return NULL;
			}

			VeXMLAttribute* pkNode = m_kAttributeSet.Find(pkAttr->Name());
			if(pkNode)
			{
				if(pkDocument)
					pkDocument->SetError(VE_XML_ERROR_PARSING_ELEMENT, pcErr, pkData, eEncoding);
				VE_DELETE(pkAttr);
				return NULL;
			}

			m_kAttributeSet.Add(pkAttr);
		}
	}
	return pcContent;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLElement::ToElement() const
{
	return this;
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLElement::ToElement()
{
	return this;
}
//--------------------------------------------------------------------------
void VeXMLElement::CopyTo(VeXMLElement* pkTarget) const
{
	VeXMLNode::CopyTo(pkTarget);

	for(const VeXMLAttribute* pkAttribute = m_kAttributeSet.First(); pkAttribute; pkAttribute = pkAttribute->Next())
	{
		pkTarget->SetAttribute(pkAttribute->Name(), pkAttribute->Value());
	}

	for(VeXMLNode* pkNode = (m_kChildren.Size() ? m_kChildren.GetHeadNode()->m_tContent : NULL); pkNode; pkNode = pkNode->NextSibling())
	{
		pkTarget->LinkEndChild(pkNode->Clone());
	}
}
//--------------------------------------------------------------------------
void VeXMLElement::ClearThis()
{
	Clear();
	while(m_kAttributeSet.First())
	{
		VeXMLAttribute* pkNode = m_kAttributeSet.First();
		m_kAttributeSet.Remove(pkNode);
		VE_DELETE(pkNode);
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLElement::ReadValue(const VeChar8* pcValue, VeXMLParsingData* pkPrevData, VeXMLEncoding eEncoding)
{
	VeXMLDocument* pkDocument = GetDocument();

	pcValue = SkipWhiteSpace(pcValue, eEncoding);

	while(pcValue && *pcValue)
	{
		if (*pcValue != '<')
		{
			VeXMLText* pkTextNode = VE_NEW VeXMLText("");
			if(!pkTextNode) return NULL;

			pcValue = pkTextNode->Parse(pcValue, pkPrevData, eEncoding);

			if(!pkTextNode->Blank())
			{
				LinkEndChild(pkTextNode);
			}
			else
			{
				VE_DELETE(pkTextNode);
			}
		} 
		else 
		{
			if(StringEqual(pcValue, "</", false, eEncoding))
			{
				return pcValue;
			}
			else
			{
				VeXMLNode* pkNode = Identify(pcValue, eEncoding);
				if(pkNode)
				{
					pcValue = pkNode->Parse(pcValue, pkPrevData, eEncoding);
					LinkEndChild(pkNode);
				}				
				else
				{
					return 0;
				}
			}
		}
		pcValue = SkipWhiteSpace(pcValue, eEncoding);
	}

	if(!pcValue)
	{
		if(pkDocument)
			pkDocument->SetError(VE_XML_ERROR_READING_ELEMENT_VALUE, 0, 0, eEncoding);
	}	
	return pcValue;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeXMLDocument, VeXMLNode);
//--------------------------------------------------------------------------
VeXMLDocument::VeXMLDocument() : VeXMLNode(VeXMLNode::VE_XML_DOCUMENT)
	, m_i32Tabsize(4), m_bUseMicrosoftBOM(false)
{
	ClearError();
}
//--------------------------------------------------------------------------
VeXMLDocument::VeXMLDocument(const VeChar8* pcDocumentName) : VeXMLNode(VeXMLNode::VE_XML_DOCUMENT)
	, m_bError(false), m_i32ErrorId(0), m_i32Tabsize(4), m_bUseMicrosoftBOM(false)
{
	m_kValue = pcDocumentName;
	ClearError();
}
//--------------------------------------------------------------------------
VeXMLDocument::VeXMLDocument(const VeXMLDocument& kCopy) : VeXMLNode(VeXMLNode::VE_XML_DOCUMENT)
	, m_bError(false), m_i32ErrorId(0), m_i32Tabsize(4), m_bUseMicrosoftBOM(false)
{
	kCopy.CopyTo(this);
}
//--------------------------------------------------------------------------
VeXMLDocument& VeXMLDocument::operator = (const VeXMLDocument& kCopy)
{
	Clear();
	kCopy.CopyTo(this);
	return *this;
}
//--------------------------------------------------------------------------
VeXMLDocument::~VeXMLDocument()
{

}
//--------------------------------------------------------------------------
void VeXMLDocument::Output(VeString& kOutput, VeInt32 i32Depth) const
{
	kOutput = "";
	for(const VeXMLNode* pkNode = FirstChild(); pkNode; pkNode = pkNode->NextSibling())
	{
		pkNode->Output(kOutput, i32Depth);
		kOutput += "\r\n";
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDocument::Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding)
{
	ClearError();

	if(!pcContent || !*pcContent)
	{
		SetError(VE_XML_ERROR_DOCUMENT_EMPTY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}

	m_kLocation.Clear();
	if(pkData)
	{
		m_kLocation.m_i32Row = pkData->m_kCursor.m_i32Row;
		m_kLocation.m_i32Col = pkData->m_kCursor.m_i32Col;
	}
	else
	{
		m_kLocation.m_i32Row = 0;
		m_kLocation.m_i32Col = 0;
	}

	VeXMLParsingData kData(pcContent, GetTabSize(), m_kLocation.m_i32Row, m_kLocation.m_i32Col);
	m_kLocation = kData.Cursor();

	if(eEncoding == VE_XML_ENCODING_UNKNOWN)
	{
		const VeUInt8* pU = (const VeUInt8*)pcContent;
		if (*(pU+0) && *(pU+0) == VE_XML_UTF_LEAD_0
			&& *(pU+1) && *(pU+1) == VE_XML_UTF_LEAD_1
			&& *(pU+2) && *(pU+2) == VE_XML_UTF_LEAD_2)
		{
			eEncoding = VE_XML_ENCODING_UTF8;
			m_bUseMicrosoftBOM = true;
		}
	}

	pcContent = SkipWhiteSpace(pcContent, eEncoding);
	if(!pcContent)
	{
		SetError(VE_XML_ERROR_DOCUMENT_EMPTY, 0, 0, VE_XML_ENCODING_UNKNOWN);
		return NULL;
	}

	while(pcContent && *pcContent)
	{
		VeXMLNode* pkNode = Identify(pcContent, eEncoding);
		if(pkNode)
		{
			pcContent = pkNode->Parse(pcContent, &kData, eEncoding);
			LinkEndChild(pkNode);
		}
		else
		{
			break;
		}

		if(eEncoding == VE_XML_ENCODING_UNKNOWN && pkNode->ToDeclaration())
		{
			VeXMLDeclaration* pkDec = pkNode->ToDeclaration();
			const VeChar8* pcEnc = pkDec->Encoding();
			VE_ASSERT(pcEnc);

			if(*pcEnc == '0')
				eEncoding = VE_XML_ENCODING_UTF8;
			else if(StringEqual(pcEnc, "UTF-8", true, VE_XML_ENCODING_UNKNOWN))
				eEncoding = VE_XML_ENCODING_UTF8;
			else if(StringEqual(pcEnc, "UTF8", true, VE_XML_ENCODING_UNKNOWN))
				eEncoding = VE_XML_ENCODING_UTF8;
			else
				eEncoding = VE_XML_ENCODING_LEGACY;
		}

		pcContent = SkipWhiteSpace(pcContent, eEncoding);
	}

	if(!FirstChild())
	{
		SetError(VE_XML_ERROR_DOCUMENT_EMPTY, 0, 0, eEncoding);
		return NULL;
	}

	return pcContent;
}
//--------------------------------------------------------------------------
const VeXMLElement* VeXMLDocument::RootElement() const
{
	return FirstChildElement();
}
//--------------------------------------------------------------------------
VeXMLElement* VeXMLDocument::RootElement()
{
	return FirstChildElement();
}
//--------------------------------------------------------------------------
bool VeXMLDocument::Error() const
{
	return m_bError;
}
//--------------------------------------------------------------------------
const VeChar8* VeXMLDocument::ErrorDesc() const
{
	return m_kErrorDesc;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLDocument::ErrorId() const
{
	return m_i32ErrorId;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLDocument::ErrorRow() const
{
	return m_kErrorLocation.m_i32Row + 1;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLDocument::ErrorCol() const
{
	return m_kErrorLocation.m_i32Col + 1;
}
//--------------------------------------------------------------------------
void VeXMLDocument::SetTabSize(VeInt32 i32TabSize)
{
	m_i32Tabsize = i32TabSize;
}
//--------------------------------------------------------------------------
VeInt32 VeXMLDocument::GetTabSize() const
{
	return m_i32Tabsize;
}
//--------------------------------------------------------------------------
void VeXMLDocument::ClearError()
{
	m_bError = false; 
	m_i32ErrorId = 0; 
	m_kErrorDesc = ""; 
	m_kErrorLocation.m_i32Row = m_kErrorLocation.m_i32Col = 0; 
}
//--------------------------------------------------------------------------
void VeXMLDocument::SetError(VeInt32 i32Err, const VeChar8* pcErrorLocation, VeXMLParsingData* pcPrevData, VeXMLEncoding eEncoding)
{
	if(m_bError) return;
	VE_ASSERT(i32Err > 0 && i32Err < VE_XML_ERROR_STRING_COUNT);
	m_bError = true;
	m_i32ErrorId = i32Err;
	m_kErrorDesc = ms_pcErrorString[m_i32ErrorId];

	m_kErrorLocation.Clear();
	if (pcErrorLocation && pcPrevData)
	{
		pcPrevData->Stamp(pcErrorLocation, eEncoding);
		m_kErrorLocation = pcPrevData->Cursor();
	}
}
//--------------------------------------------------------------------------
const VeXMLDocument* VeXMLDocument::ToDocument() const
{
	return this;
}
//--------------------------------------------------------------------------
VeXMLDocument* VeXMLDocument::ToDocument()
{
	return this;
}
//--------------------------------------------------------------------------
VeXMLNode* VeXMLDocument::Clone() const
{
	VeXMLDocument* pcClone = VE_NEW VeXMLDocument();
	if(!pcClone) return NULL;
	CopyTo(pcClone);
	return pcClone;
}
//--------------------------------------------------------------------------
void VeXMLDocument::CopyTo(VeXMLDocument* pkTarget) const
{
	VeXMLNode::CopyTo(pkTarget);

	pkTarget->m_bError = m_bError;
	pkTarget->m_i32ErrorId = m_i32ErrorId;
	pkTarget->m_kErrorDesc = m_kErrorDesc;
	pkTarget->m_i32Tabsize = m_i32Tabsize;
	pkTarget->m_kErrorLocation = m_kErrorLocation;
	pkTarget->m_bUseMicrosoftBOM = m_bUseMicrosoftBOM;

	for(VeXMLNode* pkNode = (m_kChildren.Size() ? m_kChildren.GetHeadNode()->m_tContent : NULL); pkNode; pkNode = pkNode->NextSibling())
	{
		pkTarget->LinkEndChild(pkNode->Clone());
	}
}
//--------------------------------------------------------------------------
VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeXMLDocument& kDoc)
{
	VeInt32 i32Len = kIn.RemainingLength();
	VeChar8* pcBuffer = VeAlloc(VeChar8, i32Len + 1);
	kIn.Read(pcBuffer, i32Len);
	pcBuffer[i32Len] = 0;
	kDoc.Parse(pcBuffer);
	VeFree(pcBuffer);
	return kIn;
}
//--------------------------------------------------------------------------
VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeXMLDocument& kDoc)
{
	VeString kBuffer;
	kDoc.Output(kBuffer);
	kOut.Write(kBuffer.GetString(), kBuffer.Length());
	return kOut;
}
//--------------------------------------------------------------------------
