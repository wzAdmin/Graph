#pragma once
#include "matrix.h"
#include "Bound.h"
class GRAPHIC_API CTransfrom
{
public:
	CTransfrom(void);
	~CTransfrom(void);
public:
	// Rotation 正为顺时针 单位为弧度
	void SetRotation(float skewx ,float skewy){mRotationX = skewx ; mRotationY = skewy;}

	void SetRotation(float angle){mRotationX = mRotationY = angle;}

	void SetPosition(float x, float y){mPositionX = x; mPositionY = y;}

	void SetScale(float scaleX , float scaleY){mScaleX = scaleX ; mScaleY = scaleY;}

	void SetAnchorPoint(float x ,float y){mAnchorX = x ; mAnchorY = y;}

	void Update();

	inline vectorf<2> Transform(float x , float y ) const;

	inline vectorf<2> Inverse(float x , float y) const;

	CBound Transform(const CBound& bound) const;

	const matrixf<3>& Inverse() const{return mInverse ;}

	const matrixf<3>& Transfrom() const { return mTransfrom; }
private:
	inline vectorf<2> Transform(const matrixf<3>& matrix , float x , float y) const;
	matrixf<3> GetRotation(float angleX , float angleY);
	matrixf<3> GetScale(float scaleX , float sclaeY);
	matrixf<3> GetTranslate(float x , float y);
	matrixf<3> GetInverseRotation();
private:
	float mPositionX;
	float mPositionY;
	float mAnchorX;
	float mAnchorY;
	float mScaleX;
	float mScaleY;
	float mRotationX;
	float mRotationY;
	matrixf<3> mTransfrom;
	matrixf<3> mInverse;
};

