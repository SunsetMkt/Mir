#if !defined(AFX_GRIDVIEW_H__41823591_7A0D_48A2_B972_03D8C154EEAD__INCLUDED_)
#define AFX_GRIDVIEW_H__41823591_7A0D_48A2_B972_03D8C154EEAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridView view

class CGridView : public CScrollView
{
protected:
	CGridView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGridView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGridView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEW_H__41823591_7A0D_48A2_B972_03D8C154EEAD__INCLUDED_)
