#pragma once
#include "Position.h"
#include "vectorf.h"
#include <vector>
#include "utils.h"
class GRAPHIC_API CPtAlongLine
{
public:
	CPtAlongLine(void);
	~CPtAlongLine(void);
public:
	int X() const { return int(mCurPt[0]); }
	int Y() const { return int(mCurPt[1]); }
	float GetRotation();
	bool Next();
	void Initialize(const CPosition* pts,int ptNum ,float firstDistance,float space);
private:
	bool First(); 
private:
	int mCurIndex;
	float mLeftDis;
	float mSpace;
	std::vector<vectorf<2> >  mPts;
	std::vector<vectorf<2> >  mPts_Src;
	std::vector<vectorf<2> >  mPts_Normalized;
	vectorf<2> mCurPt;
};

