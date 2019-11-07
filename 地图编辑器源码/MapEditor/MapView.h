#if !defined(AFX_MAPVIEW_H__52850ED4_E01F_4B8C_96DC_2AF57AF4D1FC__INCLUDED_)
#define AFX_MAPVIEW_H__52850ED4_E01F_4B8C_96DC_2AF57AF4D1FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMapView view

class CMapView : public CScrollView
{
protected:
	CMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMapView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMapView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPVIEW_H__52850ED4_E01F_4B8C_96DC_2AF57AF4D1FC__INCLUDED_)
