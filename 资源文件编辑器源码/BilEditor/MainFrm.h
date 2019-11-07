// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__975BB44F_F8C1_419B_9074_B235337FDFE9__INCLUDED_)
#define AFX_MAINFRM_H__975BB44F_F8C1_419B_9074_B235337FDFE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProgressStatusBar.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNewfile();
	afx_msg void OnOpenfile();
	afx_msg void OnSavefile();
	afx_msg void OnImportimg();
	afx_msg void OnExportimg();
	afx_msg void OnBatchimportimg();
	afx_msg void OnBatchexportimg();
	afx_msg void OnModoffset();
	afx_msg void OnDelimg();
	afx_msg void OnCut();
	afx_msg void OnPaste();
	afx_msg void OnDrawtransparent();
	afx_msg void OnDrawcoord();
	afx_msg void OnDrawoffset();
	afx_msg void OnPreimg();
	afx_msg void OnNextimg();
	afx_msg void OnAutoplay();
	afx_msg void OnPauseimg();
	afx_msg void OnGotoimg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HICON m_hIcon; //这个是程序图标
	CSplitterWnd m_wndSplitter; //这个是用来分割视图的
	BOOL m_bSplitterCreated; //这个是用来判断是否已经分割视图
	HBITMAP m_hToolBarBitmap; //工具栏图片句柄
	CToolBar m_wndToolBar;
	CProgressStatusBar  m_wndStatusBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__975BB44F_F8C1_419B_9074_B235337FDFE9__INCLUDED_)
