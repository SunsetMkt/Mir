// SmallTileView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "SmallTileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmallTileView

IMPLEMENT_DYNCREATE(CSmallTileView, CScrollView)

CSmallTileView::CSmallTileView()
{
	m_lpMainWnd = NULL;
}

CSmallTileView::~CSmallTileView()
{
}


BEGIN_MESSAGE_MAP(CSmallTileView, CScrollView)
	//{{AFX_MSG_MAP(CSmallTileView)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmallTileView drawing

void CSmallTileView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpSmallTileView = this; //这里需要修改为SmallTileView
}

void CSmallTileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSmallTileView diagnostics

#ifdef _DEBUG
void CSmallTileView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSmallTileView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmallTileView message handlers

BOOL CSmallTileView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CSmallTileView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
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
