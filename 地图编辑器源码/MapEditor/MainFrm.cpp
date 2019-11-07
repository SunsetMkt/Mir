// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapEditor.h"

#include "MainFrm.h"
#include "SingleTileView.h"
#include "TileView.h"
#include "MapView.h"
#include "ObjView.h"
#include "ObjSetView.h"
#include "SingleSmallTileView.h"
#include "SmallTileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(IDM_NEWFILE, OnNewfile)
	ON_COMMAND(IDM_OPENFILE, OnOpenfile)
	ON_COMMAND(IDM_SAVEFILE, OnSavefile)
	ON_COMMAND(IDM_SAVETOBMP, OnSavetobmp)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(IDM_CLEARMAP, OnClearmap)
	ON_COMMAND(IDM_UNDO, OnUndo)
	ON_COMMAND(IDM_REDO, OnRedo)
	ON_COMMAND(IDM_MARK, OnMark)
	ON_COMMAND(IDM_DOOR, OnDoor)
	ON_COMMAND(IDM_ANIMATION, OnAnimation)
	ON_COMMAND(IDM_LIGHT, OnLight)
	ON_COMMAND(IDM_ERASER, OnEraser)
	ON_COMMAND(IDM_DRAWTILE, OnDrawtile)
	ON_COMMAND(IDM_DRAWSMALLTILE, OnDrawsmalltile)
	ON_COMMAND(IDM_DRAWOBJ, OnDrawobj)
	ON_COMMAND(IDM_DRAWMARK, OnDrawmark)
	ON_COMMAND(IDM_DRAWDOOR, OnDrawdoor)
	ON_COMMAND(IDM_DRAWANIMATION, OnDrawanimation)
	ON_COMMAND(IDM_DRAWLIGHT, OnDrawlight)
	ON_COMMAND(IDM_DRAWDOOROPEN, OnDrawdooropen)
	ON_COMMAND(IDM_ZOOMOUT, OnZoomout)
	ON_COMMAND(IDM_ZOOMIN, OnZoomin)
	ON_COMMAND(IDM_REFRESHMAP, OnRefreshmap)
	ON_COMMAND(IDM_GOTO, OnGoto)
	ON_COMMAND(IDM_SAVEOBJSET, OnSaveobjset)
	ON_COMMAND(IDM_ADDOBJSET, OnAddobjset)
	ON_COMMAND(IDM_DELOBJSET, OnDelobjset)
	ON_COMMAND(IDM_REFRESHOBJSET, OnRefreshobjset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	CString szFileName;	

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bSplitterCreated = FALSE;
	m_hToolBarBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TOOLBAR));

	m_lpBilTiles = new CBilImages("Tiles.bil");     //����Tiles.bil�ķ�����
	m_lpBilSmTiles = new CBilImages("SmTiles.bil"); //����SmTiles.bil�ķ�����
	for (INT i = 0; i < 256; ++i) //����256��Objects�ļ��ķ�����
	{
		if (i == 0)
		{
			szFileName = "Objects.bil"; //��һ����Objects.bil
		}
		else
		{
			szFileName.Format("Objects%d.bil", i + 1); //�������Objects2.bil, Objects3.bil....Objects256.bil
		}	
		m_BilObjects[i] = new CBilImages(szFileName);
	}

	m_lpSingleTileView = NULL;
	m_lpSingleSmallTileView = NULL;
	m_lpTileView = NULL;
	m_lpMapView = NULL;
	m_lpObjView = NULL;
	m_lpObjSetView = NULL;
	m_lpSmallTileView = NULL;

	m_eDrawMode = dmSingleTile; //��һ�λ���Ĭ��ѡ����ש
}

CMainFrame::~CMainFrame()
{
	INT i;

	DeleteObject(m_hToolBarBitmap);

	delete m_lpBilTiles;
	delete m_lpBilSmTiles;
	for (i = 0; i < 256; ++i)
	{
		delete m_BilObjects[i];
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Set Icon
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//Create Toolbar
	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, WS_CHILD | WS_VISIBLE | CBRS_TOP); //����������
	m_wndToolBar.SetBitmap(m_hToolBarBitmap); //���ù�������ͼƬ
	m_wndToolBar.SetSizes(CSize(55, 55), CSize(32, 32)); //����ÿ����ť�Ĵ�С��ͼƬ
	//�����������ÿ����ť��Ӧ��ID�������Ͱ�ť������
	UINT button[] = {IDM_NEWFILE, IDM_OPENFILE, IDM_SAVEFILE, ID_SEPARATOR, IDM_CLEARMAP, IDM_UNDO, IDM_REDO, 
		
		ID_SEPARATOR, IDM_ZOOMIN, IDM_ZOOMOUT, IDM_REFRESHMAP, IDM_GOTO}; 
	m_wndToolBar.SetButtons(button, 12);
	m_wndToolBar.SetButtonText(0, "�½�");
	m_wndToolBar.SetButtonText(1, "��");
	m_wndToolBar.SetButtonText(2, "����");
	m_wndToolBar.SetButtonText(4, "���");
	m_wndToolBar.SetButtonText(5, "����");
	m_wndToolBar.SetButtonText(6, "����");
	m_wndToolBar.SetButtonText(8, "�Ŵ�");
	m_wndToolBar.SetButtonText(9, "��С");
	m_wndToolBar.SetButtonText(10, "ˢ��");
	m_wndToolBar.SetButtonText(11, "��ת");

	//Create Status bar
	m_wndStatusBar.CreateEx(this);
	UINT indicators[] = 
	{
		1, 2, 3
	}; //�������Ҫ����3��״̬��Ŷ����
	m_wndStatusBar.SetIndicators(indicators, 3);
	m_wndStatusBar.SetPaneInfo(0, 1, SBPS_NORMAL, 300); //�ֱ�ռ300������
	m_wndStatusBar.SetPaneInfo(1, 2, SBPS_NORMAL, 400); //400������
	m_wndStatusBar.SetPaneInfo(2, 3, SBPS_NORMAL, 600); //600������

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndSplitter.SetFocus(); //�滻�ˡ���
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndSplitter.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	//����΢��涨���������������ָ���ͼ�͵��������ˡ��������������������

	m_wndSplitter.CreateStatic(this, 1, 3); //���ȴ�����һ���ָ�, ��Ϊ3��, 1��

	//Ȼ������Ϳ�ʼ�ָ��һ����, ��Ϊ2��, 1��(׼ȷ��˵��)                     //���һ���������Ǳ�ʾ����ָ��3���е�һ�е�ID��
	m_wndLeftSplitter.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 0));
	m_wndLeftSplitter.CreateView(0, 0, RUNTIME_CLASS(CSingleTileView), CSize(0, 0), pContext); //Ȼ�󴴽�2����ͼ��������
	m_wndLeftSplitter.CreateView(1, 0, RUNTIME_CLASS(CTileView), CSize(0, 0), pContext);
	
	//����ͷָ�ڶ����ˡ����ָ�Ϊ2��, 1��(׼ȷ��˵��)                           //���һ���������Ǳ�ʾ����ָ��3���еڶ��е�ID��
	m_wndMiddleSplitter.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1));
	m_wndMiddleSplitter.CreateView(0, 0, RUNTIME_CLASS(CMapView), CSize(0, 0), pContext);//Ȼ�󴴽��м�2�е���ͼ��
	m_wndMiddleSplitter.CreateView(1, 0, RUNTIME_CLASS(CObjView), CSize(0, 0), pContext);

	//����ͷָ�������ˡ����ָ�Ϊ3��, 1��(׼ȷ��˵��)                           //���һ���������Ǳ�ʾ����ָ��3���е����е�ID��
	m_wndRightSplitter.CreateStatic(&m_wndSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 2));
	m_wndRightSplitter.CreateView(0, 0, RUNTIME_CLASS(CObjSetView), CSize(0, 0), pContext); //�������������е�3����ͼ
	m_wndRightSplitter.CreateView(1, 0, RUNTIME_CLASS(CSingleSmallTileView), CSize(0, 0), pContext);
	m_wndRightSplitter.CreateView(2, 0, RUNTIME_CLASS(CSmallTileView), CSize(0, 0), pContext);
	
	m_bSplitterCreated = TRUE; //��ͼ�Ѿ�������ɡ�����
	
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_bSplitterCreated) //�����ͼ�Ƿ��Ѿ������ˡ���
	{
		CRect rect;
		
		m_bSplitterCreated = FALSE; //�����ʾֻ����һ�ηָ����, ���Ǹմ�����ʱ������
		GetClientRect(rect);
		
		m_wndSplitter.SetColumnInfo(0, 265, 0); //����3���еĵ�һ��Ϊ265������
		m_wndSplitter.SetColumnInfo(1, max(rect.Width() - 265 - 232, 0), 0);//Ȼ�����õڶ���rect.Width() - 265 - 232��˼�ǵ�����Ϊ232��, ��Ϊ����������ǰ2��, �����оͲ���������, max(rect.Width() - 265 - 232, 0), 0)�Ӹ�max�ж��Ƿ�ֹ����rect.Width() - 265 - 232 < 0 ��������
		m_wndSplitter.RecalcLayout(); //ǰ2��������, �����о��Զ����ú���, ����ֱ�ӵ�����������Ϳ�����, ������ָ���ͼ, �õ����������
		
		//�������3���еĵ�һ���ˡ����ָ�����2��
		m_wndLeftSplitter.SetRowInfo(0, rect.Height()/2, 0); //��һ��ռһ�롣���ڶ����Զ����ú�
		m_wndLeftSplitter.RecalcLayout(); //��������Ҫ�����������
		
		//�������3���еĵڶ����ˡ����ָ�����2��
		m_wndMiddleSplitter.SetRowInfo(0, max(rect.Height() - 250, 0), 0); //�����ǵڶ���ռ250, ��һ����Ȼ����rect.Height() - 250, ͬ��max��Ϊ�˷�ֹ����С��0�������
		m_wndMiddleSplitter.RecalcLayout(); //��������Ҫ�����������
		
		//�������3���еĵ������ˡ����ָ�������3��
		m_wndRightSplitter.SetRowInfo(0, rect.Height()/2, 0); //��һ��ռһ��
		m_wndRightSplitter.SetRowInfo(1, rect.Height()/4, 0); //�ڶ���ռ�ķ�֮һ, �����о���ʣ�µ��ˡ���
		m_wndRightSplitter.RecalcLayout(); //��������Ҫ�����������
	}
}

void CMainFrame::OnNewfile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnOpenfile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSavefile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSavetobmp() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnClearmap() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUndo() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnRedo() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMark() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDoor() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnAnimation() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnLight() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEraser() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawtile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawsmalltile() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawobj() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawmark() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawdoor() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawanimation() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawlight() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawdooropen() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnZoomout() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnZoomin() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnRefreshmap() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnGoto() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSaveobjset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnAddobjset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDelobjset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnRefreshobjset() 
{
	// TODO: Add your command handler code here
	
}
