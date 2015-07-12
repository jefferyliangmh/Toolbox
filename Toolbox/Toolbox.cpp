// Toolbox.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Toolbox.h"
#include "MainFrm.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

// CToolboxApp

BEGIN_MESSAGE_MAP(CToolboxApp, LPWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()


// CToolboxApp construction

CToolboxApp::CToolboxApp()
{
	SetVisualTheme(BCGP_VISUAL_THEME_VS_2013_LIGHT);

	LPToolbarOptions toolbarOptions;

	toolbarOptions.m_nViewToolbarsMenuEntryID = ID_VIEW_TOOLBARS;
	toolbarOptions.m_nCustomizeCommandID = ID_VIEW_CUSTOMIZE;
	toolbarOptions.m_strCustomizeCommandLabel = _T("自定义...");
	toolbarOptions.m_nUserToolbarCommandIDFirst = uiFirstUserToolBarId;
	toolbarOptions.m_nUserToolbarCommandIDLast = uiLastUserToolBarId;
	toolbarOptions.m_strToolbarCustomIconsPath = _T(".\\UserImages.bmp");

	SetToolbarOptions(toolbarOptions);

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CToolboxApp object

CToolboxApp theApp;


// CToolboxApp initialization

BOOL CToolboxApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	LPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("LP向导程序"));

	SetRegistryBase(_T("设置"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	LPMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_ToolboxTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ToolboxTYPE));





	// The main window has been initialized, so show and update it
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	return TRUE;
}

// CToolboxApp message handlers

int CToolboxApp::ExitInstance() 
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return LPWinApp::ExitInstance();
}
void CToolboxApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	// create a new MDI child window
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildFrame), IDR_ToolboxTYPE, m_hMDIMenu, m_hMDIAccel);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public LPDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	LPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : LPDialog(CAboutDlg::IDD)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	LPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, LPDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CToolboxApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CToolboxApp message handlers


void CToolboxApp::PreLoadState()
{

	GetContextMenuManager()->AddMenu(_T("上下文菜单"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

BOOL CToolboxApp::SaveAllModified()
{
	if (!LPWinApp::SaveAllModified())
	{
		return FALSE;
	}
	
	LPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST(LPMDIFrameWnd, m_pMainWnd);
	if (pMainFrame != NULL)
	{
		pMainFrame->SaveMDIState(GetRegSectionPath());
	}
	
	return TRUE;
}
