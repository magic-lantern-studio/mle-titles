# Microsoft Developer Studio Project File - Name="mtea" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mtea - Win32 Float Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mtea.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mtea.mak" CFG="mtea - Win32 Float Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mtea - Win32 Float Debug" (based on "Win32 (x86) Application")
!MESSAGE "mtea - Win32 Float Release" (based on "Win32 (x86) Application")
!MESSAGE "mtea - Win32 GDK Win32 Float Debug" (based on "Win32 (x86) Application")
!MESSAGE "mtea - Win32 GDK Win32 Float Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mtea - Win32 Float Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Win32_Fl"
# PROP BASE Intermediate_Dir ".\Win32_Fl"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /Gz /Zp4 /W3 /GX /Zi /Od /I "s:\base\sharelib\src\util" /I "s:\base\sharelib\src\player" /I "s:\base\sharelib\src\pp" /I "s:\base\sharelib\src\math" /I "s:\base\parts\src\actors" /I "s:\base\parts\src\delegs" /I "s:\base\parts\src\forums" /I "s:\base\parts\src\mediaref" /I "s:\base\parts\src\stages" /I "s:\titles\teapot\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D FW_MATH_DEBUG=0 /D FW_FIXED_POINT=1 /D BASED_FLOAT=0 /D BASED_FIXED=1 /FR /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /ZI /Od /I ".." /I "$(MLE_HOME)\include" /I "$(BRENDER_PATH)\..\INC" /D "MLE_DEBUG" /D "MLE_NOT_DLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 actorsd.lib brrolesd.lib brsetsd.lib brmrefsd.lib brstaged.lib pcstaged.lib mlertd.lib playprintd.lib mlmathd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"$(MLE_HOME)/lib/brender" /libpath:"$(MLE_HOME)/lib/runtime/stdcall"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "mtea - Win32 Float Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Win32_F0"
# PROP BASE Intermediate_Dir ".\Win32_F0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /Gz /Zp4 /W3 /GX /Zi /Od /I "s:\base\sharelib\src\util" /I "s:\base\sharelib\src\player" /I "s:\base\sharelib\src\pp" /I "s:\base\sharelib\src\math" /I "s:\base\parts\src\actors" /I "s:\base\parts\src\delegs" /I "s:\base\parts\src\forums" /I "s:\base\parts\src\mediaref" /I "s:\base\parts\src\stages" /I "s:\titles\teapot\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D FW_MATH_DEBUG=0 /D FW_FIXED_POINT=1 /D BASED_FLOAT=0 /D BASED_FIXED=1 /FR /YX /c
# ADD CPP /nologo /Gz /Zp4 /ML /W3 /GX /O2 /I ".." /I "$(MLE_HOME)\include" /I "$(BRENDER_PATH)\..\INC" /D "MLE_NOT_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 actors.lib brroles.lib brsets.lib brmrefs.lib brstage.lib pcstage.lib mlert.lib playprint.lib mlmath.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"$(MLE_HOME)/lib/brender" /libpath:"$(MLE_HOME)/lib/runtime/stdcall"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "mtea - Win32 GDK Win32 Float Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\GDK_Win3"
# PROP BASE Intermediate_Dir ".\GDK_Win3"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /Gz /Zp4 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D FW_MATH_DEBUG=0 /D FW_FIXED_POINT=0 /D BASED_FLOAT=1 /D BASED_FIXED=0 /FR /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /ZI /Od /I ".." /I "$(MLE_HOME)\include" /I "$(BRENDER_PATH)\..\INC" /D "MLE_DEBUG" /D "MLE_NOT_DLL" /D "_DEBUG" /D "_GDK_" /D "WIN32" /D "_WINDOWS" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 fwd.lib fwbrd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "mtea - Win32 GDK Win32 Float Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\GDK_Win0"
# PROP BASE Intermediate_Dir ".\GDK_Win0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /Gz /Zp4 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D FW_MATH_DEBUG=0 /D FW_FIXED_POINT=0 /D BASED_FLOAT=1 /D BASED_FIXED=0 /FR /YX /c
# ADD CPP /nologo /Gz /Zp4 /ML /W3 /GX /O2 /I ".." /I "$(MLE_HOME)\include" /I "$(BRENDER_PATH)\..\INC" /D "NDEBUG" /D "MLE_NOT_DLL" /D "_GDK_" /D "WIN32" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 fw.lib fwbr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "mtea - Win32 Float Debug"
# Name "mtea - Win32 Float Release"
# Name "mtea - Win32 GDK Win32 Float Debug"
# Name "mtea - Win32 GDK Win32 Float Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\callback.cxx
# End Source File
# Begin Source File

SOURCE=.\main.cxx
# End Source File
# Begin Source File

SOURCE=.\mlchunk.cxx
# End Source File
# Begin Source File

SOURCE=.\mltables.cxx
# End Source File
# Begin Source File

SOURCE=..\spinnera.cxx
# End Source File
# Begin Source File

SOURCE=.\texture.cxx
# End Source File
# Begin Source File

SOURCE=.\title.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\app.h
# End Source File
# Begin Source File

SOURCE=.\callback.h
# End Source File
# Begin Source File

SOURCE=.\mlchunk.h
# End Source File
# Begin Source File

SOURCE=.\mlPlatformData.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\spinnera.h
# End Source File
# Begin Source File

SOURCE=.\texture.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\app.rc
# End Source File
# Begin Source File

SOURCE=.\fw.ico
# End Source File
# End Group
# End Target
# End Project
