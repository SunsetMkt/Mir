; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CScrollView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapEditor.h"
LastPage=0

ClassCount=11
Class1=CMapEditorApp
Class3=CMainFrame
Class4=CAboutDlg
Class9=CObjSetView

ResourceCount=2
Resource1=IDR_MAINFRAME
Class10=CSingleSmallTileView
Class11=CSmallTileView
Class2=CChildView
Class5=CSingleTileView
Class6=CTileView
Class7=CMapView
Class8=CObjView
Resource2=IDD_ABOUTBOX

[CLS:CMapEditorApp]
Type=0
HeaderFile=MapEditor.h
ImplementationFile=MapEditor.cpp
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
LastObject=IDM_REFRESHOBJSET




[CLS:CAboutDlg]
Type=0
HeaderFile=MapEditor.cpp
ImplementationFile=MapEditor.cpp
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
Command4=IDM_SAVETOBMP
Command5=ID_APP_EXIT
Command6=IDM_CLEARMAP
Command7=IDM_UNDO
Command8=IDM_REDO
Command9=IDM_MARK
Command10=IDM_DOOR
Command11=IDM_ANIMATION
Command12=IDM_LIGHT
Command13=IDM_ERASER
Command14=IDM_DRAWTILE
Command15=IDM_DRAWSMALLTILE
Command16=IDM_DRAWOBJ
Command17=IDM_DRAWMARK
Command18=IDM_DRAWDOOR
Command19=IDM_DRAWANIMATION
Command20=IDM_DRAWLIGHT
Command21=IDM_DRAWDOOROPEN
Command22=IDM_ZOOMOUT
Command23=IDM_ZOOMIN
Command24=IDM_REFRESHMAP
Command25=IDM_GOTO
Command26=IDM_SAVEOBJSET
Command27=IDM_ADDOBJSET
Command28=IDM_DELOBJSET
Command29=IDM_REFRESHOBJSET
Command30=ID_APP_ABOUT
CommandCount=30

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

[CLS:CSingleTileView]
Type=0
HeaderFile=SingleTileView.h
ImplementationFile=SingleTileView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CTileView]
Type=0
HeaderFile=TileView.h
ImplementationFile=TileView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CMapView]
Type=0
HeaderFile=MapView.h
ImplementationFile=MapView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CObjView]
Type=0
HeaderFile=ObjView.h
ImplementationFile=ObjView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CObjSetView]
Type=0
HeaderFile=ObjSetView.h
ImplementationFile=ObjSetView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CSingleSmallTileView]
Type=0
HeaderFile=SingleSmallTileView.h
ImplementationFile=SingleSmallTileView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

[CLS:CSmallTileView]
Type=0
HeaderFile=SmallTileView.h
ImplementationFile=SmallTileView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC

