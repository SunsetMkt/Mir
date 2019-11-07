#if !defined(AFX_SINGLESMALLTILEVIEW_H__DCD384C4_0D9F_4F7C_9EDD_2884C9F5E3A5__INCLUDED_)
#define AFX_SINGLESMALLTILEVIEW_H__DCD384C4_0D9F_4F7C_9EDD_2884C9F5E3A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SingleSmallTileView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CSingleSmallTileView view

class CSingleSmallTileView : public CScrollView
{
protected:
	CSingleSmallTileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSingleSmallTileView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingleSmallTileView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSingleSmallTileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSingleSmallTileView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
	HPEN m_hGridPen;
	INT m_iCurrentImg;

	VOID AdjustScrollSize();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLESMALLTILEVIEW_H__DCD384C4_0D9F_4F7C_9EDD_2884C9F5E3A5__INCLUDED_)
