// AVI.h : main header file for the AVI application
//

#if !defined(AFX_AVI_H__8CB0E0D5_4102_4B17_840C_51973D37099E__INCLUDED_)
#define AFX_AVI_H__8CB0E0D5_4102_4B17_840C_51973D37099E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAVIApp:
// See AVI.cpp for the implementation of this class
//

class CAVIApp : public CWinApp
{
public:
	CAVIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAVIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVI_H__8CB0E0D5_4102_4B17_840C_51973D37099E__INCLUDED_)
