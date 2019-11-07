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

	m_hGridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200)); //������ɫ����
	m_iCurrentImg = 0; //Ĭ��ѡ���һ�����ש
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
    //��ʵ����Ļ��Ʒ�ʽ��ͼƬ�༭����ĸ�����ͼ�ǲ��ġ����Ҵ�Ž�һ�¡���
	RECT rect;
	CPoint point;
	INT iStartRow, iEndRow;
	INT iStartCol, iEndCol;
	INT i, j;
	HPEN hOldPen = (HPEN)pDC->SelectObject(m_hGridPen); //����ɫ����ѡ���豸
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
	iEndRow = rect.bottom/(UNITY + 1);   //��һ��ζ����ڼ�����Ҫ��ʾ�ĸ��ӵ��к��еķ�Χ, ͼƬ�༭���ǿν��ú������
	
	for (i = iStartRow; i <= iEndRow; ++i) //Ȼ��ѭ����������ӻ��ƺ͸����еĵ�ש����
	{
		for (j = iStartCol; j <= iEndCol; ++j)
		{
			iImageIndex = i*5 + j;
			if (iImageIndex < m_lpMainWnd->m_lpBilTiles->GetImageCount())
			{
				pDC->Rectangle(j*(UNITX + 1), i*(UNITY + 1), j*(UNITX + 1) + (UNITX + 1) + 1, i*(UNITY + 1) + (UNITY + 1) + 1); //���Ƹ���
				m_lpMainWnd->m_lpBilTiles->DrawZoom(pDC->GetSafeHdc(), iImageIndex, j*(UNITX + 1) + 1, i*(UNITY + 1) + 1, 50); //����ͼƬ, �������ǵ�����CBilImages�е�DrawZoom����
				
				if (iImageIndex == m_iCurrentImg)
				{   //����ǵ�ǰѡ��ͼƬ�����һ������Ȧ��ʾ��ǰѡ��
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
{   //������ͼ����5��Ϊһ��, �������ǵü����ж����С�����
	INT iRowCount = (m_lpMainWnd->m_lpBilTiles->GetImageCount() + 4)/5;  //��������
	
	//���ù�����ΧUNITX��С��ש�Ŀ��Ҳ�ǵ�ͼ��Ŀ��, UNITY��Ϊ�߶�
	//ÿ�����ש���ŵ�һ��UNITX*UNITY��С�ĸ������
	SetScrollSizes(MM_TEXT, CSize(5*(UNITX + 1), iRowCount*(UNITY + 1)), sizeDefault, CSize(UNITX + 1, UNITY + 1));
}

void CSingleTileView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString szStatus;
	
	point += GetScrollPosition();
	INT iRow = point.y/(UNITY + 1);
	INT iCol = point.x/(UNITX + 1);
	INT iImageIndex = iRow*5 + iCol; //���㵱ǰѡ��ĵ�ש����
	
	if (iImageIndex < m_lpMainWnd->m_lpBilTiles->GetImageCount()) //�ж��Ƿ�Ϸ�
	{
		m_lpMainWnd->m_eDrawMode = dmSingleTile; //����ѡ��Ĺ���
		m_lpMainWnd->GetMenu()->CheckMenuRadioItem(IDM_MARK, IDM_ERASER, -1, MF_BYCOMMAND); //���������ù������еĲ˵��Ǹ��򹳵�, �������õ���������Ϊ-1��ʾ���в˵�������, ��Ϊ�⼸������֮���ǻ����, ����ͬʱѡ��, ����ѡ��Ĵ��ש, �������е��������߾�Ҫ�ѡ�ȡ������
		if (m_iCurrentImg != iImageIndex)
		{
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);
			iRow = m_iCurrentImg/5;
			iCol = m_iCurrentImg%5;
			point = CPoint(iCol*(UNITX + 1) + 1, iRow*(UNITY + 1) + 1) - GetScrollPosition();
			InvalidateRect(CRect(point, CSize(UNITX, UNITY)), FALSE);    //ˢ�µ�ש
			
			m_iCurrentImg = iImageIndex; //���õ�ǰѡ��ĵ�ש
			
			szStatus.Format("����:�����ŵ�ש(%d)", m_iCurrentImg);    
			m_lpMainWnd->m_wndStatusBar.SetPaneText(2, szStatus, TRUE);  //����״̬��, ��ǰѡ����ʲô����
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}
