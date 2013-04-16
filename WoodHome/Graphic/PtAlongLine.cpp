#include "PtAlongLine.h"


CPtAlongLine::CPtAlongLine(void):
mCurIndex(0),
mLeftDis(0.0f),
mSpace(0.0f)
{
}


CPtAlongLine::~CPtAlongLine(void)
{
}

bool CPtAlongLine::Next()
{
	if(mLeftDis > mSpace)
	{
		mLeftDis-=mSpace;
		mCurPt +=  (mPts_Normalized[mCurIndex] * mSpace);
		return true;
	}
	if(mLeftDis > 0)
		mLeftDis-=mSpace;
	return First();
}

void CPtAlongLine::Initialize( const CPosition* pts,int ptNum ,float firstDistance,float space )
{
	assert(space > 0);
	mSpace = space;
	mPts.clear();
	mPts_Src.clear();
	mPts_Normalized.clear();
	mCurIndex = -1;
	mLeftDis = -firstDistance;
	while (mLeftDis > 0)
	{
		mLeftDis -= space;
	}
	vectorf<2> pt;
	pt[0] = float(pts[0].X());
	pt[1] = float(pts[0].Y());
	mPts_Src.push_back(pt);
	for (int i = 1 ;i < ptNum ; i++)
	{
		pt[0] = float(pts[i].X() - pts[i-1].X());
		pt[1] = float(pts[i].Y() - pts[i-1].Y());
		mPts.push_back(pt);
		mPts_Normalized.push_back(pt.Normalize());
		pt[0] = float(pts[i].X());
		pt[1] = float(pts[i].Y());
		mPts_Src.push_back(pt);
	}
}

bool CPtAlongLine::First()
{
	while (mLeftDis <= 0 && mCurIndex < int(mPts.size() - 1))
	{
		mCurIndex++;
		mLeftDis += mPts[mCurIndex].Length();
	}
	if(mLeftDis < 0)
		return false;
	else
	{
		float dis = mPts[mCurIndex].Length() - mLeftDis;
		mCurPt = mPts_Src[mCurIndex] + (mPts_Normalized[mCurIndex] * dis);
		return true;
	}
}

float CPtAlongLine::GetRotation()
{
	if(mPts_Normalized[mCurIndex][0] == 0.0f )
	{
		if(mPts_Normalized[mCurIndex][1] > 0)
			return MATH_PI / 2;
		else
			return -MATH_PI / 2;
	}
	float angle = atan(mPts_Normalized[mCurIndex][1] / mPts_Normalized[mCurIndex][0]);
	if(mPts_Normalized[mCurIndex][1] > 0)
	{
		if(angle > 0)
			return angle;
		else
			return angle + MATH_PI;
	}
	else
	{
		if(angle > 0)
			return angle + MATH_PI;
		else
			return angle;
	}
}
