// ProgressStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "BilEditor.h"
#include "ProgressStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar

CProgressStatusBar::CProgressStatusBar()
{
}

CProgressStatusBar::~CProgressStatusBar()
{
}

void CProgressStatusBar::SetRange(int nLower, int nUpper)
{
	m_wndProgressBar.SetRange32(nLower, nUpper);
}

int CProgressStatusBar::SetPos(int nPos)
{
    MSG msg;
	
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//处理Windows消息, 使界面不会假死
    {	
		if (msg.message == WM_QUIT)
		{
			exit(0);
			return 0;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
    }
	
    if (nPos == 0)	//如果进度为0则隐藏进度条
    {
		m_wndProgressBar.ShowWindow(SW_HIDE);
    }
    else //否则则显示进度条
    {
		m_wndProgressBar.ShowWindow(SW_SHOW);
    }
    return m_wndProgressBar.SetPos(nPos); //然后设置进度, 然后返回上一次的进度位置。。
}

BEGIN_MESSAGE_MAP(CProgressStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CProgressStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar message handlers

int CProgressStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_wndProgressBar.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 1);
	
	return 0;
}

void CProgressStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//这个是用来设置进度条的尺寸的。。他跟状态栏的第一个状态项的尺寸一致
	CRect rect;
    GetItemRect(0, rect);   //获取状态栏第一个状态项的尺寸
    m_wndProgressBar.MoveWindow(rect, FALSE); //然后设置进度条的尺寸。。。
}
