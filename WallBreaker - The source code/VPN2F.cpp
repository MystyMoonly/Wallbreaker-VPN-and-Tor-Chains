//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectManager.h"
#include "VPN2F.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVPN2Form *VPN2Form;
//---------------------------------------------------------------------------
__fastcall TVPN2Form::TVPN2Form(TComponent* Owner)
	: TForm(Owner)
{
ovpncfg="none"; ovpnpass="none";
}
//---------------------------------------------------------------------------
void __fastcall TVPN2Form::Button1Click(TObject *Sender)
{
Label1->Caption="Настройка VPN №2: ";
OpenDialog1->Execute();
if (OpenDialog1->FileName!="")
{
ovpncfg=(char)34;
ovpncfg+=OpenDialog1->FileName.c_str();
ovpncfg+=(char)34;
}
}
//---------------------------------------------------------------------------

void __fastcall TVPN2Form::Button2Click(TObject *Sender)
{
OpenDialog2->Execute();
if (OpenDialog2->FileName!="")
{
ovpnpass=(char)34;
ovpnpass+=OpenDialog2->FileName.c_str();
ovpnpass+=(char)34;
}
}
//---------------------------------------------------------------------------
void __fastcall TVPN2Form::Button3Click(TObject *Sender)
{
if (ovpncfg != "none")
	{
	syscom2="openvpn.exe --config ";
	syscom2+=ovpncfg;
   	syscom2+=" --socks-proxy 127.0.0.1 9050 --socks-proxy-retry";
	if (ovpnpass != "none")
	{
	syscom2+=" --auth-user-pass ";
	syscom2+=ovpnpass;

	}
	this->Close();
	Sleep(300);
	} else Label1->Caption="Вы не указали файл конфигурации!";
}
//---------------------------------------------------------------------------
void __fastcall TVPN2Form::FormCloseQuery(TObject *Sender, bool &CanClose)
{
ConMan->Enabled=true;
}
//---------------------------------------------------------------------------

