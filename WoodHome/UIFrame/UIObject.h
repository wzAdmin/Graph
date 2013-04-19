#pragma once
#include "UItype.h"
#include "Bound.h"
#include "IMessageDealer.h"
namespace slim
{
	class XmlNode;
}
class CGraphics;
class UI_API CUIObject : public IMessageDealer
{
public:
	CUIObject(void);
	virtual ~CUIObject(void);
public:
	virtual void Load(const slim::XmlNode* node) ;
	virtual void Draw(CGraphics* pGraphic) = 0;
	virtual void DrawToWindow();
	virtual void OnFocusOut(){}
	void Bound(const CBound& bd){mBound =bd;}
	const CBound& Bound() const {return mBound;}
	bool InputMode() const {return mIsInputMode;}
	void InputMode(bool val);
	void Parent(CUIObject* parent){mParent = parent;}
	CUIObject* Parent() const {return mParent;}
	void Order(int od){mOrder = od;}
	int Order()const{return mOrder;}
	bool Visible()const{return mIsVisible;}
	void Visible(bool val){mIsVisible = val;}
	void Absolute(CBound& bound);
	void ParentToSelf(CBound& bound);
	void SelfToParent(CBound& bound);
	CPosition ParentToSelf(int x ,int y);
	CPosition SelfToParent(int x ,int y);
	CPosition Absolute(int x ,int y);
private:
	int mOrder;
	CUIObject* mParent;
	CBound mBound;
	bool mIsInputMode;
	bool mIsVisible;
};

