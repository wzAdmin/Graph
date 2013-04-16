#include "StdAfx.h"
#include "ImagePacker.h"
#include "SlimXml.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <Windows.h>

#define ImageXML "Image.xml"
#define ImageFolder "Image"

/*
<Image Count="2">
<Item  Format="png" name="image1"  SourceType="3"/>
<Item  Format="jpg" name="image2"  SourceType="3"/>
</Image>
*/
CImagePacker::CImagePacker(void)
{
	Init();
}


CImagePacker::~CImagePacker(void)
{
}

void CImagePacker::Pack()
{
	mPacked->save(ImageXML);
	GenerateHeader();
	PackFile();
}

void CImagePacker::AddFolder( const char* path )
{
	wchar_t wcsPath[MAX_PATH] = {0};
	mbstowcs(wcsPath,path,MAX_PATH);
	wcscat(wcsPath,L"/*");
	WIN32_FIND_DATA filefinddata;
	HANDLE hFind = FindFirstFile(wcsPath,&filefinddata);
	BOOL success = hFind != INVALID_HANDLE_VALUE;
	while (success)
	{
		if(FILE_ATTRIBUTE_DIRECTORY != filefinddata.dwFileAttributes)
		{
			char name[MAX_PATH] = {0};
			char filepath[MAX_PATH] = {0};
			wcstombs(name,filefinddata.cFileName,MAX_PATH);
			strncpy(filepath,path,strlen(path));
			strcat(filepath,"\\");
			strcat(filepath,name);
			AddFile(filepath);
		}
		success = FindNextFile(hFind,&filefinddata);
	}
}

AddError CImagePacker::AddFile( const char* path )
{
	CUIFile file;
	if(!file.Open(path,"rb"))
	{
		return File_NotExsit;
	}
	file.Close();
	std::string strPath(path);
	int pos = strPath.rfind('.');
	std::string format = strPath.substr(pos + 1,strPath.size() - pos - 1);
	std::transform(format.begin(), format.end(), format.begin(), tolower);
	int pos1 = strPath.rfind('\\');
	std::string strName = strPath.substr(pos1 + 1,pos - pos1 - 1);
	if(-1 == pos || pos <= pos1)
	{
		if(pos == pos1)
			return Add(path,"");
		else
			return Add(strName.c_str(),"");
	}
	return Add(strName.c_str() , format.c_str());
}

void CImagePacker::Init()
{
	mImageFormats.insert(FormatPair(PNG , "png"));
	mImageFormats.insert(FormatPair(JPG , "jpg"));
	mImageFormats.insert(FormatPair(BMP , "bmp"));
	mImageFormats.insert(FormatPair(SCENE , "scene"));
	mImageFormats.insert(FormatPair(LAYER , "layer"));
	mPacked = new slim::XmlDocument();
	mPacked->loadFromFile(ImageXML);
	slim::NodeIterator rootit;
	slim::XmlNode* root =mPacked->getFirstChild(rootit);
	if(!root)
	{
		root = mPacked->addChild("Image");
		root->addAttribute("Count",0);
	}
}

AddError CImagePacker::Add( const char* filename , const char* format )
{
	slim::NodeIterator rootit;
	slim::XmlNode* root =mPacked->getFirstChild(rootit);
	if(Existed(root,filename))
		return File_AlreadyAdded;
	slim::XmlAttribute* attr = root->findAttribute("Count");
	int Count = attr->getInt();
	attr->setInt(++Count);
	slim::XmlNode* node = root->addChild("Item");
	node->addAttribute("Format",format);
	node->addAttribute("name",filename);
	node->addAttribute("SourceType",GetSourceType(GetFormat(format)));
	return File_Success;
}

bool CImagePacker::Existed(slim::XmlNode* root, const char* filename )
{
	std::string strName(filename);
	slim::NodeIterator nodeit;
	slim::XmlNode* child = root->findFirstChild("Item",nodeit);
	for( ; child ; child = root->getNextChild(nodeit))
	{
		if(strName == child->readAttributeAsString("name"))
			return true;
	}
	return false;
}

void CImagePacker::GenerateHeader()
{
	std::ofstream ofs("resource_image.h",std::ios::out);
	ofs<<"//this file is auto generated ! do not edit"<<std::endl;
	ofs<<"#pragma once"<<std::endl;
	ofs<<"enum SourceID"<<std::endl;
	ofs<<"{"<<std::endl;
	ofs<<"	Invalid = 0,"<<std::endl;
	slim::NodeIterator rootit;
	slim::XmlNode* root =mPacked->getFirstChild(rootit);
	slim::NodeIterator nodeit;
	slim::XmlNode* child = root->findFirstChild("Item",nodeit);
	for(int ID = 1 ; child ; child = root->getNextChild(nodeit),ID++)
	{
		ofs<<GetPrefixion(child->readAttributeAsInt("SourceType"))<<child->readAttributeAsString("name")<<" = "
			<<ID<<","<<std::endl;
	}
	ofs<<"};"<<std::endl;
}

void CImagePacker::PackFile()
{
	std::ofstream ofs("Out\\Image",std::ios::out | std::ios::binary);
	slim::NodeIterator rootit;
	slim::XmlNode* root =mPacked->getFirstChild(rootit);
	slim::NodeIterator nodeit;
	slim::XmlNode* child = root->findFirstChild("Item",nodeit);
	std::vector<std::string> Files;
	slim::XmlAttribute* attr = root->findAttribute("Count");
	int Count = attr->getInt();
	char* indexData = new char[Count * 9];
	ofs.write((char*)&Count,4);
	Files.resize(Count);
	int offset = Count * 9 + 4;

	for(int index = 0 ; child ; child = root->getNextChild(nodeit),index++)
	{
		CUIFile file;
		std::string filename = child->readAttributeAsString("name");
		std::string strfm = child->readAttributeAsString("Format");
		if(strfm.size())
		{
			filename += ".";
			filename += strfm;
		}
		file.Open(filename.c_str() ,"rb");
		Files[index] = filename;
		int length = file.Length();
		FileFormat fm = GetFormat(child->readAttributeAsString("Format"));
		memcpy(indexData + 9*index,&offset,4);
		memcpy(indexData + 9*index + 4,&length,4);
		indexData[9*index + 8] = char(fm);
		offset += length;
	}
	ofs.write(indexData,9*Count);
	delete[] indexData;
	for (unsigned int i= 0 ;i < Files.size() ; i++)
	{
		CUIFile file;
		file.Open(Files[i].c_str(),"rb");
		int filelen = file.Length();
		char* pdata = new char[filelen];
		file.Read(pdata,0,filelen);
		ofs.write(pdata,filelen);
		delete[] pdata;
	}
}

FileFormat CImagePacker::GetFormat( const char* path )
{
	FormatIterator it = mImageFormats.begin();
	for (  ; mImageFormats.end() != it; it++)
	{
		if(it->second == path)
			return it->first;
	}
	return NotSupport;
}

SourceType CImagePacker::GetSourceType( FileFormat fm )
{
	switch (fm)
	{
	case PNG:
	case JPG:
	case BMP:
		return SOURCE_IMG;
	case SCENE:
		return SOURCE_SCENE;
	case LAYER:
		return SOURCE_LAYER;
	default:
		;
	}
	return SOURCE_USER;
}

const char* CImagePacker::GetPrefixion( int sourcetype )
{
	switch(sourcetype)
	{
	case SOURCE_IMG:
		return "	IMG_";
	case SOURCE_LAYER:
		return "	LAYER_";
	case SOURCE_SCENE:
		return "	SCENE_";
	case SOURCE_USER:
		return "	USER_";
	}
	return "	USER_";
}
