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

	m_lpBilTiles = new CBilImages("Tiles.bil");     //创建Tiles.bil的访问类
	m_lpBilSmTiles = new CBilImages("SmTiles.bil"); //创建SmTiles.bil的访问类
	for (INT i = 0; i < 256; ++i) //创建256个Objects文件的访问类
	{
		if (i == 0)
		{
			szFileName = "Objects.bil"; //第一个是Objects.bil
		}
		else
		{
			szFileName.Format("Objects%d.bil", i + 1); //后面的是Objects2.bil, Objects3.bil....Objects256.bil
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

	m_eDrawMode = dmSingleTile; //第一次或者默认选择大地砖
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
	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, WS_CHILD | WS_VISIBLE | CBRS_TOP); //创建工具条
	m_wndToolBar.SetBitmap(m_hToolBarBitmap); //设置工具条的图片
	m_wndToolBar.SetSizes(CSize(55, 55), CSize(32, 32)); //设置每个按钮的大小和图片
	//下面就是设置每个按钮对应的ID啦。。和按钮的文字
	UINT button[] = {IDM_NEWFILE, IDM_OPENFILE, IDM_SAVEFILE, ID_SEPARATOR, IDM_CLEARMAP, IDM_UNDO, IDM_REDO, 
		
		ID_SEPARATOR, IDM_ZOOMIN, IDM_ZOOMOUT, IDM_REFRESHMAP, IDM_GOTO}; 
	m_wndToolBar.SetButtons(button, 12);
	m_wndToolBar.SetButtonText(0, "新建");
	m_wndToolBar.SetButtonText(1, "打开");
	m_wndToolBar.SetButtonText(2, "保存");
	m_wndToolBar.SetButtonText(4, "清空");
	m_wndToolBar.SetButtonText(5, "撤销");
	m_wndToolBar.SetButtonText(6, "返回");
	m_wndToolBar.SetButtonText(8, "放大");
	m_wndToolBar.SetButtonText(9, "缩小");
	m_wndToolBar.SetButtonText(10, "刷新");
	m_wndToolBar.SetButtonText(11, "跳转");

	//Create Status bar
	m_wndStatusBar.CreateEx(this);
	UINT indicators[] = 
	{
		1, 2, 3
	}; //这次我们要创建3个状态项哦。。
	m_wndStatusBar.SetIndicators(indicators, 3);
	m_wndStatusBar.SetPaneInfo(0, 1, SBPS_NORMAL, 300); //分别占300个像素
	m_wndStatusBar.SetPaneInfo(1, 2, SBPS_NORMAL, 400); //400个像素
	m_wndStatusBar.SetPaneInfo(2, 3, SBPS_NORMAL, 600); //600个像素

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
	m_wndSplitter.SetFocus(); //替换了。。
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

	//又是微软规定的做法啦。。。分割视图就得这样做了。。必须在这个函数里做

	m_wndSplitter.CreateStatic(this, 1, 3); //首先创建第一个分割, 分为3列, 1行

	//然后下面就开始分割第一列了, 分为2行, 1列(准确地说啦)                     //最后一个参数就是表示上面分割的3列中第一列的ID了
	m_wndLeftSplitter.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 0));
	m_wndLeftSplitter.CreateView(0, 0, RUNTIME_CLASS(CSingleTileView), CSize(0, 0), pContext); //然后创建2个视图啦。。。
	m_wndLeftSplitter.CreateView(1, 0, RUNTIME_CLASS(CTileView), CSize(0, 0), pContext);
	
	//下面就分割第二列了。。分割为2行, 1列(准确地说啦)                           //最后一个参数就是表示上面分割的3列中第二列的ID了
	m_wndMiddleSplitter.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1));
	m_wndMiddleSplitter.CreateView(0, 0, RUNTIME_CLASS(CMapView), CSize(0, 0), pContext);//然后创建中间2列的视图了
	m_wndMiddleSplitter.CreateView(1, 0, RUNTIME_CLASS(CObjView), CSize(0, 0), pContext);

	//下面就分割第三列了。。分割为3行, 1列(准确地说啦)                           //最后一个参数就是表示上面分割的3列中第三列的ID了
	m_wndRightSplitter.CreateStatic(&m_wndSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 2));
	m_wndRightSplitter.CreateView(0, 0, RUNTIME_CLASS(CObjSetView), CSize(0, 0), pContext); //并创建第三列中的3个视图
	m_wndRightSplitter.CreateView(1, 0, RUNTIME_CLASS(CSingleSmallTileView), CSize(0, 0), pContext);
	m_wndRightSplitter.CreateView(2, 0, RUNTIME_CLASS(CSmallTileView), CSize(0, 0), pContext);
	
	m_bSplitterCreated = TRUE; //视图已经创建完成。。。
	
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_bSplitterCreated) //检查视图是否已经创建了。。
	{
		CRect rect;
		
		m_bSplitterCreated = FALSE; //这里表示只设置一次分割比例, 就是刚创建的时候设置
		GetClientRect(rect);
		
		m_wndSplitter.SetColumnInfo(0, 265, 0); //设置3列中的第一列为265个像素
		m_wndSplitter.SetColumnInfo(1, max(rect.Width() - 265 - 232, 0), 0);//然后设置第二列rect.Width() - 265 - 232意思是第三列为232啦, 因为我们设置了前2列, 第三列就不用设置了, max(rect.Width() - 265 - 232, 0), 0)加个max判断是防止出现rect.Width() - 265 - 232 < 0 函数出错
		m_wndSplitter.RecalcLayout(); //前2列设置了, 第三列就自动设置好了, 所以直接调用这个函数就可以了, 设置完分割视图, 得调用这个函数
		
		//这个设置3列中的第一列了。。分割上下2行
		m_wndLeftSplitter.SetRowInfo(0, rect.Height()/2, 0); //第一行占一半。。第二行自动设置好
		m_wndLeftSplitter.RecalcLayout(); //惯例。。要调用这个函数
		
		//这个设置3列中的第二列了。。分割上下2行
		m_wndMiddleSplitter.SetRowInfo(0, max(rect.Height() - 250, 0), 0); //这里是第二行占250, 第一行自然就是rect.Height() - 250, 同样max是为了防止出现小于0的情况啦
		m_wndMiddleSplitter.RecalcLayout(); //惯例。。要调用这个函数
		
		//这个设置3列中的第三列了。。分割上中下3行
		m_wndRightSplitter.SetRowInfo(0, rect.Height()/2, 0); //第一行占一半
		m_wndRightSplitter.SetRowInfo(1, rect.Height()/4, 0); //第二行占四分之一, 第三行就是剩下的了。。
		m_wndRightSplitter.RecalcLayout(); //惯例。。要调用这个函数
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
