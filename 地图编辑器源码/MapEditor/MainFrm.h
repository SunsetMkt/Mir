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

//��˵˵��Щö�����͵�����
enum DRAWMODE
{           
	dmSingleTile,           //���ש, ��ʾ�����Ͻǵ���ͼѡ����һ����ש
	dmSingleSmallTile,      //С��ש, ��ʾ���ұ��м����ͼѡ����һ��С��ש
	dmTile,                 //���ש�Զ���ʽ, ��ʾ�����½�ѡ����һ�ִ��ש�Զ���ʽ
	dmSmallTile,            //С��ש�Զ���ʽ, ��ʾ�����½�ѡ����һ��С��ש�Զ���ʽ
	dmObj,                  //��������, ��ʾ�ڵ��µ���ͼ��ѡ����һ������
	dmObjSet,               //�⼯, ��ʾ�����Ͻǵ���ͼѡ����һ���⼯
	dmMark,                 //�ƶ�����, ��ʾ�ڹ��߲˵���ѡ�����ƶ�����
	dmDoor,                 //������, ��ʾ�ڹ��߲˵���ѡ����������
	dmAnimation,            //��������, ��ʾ�ڹ��߲˵���ѡ���˶�������
	dmLight,                //����������, ��ʾ�ڹ��߲˵���ѡ���˳���������
	dmEraser                //��������, ��ʾ�ڹ��߲˵���ѡ���˲�������
};
//ÿ��ֻ����ѡ��һ�ֹ������༭��ͼ

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

	BOOL m_bSplitterCreated;   //���������ͼƬ��Դ�༭����ʱ�򽲹���, �������жϷָ���ͼ������û��
	CSplitterWnd m_wndSplitter; //����������ָ�Ϊ3����
	CSplitterWnd m_wndLeftSplitter; //����������ָ����һ�е�, �ָ�Ϊ����2��
	CSplitterWnd m_wndMiddleSplitter; //����������ָ��м����еġ���Ҳ������2��
	CSplitterWnd m_wndRightSplitter; //����������ָ��ֱ����еġ�����Ϊ������3�С������ָ����ͼ���������ӵ���

	CBilImages* m_lpBilTiles;       //�����������Tiles.bil
	CBilImages* m_lpBilSmTiles;     //�����������SmTiles.bil
	CBilImages* m_BilObjects[256];  //�����һ������, ����֧��1-256��Objects�ļ�

	CSingleTileView* m_lpSingleTileView;
	CSingleSmallTileView* m_lpSingleSmallTileView;
	CTileView* m_lpTileView;
	CMapView* m_lpMapView;
	CObjView* m_lpObjView;
	CObjSetView* m_lpObjSetView;
	CSmallTileView* m_lpSmallTileView;

	DRAWMODE m_eDrawMode; //��ʾ��ǰѡ��Ĺ���
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EFECAF29_172B_4648_B09F_319C11137BFB__INCLUDED_)
