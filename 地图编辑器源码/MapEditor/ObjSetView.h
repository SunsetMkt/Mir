#if !defined(AFX_OBJSETVIEW_H__B65B5DAF_FA0D_44BB_9198_85A0A406204B__INCLUDED_)
#define AFX_OBJSETVIEW_H__B65B5DAF_FA0D_44BB_9198_85A0A406204B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjSetView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CObjSetView view

class CObjSetView : public CScrollView
{
protected:
	CObjSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjSetView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjSetView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjSetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjSetView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJSETVIEW_H__B65B5DAF_FA0D_44BB_9198_85A0A406204B__INCLUDED_)
