﻿///////////////////////////////////////////////////////////////////////////////////////////////////
//this file is automatically generated, do not modify.
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "test_utf8.h"
#include <cassert>

using namespace slim;

namespace test_utf8
{
///////////////////////////////////////////////////////////////////////////////////////////////////
void Model::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	childNode = node->findChild( L"Skeleton" );
	if ( childNode != NULL )
	{
		Skeleton = childNode->getString();
	}

	childNode = node->findFirstChild( L"Part", iter );
	while ( childNode != NULL )
	{
		Parts.resize( Parts.size() + 1 );
		Parts.back().read( childNode );
		childNode = node->findNextChild( L"Part", iter );
	}

	childNode = node->findFirstChild( L"Animation", iter );
	while ( childNode != NULL )
	{
		Animations.resize( Animations.size() + 1 );
		Animations.back().read( childNode );
		childNode = node->findNextChild( L"Animation", iter );
	}

	childNode = node->findFirstChild( L"Light", iter );
	while ( childNode != NULL )
	{
		Lights.resize( Lights.size() + 1 );
		Lights.back().read( childNode );
		childNode = node->findNextChild( L"Light", iter );
	}

	childNode = node->findChild( L"Window" );
	if ( childNode != NULL )
	{
		Window.read( childNode );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Model::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Skeleton != L"" )
	{
		childNode = node->addChild( L"Skeleton" );
		childNode->setString( Skeleton );
	}

	for ( std::vector<Part>::const_iterator iter = Parts.begin();
		  iter != Parts.end();
		  ++iter )
	{
		const Part& obj = *iter;
		childNode = node->addChild( L"Part" );
		obj.write( childNode );
	}

	for ( std::vector<Animation>::const_iterator iter = Animations.begin();
		  iter != Animations.end();
		  ++iter )
	{
		const Animation& obj = *iter;
		childNode = node->addChild( L"Animation" );
		obj.write( childNode );
	}

	for ( std::vector<Light>::const_iterator iter = Lights.begin();
		  iter != Lights.end();
		  ++iter )
	{
		const Light& obj = *iter;
		childNode = node->addChild( L"Light" );
		obj.write( childNode );
	}

	childNode = node->addChild( L"Window" );
	Window.write( childNode );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Part::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	attribute = node->findAttribute( L"Slot" );
	if ( attribute != NULL )
	{
		Slot = attribute->getString();
	}

	attribute = node->findAttribute( L"Filename" );
	if ( attribute != NULL )
	{
		Filename = attribute->getString();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Part::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Slot != L"" )
	{
		attribute = node->addAttribute( L"Slot" );
		attribute->setString( Slot );
	}

	if ( Filename != L"" )
	{
		attribute = node->addAttribute( L"Filename" );
		attribute->setString( Filename );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Animation::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	attribute = node->findAttribute( L"Slot" );
	if ( attribute != NULL )
	{
		Slot = attribute->getString();
	}

	attribute = node->findAttribute( L"Filename" );
	if ( attribute != NULL )
	{
		Filename = attribute->getString();
	}

	childNode = node->findFirstChild( L"Event", iter );
	while ( childNode != NULL )
	{
		Events.resize( Events.size() + 1 );
		Events.back().read( childNode );
		childNode = node->findNextChild( L"Event", iter );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Animation::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Slot != L"" )
	{
		attribute = node->addAttribute( L"Slot" );
		attribute->setString( Slot );
	}

	if ( Filename != L"" )
	{
		attribute = node->addAttribute( L"Filename" );
		attribute->setString( Filename );
	}

	for ( std::vector<Event>::const_iterator iter = Events.begin();
		  iter != Events.end();
		  ++iter )
	{
		const Event& obj = *iter;
		childNode = node->addChild( L"Event" );
		obj.write( childNode );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Event::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	attribute = node->findAttribute( L"Time" );
	if ( attribute != NULL )
	{
		Time = attribute->getFloat();
	}

	attribute = node->findAttribute( L"Type" );
	if ( attribute != NULL )
	{
		Type = attribute->getString();
	}

	childNode = node->findFirstChild( L"Param", iter );
	while ( childNode != NULL )
	{
		Params.resize( Params.size() + 1 );
		Params.back() = childNode->getString();
		childNode = node->findNextChild( L"Param", iter );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Event::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Time != 0.0f )
	{
		attribute = node->addAttribute( L"Time" );
		attribute->setFloat( Time );
	}

	if ( Type != L"" )
	{
		attribute = node->addAttribute( L"Type" );
		attribute->setString( Type );
	}

	for ( std::vector<std::wstring>::const_iterator iter = Params.begin();
		  iter != Params.end();
		  ++iter )
	{
		const std::wstring& value = *iter;
		childNode = node->addChild( L"Param" );
		childNode->setString( value );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Light::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	childNode = node->findChild( L"Position" );
	if ( childNode != NULL )
	{
		Position = childNode->getString();
	}

	childNode = node->findChild( L"Bone" );
	if ( childNode != NULL )
	{
		Bone = childNode->getString();
	}

	childNode = node->findChild( L"Range" );
	if ( childNode != NULL )
	{
		Range = childNode->getFloat();
	}

	childNode = node->findChild( L"Color" );
	if ( childNode != NULL )
	{
		Color = childNode->getString();
	}

	childNode = node->findChild( L"AttenConst" );
	if ( childNode != NULL )
	{
		AttenConst = childNode->getFloat();
	}

	childNode = node->findChild( L"AttenLinear" );
	if ( childNode != NULL )
	{
		AttenLinear = childNode->getFloat();
	}

	childNode = node->findChild( L"AttenQuad" );
	if ( childNode != NULL )
	{
		AttenQuad = childNode->getFloat();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Light::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Position != L"" )
	{
		childNode = node->addChild( L"Position" );
		childNode->setString( Position );
	}

	if ( Bone != L"" )
	{
		childNode = node->addChild( L"Bone" );
		childNode->setString( Bone );
	}

	if ( Range != 0.0f )
	{
		childNode = node->addChild( L"Range" );
		childNode->setFloat( Range );
	}

	if ( Color != L"" )
	{
		childNode = node->addChild( L"Color" );
		childNode->setString( Color );
	}

	if ( AttenConst != 0.0f )
	{
		childNode = node->addChild( L"AttenConst" );
		childNode->setFloat( AttenConst );
	}

	if ( AttenLinear != 0.0f )
	{
		childNode = node->addChild( L"AttenLinear" );
		childNode->setFloat( AttenLinear );
	}

	if ( AttenQuad != 0.0f )
	{
		childNode = node->addChild( L"AttenQuad" );
		childNode->setFloat( AttenQuad );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Window::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	attribute = node->findAttribute( L"Type" );
	if ( attribute != NULL )
	{
		Type = attribute->getString();
	}

	attribute = node->findAttribute( L"Name" );
	if ( attribute != NULL )
	{
		Name = attribute->getString();
	}

	childNode = node->findFirstChild( L"Property", iter );
	while ( childNode != NULL )
	{
		Properties.resize( Properties.size() + 1 );
		Properties.back().read( childNode );
		childNode = node->findNextChild( L"Property", iter );
	}

	childNode = node->findFirstChild( L"Window", iter );
	while ( childNode != NULL )
	{
		Windows.resize( Windows.size() + 1 );
		Windows.back().read( childNode );
		childNode = node->findNextChild( L"Window", iter );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Window::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Type != L"" )
	{
		attribute = node->addAttribute( L"Type" );
		attribute->setString( Type );
	}

	if ( Name != L"" )
	{
		attribute = node->addAttribute( L"Name" );
		attribute->setString( Name );
	}

	for ( std::vector<Property>::const_iterator iter = Properties.begin();
		  iter != Properties.end();
		  ++iter )
	{
		const Property& obj = *iter;
		childNode = node->addChild( L"Property" );
		obj.write( childNode );
	}

	for ( std::vector<Window>::const_iterator iter = Windows.begin();
		  iter != Windows.end();
		  ++iter )
	{
		const Window& obj = *iter;
		childNode = node->addChild( L"Window" );
		obj.write( childNode );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Property::read( const XmlNode* node )
{
	assert( node != NULL );

	NodeIterator iter;
	const XmlNode* childNode = NULL;
	const XmlAttribute* attribute = NULL;

	attribute = node->findAttribute( L"Name" );
	if ( attribute != NULL )
	{
		Name = attribute->getString();
	}

	attribute = node->findAttribute( L"Value" );
	if ( attribute != NULL )
	{
		Value = attribute->getString();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Property::write( XmlNode* node ) const
{
	assert( node != NULL );

	node->clearChild();
	node->clearAttribute();

	XmlNode* childNode = NULL;
	XmlAttribute* attribute = NULL;

	if ( Name != L"" )
	{
		attribute = node->addAttribute( L"Name" );
		attribute->setString( Name );
	}

	if ( Value != L"" )
	{
		attribute = node->addAttribute( L"Value" );
		attribute->setString( Value );
	}
}

}
