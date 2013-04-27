#pragma once
#include "scene.h"

class UI_API IMsgBoxListner
{
public:
	virtual void OnOK() = 0;
	virtual void OnCancel() = 0;
};
typedef struct _MsgBoxParam
{
	const wchar_t* msg;
	IMsgBoxListner* listner;
}MsgBoxParam;
class UI_API CUIMsgBox :
	public CScene
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUIMsgBox;}
	CUIMsgBox(void);
	~CUIMsgBox(void);
private:
	virtual void OnShow(void* data /* = NULL */);
	virtual void OnLoad();
	void OnOK();
	void OnCancel();
private:
	IMsgBoxListner* mListner;
};
