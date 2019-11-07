// ProgressStatusBar.cpp : implementation file
//

#include "stdafx.h"
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

	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{	
		if (msg.message == WM_QUIT)
		{
			exit(0);
			return 0;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (nPos == 0)
	{
		m_wndProgressBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_wndProgressBar.ShowWindow(SW_SHOW);
	}
	return m_wndProgressBar.SetPos(nPos);
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
	CRect rect;
	GetItemRect(0, rect);
	m_wndProgressBar.MoveWindow(rect, FALSE);
}
