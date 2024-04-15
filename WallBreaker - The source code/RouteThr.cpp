//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mainfm.h"
#include "ConnectManager.h"
#include "RouteThr.h"
#pragma package(smart_init)

__fastcall Route::Route(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall Route::Execute()
{
std::string s;
	AnsiString dwl=Mainform->cwd; dwl+="//actualtorip.csv";
	URLDownloadToFile( 0, "http://torstatus.blutmagie.de/ip_list_all.php/Tor_ip_list_ALL.csv", dwl.c_str(), 0, 0);
	Sleep (1500);
	if (GetFileAttributes(dwl.c_str()) != DWORD(-1)==0) Sleep (5000);
	if (GetFileAttributes(dwl.c_str()) != DWORD(-1)!=0)
	{
	ifstream file(dwl.c_str());
	AnsiString route,gateway=ConMan->GateFind();
	while(getline(file,s))
		{
		route="route add ";route+=(s).c_str();route+=" mask 255.255.255.255 ";route+=ConMan->gateway;
		WinExec(route.c_str(), SW_HIDE);
		Sleep(7);
		ConMan->Memo1->Lines->Add(route);
		if (Terminated) break;
		}
	file.close();
		} else ConMan->Label1->Caption="!!TORIPS_DWLD_FAIL!!";
}
//---------------------------------------------------------------------------
