// BilEditor.h : main header file for the BILEDITOR application
//

#if !defined(AFX_BILEDITOR_H__16242BE0_17B1_4289_A24D_7F0E703FE30D__INCLUDED_)
#define AFX_BILEDITOR_H__16242BE0_17B1_4289_A24D_7F0E703FE30D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBilEditorApp:
// See BilEditor.cpp for the implementation of this class
//

class CBilEditorApp : public CWinApp
{
public:
	CBilEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBilEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CBilEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILEDITOR_H__16242BE0_17B1_4289_A24D_7F0E703FE30D__INCLUDED_)
