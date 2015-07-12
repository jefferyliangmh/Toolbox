// workspace2.cpp : implementation of the CResourceBar class
//

#include "stdafx.h"
#include "Toolbox.h"
#include "ResourceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

/////////////////////////////////////////////////////////////////////////////
// CResourceBar

BEGIN_MESSAGE_MAP(CResourceBar, LPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceBar construction/destruction

CResourceBar::CResourceBar()
{
	// TODO: add one-time construction code here
}

CResourceBar::~CResourceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CResourceBar message handlers

int CResourceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (LPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	// Create tree control:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS;
	
	m_wndTree.m_bVisualManagerStyle = TRUE;

	if (!m_wndTree.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("����������ʧ��\n");
		return -1;      // fail to create
	}

	// Setup tree content:
	HTREEITEM hRoot = m_wndTree.InsertItem(_T("�� 1"));
	m_wndTree.InsertItem(_T("���� 1"), hRoot);
	m_wndTree.InsertItem(_T("���� 2"), hRoot);
	
	m_wndTree.Expand(hRoot, TVE_EXPAND);

	return 0;
}

void CResourceBar::OnSize(UINT nType, int cx, int cy) 
{
	LPDockingControlBar::OnSize(nType, cx, cy);

	// Tree control should cover a whole client area:
	m_wndTree.SetWindowPos(NULL, nBorderSize, nBorderSize, 
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CResourceBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(nBorderSize, nBorderSize);

	dc.Draw3dRect(rectTree, globalData.clrBarShadow, globalData.clrBarShadow);
}
