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
	m_hToolBarBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TOOLBAR));//��ȡ������ͼƬ���
}

CMainFrame::~CMainFrame()
{
	DeleteObject(m_hToolBarBitmap);//����Ա�ĺ�ϰ�ߡ�������������ԴҪ�ǵ��ͷ�
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Set Icon
	SetIcon(m_hIcon, TRUE);  //������ô�ͼ��
	SetIcon(m_hIcon, FALSE); //�������Сͼ��

	//Create Toolbar
	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC); //����������
	m_wndToolBar.SetBitmap(m_hToolBarBitmap);  //���ù�����ͼƬ
	m_wndToolBar.SetSizes(CSize(55, 55), CSize(32, 32)); //���ù�����ͼƬ��ÿ����ť��ͼƬ�ߴ�, ��һ�������ǰ�ť�ߴ硣���ڶ���������ͼƬ�ߴ硣��һ����ťͼƬ�ĳߴ�պ���32*32
	//Ȼ�����ð�ť, ����������鶼�ǰ�ť�ı�ʶ��������ʵ���Ǹո��������õĲ˵��ı�ʶ����������ֻ�ǲ˵�������һ�ֽ��潻����ʽ���ѡ�������ͼ�λ��ͷ����û�������
	UINT button[] = {IDM_NEWFILE, IDM_OPENFILE, IDM_SAVEFILE, ID_SEPARATOR, IDM_IMPORTIMG, IDM_EXPORTIMG, IDM_BATCHIMPORTIMG, IDM_BATCHEXPORTIMG, ID_SEPARATOR, IDM_MODOFFSET, IDM_DELIMG, IDM_CUT, IDM_PASTE, ID_SEPARATOR, IDM_PREIMG, IDM_NEXTIMG, IDM_AUTOPLAY, IDM_PAUSEIMG, IDM_GOTOIMG}; 
	m_wndToolBar.SetButtons(button, 19); //���ð�ť�������ܹ�19���������а����˷ָ����ġ�������������������
	m_wndToolBar.SetButtonText(0, "�½�");	//Ȼ������ÿ����ť�����֡�����������ʾ�ڰ�ť�·�
	m_wndToolBar.SetButtonText(1, "��");
	m_wndToolBar.SetButtonText(2, "����");
	m_wndToolBar.SetButtonText(4, "����");
	m_wndToolBar.SetButtonText(5, "����");
	m_wndToolBar.SetButtonText(6, "��������");
	m_wndToolBar.SetButtonText(7, "��������");
	m_wndToolBar.SetButtonText(9, "�޸�ƫ��");
	m_wndToolBar.SetButtonText(10, "ɾ��");
	m_wndToolBar.SetButtonText(11, "����");
	m_wndToolBar.SetButtonText(12, "ճ��");
	m_wndToolBar.SetButtonText(14, "��һ��");
	m_wndToolBar.SetButtonText(15, "��һ��");
	m_wndToolBar.SetButtonText(16, "����");
	m_wndToolBar.SetButtonText(17, "��ͣ");
	m_wndToolBar.SetButtonText(18, "��ת");

   //Create Status bar
   m_wndStatusBar.CreateEx(this);
   UINT indicators[] =
   {
	   1	//����״̬���е�״̬��ı�ʶ��������ֻ����һ����������ֻ��һ���ˡ���
   };
   m_wndStatusBar.SetIndicators(indicators, 1);		//��������
   m_wndStatusBar.SetPaneInfo(0, 1, SBPS_NORMAL, 800); //����״̬��ĳ��ȡ���800��һ��

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
	m_wndSplitter.CreateStatic(this, 2, 1);	//���Ƿָ�Ϊ����������ͼ����
	
	//Ȼ����Ǵ�����ͼ���������ָ���ͼ�����ˡ�����
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDrawView), CSize(0, 0), pContext); //��������һ�С���һ��
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CGridView), CSize(0, 0), pContext); //�������ڶ��С���һ��

	m_bSplitterCreated = TRUE; //���ʾ�Ѿ��ָ����ͼ�ˡ�����
	
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_bSplitterCreated)   //����Ǳ�֤m_wndSplitter�������������֮�������÷ָ�����ġ���
	{   //WM_SIZE�����Ϣ�����Ŵ���С����������Ϣ�������Ի�Ƶ����ִ�зָ��������ֻҪ����ȷ��ִ�е�ʱ���ͺ��ˡ������Ǹմ�����ʱ�򡣡�
		m_bSplitterCreated = FALSE;	//����ֻҪ�������һ��Ϳ��Խ���ˡ������ǳ���ֻ���ڸմ�����ʱ��ָ���������Ժ�Ͳ����ˡ���
		CRect rect;
		GetClientRect(rect); //��ȡ�ͻ����Ĵ�С

		m_wndSplitter.SetRowInfo(0, rect.Height()/2, 0); //��������������еı����ġ�������ֻ��2�С���ֻҪ�����˵�һ�С����ڶ��оͻ��Զ�������
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
