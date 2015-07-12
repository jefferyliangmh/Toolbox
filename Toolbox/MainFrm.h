// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar.h"
#include "ResourceBar.h"
#include "OutputBar.h"

class CMainFrame : public LPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	LPStatusBar			m_wndStatusBar;
	LPMenuBar			m_wndMenuBar;
	LPToolBar			m_wndToolBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CResourceBar			_resourceBar;
	COutputBar				m_wndOutput;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnWindowManager();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);
};
