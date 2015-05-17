////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeXML.h
//  Version:     v1.00
//  Created:     19/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeXMLDocument;
class VeXMLElement;
class VeXMLComment;
class VeXMLUnknown;
class VeXMLAttribute;
class VeXMLText;
class VeXMLDeclaration;
class VeXMLParsingData;
class VeXMLNode;

enum VeXMLEncoding
{
	VE_XML_ENCODING_UNKNOWN,
	VE_XML_ENCODING_UTF8,
	VE_XML_ENCODING_LEGACY
};

const VeXMLEncoding VE_XML_DEFAULT_ENCODING = VE_XML_ENCODING_UNKNOWN;

struct VE_POWER_API VeXMLCursor : public VeMemObject
{
	VeXMLCursor();

	void Clear();

	VeInt32 m_i32Row;
	VeInt32 m_i32Col;
};

class VE_POWER_API VeXMLBase : public VeMemObject
{
	friend class VeXMLNode;
	friend class VeXMLElement;
	friend class VeXMLDocument;
	VeDeclareRootRTTI(VeXMLBase);
public:
	VeXMLBase();

	virtual ~VeXMLBase();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const = 0;

	VeInt32 Row() const;

	VeInt32 Column() const;

	static const VeByte ms_utf8ByteTable[256];

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding) = 0;

	static void EncodeString(const VeString& kStr, VeString& kOut);

	enum
	{
		VE_XML_NO_ERROR = 0,
		VE_XML_ERROR,
		VE_XML_ERROR_OPENING_FILE,
		VE_XML_ERROR_PARSING_ELEMENT,
		VE_XML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
		VE_XML_ERROR_READING_ELEMENT_VALUE,
		VE_XML_ERROR_READING_ATTRIBUTES,
		VE_XML_ERROR_PARSING_EMPTY,
		VE_XML_ERROR_READING_END_TAG,
		VE_XML_ERROR_PARSING_UNKNOWN,
		VE_XML_ERROR_PARSING_COMMENT,
		VE_XML_ERROR_PARSING_DECLARATION,
		VE_XML_ERROR_DOCUMENT_EMPTY,
		VE_XML_ERROR_EMBEDDED_NULL,
		VE_XML_ERROR_PARSING_CDATA,
		VE_XML_ERROR_DOCUMENT_TOP_ONLY,
		VE_XML_ERROR_STRING_COUNT
	};

protected:
	static const VeChar8* SkipWhiteSpace(const VeChar8* pcStr, VeXMLEncoding eEncoding);

	static bool IsWhiteSpace(VeChar8 c);

	static bool IsWhiteSpace(VeInt32 c);

	static const VeChar8* ReadName(const VeChar8* pcStr, VeString& kName, VeXMLEncoding eEncoding);

	static const VeChar8* ReadText(const VeChar8* pcStr, VeString& kText,
		bool bIgnoreWhiteSpace, const VeChar8* pcEndTag,
		bool bIgnoreCase, VeXMLEncoding eEncoding);

	static const VeChar8* GetEntity(const VeChar8* pcStr, VeChar8* pcValue, VeInt32* pi32Length, VeXMLEncoding eEncoding);

	static const VeChar8* GetChar(const VeChar8* pcStr, VeChar8* pcValue, VeInt32* pi32Length, VeXMLEncoding eEncoding);

	static bool StringEqual(const VeChar8* pcStr, const VeChar8* pcEndTag, bool bIgnoreCase, VeXMLEncoding eEncoding);

	static VeInt32 IsAlpha(VeUInt8 u8AnyByte, VeXMLEncoding eEncoding);

	static VeInt32 IsAlphaNum(VeUInt8 u8AnyByte, VeXMLEncoding eEncoding);

	static VeInt32 ToLower(VeInt32 v, VeXMLEncoding eEncoding);

	static void ConvertUTF32ToUTF8(VeUInt32 u32Input, VeChar8* pcOutput, VeInt32* pi32Length);

	VeXMLCursor m_kLocation;

	VeXMLBase(const VeXMLBase&);

	void operator = (const VeXMLBase&);

	struct Entity
	{
		const VeChar8* m_pcStr;
		VeUInt32 m_u32Length;
		VeChar8 m_cChar;
	};

	enum
	{
		NUM_ENTITY = 5,
		MAX_ENTITY_LENGTH = 6
	};

	static const VeChar8* ms_pcErrorString[VE_XML_ERROR_STRING_COUNT];

	static Entity ms_akEntity[NUM_ENTITY];
};

class VE_POWER_API VeXMLNode : public VeXMLBase
{
	friend class VeXMLDocument;
	friend class VeXMLElement;
	VeDeclareRTTI;

public:
	enum NodeType
	{
		VE_XML_DOCUMENT,
		VE_XML_ELEMENT,
		VE_XML_COMMENT,
		VE_XML_UNKNOWN,
		VE_XML_TEXT,
		VE_XML_DECLARATION,
		VE_XML_TYPECOUNT
	};

	virtual ~VeXMLNode();

	const VeChar8* Value() const;

	const VeString& ValueToStr() const;

	void SetValue(const VeChar8* pcValue);

	void Clear();

	VeXMLNode* Parent();

	const VeXMLNode* Parent() const;

	VeXMLNode* FirstChild();

	const VeXMLNode* FirstChild() const;

	VeXMLNode* FirstChild(const VeChar8* pcValue);

	const VeXMLNode* FirstChild(const VeChar8* pcValue) const;

	VeXMLNode* LastChild();
	
	const VeXMLNode* LastChild() const;

	VeXMLNode* LastChild(const VeChar8* pcValue);
	
	const VeXMLNode* LastChild(const VeChar8* pcValue) const;

	VeXMLNode* IterateChildren(VeXMLNode* pkPrevious);

	const VeXMLNode* IterateChildren(const VeXMLNode* pkPrevious) const;

	VeXMLNode* IterateChildren(const VeChar8* pcValue, VeXMLNode* pkPrevious);

	const VeXMLNode* IterateChildren(const VeChar8* pcValue, const VeXMLNode* pkPrevious) const;

	VeXMLNode* InsertEndChild(const VeXMLNode& kAddThis);

	VeXMLNode* LinkEndChild(VeXMLNode* pkAddThis);

	VeXMLNode* InsertBeforeChild(VeXMLNode* pkBeforeThis, const VeXMLNode& kAddThis);

	VeXMLNode* InsertAfterChild(VeXMLNode* pkAfterThis, const VeXMLNode& kAddThis);

	VeXMLNode* ReplaceChild(VeXMLNode* pkReplaceThis, const VeXMLNode& kWithThis);

	bool RemoveChild(VeXMLNode* pkRemoveThis);

	VeXMLNode* PreviousSibling();

	const VeXMLNode* PreviousSibling() const;

	VeXMLNode* PreviousSibling(const VeChar8* pcValue);

	const VeXMLNode* PreviousSibling(const VeChar8* pcValue) const;

	VeXMLNode* NextSibling();

	const VeXMLNode* NextSibling() const;
	
	VeXMLNode* NextSibling(const VeChar8* pcValue);

	const VeXMLNode* NextSibling(const VeChar8* pcValue) const;

	const VeXMLElement* NextSiblingElement() const;

	VeXMLElement* NextSiblingElement();

	const VeXMLElement* NextSiblingElement(const VeChar8* pcValue) const;

	VeXMLElement* NextSiblingElement(const VeChar8* pcValue);

	VeXMLElement* FirstChildElement();

	const VeXMLElement* FirstChildElement()	const;

	VeXMLElement* FirstChildElement(const VeChar8* pcValue);

	const VeXMLElement* FirstChildElement(const VeChar8* pcValue) const;	

	NodeType Type() const;

	VeXMLDocument* GetDocument();

	const VeXMLDocument* GetDocument() const;

	bool NoChildren() const;

	virtual const VeXMLDocument* ToDocument() const { return 0; }
	virtual const VeXMLElement* ToElement() const { return 0; }
	virtual const VeXMLComment* ToComment() const { return 0; }
	virtual const VeXMLUnknown* ToUnknown() const { return 0; }
	virtual const VeXMLText* ToText() const { return 0; }
	virtual const VeXMLDeclaration* ToDeclaration() const { return 0; }

	virtual VeXMLDocument* ToDocument() { return 0; }
	virtual VeXMLElement* ToElement() { return 0; }
	virtual VeXMLComment* ToComment() { return 0; }
	virtual VeXMLUnknown* ToUnknown() { return 0; }
	virtual VeXMLText* ToText() { return 0; }
	virtual VeXMLDeclaration* ToDeclaration() { return 0; }

	virtual VeXMLNode* Clone() const = 0;

protected:
	VeXMLNode(NodeType eType);

	void CopyTo(VeXMLNode* pkTarget) const;

	VeXMLNode* Identify(const VeChar8* pcStart, VeXMLEncoding eEncoding);

	const NodeType m_eType;
	VeString m_kValue;
	VeXMLNode* m_pkParent;
	VeRefNode<VeXMLNode*> m_kNode;
	VeRefList<VeXMLNode*> m_kChildren;

private:
	VeXMLNode(const VeXMLNode&);
	
	void operator = (const VeXMLNode&);

};

class VE_POWER_API VeXMLComment : public VeXMLNode
{
	VeDeclareRTTI;
public:
	VeXMLComment();

	VeXMLComment(const VeChar8* pcValue);

	VeXMLComment(const VeXMLComment& kCopy);

	VeXMLComment& operator = (const VeXMLComment& kBase);

	virtual ~VeXMLComment();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const;

	virtual VeXMLNode* Clone() const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	virtual VeXMLComment* ToComment();

	virtual const VeXMLComment* ToComment() const;

protected:
	void CopyTo(VeXMLComment* pkTarget) const;

};

class VE_POWER_API VeXMLUnknown : public VeXMLNode
{
	VeDeclareRTTI;
public:
	VeXMLUnknown();

	virtual ~VeXMLUnknown();

	VeXMLUnknown(const VeXMLUnknown& kCopy);

	VeXMLUnknown& operator = (const VeXMLUnknown& kCopy);

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const {}

	virtual VeXMLNode* Clone() const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	virtual VeXMLUnknown* ToUnknown();

	virtual const VeXMLUnknown* ToUnknown() const;

protected:
	void CopyTo(VeXMLUnknown* pkTarget) const;

};

class VE_POWER_API VeXMLDeclaration : public VeXMLNode
{
	VeDeclareRTTI;
public:
	VeXMLDeclaration();

	VeXMLDeclaration(const VeChar8* pcVersion, const VeChar8* pcEncoding, const VeChar8* pcStandalone);

	VeXMLDeclaration(const VeXMLDeclaration& kCopy);

	VeXMLDeclaration& operator = (const VeXMLDeclaration& kCopy);

	virtual ~VeXMLDeclaration();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const;

	const VeChar8* Version() const;

	const VeChar8* Encoding() const;

	const VeChar8* Standalone() const;

	virtual VeXMLNode* Clone() const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	virtual VeXMLDeclaration* ToDeclaration();

	virtual const VeXMLDeclaration* ToDeclaration() const;

protected:
	void CopyTo(VeXMLDeclaration* pkTarget) const;

private:
	VeString m_kVersion;
	VeString m_kEncoding;
	VeString m_kStandalone;

};

class VE_POWER_API VeXMLAttribute : public VeXMLBase
{
	friend class VeXMLAttributeSet;
	VeDeclareRTTI;
public:
	VeXMLAttribute();

	VeXMLAttribute(const VeChar8* pcName, const VeChar8* pcValue);

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const;

	const VeChar8* Name()  const;

	const VeChar8* Value() const;

	VeInt32 IntValue() const;

	VeFloat32 FloatValue() const;

	const VeString& NameToStr() const;

	bool QueryIntValue(VeInt32* pi32Value) const;

	bool QueryFloatValue(VeFloat32* pf32Value) const;

	void SetName(const VeChar8* pcName);

	void SetValue(const VeChar8* pcValue);

	void SetIntValue(VeInt32 i32Value);

	void SetFloatValue(VeFloat32 f32Value);

	const VeXMLAttribute* Next() const;

	VeXMLAttribute* Next();

	const VeXMLAttribute* Previous() const;

	VeXMLAttribute* Previous();

	bool operator == (const VeXMLAttribute& kAttri) const;

	bool operator < (const VeXMLAttribute& kAttri) const;
	
	bool operator > (const VeXMLAttribute& kAttri) const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	void SetDocument(VeXMLDocument* pkDoc);

private:
	VeXMLAttribute(const VeXMLAttribute&);

	void operator = (const VeXMLAttribute&);

	VeXMLDocument* m_pkDocument;
	VeString m_kName;
	VeString m_kValue;
	VeRefNode<VeXMLAttribute*> m_kNode;

};

class VE_POWER_API VeXMLAttributeSet : public VeMemObject
{
public:
	VeXMLAttributeSet();

	~VeXMLAttributeSet();

	void Add(VeXMLAttribute* pkAttribute);

	void Remove(VeXMLAttribute* pkAttribute);

	const VeXMLAttribute* First() const;

	VeXMLAttribute* First();
	
	const VeXMLAttribute* Last() const;

	VeXMLAttribute* Last();

	VeXMLAttribute*	Find(const VeChar8* pcName) const;

	VeXMLAttribute* FindOrCreate(const VeChar8* pcName);

private:
	VeXMLAttributeSet(const VeXMLAttributeSet&);

	void operator = (const VeXMLAttributeSet&);

	VeRefList<VeXMLAttribute*> m_kList;

};

class VE_POWER_API VeXMLText : public VeXMLNode
{
	friend class VeXMLElement;
	VeDeclareRTTI;
public:
	VeXMLText(const VeChar8* pcValue);

	VeXMLText(const VeXMLText& kCopy);

	VeXMLText& operator = (const VeXMLText& kBase);

	virtual ~VeXMLText();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const;

	bool GetCData() const;

	void SetCData(bool bData);

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	virtual const VeXMLText* ToText() const;
	
	virtual VeXMLText* ToText();

protected :
	virtual VeXMLText* Clone() const;

	void CopyTo(VeXMLText* pkTarget) const;

	bool Blank() const;

private:
	bool m_bCData;

};

class VE_POWER_API VeXMLElement : public VeXMLNode
{
	VeDeclareRTTI;
public:
	VeXMLElement(const VeChar8* pcValue);

	VeXMLElement(const VeXMLElement& kCopy);

	VeXMLElement& operator = (const VeXMLElement& kBase);

	virtual ~VeXMLElement();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth) const;

	const VeChar8* GetAttribute(const VeChar8* pcName) const;

	void SetAttribute(const VeChar8* pcName, const VeChar8* pcValue);

	void RemoveAttribute(const VeChar8 * pcName);

	template <typename T>
	T Attribute(const VeChar8* pcName, const T& tDefault)
	{
		const VeChar8* pcAttr = GetAttribute(pcName);
		if(pcAttr)
		{
			T kRes;
			bool bRes = VeString(pcAttr).To(kRes);
			if(bRes)
			{
				return kRes;
			}
		}
		return tDefault;		
	}

	const VeChar8* Attribute(const VeChar8* pcName, const VeChar8* pcDefault = "")
	{
		const VeChar8* pcAttr = GetAttribute(pcName);
		return pcAttr ? pcAttr : pcDefault;
	}

	const VeXMLAttribute* FirstAttribute() const;

	VeXMLAttribute* FirstAttribute();

	const VeXMLAttribute* LastAttribute() const;

	VeXMLAttribute* LastAttribute();

	const VeChar8* GetText() const;

	virtual VeXMLNode* Clone() const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData, VeXMLEncoding eEncoding);

	virtual const VeXMLElement* ToElement() const;

	virtual VeXMLElement* ToElement();

protected:
	void CopyTo(VeXMLElement* pkTarget) const;

	void ClearThis();

	const VeChar8* ReadValue(const VeChar8* pcValue, VeXMLParsingData* pkPrevData, VeXMLEncoding eEncoding);

private:
	VeXMLAttributeSet m_kAttributeSet;

};

class VE_POWER_API VeXMLDocument : public VeXMLNode
{
	VeDeclareRTTI;
public:
	VeXMLDocument();

	VeXMLDocument(const VeChar8* pcDocumentName);

	VeXMLDocument(const VeXMLDocument& kCopy);

	VeXMLDocument& operator = (const VeXMLDocument& kCopy);

	virtual ~VeXMLDocument();

	virtual void Output(VeString& kOutput, VeInt32 i32Depth = 0) const;

	virtual const VeChar8* Parse(const VeChar8* pcContent, VeXMLParsingData* pkData = NULL, VeXMLEncoding eEncoding = VE_XML_DEFAULT_ENCODING);

	const VeXMLElement* RootElement() const;

	VeXMLElement* RootElement();

	bool Error() const;

	const VeChar8* ErrorDesc() const;

	VeInt32 ErrorId() const;

	VeInt32 ErrorRow() const;

	VeInt32 ErrorCol() const;

	void SetTabSize(VeInt32 i32TabSize);

	VeInt32 GetTabSize() const;

	void ClearError();

	void SetError(VeInt32 i32Err, const VeChar8* pcErrorLocation, VeXMLParsingData* pcPrevData, VeXMLEncoding eEncoding);

	virtual const VeXMLDocument* ToDocument() const;
	
	virtual VeXMLDocument* ToDocument();

protected :
	virtual VeXMLNode* Clone() const;

private:
	void CopyTo(VeXMLDocument* pkTarget) const;

	bool m_bError;
	VeInt32 m_i32ErrorId;
	VeString m_kErrorDesc;
	VeInt32 m_i32Tabsize;
	VeXMLCursor m_kErrorLocation;
	bool m_bUseMicrosoftBOM;

};

VE_POWER_API VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeXMLDocument& kDoc);

VE_POWER_API VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeXMLDocument& kDoc);
