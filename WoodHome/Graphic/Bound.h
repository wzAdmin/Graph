#pragma once
#include "Position.h"
class GRAPHIC_API CBound
{
public:
	CBound(int left = 0,int right = 0,int top = 0 ,int bottom = 0);
	~CBound(void);
public:
	int Left() const { return mLeft; }
	void Left(int val) { mLeft = val; }
	int Right() const { return mRight; }
	void Right(int val) { mRight = val; }
	int Top() const { return mTop; }
	void Top(int val) { mTop = val; }
	int Bottom() const { return mBottom; }
	void Bottom(int val) { mBottom = val; }
public:
	int Width() const {return mRight - mLeft + 1;}
	int Height() const {return mBottom - mTop + 1;}
	bool Contain(int x , int y) const;
	bool Contain(CPosition p) const;
	const CBound& Move(int x, int y);
	static bool Intersect(const CBound& a , const CBound& b ,CBound& dest);
private:
	int mLeft;
	int mRight;
	int mTop;
	int mBottom;
};

