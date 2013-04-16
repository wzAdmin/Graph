﻿// XmlToolDlg.h : 头文件
//

#pragma once


// CXmlToolDlg 对话框
class CXmlToolDlg : public CDialog
{
// 构造
public:
	CXmlToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XMLTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strParSrc;
	CString m_strParDst;
	CString m_strGenSrc;
	CString m_strGenDst;
	afx_msg void OnBnClickedButtonParBrs();
	afx_msg void OnBnClickedButtonParse();
	afx_msg void OnBnClickedButtonGenBrs();
	afx_msg void OnBnClickedButtonGenerate();
	CString m_strPch;
};
