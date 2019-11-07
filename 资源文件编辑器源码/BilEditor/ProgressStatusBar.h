#if !defined(AFX_PROGRESSSTATUSBAR_H__90803E5A_78B0_4AEA_BB55_445914A7D590__INCLUDED_)
#define AFX_PROGRESSSTATUSBAR_H__90803E5A_78B0_4AEA_BB55_445914A7D590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar window

class CProgressStatusBar : public CStatusBar
{
// Construction
public:
	CProgressStatusBar();

// Attributes
public:

// Operations
public:
	void SetRange(int nLower, int nUpper); //������������ý�������Χ�ġ���
	int SetPos(int nPos); //������������ý��������ȵġ���

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgressStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgressStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CProgressCtrl m_wndProgressBar; //������ǽ�������Ŷ����
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSSTATUSBAR_H__90803E5A_78B0_4AEA_BB55_445914A7D590__INCLUDED_)
