#if !defined(AFX_SMALLTILEVIEW_H__3A99D379_2ECB_461A_AE63_B05A2B4ADE72__INCLUDED_)
#define AFX_SMALLTILEVIEW_H__3A99D379_2ECB_461A_AE63_B05A2B4ADE72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallTileView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CSmallTileView view

class CSmallTileView : public CScrollView
{
protected:
	CSmallTileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSmallTileView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmallTileView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSmallTileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSmallTileView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLTILEVIEW_H__3A99D379_2ECB_461A_AE63_B05A2B4ADE72__INCLUDED_)
