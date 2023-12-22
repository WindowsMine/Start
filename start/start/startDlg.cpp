
// startDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "start.h"
#include "startDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CStatic idcstatic;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CstartDlg 对话框



CstartDlg::CstartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_START_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CstartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CstartDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CstartDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CstartDlg 消息处理程序

BOOL CstartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	idcstatic.SubclassDlgItem(IDC_STATIC1, this);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CstartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

string GetFileNameFromPath(const std::string& path)
{
	size_t lastSlash = path.find_last_of("\\/");

	std::string fileName = path.substr(lastSlash + 1);

	size_t lastDot = fileName.find_last_of(".");

	if (lastDot != std::string::npos)
	{
		fileName = fileName.substr(0, lastDot);
	}

	return fileName;
}

void CstartDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT nFilesDropped = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (UINT i = 0; i < nFilesDropped; i++)
	{
		UINT nFilePathLength = DragQueryFile(hDropInfo, i, NULL, 0);

		wchar_t* szFilePath = new wchar_t[nFilePathLength + 1];

		DragQueryFile(hDropInfo, i, szFilePath, nFilePathLength + 1);

		std::wstring wtemp(szFilePath);
		std::string str(wtemp.begin(), wtemp.end());

		std::string str2 = GetFileNameFromPath(str);
		#ifdef UNICODE
				std::wstring wstr2(str2.begin(), str2.end());
				LPCTSTR lpctstr = wstr2.c_str();
		#else
				LPCTSTR lpctstr = str2.c_str();
		#endif 
		
		SetDlgItemText(IDC_EDIT1, lpctstr);
		SetDlgItemText(IDC_EDIT2, szFilePath);

		// 释放缓冲区
		delete[] szFilePath;
	}

	// 结束拖放操作
	DragFinish(hDropInfo);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CstartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CstartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

VOID setstartregedit(wstring programName,wstring programPath)
{
	HKEY hKey;
	const std::wstring subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	if (RegOpenKeyExW(HKEY_CURRENT_USER, subkey.c_str(), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {

		if (RegSetValueExW(hKey, programName.c_str(), 0, REG_SZ, (BYTE*)programPath.c_str(), (programPath.size() + 1) * sizeof(wchar_t)) == ERROR_SUCCESS) {
			wcout << L"。" << endl;
			idcstatic.SetWindowTextW(L"成功将程序添加到注册表启动项");
		}
		else {
			idcstatic.SetWindowTextW(L"无法设置注册表值");
		}

		RegCloseKey(hKey);
	}
	else {
		idcstatic.SetWindowTextW(L"无法打开或创建注册表项");
		return;
	}
}

void CstartDlg::OnBnClickedButton1()
{
	CEdit* a = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString b;
	a->GetWindowText(b);
	CEdit* aa = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString bb;
	aa->GetWindowText(bb);
	setstartregedit((wstring)b, (wstring)bb);
}

void CstartDlg::OnBnClickedButton2()
{
	CEdit* a = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString b;
	a->GetWindowText(b);
	CEdit* aa = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString bb;
	aa->GetWindowText(bb);
	setstartregedit((wstring)b, (wstring)bb);
}