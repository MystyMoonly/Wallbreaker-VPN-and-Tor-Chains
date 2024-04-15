//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mainfm.h"
#include "ConnectManager.h"
#include "OvpnThr.h"
#include "VPN2F.h"
#include "ConsoleOvpn.h"

#pragma package(smart_init)

__fastcall ovpnth::ovpnth(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ovpnth::Execute()
{
int timer=0;
if (!Terminated) {
if ((Mainform->SetC==3)&&(ConMan->step==2))
{
Csl->Console->Text += "=================\n=Подключено!=\n=================";
ConMan->Stat="";
Sleep (5500);
ConMan->Ovpncon(1,VPN2Form->syscom2);
this->Terminate();
}
else if (Mainform->SetC!=1) { ConMan->Ovpncon(1,ConMan->syscom); this->Terminate(); }
else {ConMan->Ovpncon(1,ConMan->syscom); this->Terminate(); }
}
}
//---------------------------------------------------------------------------
