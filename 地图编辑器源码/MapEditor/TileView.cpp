// TileView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "TileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTileView

IMPLEMENT_DYNCREATE(CTileView, CScrollView)

CTileView::CTileView()
{
	m_lpMainWnd = NULL;
}

CTileView::~CTileView()
{
}


BEGIN_MESSAGE_MAP(CTileView, CScrollView)
	//{{AFX_MSG_MAP(CTileView)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTileView drawing

void CTileView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpTileView = this;
}

void CTileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTileView diagnostics

#ifdef _DEBUG
void CTileView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTileView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTileView message handlers

BOOL CTileView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CTileView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
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
