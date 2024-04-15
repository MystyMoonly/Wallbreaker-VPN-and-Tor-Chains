//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mainfm.h"
#include "OvpnThr.h"
#include "TorThr.h"
#include "ConnectManager.h"
#pragma package(smart_init)
__fastcall Torcon::Torcon(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//1---------------------------------------------------------------------------
void __fastcall Torcon::Execute()
{
if (Mainform->SetC==1) ShellExecute(0, "open", ConMan->Ctt.c_str(), 0, 0, SW_SHOW);
else { ShellExecute(0, "open", ConMan->Ctt.c_str(), ConMan->Ctn.c_str(), 0, SW_SHOW); }
}
//---------------------------------------------------------------------------
