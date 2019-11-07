// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EFECAF29_172B_4648_B09F_319C11137BFB__INCLUDED_)
#define AFX_MAINFRM_H__EFECAF29_172B_4648_B09F_319C11137BFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProgressStatusBar.h"
#include "BilImages.h"

#define UNITX 48
#define UNITY 32

class CSingleTileView;
class CSingleSmallTileView;
class CTileView;
class CMapView;
class CObjView;
class CObjSetView;
class CSmallTileView;

//我说说这些枚举类型的意义
enum DRAWMODE
{           
	dmSingleTile,           //大地砖, 表示在左上角的视图选择了一个地砖
	dmSingleSmallTile,      //小地砖, 表示在右边中间的视图选择了一个小地砖
	dmTile,                 //大地砖自动样式, 表示在左下角选择了一种大地砖自动样式
	dmSmallTile,            //小地砖自动样式, 表示在右下角选择了一种小地砖自动样式
	dmObj,                  //地面物体, 表示在底下的视图中选择了一个物体
	dmObjSet,               //库集, 表示在右上角的视图选择了一个库集
	dmMark,                 //移动设置, 表示在工具菜单中选择了移动设置
	dmDoor,                 //门设置, 表示在工具菜单中选择了门设置
	dmAnimation,            //动画设置, 表示在工具菜单中选择了动画设置
	dmLight,                //常亮点设置, 表示在工具菜单中选择了常亮点设置
	dmEraser                //擦除设置, 表示在工具菜单中选择了擦除设置
};
//每次只可以选择一种工具来编辑地图

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNewfile();
	afx_msg void OnOpenfile();
	afx_msg void OnSavefile();
	afx_msg void OnSavetobmp();
	afx_msg void OnAppExit();
	afx_msg void OnClearmap();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnMark();
	afx_msg void OnDoor();
	afx_msg void OnAnimation();
	afx_msg void OnLight();
	afx_msg void OnEraser();
	afx_msg void OnDrawtile();
	afx_msg void OnDrawsmalltile();
	afx_msg void OnDrawobj();
	afx_msg void OnDrawmark();
	afx_msg void OnDrawdoor();
	afx_msg void OnDrawanimation();
	afx_msg void OnDrawlight();
	afx_msg void OnDrawdooropen();
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	afx_msg void OnRefreshmap();
	afx_msg void OnGoto();
	afx_msg void OnSaveobjset();
	afx_msg void OnAddobjset();
	afx_msg void OnDelobjset();
	afx_msg void OnRefreshobjset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HICON m_hIcon;
	HBITMAP m_hToolBarBitmap;
	CToolBar m_wndToolBar;
	CProgressStatusBar  m_wndStatusBar;

	BOOL m_bSplitterCreated;   //这个变量在图片资源编辑器的时候讲过了, 是用来判断分割视图创建好没的
	CSplitterWnd m_wndSplitter; //这个是用来分割为3个列
	CSplitterWnd m_wndLeftSplitter; //这个是用来分割左边一列的, 分割为上下2行
	CSplitterWnd m_wndMiddleSplitter; //这个是用来分割中间这列的。。也是上下2行
	CSplitterWnd m_wndRightSplitter; //这个是用来分割又边这列的。。分为上中下3行。。最后分割的视图就是这样子的了

	CBilImages* m_lpBilTiles;       //这个用来访问Tiles.bil
	CBilImages* m_lpBilSmTiles;     //这个用来访问SmTiles.bil
	CBilImages* m_BilObjects[256];  //这个是一个数组, 我们支持1-256个Objects文件

	CSingleTileView* m_lpSingleTileView;
	CSingleSmallTileView* m_lpSingleSmallTileView;
	CTileView* m_lpTileView;
	CMapView* m_lpMapView;
	CObjView* m_lpObjView;
	CObjSetView* m_lpObjSetView;
	CSmallTileView* m_lpSmallTileView;

	DRAWMODE m_eDrawMode; //表示当前选择的工具
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EFECAF29_172B_4648_B09F_319C11137BFB__INCLUDED_)
