#pragma once
#include "Scene.h"
#include "TimerManager.h"
#include "UIMsgBox.h"

class CStartScene :
	public CScene , public ITimerListener ,public IMsgBoxListner
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CStartScene;}
	CStartScene(void);
	~CStartScene(void);
private:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void OnLoad();
	void OnBtn1Click();
	void OnBtn2Click();
	void OnBtn3Click();
	void OnBtn4Click();
	void OnBtn5Click();
	void OnBtnListClick();
	void OnTimer(TimerID timerid);
private:
	TimerID mtimerid;
};
