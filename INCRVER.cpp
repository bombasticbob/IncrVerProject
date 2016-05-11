//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//   ___  _   _   ____  ____ __     __ _____  ____                          //
//  |_ _|| \ | | / ___||  _ \\ \   / /| ____||  _ \     ___  _ __   _ __    //
//   | | |  \| || |    | |_) |\ \ / / |  _|  | |_) |   / __|| '_ \ | '_ \   //
//   | | | |\  || |___ |  _ <  \ V /  | |___ |  _ <  _| (__ | |_) || |_) |  //
//  |___||_| \_| \____||_| \_\  \_/   |_____||_| \_\(_)\___|| .__/ | .__/   //
//                                                          |_|    |_|      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//          Copyright (c) 2016 by S.F.T. Inc. - All rights reserved         //
//  Use, copying, and distribution of this software are licensed according  //
//           to the the 2-clause BSD license specified in LICENSE           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "INCRVER.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString GetVersionFromFileName(LPCSTR szName);
CString TodaysDateStr(void);

const char szHelpMessage[]=
  "COMMAND LINE:\n"
  "INCRVER.EXE [-?|H|V:n.n.n.n|R:\"rcfilename\"] RC FILE NAME\n"
  " where  -? or -H displays this message\n"
  "   and      -V:n.n.n.n sets the version string to 'n.n.n.n'\n"
  "   and      -R:\"rcfilename\" extracts the version from \"rcfilename\"\n"
  "   and      RC FILE NAME represents the RC file name\n"
  "               (the RC file name does not need to be quoted if it contains spaces)";


/////////////////////////////////////////////////////////////////////////////
// CINCRVERApp

BEGIN_MESSAGE_MAP(CINCRVERApp, CWinApp)
	//{{AFX_MSG_MAP(CINCRVERApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINCRVERApp construction

CINCRVERApp::CINCRVERApp()
{
  m_bSetVersion = FALSE;

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CINCRVERApp object

CINCRVERApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CINCRVERApp initialization

BOOL CINCRVERApp::InitInstance()
{
int i1, iBeginEndCount;


  CString csFileName = GetFileNameAndOptions();

  if(!csFileName.GetLength())
  {
    ::MessageBox(NULL, szHelpMessage, m_pszAppName,
                 MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

    return FALSE;
  }

  CString csNewVersion = m_csNewVersion;   // TODO:  fix this
  CString csNewVersion0 = m_csNewVersion0; // TODO:  fix this
  BOOL bSetVersion = m_bSetVersion; // TODO:  fix this

  // open specified file name, search for 'VF_VERSIONINFO' in the
  // script.  When found, interpret each line and re-write to same
  // file with updated version information.

  CopyFile(csFileName, csFileName + ".bak", FALSE); // ignore the return value
    // making a copy of the RC file in case the power goes out during the process

  // TODO:  verify that '.bak' file matches the original

  HANDLE hFile = CreateFile(csFileName, GENERIC_READ | GENERIC_WRITE, 0,
                            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                            INVALID_HANDLE_VALUE);

  if(hFile == INVALID_HANDLE_VALUE)
  {
    ::MessageBox(NULL, "File open error on \"" + csFileName + "\"",
                  m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

    return FALSE;
  }

  DWORD cbBytes, dwLen;
  BOOL bIsINF;

  // differentiate between INF files and RC files
  bIsINF = !(csFileName.Right(4).CompareNoCase(".INF"));

  dwLen = SetFilePointer(hFile, 0, NULL, FILE_END);
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

  LPSTR lpBuf = (LPSTR)GlobalAlloc(GPTR, dwLen * 3 + 0x10000);

  if(!lpBuf)
  {
    ::MessageBox(NULL, "Not enough memory to complete operation",
                m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

    goto error_exit;
  }

  if(!dwLen || 
     !ReadFile(hFile, lpBuf, dwLen, &cbBytes, NULL) ||
     cbBytes != dwLen)
  {
    ::MessageBox(NULL, "Read error on input file",
                m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

    goto error_exit;
  }

  LPSTR lpBuf1 = lpBuf;
  LPSTR lpBuf2 = lpBuf + dwLen;

  BOOL bUnicode = FALSE;

  LPSTR lp1=lpBuf1, lp2=lpBuf2, lp3, lp4;

  if(dwLen > 1 &&
     (unsigned char)lpBuf[0] == 0xff &&
     (unsigned char)lpBuf[1] == 0xfe)
  {
    bUnicode = TRUE;

    *(lp2++) = lpBuf[0];  // I'll copy the first WCHAR that indicates it's a UNICODE file
    *(lp2++) = lpBuf[1];  // and then skip it for later as 'already processed'

    lp1 += sizeof(WCHAR);  // skip past the first char on input
  }

  DWORD dwPos = 0;
  BOOL bChangedFlag = FALSE, bVersionInfoFlag=FALSE;

  iBeginEndCount = 0;

  while((DWORD)(lp1 - lpBuf1) < (bUnicode ? dwLen - 1 : dwLen))
  {
    if((!bUnicode && !*lp1) ||
        (bUnicode && !*((WCHAR *)lp1)))
    {
      break;
    }

    CString csTemp, csTemp2, csTemp3; // declare here (should re-init to "")
    // otherwise I get this bizarre warning because of 'error_exit'

    lp3 = lp1;

    if(bUnicode)
    {
      while((DWORD)(lp3 - lpBuf1) < (dwLen - 1) &&
            *((WCHAR *)lp3) &&
            *((WCHAR *)lp3) != '\r' &&
            *((WCHAR *)lp3) != '\n' &&
            *((WCHAR *)lp3) != '\xd')
      {
        lp3 += sizeof(WCHAR);
      }
    }
    else
    {
      while((DWORD)(lp3 - lpBuf1) < dwLen &&
            *lp3 &&
            *lp3 != '\r' &&
            *lp3 != '\n' &&
            *lp3 != '\xd')
      {
        lp3++;
      }
    }

    // make a copy of the line (as is)

    if(bUnicode)
    {
      lp4 = csTemp2.GetBufferSetLength(lp3 - lp1 + 2);
      memcpy(lp4, lp1, lp3 - lp1);
      lp4[lp3 - lp1] = 0;
      lp4[(lp3 - lp1) + 1] = 0;

      csTemp = (BSTR)lp4; // converts to ASCII
      csTemp2.ReleaseBuffer(0);
    }
    else
    {
      lp4 = csTemp.GetBufferSetLength(lp3 - lp1 + 1);
      memcpy(lp4, lp1, lp3 - lp1);
      lp4[lp3 - lp1] = 0;

      csTemp.ReleaseBuffer(-1);
    }

    // trim lead white space as a copy in 'csTemp2'

    csTemp2 = csTemp;
    csTemp2.TrimLeft();

    if(bIsINF) // INF files are different - I need a date,version
    {
      if(!csTemp2.Left(9).CompareNoCase("DriverVer"))
      {
        // the 'DriverVer' string looks like this (typically)
        // DriverVer = 04/04/2016,6.01.7600.16385    [white space optional]

        csTemp2 = csTemp2.Mid(9);  // trim off 'DriverVer' from original
        csTemp2.TrimLeft();

        if(csTemp2.GetLength() > 0 && csTemp2.GetAt(0) == '=')
        {
          csTemp2 = csTemp2.Mid(1);
          csTemp2.TrimLeft();

          // csTemp2 should have date,version now
          // I shall re-construct this with today's date and the incremented version

          if(bSetVersion)
          {
            for(i1=0; i1 < csNewVersion.GetLength(); i1++)
            {
              if(csNewVersion.GetAt(i1) == ',')
              {
                csTemp3 += ".";
              }
              else if(csNewVersion.GetAt(i1) > ' ') // not white space
              {
                csTemp3 += csNewVersion.GetAt(i1);
              }
            }

            csTemp = "DriverVer = "
                    + TodaysDateStr()
                    + ","
                    + csTemp3; // CRLF will be added later
          }
          else
          {
            i1 = csTemp2.ReverseFind('.');
            csTemp3.Format("%d", atoi(csTemp2.Mid(i1 + 1)) + 1);
            csTemp2 = csTemp2.Left(i1 + 1) + csTemp3; // incremented version

            i1 = csTemp2.Find(',');
            if(i1 >= 0)
            {
              csTemp2 = csTemp2.Mid(i1 + 1);
            }

            csTemp = "Driverver = "
                    + TodaysDateStr()
                    + ","
                    + csTemp2; // CRLF will be added later
          }

          if(bUnicode)
          {
            BSTR bstrTemp = csTemp.AllocSysString();

            if(!bstrTemp)
            {
              ::MessageBoxA(NULL, "ERROR:  unable to 'AllocSysString' (output file may be inconsistent)",
                            m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

              goto error_exit;
            }
            else
            {
              i1 = lstrlenW(bstrTemp) * sizeof(WCHAR);
              memcpy(lp2, (LPCSTR)bstrTemp, i1);
              lp2 += i1;

              SysFreeString(bstrTemp);

              bChangedFlag = TRUE;
            }
          }
          else
          {
            memcpy(lp2, (LPCSTR)csTemp, csTemp.GetLength());
            lp2 += csTemp.GetLength();

            bChangedFlag = TRUE;
          }

          lp1 = lp3;  // this keeps me from re-copying the same thing
        }
      }
    }
    else if(bVersionInfoFlag)  // am I looking through version info?
    {
      // version info has nested begin/end, but when nesting completes
      // the version info is complete.  Look for the final 'END'

      if(!iBeginEndCount && 
          (!csTemp2.Left(12).CompareNoCase("FILEVERSION ") ||
          !csTemp2.Left(15).CompareNoCase("PRODUCTVERSION ")) )
      {
        // last number in string is version to update - do it!

        if(bSetVersion)
        {
          i1 = csTemp.ReverseFind(',');
          if(i1 > 0)
          {
            csTemp = csTemp.Left(i1);
            i1 = csTemp.ReverseFind(',');

            if(i1 > 0)
            {
              csTemp = csTemp.Left(i1);
              i1 = csTemp.ReverseFind(',');

              if(i1 > 0)
              {
                csTemp = csTemp.Left(i1);

                csTemp.TrimRight();

                while(csTemp.GetLength() &&
                      csTemp[csTemp.GetLength() - 1] >= '0' &&
                      csTemp[csTemp.GetLength() - 1] <= '9')
                {
                  csTemp = csTemp.Left(csTemp.GetLength() - 1);  // trim down to white space
                }

                if(csTemp.GetLength())
                {
                  csTemp = csTemp + csNewVersion;

                  if(bUnicode)
                  {
                    BSTR bstrTemp = csTemp.AllocSysString();

                    if(!bstrTemp)
                    {
                      ::MessageBoxA(NULL, "ERROR:  unable to 'AllocSysString' (output file may be inconsistent)",
                                    m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

                      goto error_exit;
                    }
                    else
                    {
                      i1 = lstrlenW(bstrTemp) * sizeof(WCHAR);
                      memcpy(lp2, (LPCSTR)bstrTemp, i1);
                      lp2 += i1;

                      SysFreeString(bstrTemp);

                      bChangedFlag = TRUE;
                    }
                  }
                  else
                  {
                    memcpy(lp2, (LPCSTR)csTemp, csTemp.GetLength());
                    lp2 += csTemp.GetLength();

                    bChangedFlag = TRUE;
                  }

                  lp1 = lp3;  // this keeps me from re-copying the same thing
                }
              }
            }
          }
        }
        else
        {
          i1 = csTemp.ReverseFind(',');

          if(i1 > 0)
          {
            csTemp2 = csTemp.Mid(i1 + 1);  // exclude ','
            csTemp = csTemp.Left(i1 + 1);  // include ','

            while(csTemp2.GetLength() && csTemp2.Left(1) <= ' ')
              csTemp2 = csTemp2.Mid(1);

            i1 = atoi(csTemp2) + 1;
            csTemp2.Format("%d", i1);

            csTemp += csTemp2;  // re-built line, eh??

            if(bUnicode)
            {
              BSTR bstrTemp = csTemp.AllocSysString();

              if(!bstrTemp)
              {
                ::MessageBoxA(NULL, "ERROR:  unable to 'AllocSysString' (output file may be inconsistent)",
                              m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

                goto error_exit;
              }
              else
              {
                i1 = lstrlenW(bstrTemp) * sizeof(WCHAR);
                memcpy(lp2, (LPCSTR)bstrTemp, i1);
                lp2 += i1;

                SysFreeString(bstrTemp);

                bChangedFlag = TRUE;
              }
            }
            else
            {
              memcpy(lp2, (LPCSTR)csTemp, csTemp.GetLength());
              lp2 += csTemp.GetLength();

              bChangedFlag = TRUE;
            }

            lp1 = lp3;  // this keeps me from re-copying the same thing
          }
        }
      }
      else if(iBeginEndCount && 
              !csTemp2.Left(6).CompareNoCase("VALUE "))
      {
        // one of the 'value' items that I need to update?

        csTemp2 = csTemp2.Mid(6);  // skip all of the crap

        while(csTemp2.GetLength() && csTemp2.Left(1) <= ' ')
          csTemp2 = csTemp2.Mid(1);

        if(!csTemp2.Left(i1 = 13).CompareNoCase("\"FileVersion\"") ||
            !csTemp2.Left(i1 = 16).CompareNoCase("\"ProductVersion\"") )
        {
          // re-build the first part of the string, then increment the
          // version information and tack it onto the end, nicely formatted

          csTemp2 = csTemp2.Left(i1); // trim it down
          csTemp2.TrimRight(); // by convention, always do this
          csTemp2.TrimLeft();

          i1 = csTemp.Find(csTemp2);  // find the string again

          ASSERT(!strncmp(((LPCSTR)csTemp) + i1, csTemp2, csTemp2.GetLength()));

          if(i1 < 0) // oops
          {
            ::MessageBoxA(NULL, "ERROR:  unable to re-find the \"" + csTemp2 + "\" string",
                          m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

            goto error_exit;
          }

          csTemp3 = csTemp.Left(i1 + csTemp2.GetLength());
          csTemp2 = csTemp.Mid(i1 + 1 + csTemp2.GetLength()); // skip comma by adding 1

          // first char in 'csTemp2' might be white space

          csTemp2.TrimRight();
          csTemp2.TrimLeft();
          // at this point, csTemp2 will be a string formatted as follows:
          // "1, 0, 2, 3\0"
          //  - or -
          // "1.0.2.3"
          // but I will *ONLY* write the 2nd version
          // and 'csTemp3' contains the entire line up to and including the
          // 'FileVersion' or 'ProductVersion', minus the ','

          if(bSetVersion)
          {
            // this re-builds the line to include the 'dotted' version
            // that's been saved in 'csNewVersion0'
            csTemp = csTemp3 + ", \"" + csNewVersion0 + "\"";

            if(bUnicode)
            {
              BSTR bstrTemp = csTemp.AllocSysString();

              if(!bstrTemp)
              {
                ::MessageBoxA(NULL, "ERROR:  unable to 'AllocSysString' (output file may be inconsistent)",
                              m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

                goto error_exit;
              }
              else
              {
                i1 = lstrlenW(bstrTemp) * sizeof(WCHAR);
                memcpy(lp2, (LPCSTR)bstrTemp, i1);
                lp2 += i1;

                SysFreeString(bstrTemp);

                bChangedFlag = TRUE;
              }
            }
            else
            {
              memcpy(lp2, (LPCSTR)csTemp, csTemp.GetLength());
              lp2 += csTemp.GetLength();

              bChangedFlag = TRUE;
            }

            lp1 = lp3;  // this keeps me from re-copying the same thing
          }
          else
          {
            // older versions of this had ',', newer use a '.' method
            // so it USED to be something like this:   VALUE "FileVersion", "1, 1, 0, 18\0"
            // but *NOW* it is like this:              VALUE "FileVersion", "1.2.0.1"

            csTemp = csTemp3 + ", "; // add the ',' back in (for compatibility; later re-factor this)



            // now 'massage' the value to eliminate the 'crap'
            if(csTemp2.GetAt(0) == '"')
            {
              csTemp2 = csTemp2.Mid(1);

              if(csTemp2.GetLength() &&
                  csTemp2.GetAt(csTemp2.GetLength() - 1) == '"')
              {
                csTemp2 = csTemp2.Left(csTemp2.GetLength() - 1);
                csTemp2.TrimRight();

                // is there a '\0' at the end?
                if(csTemp2.GetLength() >= 2 &&
                   !csTemp2.Right(2).Compare("\\0"))
                {
                  csTemp2 = csTemp2.Left(csTemp2.GetLength() - 2);
                  csTemp2.TrimRight();
                }
              }
            }

            // change ',' to '.' and eliminate white space

            csTemp3 = "";
            for(i1=0; i1 < csTemp2.GetLength(); i1++)
            {
              if(csTemp2.GetAt(i1) == ',')
              {
                csTemp3 += '.';
              }
              else if(csTemp2.GetAt(i1) > ' ')
              {
                csTemp3 += csTemp2.GetAt(i1);
              }
            }

            i1 = csTemp3.ReverseFind('.');  // find the last dot

            if(i1 <= 0)
            {
              ::MessageBoxA(NULL,
                            "ERROR:  improperly formatted version string \"" + csTemp3 + "\"\n"
                            "'somewhat original' line: " + csTemp + "\"" + csTemp3 + "\"",
                            m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

              goto error_exit;
            }

            csTemp += "\"" + csTemp3.Left(i1 + 1); // include the '.'
            csTemp2 = csTemp3.Mid(i1 + 1);

            i1 = atoi(csTemp2) + 1;
            csTemp2.Format("%d", i1);

            csTemp += csTemp2 + "\""; // and that ends the line

            if(bUnicode)
            {
              BSTR bstrTemp = csTemp.AllocSysString();

              if(!bstrTemp)
              {
                ::MessageBoxA(NULL, "ERROR:  unable to 'AllocSysString' (output file may be inconsistent)",
                              m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

                goto error_exit;
              }
              else
              {
                i1 = lstrlenW(bstrTemp) * sizeof(WCHAR);
                memcpy(lp2, (LPCSTR)bstrTemp, i1);
                lp2 += i1;

                SysFreeString(bstrTemp);

                bChangedFlag = TRUE;
              }
            }
            else
            {
              memcpy(lp2, (LPCSTR)csTemp, csTemp.GetLength());
              lp2 += csTemp.GetLength();

              bChangedFlag = TRUE;
            }

            lp1 = lp3;  // this keeps me from re-copying the same thing
          }
        }
      }
      else if(!csTemp2.Left(5).CompareNoCase("BEGIN"))
      {
        iBeginEndCount++;
      }
      else if(!csTemp2.Left(3).CompareNoCase("END"))
      {
        if(iBeginEndCount)
        {
          iBeginEndCount--;
        }

        if(!iBeginEndCount)
        {
          bVersionInfoFlag = FALSE;
        }
      }
    }
    else if(!csTemp.Left(15).CompareNoCase("VS_VERSION_INFO"))
    {
      // See if this line begins with 'VS_VERSION_INFO', and if
      // so, flag it so that I can do the other stuff...

      bVersionInfoFlag = TRUE;
    }

    // now, copy the line 'as-is' to destination buffer if I haven't
    // already made an 'updated' copy (in which case, lp3 == lp1)

    if(lp3 > lp1)  // i.e. there's something to copy
    {
      memcpy(lp2, lp1, lp3 - lp1);

      lp2 += (DWORD)(lp3 - lp1);

      lp1 = lp3;
    }

    if(bUnicode)
    {
      while((DWORD)(lp1 - lpBuf1) < (dwLen - 1) &&
            (*((WCHAR *)lp1) == '\r' ||
              *((WCHAR *)lp1) == '\n'))
      {
        lp1 += sizeof(WCHAR);  // pass up additional blank lines, etc.
      }
    }
    else
    {
      while((DWORD)(lp1 - lpBuf1) < dwLen &&
            (*lp1 == '\r' || *lp1 == '\n'))
      {
        lp1++;  // pass up additional blank lines, etc.
      }
    }

    // write additional stuff (as required)

    if(lp1 > lp3)  // anything more to copy?
    {
      memcpy(lp2, lp3, lp1 - lp3);

      lp2 += (DWORD)(lp1 - lp3);
    }

    if(bUnicode)
    {
      *((WCHAR *)lp2) = 0;
    }
    else
    {
      *lp2 = 0;  // terminate (just because)
    }
  }

  if(bChangedFlag)
  {
    // OK!  'lp2' marks the end of the file.  Now, re-write
    // the whole thing, but make sure I mark the end of file
    // correctly when I do it.....

#ifdef _DEBUG

    CString csTempOut;

    TRACE0("WOULD BE WRITING OUTPUT BACK TO FILE\r\n");

    memcpy(csTempOut.GetBufferSetLength(dwLen), lpBuf2, dwLen);
    csTempOut.ReleaseBuffer(dwLen);
    afxDump << csTempOut;

    TRACE0("\r\n****************************************************\r\n\n");

#else // _DEBUG

    dwLen = lp2 - lpBuf2;
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

    SetEndOfFile(hFile);

    if(!WriteFile(hFile, lpBuf2, dwLen, &cbBytes, NULL) ||
        cbBytes != dwLen)
    {
      ::MessageBox(NULL, "Write error on output file (original may have been destroyed, sorry!)",
              m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);
    }

    FlushFileBuffers(hFile); // just because (force write to happen NOW)
    // TODO:  check for error, and restore original file if needed

#endif // _DEBUG
  }

error_exit:

  if(lpBuf)
  {
    GlobalFree((HGLOBAL)lpBuf);
  }

  if(hFile != INVALID_HANDLE_VALUE)
  {
    CloseHandle(hFile);
  }

  return FALSE;
}

CString CINCRVERApp::GetFileNameAndOptions(void)
{
int i1;

  if(m_lpCmdLine[0])  // command line contains RC file and other stuff
  {
    LPCSTR lpc1 = m_lpCmdLine;

    while(*lpc1)
    {
      while(*lpc1 && *lpc1 <= ' ')
        lpc1++;

      if(!*lpc1)
        break;

      LPCSTR lpc2 = lpc1++;
      LPCSTR lpcRestOfLine = lpc2;

      CString csTerm;

      // find "end of term"

      if(*lpc2 == '"')
      {
        lpc2 = lpc1;  // point past quote mark
        lpcRestOfLine = NULL;

        while(*lpc1 && *lpc1 != '"') // TODO:  check for '\' escaped quotes?
          lpc1++;

        csTerm = ((CString)lpc2).Left(lpc1 - lpc2);

        if(*lpc1)  // a quote mark
          lpc1++;
      }
      else
      {
        while(*lpc1 > ' ')
          lpc1++;

        csTerm = ((CString)lpc2).Left(lpc1 - lpc2);
      }

      if(csTerm.GetLength())
      {
        if(csTerm[0] == '-' || csTerm[0] == '/')
        {
          csTerm.MakeUpper();

          // a switch!

          if(csTerm[1] == '?' || csTerm[1] == 'H')
          {
            return (CString)"";
          }
          else if(csTerm.GetLength() > 3 &&
                  csTerm[1]=='V' && csTerm[2]==':')
          {
            m_bSetVersion = TRUE;
            m_csNewVersion0 = csTerm.Mid(3);

            // change the '.' into ',' and add some white space between
            // 'm_csNewVersion0 will continue to have '.'s

            m_csNewVersion = "";
            for(i1=0; i1 < m_csNewVersion0.GetLength(); i1++)
            {
              if(m_csNewVersion0[i1] == '.')
              {
                m_csNewVersion += ", ";
              }
              else
              {
                m_csNewVersion += m_csNewVersion0[i1];
              }
            }

            TRACE0("CHANGING VERSION TO " + m_csNewVersion + "\r\n");
          }
          else if(csTerm.GetLength() > 3 &&
                  csTerm[1]=='R' && csTerm[2]==':')
          {
            m_bSetVersion = TRUE;
            m_csNewVersion0 = GetVersionFromFileName(csTerm.Mid(3));

            if(!m_csNewVersion0.GetLength()) // an error
            {
              return (CString)"";
            }

            // change the '.' into ',' and add some white space between
            // 'm_csNewVersion0 will continue to have '.'s

            m_csNewVersion = "";
            for(i1=0; i1 < m_csNewVersion0.GetLength(); i1++)
            {
              if(m_csNewVersion0[i1] == '.')
              {
                m_csNewVersion += ", ";
              }
              else
              {
                m_csNewVersion += m_csNewVersion0[i1];
              }
            }

            TRACE0("CHANGING VERSION TO " + m_csNewVersion + "\r\n");
          }
          else
          {
            ::MessageBox(NULL, "ERROR - Illegal switch specified - " + csTerm,
                         m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);
            return (CString)"";
          }
        }
        else
        {
          if(lpcRestOfLine)
            return (CString)lpcRestOfLine;
          else
            return csTerm;
        }
      }
    }
  }

  CFileDialog dlg(TRUE, "rc", NULL, OFN_HIDEREADONLY, 
                  "Resource Script (*.rc)|*.rc|All Files (*.*)|*.*||",
                  NULL);

  m_pMainWnd = &dlg;

  int nResponse = dlg.DoModal();

  m_pMainWnd = NULL;

  if(nResponse == IDOK)
    return dlg.GetPathName();


  return (CString)"";
}


// -----------------
// UTILITY FUNCTIONS
// -----------------

CString GetVersionFromFileName(LPCSTR szName)
{
int i1, iBeginEndCount;
CString csFileName;
LPSTR lpBuf = NULL;
HANDLE hFile = INVALID_HANDLE_VALUE;


  if(!szName || !*szName)
  {
    return (CString)"";
  }

  csFileName = szName;

  hFile = CreateFile(csFileName, GENERIC_READ, 0,
                     NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                     INVALID_HANDLE_VALUE);

  if(hFile == INVALID_HANDLE_VALUE)
  {
    ::MessageBox(NULL, "File open error on \"" + csFileName + "\"",
                  theApp.m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);
    return (CString)"";
  }

  DWORD cbBytes, dwLen;
  BOOL bIsINF;

  // differentiate between INF files and RC files
  bIsINF = !(csFileName.Right(4).CompareNoCase(".INF"));

  dwLen = SetFilePointer(hFile, 0, NULL, FILE_END);
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

  lpBuf = (LPSTR)GlobalAlloc(GPTR, dwLen + 0x100);

  if(!lpBuf)
  {
    ::MessageBox(NULL, "Not enough memory to complete operation",
                  theApp.m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

    goto error_exit;
  }

  if(!dwLen ||
      !ReadFile(hFile, lpBuf, dwLen, &cbBytes, NULL) ||
      cbBytes != dwLen)
  {
    ::MessageBox(NULL, "Read error on input file",
                  theApp.m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);
    goto error_exit;
  }


  LPSTR lpBuf1 = lpBuf;
  LPSTR lpBuf2 = lpBuf + dwLen;

  BOOL bUnicode = FALSE;

  LPSTR lp1=lpBuf1, lp2=lpBuf2, lp3, lp4;

  if(dwLen > 1 &&
     (unsigned char)lpBuf[0] == 0xff &&
     (unsigned char)lpBuf[1] == 0xfe)
  {
    // detecting UNICODE - I need to support BOTH UNICODE and ASCII
    // though I can convert the text for comparisons, string manipulation, etc.
    // for a while, now, RC files have been unicode (but not always)
    // and INF files are typical ASCII.  But I must allow for EITHER ONE.

    bUnicode = TRUE; // this is a UNICODE file - begins with 0xff,0xfe

    lp1 += sizeof(WCHAR);  // skip past the first char on input
  }

  DWORD dwPos = 0;
  BOOL bChangedFlag = FALSE, bVersionInfoFlag=FALSE;

  iBeginEndCount = 0;

  while((DWORD)(lp1 - lpBuf1) < dwLen)
  {
    if((!bUnicode && !*lp1) ||  // for ASCII/UTF-8 files
        (bUnicode && !*((WCHAR *)lp1))) // for WCHAR unicode files
    {                                   // TODO:  handle 24-bit and 32-bit unicode?
      break;
    }

    CString csTemp, csTemp2;

    lp3 = lp1;

    if(bUnicode)
    {
      while((DWORD)(lp3 - lpBuf1) < (dwLen - 1) &&
            *((WCHAR *)lp3) &&
            *((WCHAR *)lp3) != '\r' &&
            *((WCHAR *)lp3) != '\n' &&
            *((WCHAR *)lp3) != '\xd')
      {
        lp3 += sizeof(WCHAR);
      }
    }
    else
    {
      while((DWORD)(lp3 - lpBuf1) < dwLen &&
            *lp3 &&
            *lp3 != '\r' &&
            *lp3 != '\n' &&
            *lp3 != '\xd')
      {
        lp3++;
      }
    }

    // make a copy of the line (as is)

    if(bUnicode)
    {
      lp4 = csTemp2.GetBufferSetLength(lp3 - lp1 + 2);
      memcpy(lp4, lp1, lp3 - lp1);
      lp4[lp3 - lp1] = 0;
      lp4[(lp3 - lp1) + 1] = 0;

      csTemp = (BSTR)lp4; // converts to ASCII
      csTemp2.ReleaseBuffer(0);
    }
    else
    {
      lp4 = csTemp.GetBufferSetLength(lp3 - lp1 + 1);
      memcpy(lp4, lp1, lp3 - lp1);
      lp4[lp3 - lp1] = 0;

      csTemp.ReleaseBuffer(-1);
    }

    // trim lead white space in a copy as 'csTemp2'

    csTemp2 = csTemp;
    csTemp2.TrimLeft();

    if(bIsINF) // INF files are different - I need a date,version
    {
      if(!csTemp2.Left(9).CompareNoCase("DriverVer"))
      {
        // the 'DriverVer' string looks like this (typically)
        // DriverVer = 04/04/2016,6.01.7600.16385    [white space optional]

        csTemp2 = csTemp2.Mid(9);  // trim off 'DriverVer'
        csTemp2.TrimLeft();

        if(csTemp2.GetLength() > 0 && csTemp2.GetAt(0) == '=')
        {
          // csTemp2 should have date,version now
          // return value will have '.' in it, not ','

          i1 = csTemp2.ReverseFind(',');
          if(i1 > 0)
          {
            csTemp2 = csTemp2.Mid(i1 + 1);
            csTemp2.TrimRight();
            csTemp2.TrimLeft();

            CloseHandle(hFile);
            GlobalFree((HANDLE)lpBuf);

            return csTemp2;
          }
        }
      }
    }
    else if(bVersionInfoFlag)  // am I looking through version info?
    {
      // version info has nested begin/end, but when nesting completes
      // the version info is complete.  Look for the final 'END'

      if(!iBeginEndCount && 
          (!csTemp2.Left(12).CompareNoCase("FILEVERSION ")) ) // only do THIS one
      {
        csTemp2 = csTemp2.Mid(12);

        csTemp2.TrimRight();
        csTemp2.TrimLeft();

        if(csTemp2.GetLength())
        {
          // convert the ',' into '.' and remove white space

          csTemp = "";
          for(i1=0; i1 < csTemp2.GetLength(); i1++)
          {
            if(csTemp2.GetAt(i1) == ',')
            {
              csTemp += '.';
            }
            else if(csTemp2.GetAt(i1) > ' ')
            {
              csTemp += csTemp2.GetAt(i1);
            }
          }

          CloseHandle(hFile);
          GlobalFree((HANDLE)lpBuf);

          return csTemp;
        }
      }
      else if(iBeginEndCount && 
              !csTemp2.Left(6).CompareNoCase("VALUE "))
      {
      }
      else if(!csTemp2.Left(5).CompareNoCase("BEGIN"))
      {
        iBeginEndCount++;
      }
      else if(!csTemp2.Left(3).CompareNoCase("END"))
      {
        if(iBeginEndCount)
        {
          iBeginEndCount--;
        }

        if(!iBeginEndCount)
        {
          bVersionInfoFlag = FALSE;
        }
      }
    }
    else if(!csTemp.Left(15).CompareNoCase("VS_VERSION_INFO"))
    {
      // See if this line begins with 'VS_VERSION_INFO', and if
      // so, flag it so that I can do the other stuff...

      bVersionInfoFlag = TRUE;
    }

    if(lp3 > lp1)  // i.e. there would have been something to copy
    {
      lp1 = lp3; // so I don't 'infinite loop'
    }

    if(bUnicode)
    {
      while((DWORD)(lp1 - lpBuf1) < (dwLen - 1) &&
            (*((WCHAR *)lp1) == '\r' ||
              *((WCHAR *)lp1) == '\n'))
      {
        lp1 += sizeof(WCHAR);  // pass up additional blank lines, etc.
      }
    }
    else
    {
      while((DWORD)(lp1 - lpBuf1) < dwLen &&
            (*lp1 == '\r' || *lp1 == '\n'))
      {
        lp1++;  // pass up additional blank lines, etc.
      }
    }

  }

  // if I get here there was an error but I did not prompt
  // so just indicate the problem (caller will not prompt on error return)

  ::MessageBox(NULL, "ERROR - unable to get version information from " + csFileName,
               theApp.m_pszAppName, MB_OK | MB_ICONHAND | MB_SETFOREGROUND);

error_exit: // error exit point - the only really good use for a label in C/C++

  if(hFile != INVALID_HANDLE_VALUE)
  {
    CloseHandle(hFile);
  }

  if(lpBuf)
  {
    GlobalFree((HANDLE)lpBuf);
  }

  return (CString)"";  // not found
}


CString TodaysDateStr(void)
{
CString csRval;
SYSTEMTIME tm;

  GetLocalTime(&tm);


  csRval.Format("%02d/%02d/%04d", tm.wMonth, tm.wDay, tm.wYear);

  return csRval;
}

