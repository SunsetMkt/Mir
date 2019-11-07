// ObjView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEditor.h"
#include "ObjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjView

IMPLEMENT_DYNCREATE(CObjView, CScrollView)

CObjView::CObjView()
{
	m_lpMainWnd = NULL;
	m_iCurrentObj = 0;
	m_iCurrentImg = 0;
	m_hGridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
}

CObjView::~CObjView()
{
	DeleteObject(m_hGridPen);
}


BEGIN_MESSAGE_MAP(CObjView, CScrollView)
	//{{AFX_MSG_MAP(CObjView)
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBOOBJ, OnSelchangeObjCombo)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjView drawing

void CObjView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	m_lpMainWnd = (CMainFrame*)AfxGetMainWnd();
	m_lpMainWnd->m_lpObjView = this;
		
	AdjustScrollSize();
}

void CObjView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
    //图片绘制是从ComboBox右边开始的
	RECT rect;
	CPoint point;
	INT iStartCol, iEndCol;
	INT j;
	HPEN hOldPen = (HPEN)pDC->SelectObject(m_hGridPen);
	INT iImageIndex = 0;
	//看到没, 绘制需要考虑到OBJCOMBOWIDTH, ComboBox的宽度, 其他就跟其他的格子视图差不多了。。
	GetClientRect(&rect);
	point = GetScrollPosition();
	rect.left += point.x;
	rect.right += point.x;
	iStartCol = max((rect.left - OBJCOMBOWIDTH)/(UNITX/2 + 1), 0);
	iEndCol = (rect.right - OBJCOMBOWIDTH)/(UNITX/2 + 1);
	
	for (j = iStartCol; j <= iEndCol; ++j)
	{
		iImageIndex = j;
		if (iImageIndex < m_lpMainWnd->m_BilObjects[m_iCurrentObj]->GetImageCount())
		{
			pDC->Rectangle(OBJCOMBOWIDTH + j*(UNITX/2 + 1), 0, OBJCOMBOWIDTH + j*(UNITX/2 + 1) + (UNITX/2 + 1) + 1, rect.bottom + 1);
			m_lpMainWnd->m_BilObjects[m_iCurrentObj]->DrawZoom(pDC->GetSafeHdc(), iImageIndex, OBJCOMBOWIDTH + j*(UNITX/2 + 1) + 1, 1, 50);
			
			if (iImageIndex == m_iCurrentImg)
			{
				pDC->DrawFocusRect(CRect(OBJCOMBOWIDTH + j*(UNITX/2 + 1) + 1, 1, OBJCOMBOWIDTH + j*(UNITX/2 + 1) + 1 + UNITX/2, 1 + rect.bottom));
			}
		}
	}
	
	pDC->SelectObject(hOldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CObjView diagnostics

#ifdef _DEBUG
void CObjView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CObjView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjView message handlers

BOOL CObjView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	DoMouseWheel(nFlags, zDelta, pt);
	
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CObjView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
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

int CObjView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CString szFile;
	
	//创建ComboBox
	m_cbObj.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST, CRect(0, 0, OBJCOMBOWIDTH, 0), this, IDC_COMBOOBJ);
	
	//为ComboBox添加256个选项 Objects Objects2 Objects3 .... Objects256
	for (INT i = 0; i < 256; ++i)
	{
		if (i == 0)
		{
			szFile = "Objects";
		}
		else
		{
			szFile.Format("Objects%d", i + 1);
		}
		m_cbObj.AddString(szFile);
	}
	m_cbObj.SetCurSel(0); //默认选择第一个Objects
	
	return 0;
}

void CObjView::OnSelchangeObjCombo()
{
	INT iSel = m_cbObj.GetCurSel(); //获取ComboBox当前选择的项
	if (iSel != m_iCurrentObj) //如果选择的项变了 则要从新设置当前选择或调整视图范围
	{
		m_iCurrentObj = iSel; //变更当前Objects文件的选择
		m_iCurrentImg = 0; //变更后默认选择第一个图片
		AdjustScrollSize(); //还得调整视图的大小。。这个函数稍后添加
		Invalidate(TRUE); //刷新视图
	}
	SetFocus(); //选择后设置视图为焦点所在。。
}

VOID CObjView::AdjustScrollSize()
{
	INT iColCount = m_lpMainWnd->m_BilObjects[m_iCurrentObj]->GetImageCount(); //根据当前选择的Objects文件的图片计算列数, 一个图片占一列
	
	//这里设置的滚动视图范围还得必须计算ComboBox的宽度, 每个图片所占的格子是UNITX/2, 第一个格子从 ComboBox右边开始
	SetScrollSizes(MM_TEXT, CSize(OBJCOMBOWIDTH + iColCount*(UNITX/2 + 1), 0), sizeDefault, CSize(UNITX/2 + 1, 0));
}

void CObjView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString szStatus;
	//这个也是大同小异的。。我就不多说了。。
	CRect rect;
	GetClientRect(rect);
	point += GetScrollPosition();
	INT iImageIndex = (point.x - OBJCOMBOWIDTH)/(UNITX/2 + 1);
	
	if (iImageIndex >= 0 && iImageIndex < m_lpMainWnd->m_BilObjects[m_iCurrentObj]->GetImageCount())
	{
		m_lpMainWnd->m_eDrawMode = dmObj;
		m_lpMainWnd->GetMenu()->CheckMenuRadioItem(IDM_MARK, IDM_ERASER, -1, MF_BYCOMMAND);
		if (m_iCurrentImg != iImageIndex)
		{
			point = CPoint(OBJCOMBOWIDTH + iImageIndex*(UNITX/2 + 1) + 1, 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX/2, rect.bottom)), FALSE);
			point = CPoint(OBJCOMBOWIDTH + m_iCurrentImg*(UNITX/2 + 1) + 1, 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX/2, rect.bottom)), FALSE);
			
			m_iCurrentImg = iImageIndex;
			
			szStatus.Format("工具:物体(%d)", m_iCurrentImg);
			m_lpMainWnd->m_wndStatusBar.SetPaneText(2, szStatus, TRUE);
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
	
	CScrollView::OnLButtonDown(nFlags, point);
}
