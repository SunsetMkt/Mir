// SingleTileView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "SingleTileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSingleTileView

IMPLEMENT_DYNCREATE(CSingleTileView, CScrollView)

CSingleTileView::CSingleTileView()
{
	m_lpMainWnd = NULL;

	m_hGridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200)); //创建灰色画笔
	m_iCurrentImg = 0; //默认选择第一个大地砖
}

CSingleTileView::~CSingleTileView()
{
	DeleteObject(m_hGridPen);
}


BEGIN_MESSAGE_MAP(CSingleTileView, CScrollView)
	//{{AFX_MSG_MAP(CSingleTileView)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSingleTileView drawing

void CSingleTileView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpSingleTileView = this;

	AdjustScrollSize();
}

void CSingleTileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
    //其实这里的绘制方式跟图片编辑器里的格子视图是差不多的。。我大概讲一下。。
	RECT rect;
	CPoint point;
	INT iStartRow, iEndRow;
	INT iStartCol, iEndCol;
	INT i, j;
	HPEN hOldPen = (HPEN)pDC->SelectObject(m_hGridPen); //将灰色画笔选进设备
	INT iImageIndex = 0;
	
	GetClientRect(&rect);
	point = GetScrollPosition();
	rect.left += point.x;
	rect.top += point.y;
	rect.right += point.x;
	rect.bottom += point.y;
	iStartCol = rect.left/(UNITX + 1) < 5 ? rect.left/(UNITX + 1) : 5 - 1;
	iEndCol = rect.right/(UNITX + 1) < 5 ? rect.right/(UNITX + 1) : 5 - 1;
	iStartRow = rect.top/(UNITY + 1);
	iEndRow = rect.bottom/(UNITY + 1);   //这一大段都是在计算需要显示的格子的行和列的范围, 图片编辑器那课讲得很清楚了
	
	for (i = iStartRow; i <= iEndRow; ++i) //然后循环把组个格子绘制和格子中的地砖绘制
	{
		for (j = iStartCol; j <= iEndCol; ++j)
		{
			iImageIndex = i*5 + j;
			if (iImageIndex < m_lpMainWnd->m_lpBilTiles->GetImageCount())
			{
				pDC->Rectangle(j*(UNITX + 1), i*(UNITY + 1), j*(UNITX + 1) + (UNITX + 1) + 1, i*(UNITY + 1) + (UNITY + 1) + 1); //绘制格子
				m_lpMainWnd->m_lpBilTiles->DrawZoom(pDC->GetSafeHdc(), iImageIndex, j*(UNITX + 1) + 1, i*(UNITY + 1) + 1, 50); //绘制图片, 这里我们调用了CBilImages中的DrawZoom函数
				
				if (iImageIndex == m_iCurrentImg)
				{   //如果是当前选择图片则绘制一个虚线圈表示当前选择
					pDC->DrawFocusRect(CRect(j*(UNITX + 1) + 1, i*(UNITY + 1) + 1, j*(UNITX + 1) + 1 + UNITX, i*(UNITY + 1) + 1 + UNITY));
				}
			}
		}
	}
	
	pDC->SelectObject(hOldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CSingleTileView diagnostics

#ifdef _DEBUG
void CSingleTileView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSingleTileView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSingleTileView message handlers

BOOL CSingleTileView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CSingleTileView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
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

VOID CSingleTileView::AdjustScrollSize()
{   //整个视图是以5列为一行, 所以我们得计算有多少行。。。
	INT iRowCount = (m_lpMainWnd->m_lpBilTiles->GetImageCount() + 4)/5;  //计算行数
	
	//设置滚动范围UNITX是小地砖的宽度也是地图格的宽度, UNITY则为高度
	//每个大地砖被放到一个UNITX*UNITY大小的格子里。。
	SetScrollSizes(MM_TEXT, CSize(5*(UNITX + 1), iRowCount*(UNITY + 1)), sizeDefault, CSize(UNITX + 1, UNITY + 1));
}

void CSingleTileView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString szStatus;
	
	point += GetScrollPosition();
	INT iRow = point.y/(UNITY + 1);
	INT iCol = point.x/(UNITX + 1);
	INT iImageIndex = iRow*5 + iCol; //计算当前选择的地砖索引
	
	if (iImageIndex < m_lpMainWnd->m_lpBilTiles->GetImageCount()) //判断是否合法
	{
		m_lpMainWnd->m_eDrawMode = dmSingleTile; //设置选择的工具
		m_lpMainWnd->GetMenu()->CheckMenuRadioItem(IDM_MARK, IDM_ERASER, -1, MF_BYCOMMAND); //这里是设置工具栏中的菜单那个打钩的, 这里设置第三个参数为-1表示所有菜单都不打钩, 因为这几个工具之间是互斥的, 不能同时选择, 所以选择的大地砖, 工具栏中的其他工具就要把√取消掉了
		if (m_iCurrentImg != iImageIndex)
		{
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);
			iRow = m_iCurrentImg/5;
			iCol = m_iCurrentImg%5;
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);    //刷新地砖
			
			m_iCurrentImg = iImageIndex; //设置当前选择的地砖
			
			szStatus.Format("工具:单块大号地砖(%d)", m_iCurrentImg);    
			m_lpMainWnd->m_wndStatusBar.SetPaneText(2, szStatus, TRUE);  //设置状态栏, 当前选择了什么工具
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}
