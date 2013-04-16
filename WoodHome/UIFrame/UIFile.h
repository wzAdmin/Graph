#pragma once
#include "UItype.h"
#include <stdio.h>
class UI_API CUIFile
{
public:
	CUIFile(void);
	CUIFile(const char* path,const char* mode);
	~CUIFile(void);
public:
	bool Open(const char* path ,const char* mode);
	void Read(void* pData , int offset , int length);
	void Close();
	int Length();
private:
	FILE* mFile;
};

