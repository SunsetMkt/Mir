; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProgressStatusBar
LastTemplate=CStatusBarCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BilEditor.h"
LastPage=0

ClassCount=7
Class1=CBilEditorApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class2=CChildView
Class5=CDrawView
Class6=CGridView
Class7=CProgressStatusBar
Resource2=IDD_ABOUTBOX

[CLS:CBilEditorApp]
Type=0
HeaderFile=BilEditor.h
ImplementationFile=BilEditor.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDM_GOTOIMG




[CLS:CAboutDlg]
Type=0
HeaderFile=BilEditor.cpp
ImplementationFile=BilEditor.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_NEWFILE
Command2=IDM_OPENFILE
Command3=IDM_SAVEFILE
Command4=ID_APP_EXIT
Command5=IDM_IMPORTIMG
Command6=IDM_EXPORTIMG
Command7=IDM_BATCHIMPORTIMG
Command8=IDM_BATCHEXPORTIMG
Command9=IDM_MODOFFSET
Command10=IDM_DELIMG
Command11=IDM_CUT
Command12=IDM_PASTE
Command13=IDM_DRAWTRANSPARENT
Command14=IDM_DRAWCOORD
Command15=IDM_DRAWOFFSET
Command16=IDM_PREIMG
Command17=IDM_NEXTIMG
Command18=IDM_AUTOPLAY
Command19=IDM_PAUSEIMG
Command20=IDM_GOTOIMG
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[CLS:CDrawView]
Type=0
HeaderFile=DrawView.h
ImplementationFile=DrawView.cpp
BaseClass=CScrollView
Filter=C

[CLS:CGridView]
Type=0
HeaderFile=GridView.h
ImplementationFile=GridView.cpp
BaseClass=CScrollView
Filter=C

[CLS:CProgressStatusBar]
Type=0
HeaderFile=ProgressStatusBar.h
ImplementationFile=ProgressStatusBar.cpp
BaseClass=CStatusBar
Filter=W

