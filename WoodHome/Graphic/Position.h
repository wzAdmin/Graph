#pragma once
#include "GraphicType.h"
#include "vectorf.h"
class GRAPHIC_API CPosition
{
public:
	CPosition( int x = 0, int y = 0);
	~CPosition(void);
public:
	void X(int x){mX = x;}
	void Y(int y){mY = y;}
	int X()const{return mX;}
	int Y()const{return mY;}
	void TransposeXY()
	{
		mX ^= mY;
		mY ^= mX;
		mX ^= mY;
	}
	 operator vectorf<2>()
	{
		vectorf<2> result;
		result[0] = float(mX);
		result[1] = float(mY);
		return result;
	}
	static void inline Swap(CPosition& a , CPosition& b)
	{
		a.mX ^= b.mX;
		b.mX ^= a.mX;
		a.mX ^= b.mX;
		a.mY ^= b.mY;
		b.mY ^= a.mY;
		a.mY ^= b.mY;
	}
private:
	int mX;
	int mY;
};

