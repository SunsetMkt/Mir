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
    //ͼƬ�����Ǵ�ComboBox�ұ߿�ʼ��
	RECT rect;
	CPoint point;
	INT iStartCol, iEndCol;
	INT j;
	HPEN hOldPen = (HPEN)pDC->SelectObject(m_hGridPen);
	INT iImageIndex = 0;
	//����û, ������Ҫ���ǵ�OBJCOMBOWIDTH, ComboBox�Ŀ��, �����͸������ĸ�����ͼ����ˡ���
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
	
	//����ComboBox
	m_cbObj.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST, CRect(0, 0, OBJCOMBOWIDTH, 0), this, IDC_COMBOOBJ);
	
	//ΪComboBox���256��ѡ�� Objects Objects2 Objects3 .... Objects256
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
	m_cbObj.SetCurSel(0); //Ĭ��ѡ���һ��Objects
	
	return 0;
}

void CObjView::OnSelchangeObjCombo()
{
	INT iSel = m_cbObj.GetCurSel(); //��ȡComboBox��ǰѡ�����
	if (iSel != m_iCurrentObj) //���ѡ�������� ��Ҫ�������õ�ǰѡ��������ͼ��Χ
	{
		m_iCurrentObj = iSel; //�����ǰObjects�ļ���ѡ��
		m_iCurrentImg = 0; //�����Ĭ��ѡ���һ��ͼƬ
		AdjustScrollSize(); //���õ�����ͼ�Ĵ�С������������Ժ����
		Invalidate(TRUE); //ˢ����ͼ
	}
	SetFocus(); //ѡ���������ͼΪ�������ڡ���
}

VOID CObjView::AdjustScrollSize()
{
	INT iColCount = m_lpMainWnd->m_BilObjects[m_iCurrentObj]->GetImageCount(); //���ݵ�ǰѡ���Objects�ļ���ͼƬ��������, һ��ͼƬռһ��
	
	//�������õĹ�����ͼ��Χ���ñ������ComboBox�Ŀ��, ÿ��ͼƬ��ռ�ĸ�����UNITX/2, ��һ�����Ӵ� ComboBox�ұ߿�ʼ
	SetScrollSizes(MM_TEXT, CSize(OBJCOMBOWIDTH + iColCount*(UNITX/2 + 1), 0), sizeDefault, CSize(UNITX/2 + 1, 0));
}

void CObjView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString szStatus;
	//���Ҳ�Ǵ�ͬС��ġ����ҾͲ���˵�ˡ���
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
			
			szStatus.Format("����:����(%d)", m_iCurrentImg);
			m_lpMainWnd->m_wndStatusBar.SetPaneText(2, szStatus, TRUE);
		}
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
	
	CScrollView::OnLButtonDown(nFlags, point);
}
