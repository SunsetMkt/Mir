// SingleSmallTileView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "SingleSmallTileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSingleSmallTileView

IMPLEMENT_DYNCREATE(CSingleSmallTileView, CScrollView)

CSingleSmallTileView::CSingleSmallTileView()
{
	m_lpMainWnd = NULL;
	m_hGridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
	m_iCurrentImg = 0;
}

CSingleSmallTileView::~CSingleSmallTileView()
{
	DeleteObject(m_hGridPen);
}


BEGIN_MESSAGE_MAP(CSingleSmallTileView, CScrollView)
	//{{AFX_MSG_MAP(CSingleSmallTileView)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSingleSmallTileView drawing

void CSingleSmallTileView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpSingleSmallTileView = this;
		
	AdjustScrollSize();
}

void CSingleSmallTileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	//基本跟上面的一样, 我就不多说了
	RECT rect;
	CPoint point;
	INT iStartRow, iEndRow;
	INT iStartCol, iEndCol;
	INT i, j;
	HPEN hOldPen = (HPEN)pDC->SelectObject(m_hGridPen);
	INT iImageIndex = 0;
	
	GetClientRect(&rect);
	point = GetScrollPosition();
	rect.left += point.x;
	rect.top += point.y;
	rect.right += point.x;
	rect.bottom += point.y;
	iStartCol = rect.left/(UNITX + 1) < 4 ? rect.left/(UNITX + 1) : 4 - 1;
	iEndCol = rect.right/(UNITX + 1) < 4 ? rect.right/(UNITX + 1) : 4 - 1;
	iStartRow = rect.top/(UNITY + 1);
	iEndRow = rect.bottom/(UNITY + 1);
	
	for (i = iStartRow; i <= iEndRow; ++i)
	{
		for (j = iStartCol; j <= iEndCol; ++j)
		{
			iImageIndex = i*4 + j;
			if (iImageIndex < m_lpMainWnd->m_lpBilSmTiles->GetImageCount())
			{
				pDC->Rectangle(j*(UNITX + 1), i*(UNITY + 1), j*(UNITX + 1) + (UNITX + 1) + 1, i*(UNITY + 1) + (UNITY + 1) + 1);
				m_lpMainWnd->m_lpBilSmTiles->DrawZoom(pDC->GetSafeHdc(), iImageIndex, j*(UNITX + 1) + 1, i*(UNITY + 1) + 1, 100);
				
				if (iImageIndex == m_iCurrentImg)
				{
					pDC->DrawFocusRect(CRect(j*(UNITX + 1) + 1, i*(UNITY + 1) + 1, j*(UNITX + 1) + 1 + UNITX, i*(UNITY + 1) + 1 + UNITY));
				}
			}
		}
	}
	
	pDC->SelectObject(hOldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CSingleSmallTileView diagnostics

#ifdef _DEBUG
void CSingleSmallTileView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSingleSmallTileView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSingleSmallTileView message handlers

BOOL CSingleSmallTileView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CSingleSmallTileView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
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

VOID CSingleSmallTileView::AdjustScrollSize()
{
	INT iRowCount = (m_lpMainWnd->m_lpBilSmTiles->GetImageCount() + 3)/4; //我们的小地砖视图是以4个格子为一行的
	
	SetScrollSizes(MM_TEXT, CSize(4*(UNITX + 1), iRowCount*(UNITY + 1)), sizeDefault, CSize(UNITX + 1, UNITY + 1));
}

void CSingleSmallTileView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//这个也不多说了。。
	CString szStatus;
	
	point += GetScrollPosition();
	INT iRow = point.y/(UNITY + 1);
	INT iCol = point.x/(UNITX + 1);
	INT iImageIndex = iRow*4 + iCol;
	
	if (iImageIndex < m_lpMainWnd->m_lpBilTiles->GetImageCount())
	{
		m_lpMainWnd->m_eDrawMode = dmSingleSmallTile;
		m_lpMainWnd->GetMenu()->CheckMenuRadioItem(IDM_MARK, IDM_ERASER, -1, MF_BYCOMMAND);
		if (m_iCurrentImg != iImageIndex)
		{
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);
			iRow = m_iCurrentImg/4;
			iCol = m_iCurrentImg%4;
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);
			
			m_iCurrentImg = iImageIndex;
			
			szStatus.Format("工具:单块小号地砖(%d)", m_iCurrentImg);
			m_lpMainWnd->m_wndStatusBar.SetPaneText(2, szStatus, TRUE);
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}
