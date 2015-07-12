// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Toolbox.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, LPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, LPMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (LPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	LPToolBar::EnableQuickCustomization ();

	LPMDITabParams mdiTabParams;

	mdiTabParams.m_bTabIcons = TRUE;
	mdiTabParams.m_bDocumentMenu = TRUE;
	mdiTabParams.m_style = LPTabWnd::STYLE_3D_SCROLLED;
	mdiTabParams.m_closeButtonMode = LPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED_COMPACT;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	// Menu will not take the focus on activation:
	LPPopupMenu::SetForceMenuFocus (FALSE);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("创建菜单栏错误\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("创建工具栏错误\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("创建状态栏失败\n");
		return -1;      // fail to create
	}

	// Load control bar icons:
	LPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	CString toolboxTitle;
	toolboxTitle.LoadString(IDS_WORKSPACEBAR);
	if (!m_wndWorkSpace.Create (toolboxTitle, this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("创建工作区失败\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!_resourceBar.Create (_T("视图 2"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("创建工作区失败 2\n");
		return -1;      // fail to create
	}

	_resourceBar.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);


	if (!m_wndOutput.Create (_T("输出"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("创建输出窗口失败\n");
		return -1;      // fail to create
	}
	m_wndOutput.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	_resourceBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndWorkSpace);
	_resourceBar.AttachToTabWnd (&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	DockControlBar(&m_wndOutput);

	// Enable windows manager:
	EnableWindowsDialog (ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !LPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	LPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	LPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	return 0;
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	LPPopupMenu* pPopupMenu = new LPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

void CMainFrame::OnMdiMoveToNextGroup() 
{
	MDITabMoveToNextGroup ();
}

void CMainFrame::OnMdiMoveToPrevGroup() 
{
	MDITabMoveToNextGroup (FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup() 
{
	MDITabNewGroup (FALSE);
}

void CMainFrame::OnMdiNewVertGroup() 
{
	MDITabNewGroup ();
}

void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}
 // UI_TYPE_RIBBON

