#if !defined(AFX_SINGLETILEVIEW_H__DE1ADC9B_67A6_45FB_B7B6_8E117E6D659B__INCLUDED_)
#define AFX_SINGLETILEVIEW_H__DE1ADC9B_67A6_45FB_B7B6_8E117E6D659B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SingleTileView.h : header file
//

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CSingleTileView view

class CSingleTileView : public CScrollView
{
protected:
	CSingleTileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSingleTileView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingleTileView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSingleTileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSingleTileView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
	HPEN m_hGridPen;   //绘制格子的灰色画笔
	INT m_iCurrentImg; //当前选择的大地砖索引

	VOID AdjustScrollSize();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLETILEVIEW_H__DE1ADC9B_67A6_45FB_B7B6_8E117E6D659B__INCLUDED_)
