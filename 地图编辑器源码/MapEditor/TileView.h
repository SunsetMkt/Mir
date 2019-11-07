#if !defined(AFX_TILEVIEW_H__B641A8E3_2B8D_4131_8FC7_86A65AE810D6__INCLUDED_)
#define AFX_TILEVIEW_H__B641A8E3_2B8D_4131_8FC7_86A65AE810D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TileView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CTileView view

class CTileView : public CScrollView
{
protected:
	CTileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTileView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTileView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTileView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TILEVIEW_H__B641A8E3_2B8D_4131_8FC7_86A65AE810D6__INCLUDED_)
