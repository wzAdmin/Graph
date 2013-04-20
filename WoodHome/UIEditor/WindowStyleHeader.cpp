#include "StdAfx.h"
#include "WindowStyleHeader.h"
#include "SlimXml.h"
#include "UIFile.h"
#include <fstream>

CWindowStyleHeader::CWindowStyleHeader(void)
{
}


CWindowStyleHeader::~CWindowStyleHeader(void)
{
}

void CWindowStyleHeader::GenerateHeader( const char* filePath )
{
	slim::XmlDocument doc;
	doc.loadFromFile(filePath);
	slim::NodeIterator it;
	slim::XmlNode* root = doc.getFirstChild(it);
	slim::XmlNode* child = root->getFirstChild(it);
	std::ofstream ofs("window_Style.h",std::ios::out);
	ofs<<"//this file is auto generated ! do not edit"<<std::endl;
	ofs<<"#pragma once"<<std::endl;
	ofs<<"enum Style_Window"<<std::endl;
	ofs<<"{"<<std::endl;
	ofs<<"	Invalid_Style = 0,"<<std::endl;
	while (child)
	{
		ofs<<"	"<<child->readAttributeAsString("name");
		ofs<<" = "<<child->readAttributeAsInt("id")<<","<<std::endl;
		child = root->getNextChild(it);
	}
	ofs<<"};"<<std::endl;
}
