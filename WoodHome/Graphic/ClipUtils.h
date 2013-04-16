#pragma once
#include "Position.h"
class CClipUtils
{
public:
	CClipUtils(int minx ,int miny ,int maxx ,int maxy);
	~CClipUtils(void);
public:	
	bool ClipLine(CPosition& A , CPosition& B);
private:
	bool ClipLineMinX(CPosition& A , CPosition& B);
	bool ClipLineMinY(CPosition& A , CPosition& B);
	bool ClipLineMaxX(CPosition& A , CPosition& B);
	bool ClipLineMaxY(CPosition& A , CPosition& B);
private:
	int mMinX;
	int mMinY;
	int mMaxX;
	int mMaxY;
};

