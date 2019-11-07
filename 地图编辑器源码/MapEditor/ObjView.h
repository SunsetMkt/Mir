#if !defined(AFX_OBJVIEW_H__54292E3B_3511_4D12_B46E_1A2C817E3AC2__INCLUDED_)
#define AFX_OBJVIEW_H__54292E3B_3511_4D12_B46E_1A2C817E3AC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjView.h : header file
//

#include "MainFrm.h"

#define OBJCOMBOWIDTH 100

/////////////////////////////////////////////////////////////////////////////
// CObjView view

class CObjView : public CScrollView
{
protected:
	CObjView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjView)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeObjCombo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMainFrame* m_lpMainWnd;
	CComboBox m_cbObj;  //ComboBox控件类
	INT m_iCurrentObj;  //当前选择的Objects文件
	INT m_iCurrentImg;  //当前选择的图片索引
	HPEN m_hGridPen;    //绘制格子的灰色画笔

	VOID AdjustScrollSize();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJVIEW_H__54292E3B_3511_4D12_B46E_1A2C817E3AC2__INCLUDED_)
