// MapEditor.h : main header file for the MAPEDITOR application
//

#if !defined(AFX_MAPEDITOR_H__B8708C57_8522_47D1_830B_A68DC066BC58__INCLUDED_)
#define AFX_MAPEDITOR_H__B8708C57_8522_47D1_830B_A68DC066BC58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapEditorApp:
// See MapEditor.cpp for the implementation of this class
//

class CMapEditorApp : public CWinApp
{
public:
	CMapEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMapEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITOR_H__B8708C57_8522_47D1_830B_A68DC066BC58__INCLUDED_)
