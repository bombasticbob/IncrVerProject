##################################################################################
##                                                                              ##
##   ___  _   _   ____  ____ __     __ _____  ____      __  __     _     _  __  ##
##  |_ _|| \ | | / ___||  _ \\ \   / /| ____||  _ \    |  \/  |   / \   | |/ /  ##
##   | | |  \| || |    | |_) |\ \ / / |  _|  | |_) |   | |\/| |  / _ \  | ' /   ##
##   | | | |\  || |___ |  _ <  \ V /  | |___ |  _ <  _ | |  | | / ___ \ | . \   ##
##  |___||_| \_| \____||_| \_\  \_/   |_____||_| \_\(_)|_|  |_|/_/   \_\|_|\_\  ##
##                                                                              ##
##                                                                              ##
##################################################################################
##                                                                              ##
##            Copyright (c) 2016 by S.F.T. Inc. - All rights reserved           ##
##    Use, copying, and distribution of this software are licensed according    ##
##             to the the 2-clause BSD license specified in LICENSE             ##
##                                                                              ##
##################################################################################


# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
#CFG=INCRVER - Win32 Debug
CFG=INCRVER - Win32 Release
!MESSAGE No configuration specified.  Defaulting to INCRVER - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "INCRVER - Win32 Release" && "$(CFG)" !=\
 "INCRVER - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "INCRVER.MAK" CFG="INCRVER - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "INCRVER - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "INCRVER - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "INCRVER - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\INCRVER.exe"

CLEAN : 
	-@erase ".\Release\INCRVER.exe"
	-@erase ".\Release\INCRVER.obj"
	-@erase ".\Release\INCRVER.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\INCRVER.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/INCRVER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INCRVER.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/INCRVER.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/INCRVER.pdb" /machine:I386 /out:"$(OUTDIR)/INCRVER.exe" 
LINK32_OBJS= \
	"$(INTDIR)/INCRVER.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/INCRVER.res"

"$(OUTDIR)\INCRVER.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "INCRVER - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\INCRVER.exe"

CLEAN : 
	-@erase ".\Debug\INCRVER.exe"
	-@erase ".\Debug\INCRVER.obj"
	-@erase ".\Debug\INCRVER.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\INCRVER.res"
	-@erase ".\Debug\INCRVER.ilk"
	-@erase ".\Debug\INCRVER.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/INCRVER.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/INCRVER.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/INCRVER.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/INCRVER.pdb" /debug /machine:I386 /out:"$(OUTDIR)/INCRVER.exe" 
LINK32_OBJS= \
	"$(INTDIR)/INCRVER.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/INCRVER.res"

"$(OUTDIR)\INCRVER.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "INCRVER - Win32 Release"
# Name "INCRVER - Win32 Debug"

!IF  "$(CFG)" == "INCRVER - Win32 Release"

!ELSEIF  "$(CFG)" == "INCRVER - Win32 Debug"

!ENDIF 

# REBUILD TARGET

REBUILD : CLEAN ALL


################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "INCRVER - Win32 Release"

!ELSEIF  "$(CFG)" == "INCRVER - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INCRVER.cpp
DEP_CPP_INCRV=\
	".\StdAfx.h"\
	".\INCRVER.h"\
	

"$(INTDIR)\INCRVER.obj" : $(SOURCE) $(DEP_CPP_INCRV) "$(INTDIR)"\
 "$(INTDIR)\INCRVER.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "INCRVER - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/INCRVER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\INCRVER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "INCRVER - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/INCRVER.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\INCRVER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INCRVER.rc
DEP_RSC_INCRVE=\
	".\res\INCRVER.ico"\
	".\res\INCRVER.rc2"\
	

"$(INTDIR)\INCRVER.res" : $(SOURCE) $(DEP_RSC_INCRVE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
