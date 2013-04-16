#include "Transfrom.h"
#include <math.h>

CTransfrom::CTransfrom(void):
mScaleY(1.0f),
mScaleX(1.0f),
mAnchorY(0.0f),
mAnchorX(0.0f),
mPositionY(0.0f),
mPositionX(0.0f),
mRotationX(0.0f),
mRotationY(0.0f)
{
	mTransfrom.Normalize();
	mInverse.Normalize();
}


CTransfrom::~CTransfrom(void)
{
}

void CTransfrom::Update()
{
	if(0.0f == mScaleX || 0.0f == mScaleY)
	{
		mTransfrom.Zero();
		mInverse.Zero();
		return ;
	}
	mTransfrom.Normalize();
	mTransfrom *= GetTranslate(-mAnchorX , -mAnchorY);
	mTransfrom *= GetScale(mScaleX , mScaleY);
	mTransfrom *= GetRotation(mRotationX , mRotationY);
	mTransfrom *= GetTranslate(mPositionX , mPositionY);

	mInverse.Normalize();
	mInverse *= GetTranslate(-mPositionX , -mPositionY);
	mInverse *= GetInverseRotation();
	mInverse *= GetScale(1.0f/mScaleX , 1.0f/mScaleY);
	mInverse *= GetTranslate(mAnchorX , mAnchorY);
}

matrixf<3> CTransfrom::GetRotation(float angleX , float angleY)
{
	//顺时针旋转 单位弧度
	matrixf<3> result;
	result.Normalize();
	result[0][0] = cos(angleX);
	result[0][1] = sin(angleY);
	result[1][0] = -sin(angleX);
	result[1][1] = cos(angleY);
	return result;
}

matrixf<3> CTransfrom::GetScale(float scaleX , float sclaeY)
{
	matrixf<3> result;
	result.Normalize();
	result[0][0] = scaleX;
	result[1][1] = sclaeY;
	return result;
}


matrixf<3> CTransfrom::GetTranslate(float x , float y)
{
	matrixf<3> result;
	result.Normalize();
	result[2][0] = x;
	result[2][1] = y;
	return result;
}

vectorf<2> CTransfrom::Transform( float x , float y ) const
{
	return Transform(mTransfrom , x , y);
}

vectorf<2> CTransfrom::Transform( const matrixf<3>& matrix , float x , float y ) const
{
	vectorf<2> result;
	vectorf<3> vec;
	vec[0] = x;
	vec[1] = y;
	vec[2] = 1;
	result.Zero();
	vec = matrix * vec;
	result[0] = vec[0];
	result[1] = vec[1];

	return result;
}

CBound CTransfrom::Transform( const CBound& bound ) const
{
	CBound result;
	vectorf<2> points[4];
	points[0] = Transform(float(bound.Left()) , float(bound.Top()));
	points[1] = Transform(float(bound.Right()) , float(bound.Top())); 
	points[2] = Transform(float(bound.Left()) , float(bound.Bottom()));
	points[3] = Transform(float(bound.Right()) , float(bound.Bottom()));
	result.Left(int(points[0][0]));
	result.Right(int(points[0][0]));
	result.Bottom(int(points[0][1]));
	result.Top(int(points[0][1]));
	for (int i = 1; i < 4 ; i++)
	{
		result.Left( MIN(result.Left() , int(points[i][0])));
		result.Right( MAX(result.Right() , int(points[i][0])));
		result.Bottom( MAX(result.Bottom() , int(points[i][1])));
		result.Top( MIN(result.Top() , int(points[i][1])));
	}
	return result;
}

vectorf<2> CTransfrom::Inverse( float x , float y ) const
{
	return Transform(mInverse , x , y);
}

matrixf<3> CTransfrom::GetInverseRotation()
{
	matrixf<3> result;
	float delta = cos(mRotationX - mRotationY);
	if(.0f ==delta)
	{
		result.Zero();
		return result;
	}
	result.Normalize();
	result[0][0] = cos(mRotationY) / delta;
	result[0][1] = -sin(mRotationY)/ delta;
	result[1][0] = sin(mRotationX)/ delta;
	result[1][1] = cos(mRotationX)/ delta;
	return result;
}
