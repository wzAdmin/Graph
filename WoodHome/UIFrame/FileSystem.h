#pragma once
#include "resource_image.h"
enum UIFileFormat
{
	FM_PNG,
	FM_JPG,
	FM_BMP,
	FM_SCENE,
	FM_LAYER,
	FM_USER,
	FM_NotSupport
};
typedef struct _Suorceitem
{
	int offset;
	int length;
	UIFileFormat format;
}Sourceitem;
class CUIFile;
class CFileSystem
{
private:
	CFileSystem(void);
	~CFileSystem(void);
public:
	static CFileSystem& Instance();
	void Open(const char* dataPath);
	Sourceitem GetSource(SourceID id);
	void LoadSource(const Sourceitem& item , char* data);
private:
	CUIFile* mFile;
	char* mIndexData;
};
#define sFilesystem CFileSystem::Instance()

