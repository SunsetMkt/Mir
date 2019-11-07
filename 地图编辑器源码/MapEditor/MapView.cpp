// MapView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapView

IMPLEMENT_DYNCREATE(CMapView, CScrollView)

CMapView::CMapView()
{
	m_lpMainWnd = NULL;
}

CMapView::~CMapView()
{
}


BEGIN_MESSAGE_MAP(CMapView, CScrollView)
	//{{AFX_MSG_MAP(CMapView)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapView drawing

void CMapView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpMapView = this;
}

void CMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMapView diagnostics

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapView message handlers

BOOL CMapView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CMapView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	SCROLLINFO info;
	
    info.cbSize = sizeof(SCROLLINFO);	
    info.fMask = SIF_TRACKPOS;	
	
    if (LOBYTE(nScrollCode) == SB_THUMBTRACK)		
    {		
		GetScrollInfo(SB_HORZ, &info);		
		nPos = info.nTrackPos;		
    }	
	
    if (HIBYTE(nScrollCode) == SB_THUMBTRACK)		
    {		
		GetScrollInfo(SB_VERT, &info);		
		nPos = info.nTrackPos;		
    }
	
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}
