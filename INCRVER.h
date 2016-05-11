//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//         ___  _   _   ____  ____ __     __ _____  ____      _             //
//        |_ _|| \ | | / ___||  _ \\ \   / /| ____||  _ \    | |__          //
//         | | |  \| || |    | |_) |\ \ / / |  _|  | |_) |   | '_ \         //
//         | | | |\  || |___ |  _ <  \ V /  | |___ |  _ <  _ | | | |        //
//        |___||_| \_| \____||_| \_\  \_/   |_____||_| \_\(_)|_| |_|        //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//          Copyright (c) 2016 by S.F.T. Inc. - All rights reserved         //
//  Use, copying, and distribution of this software are licensed according  //
//           to the the 2-clause BSD license specified in LICENSE           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CINCRVERApp:
// See INCRVER.cpp for the implementation of this class
//

class CINCRVERApp : public CWinApp
{
public:
	CINCRVERApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINCRVERApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

  CString GetFileNameAndOptions();

// Implementation

  BOOL m_bSetVersion;
  CString m_csNewVersion, m_csNewVersion0;

	//{{AFX_MSG(CINCRVERApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
