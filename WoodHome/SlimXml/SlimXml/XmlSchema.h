#ifndef __SLIM_XML_SCHEMA_H__
#define __SLIM_XML_SCHEMA_H__

#include "SlimXml.h"

namespace slim
{

class XmlSchema : public XmlDocument
{
public:
	//parse schema from xml file
	bool constructFromXml( XmlDocument* file );

	//generate reading/writing c++ code automatically
	bool generateCode( const Char* filename, const Char* pchFilename = NULL ) const;

private:
	bool parseNodeStruct( XmlNode* dst, XmlNode* src );

	const Char* guessType( const Char* content ) const;

	bool generateCodeForNode( const XmlNode* node, String& headerCode, String& sourceCode ) const;

	size_t getNodeMemberTypeWidth( const XmlNode* node ) const;

	void addSimpleMember( const XmlNode* child, String& structure, size_t typeWidth,
						  String& readFunction, String& writeFunction ) const;
	void addSimpleVector( const XmlNode* child, String& structure, size_t typeWidth,
						  String& readFunction, String& writeFunction ) const;
	void addStructMember( const XmlNode* child, String& structure, size_t typeWidth,
						  String& readFunction, String& writeFunction ) const;
	void addStructVector( const XmlNode* child, String& structure, size_t typeWidth,
						  String& readFunction, String& writeFunction ) const;

	void addConstructorItem( const XmlNode* child, String& structure, int& index ) const;

	String getSimpleTypeString( const XmlAttribute* type ) const;

	const Char* getTypeDefaultValue( const Char* type ) const;

	String getPluralName( const String& name ) const;
};

}

#endif
