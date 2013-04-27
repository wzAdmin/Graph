#pragma once
#include "UItype.h"
#include "Bound.h"
#include "IMessageDealer.h"
#include <string>
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
	virtual void DrawToWindow(const CBound* bd = NULL);
	virtual void OnFocusOut(){}
	CUIObject* operator [] (const std::string& name){return get(name);}
	void Bound(const CBound& bd){mBound =bd;}
	const CBound& Bound() const {return mBound;}
	bool InputMode() const {return mIsInputMode;}
	void InputMode(bool val);
	void Parent(CUIObject* parent){mParent = parent;}
	CUIObject* Parent() const {return mParent;}
	void Order(int od){mOrder = od;}
	int Order()const{return mOrder;}

	//
	//why there is IsRealVisible ? 
	//function Visible is just return the visible attribute of itself.
	//it is maybe hidden even if the mIsVisible is true as it's parent
	//or parent's parent and so on is hidden.
	//so IsRealVisible returns the object is showing or hiding indeed.
	bool IsRealVisible();

	bool Visible()const{return mIsVisible;}
	void Visible(bool val){mIsVisible = val;}


	void Absolute(CBound& bound);
	void ParentToSelf(CBound& bound);
	void SelfToParent(CBound& bound);
	CPosition ParentToSelf(int x ,int y);
	CPosition SelfToParent(int x ,int y);
	CPosition Absolute(int x ,int y);
	const std::string& Name() const {return mName;}
protected:
	virtual CUIObject* get(const std::string& name){return NULL;}
private:
	std::string mName;
	int mOrder;
	CUIObject* mParent;
	CBound mBound;
	bool mIsInputMode;
	bool mIsVisible;
};

