#if !defined(AFX_PROGRESSSTATUSBAR_H__77BF57C3_48D3_47E5_AA21_C1AA22FDC17A__INCLUDED_)
#define AFX_PROGRESSSTATUSBAR_H__77BF57C3_48D3_47E5_AA21_C1AA22FDC17A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar window

class CProgressStatusBar : public CStatusBar
{
// Construction
public:
	CProgressStatusBar();

// Attributes
public:

// Operations
public:
	void SetRange(int nLower, int nUpper);
	int SetPos(int nPos);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgressStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgressStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CProgressCtrl m_wndProgressBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSSTATUSBAR_H__77BF57C3_48D3_47E5_AA21_C1AA22FDC17A__INCLUDED_)
