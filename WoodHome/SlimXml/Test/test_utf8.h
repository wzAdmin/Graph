﻿///////////////////////////////////////////////////////////////////////////////////////////////////
//this file is automatically generated, do not modify.
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __XML_test_utf8_H__
#define __XML_test_utf8_H__

#include "SlimXml.h"
#include <vector>

namespace test_utf8
{
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Property
{
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring Name;
	std::wstring Value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Window
{
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring          Type;
	std::wstring          Name;
	std::vector<Property> Properties;
	std::vector<Window>   Windows;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Light
{
	Light()
		:	Range( 0.0f )
		,	AttenConst( 0.0f )
		,	AttenLinear( 0.0f )
		,	AttenQuad( 0.0f )
	{
	}
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring Position;
	std::wstring Bone;
	float        Range;
	std::wstring Color;
	float        AttenConst;
	float        AttenLinear;
	float        AttenQuad;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Event
{
	Event()
		:	Time( 0.0f )
	{
	}
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	float                     Time;
	std::wstring              Type;
	std::vector<std::wstring> Params;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Animation
{
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring       Slot;
	std::wstring       Filename;
	std::vector<Event> Events;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Part
{
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring Slot;
	std::wstring Filename;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct Model
{
	void read( const slim::XmlNode* node );
	void write( slim::XmlNode* node ) const;

	std::wstring           Skeleton;
	std::vector<Part>      Parts;
	std::vector<Animation> Animations;
	std::vector<Light>     Lights;
	Window                 Window;
};

}

#endif
