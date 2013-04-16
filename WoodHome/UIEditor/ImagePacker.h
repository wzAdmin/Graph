#pragma once
#include "UIFile.h"
#include <map>
namespace slim
{
	class XmlDocument;
	class XmlNode;
}

enum AddError
{
	File_Success,
	File_AlreadyAdded,
	File_NotExsit,
	File_FormatNotSupport
};
enum FileFormat
{
	PNG,
	JPG,
	BMP,
	SCENE,
	LAYER,
	USER,
	NotSupport
};
enum SourceType
{
	SOURCE_IMG,
	SOURCE_SCENE,
	SOURCE_LAYER,
	SOURCE_USER
};
class CImagePacker
{
public:
	CImagePacker(void);
	~CImagePacker(void);
public:
	void Pack();
	void AddFolder(const char* path);
	AddError AddFile(const char* path);
private:
	typedef std::pair<FileFormat ,std::string> FormatPair;
	typedef std::map<FileFormat ,std::string>::iterator FormatIterator;

	void Init();
	FileFormat GetFormat(const char* path);
	AddError Add(const char* filename , const char* format);
	bool Existed(slim::XmlNode* root,const char* filename);
	void GenerateHeader();
	void PackFile();
	SourceType GetSourceType(FileFormat fm);
	const char*	GetPrefixion(int sourcetype);
private:
	slim::XmlDocument* mPacked;
	std::map<FileFormat,std::string> mImageFormats;
};

