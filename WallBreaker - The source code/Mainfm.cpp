//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <direct.h>

#include "Mainfm.h"
#include "TorThr.h"
#include "ConnectManager.h"
#include "HF.h"

#include <iphlpapi.h>
#include <Iptypes.h>
#include <string.h>
#include <dstring.h>

#pragma link "iphlpapi.lib"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainform *Mainform;

//---------------------------------------------------------------------------
__fastcall TMainform::TMainform(TComponent* Owner)
	: TForm(Owner)
{
fr=1;
_getcwd(cwd, sizeof(cwd));
Note1->Caption="����� �������������� OpenVPN ���������� ���������� ������� TAP ��������\r\                 �� ����� ��������� ����� ������������� �������������!";
IsConAct=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainform::AVTBClick(TObject *Sender)
{
SetC=1;
ConMan->Button3->Left=172; ConMan->Button3->Top=196;
ConMan->Label1->Caption="��������� OpenVPN";ConMan->Button6->Visible=false; ConMan->Button6->Visible=false;ConMan->Label2->Visible=false;
ConMan->Button7->Visible=false;
ConMan->Caption="��������� ����������� VPN+TOR";
ConMan->Show();
this->Enabled=false;
this->Hide();
}
//---------------------------------------------------------------------------


void __fastcall TMainform::InstallDriverClick(TObject *Sender)
{
 if (MessageBox(0,"�� ������������� ������ ���������� �������? (����� ������������� ���������� �� ���������)","��������� ��� ��������!", MB_YESNO) == mrYes)
 {cmd='"'; cmd+=cwd; cmd+="\\addtap.bat"; cmd+='"';	WinExec(cmd.c_str(), SW_HIDE);}
}
//---------------------------------------------------------------------------

void __fastcall TMainform::UninstallDriversClick(TObject *Sender)
{
 if (MessageBox(0,"�� ������������� ������ ������� ��� tap ��������?","��������� ��� ��������!", MB_YESNO) == mrYes)
 {cmd='"'; cmd+=cwd; cmd+="\\deltap.bat"; cmd+='"';	WinExec(cmd.c_str(), SW_HIDE);}
}
//---------------------------------------------------------------------------


void __fastcall TMainform::ATVBClick(TObject *Sender)
{
SetC=2;
ConMan->Button3->Left=172; ConMan->Button3->Top=196;
ConMan->Label1->Caption="��������� OpenVPN";ConMan->Button6->Visible=false;ConMan->Label2->Visible=false;
ConMan->Button7->Visible=true;
ConMan->Caption="��������� ����������� TOR+VPN";
ConMan->Show();
this->Enabled=false;
this->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainform::AVTVBClick(TObject *Sender)
{
SetC=3;
ConMan->Button3->Left=287; ConMan->Button3->Top=196;
ConMan->Label1->Caption="��������� OpenVPN �1";ConMan->Button6->Visible=true;ConMan->Label2->Visible=true;
ConMan->Button7->Visible=true;
ConMan->Caption="��������� ����������� VPN+TOR+VPN";
ConMan->Show();
this->Enabled=false;
this->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainform::HelpClick(TObject *Sender)
{
HelpForm->HelpFromMain();
HelpForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainform::FormCloseQuery(TObject *Sender, bool &CanClose)
{
if (IsConAct==1) {
 if (MessageBox(0,"� ��� �� ��� ������� �����������! ��� �������� ���������, ��� ��������. ������� ���������?","��������!", MB_YESNO) == mrYes)
 {ConMan->Button4->Click(); CanClose=true;}
 else  {CanClose=false; ConMan->Show();}
 } else CanClose=true;
}
//---------------------------------------------------------------------------


