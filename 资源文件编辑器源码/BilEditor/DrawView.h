#if !defined(AFX_DRAWVIEW_H__5AD80D34_D1C3_4EF4_8CC1_A94AD3850F3E__INCLUDED_)
#define AFX_DRAWVIEW_H__5AD80D34_D1C3_4EF4_8CC1_A94AD3850F3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawView view

class CDrawView : public CScrollView
{
protected:
	CDrawView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDrawView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDrawView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWVIEW_H__5AD80D34_D1C3_4EF4_8CC1_A94AD3850F3E__INCLUDED_)
