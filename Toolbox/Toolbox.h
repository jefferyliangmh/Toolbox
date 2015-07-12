// Toolbox.h : main header file for the Toolbox application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CToolboxApp:
// See Toolbox.cpp for the implementation of this class
//

class CToolboxApp : public LPWinApp
{
public:
	CToolboxApp();

	// Override from LPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual BOOL SaveAllModified();

// Implementation
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CToolboxApp theApp;