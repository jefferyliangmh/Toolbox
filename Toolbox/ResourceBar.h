// workspace2.h : interface of the CResourceBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CResourceBar : public LPDockingControlBar
{
public:
	CResourceBar();

// Attributes
protected:
	LPTreeCtrl	m_wndTree;

// Operations
public:

// Overrides

// Implementation
public:
	virtual ~CResourceBar();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
