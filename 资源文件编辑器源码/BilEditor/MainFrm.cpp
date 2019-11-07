// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BilEditor.h"

#include "MainFrm.h"
#include "DrawView.h"
#include "GridView.h"

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
	ON_COMMAND(IDM_IMPORTIMG, OnImportimg)
	ON_COMMAND(IDM_EXPORTIMG, OnExportimg)
	ON_COMMAND(IDM_BATCHIMPORTIMG, OnBatchimportimg)
	ON_COMMAND(IDM_BATCHEXPORTIMG, OnBatchexportimg)
	ON_COMMAND(IDM_MODOFFSET, OnModoffset)
	ON_COMMAND(IDM_DELIMG, OnDelimg)
	ON_COMMAND(IDM_CUT, OnCut)
	ON_COMMAND(IDM_PASTE, OnPaste)
	ON_COMMAND(IDM_DRAWTRANSPARENT, OnDrawtransparent)
	ON_COMMAND(IDM_DRAWCOORD, OnDrawcoord)
	ON_COMMAND(IDM_DRAWOFFSET, OnDrawoffset)
	ON_COMMAND(IDM_PREIMG, OnPreimg)
	ON_COMMAND(IDM_NEXTIMG, OnNextimg)
	ON_COMMAND(IDM_AUTOPLAY, OnAutoplay)
	ON_COMMAND(IDM_PAUSEIMG, OnPauseimg)
	ON_COMMAND(IDM_GOTOIMG, OnGotoimg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bSplitterCreated = FALSE;
	m_hToolBarBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TOOLBAR));//获取工具栏图片句柄
}

CMainFrame::~CMainFrame()
{
	DeleteObject(m_hToolBarBitmap);//程序员的好习惯。。。创建的资源要记得释放
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Set Icon
	SetIcon(m_hIcon, TRUE);  //这个设置大图标
	SetIcon(m_hIcon, FALSE); //这个设置小图标

	//Create Toolbar
	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC); //创建工具栏
	m_wndToolBar.SetBitmap(m_hToolBarBitmap);  //设置工具栏图片
	m_wndToolBar.SetSizes(CSize(55, 55), CSize(32, 32)); //设置工具栏图片中每个按钮的图片尺寸, 第一个参数是按钮尺寸。。第二个参数是图片尺寸。。一个按钮图片的尺寸刚好是32*32
	//然后设置按钮, 下面这个数组都是按钮的标识。。。其实就是刚刚我们设置的菜单的标识。。工具栏只是菜单的另外一种界面交互形式而已。。更加图形化和方便用户。。。
	UINT button[] = {IDM_NEWFILE, IDM_OPENFILE, IDM_SAVEFILE, ID_SEPARATOR, IDM_IMPORTIMG, IDM_EXPORTIMG, IDM_BATCHIMPORTIMG, IDM_BATCHEXPORTIMG, ID_SEPARATOR, IDM_MODOFFSET, IDM_DELIMG, IDM_CUT, IDM_PASTE, ID_SEPARATOR, IDM_PREIMG, IDM_NEXTIMG, IDM_AUTOPLAY, IDM_PAUSEIMG, IDM_GOTOIMG}; 
	m_wndToolBar.SetButtons(button, 19); //设置按钮。。。总共19个。。其中包括了分割栏的。。就是这条东西。。
	m_wndToolBar.SetButtonText(0, "新建");	//然后设置每个按钮的文字。。。文字显示在按钮下方
	m_wndToolBar.SetButtonText(1, "打开");
	m_wndToolBar.SetButtonText(2, "保存");
	m_wndToolBar.SetButtonText(4, "导入");
	m_wndToolBar.SetButtonText(5, "导出");
	m_wndToolBar.SetButtonText(6, "批量导入");
	m_wndToolBar.SetButtonText(7, "批量导出");
	m_wndToolBar.SetButtonText(9, "修改偏移");
	m_wndToolBar.SetButtonText(10, "删除");
	m_wndToolBar.SetButtonText(11, "剪切");
	m_wndToolBar.SetButtonText(12, "粘贴");
	m_wndToolBar.SetButtonText(14, "上一张");
	m_wndToolBar.SetButtonText(15, "下一张");
	m_wndToolBar.SetButtonText(16, "播放");
	m_wndToolBar.SetButtonText(17, "暂停");
	m_wndToolBar.SetButtonText(18, "跳转");

   //Create Status bar
   m_wndStatusBar.CreateEx(this);
   UINT indicators[] =
   {
	   1	//这是状态栏中的状态项的标识。。我们只创建一个。。所以只有一个了。。
   };
   m_wndStatusBar.SetIndicators(indicators, 1);		//关联。。
   m_wndStatusBar.SetPaneInfo(0, 1, SBPS_NORMAL, 800); //设置状态项的长度。。800长一点

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
	m_wndSplitter.SetFocus();
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
	m_wndSplitter.CreateStatic(this, 2, 1);	//我们分割为上下两个视图。。
	
	//然后就是创建视图并关联到分割视图当中了。。。
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDrawView), CSize(0, 0), pContext); //关联到第一行、第一列
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CGridView), CSize(0, 0), pContext); //关联到第二行、第一列

	m_bSplitterCreated = TRUE; //这表示已经分割好视图了。。。
	
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_bSplitterCreated)   //这个是保证m_wndSplitter这个东西创建了之后再设置分割比例的。。
	{   //WM_SIZE这个消息。。放大缩小会产生这个消息。。所以会频繁地执行分割比例。。只要我们确定执行的时机就好了。。就是刚创建的时候。。
		m_bSplitterCreated = FALSE;	//我们只要添加这样一句就可以解决了。。就是程序只会在刚创建的时候分割比例。。以后就不管了。。
		CRect rect;
		GetClientRect(rect); //获取客户区的大小

		m_wndSplitter.SetRowInfo(0, rect.Height()/2, 0); //这个是用来设置行的比例的。。我们只有2行。。只要设置了第一行。。第二行就会自动设置了
		m_wndSplitter.RecalcLayout(); 
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

void CMainFrame::OnImportimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnExportimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnBatchimportimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnBatchexportimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnModoffset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDelimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnCut() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawtransparent() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawcoord() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDrawoffset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnPreimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnNextimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnAutoplay() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnPauseimg() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnGotoimg() 
{
	// TODO: Add your command handler code here
	
}
