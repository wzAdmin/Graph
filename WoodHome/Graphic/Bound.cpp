#include "Bound.h"

CBound::CBound( int left /*= 0*/,int right /*= 0*/,int top /*= 0 */,int bottom /*= 0*/ ):
mLeft(left),
mRight(right),
mTop(top),
mBottom(bottom)
{

}

CBound::~CBound(void)
{
}

bool CBound::Contain( CPosition p ) const
{
	return Contain(p.X() , p.Y());
}

bool CBound::Contain( int x , int y ) const
{
	return !(x < mLeft || x > mRight || y < mTop || y > mBottom ) ;
}

bool CBound::Intersect( const CBound& a , const CBound& b ,CBound& dest )
{
	dest.mLeft = MAX(a.mLeft,b.mLeft);
	dest.mRight = MIN(a.mRight,b.mRight);
	dest.mTop = MAX(a.mTop,b.mTop);
	dest.mBottom = MIN(a.mBottom,b.mBottom);
	return dest.mLeft <= dest.mRight && dest.mTop <= dest.mBottom;
}

const CBound& CBound::Move( int x, int y )
{
	mBottom +=y;
	mTop +=y;
	mLeft +=x;
	mRight +=x;
	return (*this);
}


