#include "Graphics.h"
#include <vector>
#include <algorithm>
#include "Trace.h"
#include "utils.h"

class CEdge
{
public:
	CEdge(){}
	~CEdge(){}
	void Set(const CPosition& A , const CPosition& B)
	{
		if (A.Y() > B.Y())
		{
			mA = B;
			mB = A;
		}
		else
		{
			mA = A;
			mB = B;
		}
		if(mA.Y() !=  mB.Y())
			mdeltaX = double(mA.X() - mB.X()) / (mA.Y() - mB.Y());
	}
public:
	inline bool Intersect(int& x , int y)
	{
		if(y < mA.Y() || y > mB.Y() || mB.Y() == mA.Y())
			return false;
		if(y == mA.Y())
		{
			x = mA.X();
			mCurX = x;
			return true;
		}
		mCurX += mdeltaX;
		x = Double2Int(mCurX);
		return true;
	}
private:
	CPosition mA;
	CPosition mB;
	double mdeltaX;
	double mCurX;
};


void CGraphics::Polygon(const CPosition* points , int pointCount,COLORARGB color)
{
	if(!points || pointCount < 3)
		return;
	unsigned short color565 = RGB888ToRGB565(color);
	CEdge* edges = NEW_LEAKCHECK CEdge[pointCount];
	std::vector<int> Xcoordinates;
	Xcoordinates.resize(pointCount);
	int minY = points[0].Y() ,maxY = points[0].Y();
	for (int i = 0; i < pointCount ; i++)
	{
		if(i == pointCount - 1)
			edges[i].Set(points[0] , points[i]);
		else
			edges[i].Set(points[i + 1] , points[i]);
		if(points[i].Y() < minY)
			minY = points[i].Y();
		if(points[i].Y() > maxY)
			maxY = points[i].Y();
	}
	minY = minY < mClip->mMinY ? mClip->mMinY : minY;
	maxY = maxY > mClip->mMaxY ? mClip->mMaxY : maxY;
	for(int j = minY ; j < maxY + 1 ; j++)
	{
		int xcount= 0;
		for (int i = 0 ;i < pointCount ; i++)
		{
			if(edges[i].Intersect(Xcoordinates[xcount],j))
				xcount++;
		}
		if(xcount > 1)
		{
			std::sort(Xcoordinates.begin(),Xcoordinates.begin() + xcount);
			for (int i = 0;i < xcount - 1 ; i+=2)
			{
				int minX = Xcoordinates[i] < mClip->mMinX ? mClip->mMinX : Xcoordinates[i];
				int maxX = Xcoordinates[i+1] > mClip->mMaxX ? mClip->mMaxX : Xcoordinates[i+1];
				mem_set(mpFrambuffer + Stride() * j + minX,maxX - minX + 1,&color565,1);
			}
		}
	}
	DELETEARR_LEAKCHECK (edges);
}