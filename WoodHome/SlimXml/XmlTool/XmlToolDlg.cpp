// XmlToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XmlTool.h"
#include "XmlToolDlg.h"
#include ".\xmltooldlg.h"
#include "XmlSchema.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CXmlToolDlg 对话框



CXmlToolDlg::CXmlToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXmlToolDlg::IDD, pParent)
	, m_strParSrc(_T(""))
	, m_strParDst(_T(""))
	, m_strGenSrc(_T(""))
	, m_strGenDst(_T(""))
	, m_strPch(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXmlToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PAR_SRC, m_strParSrc);
	DDX_Text(pDX, IDC_EDIT_PAR_DST, m_strParDst);
	DDX_Text(pDX, IDC_EDIT_GEN_SRC, m_strGenSrc);
	DDX_Text(pDX, IDC_EDIT_GEN_DST, m_strGenDst);
	DDX_Text(pDX, IDC_EDIT_PCH, m_strPch);
}

BEGIN_MESSAGE_MAP(CXmlToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PAR_BRS, OnBnClickedButtonParBrs)
	ON_BN_CLICKED(IDC_BUTTON_PARSE, OnBnClickedButtonParse)
	ON_BN_CLICKED(IDC_BUTTON_GEN_BRS, OnBnClickedButtonGenBrs)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CXmlToolDlg 消息处理程序

BOOL CXmlToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef UNICODE
	m_strParSrc = L"../Test/test_utf8.xml";
	m_strParDst = L"../Test/test_utf8_schema";
	m_strGenSrc = L"../Test/test_utf8_schema.xml";
	m_strGenDst = L"../Test/test_utf8";
#else
	m_strParSrc = "../Test/test_gb2312.xml";
	m_strParDst = "../Test/test_gb2312_schema";
	m_strGenSrc = "../Test/test_gb2312_schema.xml";
	m_strGenDst = "../Test/test_gb2312";
#endif
	//m_strPch = TEXT("Stdafx");
	UpdateData( FALSE );

#ifdef UNICODE
	::SetWindowTextW( m_hWnd, L"XmlTool_Unicode" );
#else
	::SetWindowTextA( m_hWnd, "XmlTool_Multibyte" );
#endif

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CXmlToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXmlToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CXmlToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CXmlToolDlg::OnBnClickedButtonParBrs()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = TEXT("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");

	CFileDialog dlg( TRUE, TEXT("xml"), m_strParSrc, 0, szFilter );
	if ( IDOK == dlg.DoModal() )
	{
		m_strParSrc = dlg.GetPathName();
		m_strParDst = dlg.GetFileTitle();
		m_strParDst += TEXT("_schema");
		m_strGenSrc = m_strParDst;
		m_strGenDst = m_strGenSrc;
		m_strGenSrc += TEXT(".xml");
		UpdateData( FALSE );
	}
}

void CXmlToolDlg::OnBnClickedButtonParse()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	slim::XmlDocument src;
	if ( !src.loadFromFile( m_strParSrc ) )
	{
		::MessageBox( NULL, TEXT("Source file not found or bad XML file."), TEXT("Parsing error"), MB_ICONERROR | MB_OK );
		return;
	}

	slim::XmlSchema dst;
	if ( !dst.constructFromXml( &src ) )
	{
		::MessageBox( NULL, TEXT("Failed in parsing structure from XML file."), TEXT("Parsing error"), MB_ICONERROR | MB_OK );
		return;
	}
	m_strParDst += TEXT(".xml");
	if ( !dst.save( m_strParDst ) )
	{
		::MessageBox( NULL, TEXT("Failed in saving structure file.\nPlease check if the existing file is read only."), TEXT("Parsing error"), MB_ICONERROR | MB_OK );
		return;
	}
	else
	{
		::MessageBox( NULL, TEXT("Done."), TEXT("Parsing finished"), MB_ICONINFORMATION | MB_OK );
	}
}

void CXmlToolDlg::OnBnClickedButtonGenBrs()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = TEXT("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");

	CFileDialog dlg( TRUE, TEXT("xml"), m_strGenSrc, 0, szFilter );
	if ( IDOK == dlg.DoModal() )
	{
		m_strGenSrc = dlg.GetPathName();
		m_strGenDst = dlg.GetFileTitle();
		UpdateData( FALSE );
	}
}

void CXmlToolDlg::OnBnClickedButtonGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	slim::XmlSchema dst;
	if ( !dst.loadFromFile( m_strGenSrc ) )
	{
		::MessageBox( NULL, TEXT("Source file not found or bad structure XML file."), TEXT("Generating error"), MB_ICONERROR | MB_OK );
		return;
	}
	CString pchFilename;
	const TCHAR* pchPointer = NULL;
	if ( m_strPch.GetLength() > 0 )
	{
		pchFilename = m_strPch + TEXT(".h");
		pchPointer = pchFilename;
	}
	if ( !dst.generateCode( m_strGenDst, pchPointer ) )
	{
		::MessageBox( NULL, TEXT("Failed in generating code."), TEXT("Generating error"), MB_ICONERROR | MB_OK );
		return;
	}
	else
	{
		::MessageBox( NULL, TEXT("Done."), TEXT("Generating finished"), MB_ICONINFORMATION | MB_OK );
	}
}

