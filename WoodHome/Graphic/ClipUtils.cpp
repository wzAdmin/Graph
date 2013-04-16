#include "ClipUtils.h"


CClipUtils::CClipUtils(int minx ,int miny ,int maxx ,int maxy):
mMinX(minx),
mMinY(miny),
mMaxX(maxx),
mMaxY(maxy)
{
}


CClipUtils::~CClipUtils(void)
{
}
bool CClipUtils::ClipLine( CPosition& A , CPosition& B )
{
	if(ClipLineMinX(A,B) && ClipLineMaxX(A , B) 
		&& ClipLineMinY(A ,B) && ClipLineMaxY(A , B))
		return true;
	return false;
}

bool CClipUtils::ClipLineMinX( CPosition& A , CPosition& B )
{
	if(A.X() < mMinX && B.X() < mMinX)
		return false;
	else if(A.X() >= mMinX && B.X() >= mMinX)
		return true;
	else if(A.X() < mMinX)
	{
		A.Y(int(A.Y() - double(A.X() - mMinX) * (A.Y() - B.Y()) / (A.X() - B.X())));
		A.X(mMinX);
		return true;
	}
	else
	{
		B.Y(int(B.Y() - double(B.X() - mMinX) * (B.Y() - A.Y()) / (B.X() - A.X())));
		B.X(mMinX);
		return true;
	}
}

bool CClipUtils::ClipLineMaxX( CPosition& A , CPosition& B )
{
	if(A.X() > mMaxX && B.X() > mMaxX)
		return false;
	else if(A.X() <= mMaxX && B.X() <= mMaxX)
		return true;
	else if(A.X() > mMaxX)
	{
		A.Y(int(A.Y() - double(A.X() - mMaxX) * (A.Y() - B.Y()) / (A.X() - B.X())));
		A.X(mMaxX);
		return true;
	}
	else
	{
		B.Y(int(B.Y() - double(B.X() - mMaxX) * (B.Y() - A.Y()) / (B.X() - A.X())));
		B.X(mMaxX);
		return true;
	}
}

bool CClipUtils::ClipLineMinY( CPosition& A , CPosition& B )
{
	if(A.Y() < mMinY && B.Y() < mMinY)
		return false;
	else if(A.Y() >= mMinY && B.Y() >= mMinY)
		return true;
	else if(A.Y() < 0)
	{
		A.X(int(A.X() - double(A.Y() - mMinY) * (A.X() - B.X()) / (A.Y() - B.Y())));
		A.Y(mMinY);
		return true;
	}
	else
	{
		B.X(int(B.X() - double(B.Y() - mMinY) * (B.X() - A.X()) / (B.Y() - A.Y())));
		B.Y(mMinY);
		return true;
	}
}

bool CClipUtils::ClipLineMaxY( CPosition& A , CPosition& B )
{
	if(A.Y() > mMaxY && B.Y() > mMaxY)
		return false;
	else if(A.Y() <= mMaxY && B.Y() <= mMaxY)
		return true;
	else if(A.Y() > mMaxY)
	{
		A.X(int(A.X() - double(A.Y() - mMaxY) * (A.X() - B.X()) / (A.Y() - B.Y())));
		A.Y(mMaxY);
		return true;
	}
	else
	{
		B.X(int(B.X() - double(B.Y() - mMaxY) * (B.X() - A.X()) / (B.Y() - A.Y())));
		B.Y(mMaxY);
		return true;
	}
}