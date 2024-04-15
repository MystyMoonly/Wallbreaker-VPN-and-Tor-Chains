//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mainfm.h"
#include "Unit1.h"
#pragma package(smart_init)


__fastcall TorThr1::TorThr1(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TorThr1::Execute()
{
AnsiString torc=Mainform->cwd;torc+="//tor.exe"; WinExec(torc.c_str(), SW_HIDE);
}
//---------------------------------------------------------------------------
