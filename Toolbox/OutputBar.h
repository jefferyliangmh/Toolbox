// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class COutputBar : public LPDockingControlBar
{
public:
	COutputBar();

// Attributes
protected:
	LPTabWnd	_wndTabs;
	
	LPListCtrl	_wndList1;
	LPListCtrl	_wndList2;
	LPListCtrl	_wndList3;

// Operations
public:

// Overrides

// Implementation
public:
	virtual ~COutputBar();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
