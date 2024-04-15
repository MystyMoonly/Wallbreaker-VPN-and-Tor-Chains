//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mainfm.h"
#include "OvpnThr.h"
#include "TorThr.h"
#include "ConnectManager.h"
#include "VPN2F.h"
#include "HF.h"
#include "ConsoleOvpn.h"

#pragma comment(lib,"iphlpapi.lib")
#include <winsock.h>
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include "Unit1.h"
#pragma comment (lib, "urlmon.lib")
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
class ovpnth *VP = new ovpnth(true);
class Torcon *TR = new Torcon(true);

std::string ovch="";
TConMan *ConMan;
//---------------------------------------------------------------------------
__fastcall TConMan::TConMan(TComponent* Owner)
	: TForm(Owner)
{
fcnt=0;
ovpncfg=ovpnpass="none"; st=Ro=0;
MyEntryNode="-none-";
VPN1GLIP="Empty";
}
//---------------------------------------------------------------------------
void __fastcall TConMan::Button1Click(TObject *Sender)
{
if (Mainform->SetC!=3) Label1->Caption="Настройка VPN "; else Label1->Caption="Настройка VPN №1: ";
OpenDialog1->Execute();
if (OpenDialog1->FileName!="")
{
ovpncfg=(char)34;
ovpncfg+=OpenDialog1->FileName.c_str();
ovpncfg+=(char)34;
}
}
//---------------------------------------------------------------------------
void __fastcall TConMan::Button2Click(TObject *Sender)
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
void __fastcall TConMan::Button3Click(TObject *Sender)
{
	if (ovpncfg != "none")
	{
	if ((Mainform->SetC==3)&&(VPN2Form->ovpncfg == "none")) ShowMessage ("Ошибка! Проверьте настройки VPN №2");
	else {
	if (Mainform->SetC==3) Button6->Visible=false;
	syscom="openvpn.exe --config ";
	syscom+=ovpncfg;
	if (Mainform->SetC==2)	syscom+=" --socks-proxy 127.0.0.1 9050 --socks-proxy-retry";
	if (ovpnpass != "none")
	{
	syscom+=" --auth-user-pass ";
	syscom+=ovpnpass;
	}
	Csl->Console->Text=""; ovch=""; Button2->Visible=false;
	Button3->Visible=false;Button4->Visible=true;Button1->Visible=false;
	Button6->Visible=false;Button8->Visible=false;Button9->Visible=true;
	Mainform->IsConAct=1;
	Status->Caption="Состояние: Подключение...";
	if (Mainform->SetC==2) Torset();
	if (Mainform->SetC!=2) { delete VP;  class ovpnth *VP = new ovpnth(true); VP->Resume(); }

	Sleep(300);   }
	} else ShowMessage ("Вы не указали файл конфигурации!");
}
//---------------------------------------------------------------------------
void __fastcall TConMan::Button4Click(TObject *Sender)
{AnsiString rdel; scnt=0;
if ((VPN1GLIP!="127.0.0.1")&&(VPN1GLIP!="Empty")) {
	rdel="route delete "+VPN1GLIP;
	WinExec(rdel.c_str(), SW_HIDE); }
	rdel="route delete "+MyEntryNode;
	WinExec(rdel.c_str(), SW_HIDE);
VPN1GLIP="Empty";
if (Stat=="ERROR_BAD_OVPN")MessageBox(NULL, "Конфигурационный файл OpenVPN поврежден!", "Ошибка подключения!", NULL);
if (Stat=="ERROR_AUTH_MISSING")MessageBox(NULL, "VPN сервер требует авторизации по логину/паролю!", "Ошибка подключения!", NULL);
if (Stat=="ERROR_AUTH_FAIL")MessageBox(NULL, "Данные авторизации неверны! Проверьте логин или пароль в файле", "Ошибка подключения!", NULL);
if (Stat=="ERROR_CON_FAIL")MessageBox(NULL, "При соединении с сервером возникла ошибка!", "Ошибка подключения!", NULL);
if (Stat=="ERROR_TAP_MISSING")MessageBox(NULL, "Отсутствует TAP адаптер!", "Ошибка подключения!", NULL);
if (Stat=="ERROR_TIMEDOUT")MessageBox(NULL, "Превышено время ожидания ответа сервера", "Ошибка подключения!", NULL);
if (Mainform->SetC==3){ if (Stat=="ERROR_TAP_IN_USE")MessageBox(NULL, "Все TAP адаптеры заняты! Для подключения VPN+TOR+VPN Требуется два TAP адаптера!", "Ошибка подключения!", NULL);
else if (Stat=="ERROR_TAP_IN_USE") MessageBox(NULL, "Все TAP адаптеры заняты!", "Ошибка подключения!", NULL); }
if (Stat=="ERROR_BAD_TOR_ENTRY")MessageBox(NULL, "Не удаётся подключиться к VPN серверу через ТОР попробуйте подключиться снова!", "Ошибка подключения!", NULL);
if (Stat=="NOT_SO_SUCCESS")MessageBox(NULL, "Возникли ошибки во время подключения к серверу VPN. Пожалуйста повторите попытку!", "Ошибка подключения!", NULL);
Csl->Hide();
Stat="";
VP->Terminate();
TR->Terminate();
step=0;  fcnt=0;
WinExec("taskkill /f /im openvpn.exe", SW_HIDE);
WinExec("taskkill /f /im tor.exe", SW_HIDE);
Sleep(300);
if (Mainform->SetC==3) Button6->Visible=true;
Button2->Visible=true;Button8->Visible=true;Button9->Visible=false;
Button3->Visible=true;Button4->Visible=false;Button1->Visible=true;
Csl->Console->Text="Отключено!";
Status->Caption="Состояние: Отключено";
Mainform->IsConAct=0;
}
//---------------------------------------------------------------------------

void __fastcall TConMan::Ovpncon(int cn, AnsiString App)
{
#define READ_BUFFER_SIZE 1024
AnsiString AppName = App;
SECURITY_ATTRIBUTES Security;
HANDLE ReadPipe, WritePipe;
STARTUPINFO Start;
TProcessInformation ProcessInfo;
char Data;
DWORD BytesRead, Apprunning;
int Result, DataSize;
Csl->Console->Text="";

Security.nLength = sizeof(TSecurityAttributes);
Security.bInheritHandle = true;
Security.lpSecurityDescriptor = NULL;

if (CreatePipe(&ReadPipe, &WritePipe, &Security, 0))
  {
  Buffer = new char[READ_BUFFER_SIZE + 1];

  memset(&Start, 0, sizeof(Start));
  Start.cb = sizeof(Start) ;
  Start.hStdOutput = WritePipe;
  Start.hStdInput = ReadPipe;
  Start.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
  Start.wShowWindow = SW_HIDE;

  if (CreateProcess(NULL, AppName.c_str(), &Security, &Security, true, NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE, NULL, NULL, &Start, &ProcessInfo))
	{
	do
	  {
	  Apprunning = WaitForSingleObject(ProcessInfo.hProcess, 100);
	  Application->ProcessMessages();
	  // вычитываем данные работающей консоли
	  do
		{
		Result = PeekNamedPipe(ReadPipe, NULL, 0, NULL, (LPDWORD) &DataSize, NULL);
		if ((Result) && (DataSize))
		  {
		  if (DataSize > READ_BUFFER_SIZE) DataSize = READ_BUFFER_SIZE;
		  ReadFile(ReadPipe, Buffer, DataSize, &BytesRead, NULL);
		  Buffer[BytesRead] = 0;
		  OemToAnsi(Buffer, Buffer);
		  if (cn==1) Csl->Console->Text = Csl->Console->Text + (AnsiString)Buffer;
		  if (cn==0) Memo2->Text = Memo2->Text + (AnsiString)Buffer;
		  if (scnt==1) ovch="";
		  ovch=Buffer;
		  if (cn==1) Ovpnstat();
		  }
		}
	  while ((Result) && (DataSize));
	  }
	while (Apprunning == WAIT_TIMEOUT);
	}

  delete [] Buffer;

  CloseHandle(ProcessInfo.hProcess);
  CloseHandle(ProcessInfo.hThread);
  CloseHandle(ReadPipe);
  CloseHandle(WritePipe);
	}
}

void __fastcall TConMan::Ovpnstat()
{
std::string temp;
int sr;
// Ошибка: Невозможно открыть конфигурацию
//------------------------------------------
temp = "Options error: Unrecognized option or missing parameter(s) in";
sr = ovch.find(temp); // поиск

if (sr != -1)
{ Stat="ERROR_BAD_OVPN"; Button4->Click(); }
//------------------------------------------

// Ошибка: Сервер требует авторизации
//------------------------------------------
temp = "ERROR: could not read Auth username from";
sr = ovch.find(temp); // поиск

if (sr != -1)
{Stat="ERROR_AUTH_MISSING"; Button4->Click(); }
//------------------------------------------

// Ошибка: Неверный логин или пароль
//------------------------------------------

temp = "AUTH: Received control message: AUTH_FAILED";
sr = ovch.find(temp); // поиск

if (sr != -1)
{Stat="ERROR_AUTH_FAIL"; Button4->Click(); }
//------------------------------------------

// Ошибка при подключении (Повтор)
//------------------------------------------
if (st != 1)
{
temp = "Restart pause, 2 second(s)";
sr = ovch.find(temp); // поиск

if (sr != -1)
{Stat="ERROR_CON_FAIL"; Button4->Click(); }
}
//------------------------------------------

// Ошибка при подключении
//------------------------------------------
if (st == 0)
{
temp = "Restart pause, 2 second(s)";
sr = ovch.find(temp); // поиск
if (sr != -1) st=1;
}
//------------------------------------------



// Ошибка: TAP-Адаптер не найден
//------------------------------------------

temp = "Sequence Completed With Errors";
sr = ovch.find(temp); // поиск
if (sr != -1)
{Stat="NOT_SO_SUCCESS"; Button4->Click(); }

//------------------------------------------

// Ошибка: TAP-Адаптер не найден
//------------------------------------------

temp = "There are no TAP-Windows adapters on this system.";
sr = ovch.find(temp); // поиск
if (sr != -1)
{Stat="ERROR_TAP_MISSING"; Button4->Click(); }

//------------------------------------------

// Ошибка: Сервер недоступен
//------------------------------------------

temp = "failed, will try again in 5 seconds: Connection timed out (WSAETIMEDOUT)";
sr = ovch.find(temp); // поиск
if (sr != -1)
{Stat="ERROR_TIMEDOUT"; Button4->Click(); }

//------------------------------------------

// Ошибка: Все ТАР адаптеры заняты!
//------------------------------------------

temp = "All TAP-Windows adapters on this system are currently in use";
sr = ovch.find(temp); // поиск
if (sr != -1)
{Stat="ERROR_TAP_IN_USE"; Button4->Click(); }

//------------------------------------------

// Ошибка: Тор не подключается!
//------------------------------------------

temp = "SIGUSR1[soft,init_instance] received, process restarting";

sr = ovch.find(temp); // поиск
if (sr != -1)
fcnt++;
if (fcnt>4) {Stat="ERROR_BAD_TOR_ENTRY"; fcnt=0; Button4->Click(); }
//------------------------------------------
// Успешное подключение
//------------------------------------------
temp = "Initialization Sequence Completed";
sr = ovch.find(temp); // поиск

if (sr != -1)
{ if ((Mainform->SetC!=2)&&(step!=2)) Torset(); Stat="SUCCESS"; if (scnt==0) scnt=1;
  if (Mainform->SetC==1) { MessageBox(NULL, "Вы подключены по VPN+TOR", "Успешное подключение", NULL); Status->Caption="Состояние: Подключено VPN+TOR"; }
  if (Mainform->SetC==2) { MessageBox(NULL, "Вы подключены по TOR+VPN", "Успешное подключение", NULL); Status->Caption="Состояние: Подключено TOR+VPN"; }
  if ((Mainform->SetC==3)&&(scnt==2)) { MessageBox(NULL, "Вы подключены по VPN+TOR+VPN", "Успешное подключение", NULL); Status->Caption="Состояние: Подключено VPN+TOR+VPN"; scnt=0;}}
if ((scnt==1)&&(sr==-1)) scnt=2;
//------------------------------------------
// Находим IP VPN #1
//------------------------------------------
temp = "connection with [AF_INET]";
sr = ovch.find(temp); // поиск
if ((sr != -1)&&(step!=2)&&(VPN1GLIP=="Empty"))                        {
char tmpip[15]; ZeroMemory(tmpip,15);
	for (unsigned int i=sr+25; i<=(strlen((ovch).c_str()));i++)
	if (((ovch).c_str()[i]!='[')&&((ovch).c_str()[i]!=':')) tmpip[i-(sr+25)]=(ovch).c_str()[i]; else break;
	VPN1GLIP=tmpip; }
}
//------------------------------------------

void TConMan::Torset()
{
if (Mainform->SetC!=1)
{
AnsiString route="/C ";
Ctt=Mainform->cwd; Ctt+="//tor.exe";
AnsiString dwl=Mainform->cwd; dwl+="//actualtorip.csv";
if (GetFileAttributes(dwl.c_str()) != DWORD(-1)==0) URLDownloadToFile( 0, "http://torstatus.blutmagie.de/ip_list_all.php/Tor_ip_list_ALL.csv", dwl.c_str(), 0, 0);
if (GetFileAttributes(dwl.c_str()) != DWORD(-1)==0) Sleep (5000);
if (GetFileAttributes(dwl.c_str()) != DWORD(-1)!=0)
	{
	if (ConMan->MyEntryNode=="-none-") GetEntryNode();
	Ctn="EntryNode ";Ctn+=MyEntryNode;
	delete TR; class Torcon *TR = new Torcon(true); TR->Resume();
	route+="route add ";route+=ConMan->MyEntryNode;route+=" mask 255.255.255.255 ";if (Mainform->SetC==2) route+=GateFind(); else route+=VPN1LCGW=ConMan->GateFind();
	ShellExecute(0, "open", "cmd.exe", route.c_str(), 0, SW_HIDE);
if (Mainform->SetC==3) ConMan->step=2;
Sleep (500); class ovpnth *VP = new ovpnth(true); VP->Resume();
	}
else { MessageBox(NULL, "Ошибка загрузки списка IP адресов TOR, вы можете найти их самостоятельно, и поместить в файл actualtopip", "Ошибка подключения к TOR", NULL); Status->Caption="Состояние: Отключено"; }
}
else { Ctt=Mainform->cwd; Ctt+="//tor.exe"; delete TR; class Torcon *TR = new Torcon(true); TR->Resume(); }
}

char *TConMan::IPFind()
{
   WORD wVersionRequested;
  WSADATA wsaData;
   wVersionRequested = MAKEWORD(1, 0);
   int err = WSAStartup(wVersionRequested, &wsaData);
    if(err == 0)
  {        char hn[1024];
        struct hostent *adr;
		if(gethostname((char *)&hn, 1024))
 {            int err = WSAGetLastError();
			Beep();
        };
		adr = gethostbyname(hn);
	   if(adr)        {          char *LocalIp = new char[15];
		  sprintf(LocalIp,"%d.%d.%d.%d",
        (unsigned char)adr->h_addr_list[0][0],
	   (unsigned char)adr->h_addr_list[0][1],
      (unsigned char)adr->h_addr_list[0][2],
	  (unsigned char)adr->h_addr_list[0][3]);
	   return LocalIp;
	  }
   }

}

char *TConMan::GateFind()
{
	char *IP=IPFind();
	AnsiString cmd = "route print";
	ConMan->Ovpncon(0,cmd);
		std::string findstr; int sr=0;
		TStringList *list = new TStringList;
		list->Text=ConMan->Memo2->Text;
		AnsiString temp;
		for(int i = 0; i < list->Count-1; i++)
		{
			temp = list->Strings[i];
			findstr=temp.c_str();
			if(temp.Length() < 10)
				list->Delete(i--); // удаляем пустые строки
			else if(temp[1] != ' ')
				list->Delete(i--); // удаляем если первый символ не равен пробелу
			else if(!isdigit(temp[temp.Length()]))
				list->Delete(i--); // удаляем если последний символ в строке не равен числу
			else if ((findstr.find("224.0.0.0")!=-1)||(findstr.find("225.0.0.0")!=-1)||(findstr.find("226.0.0.0")!=-1))
				list->Delete(i--);
			else if ((findstr.find("227.0.0.0")!=-1)||(findstr.find("228.0.0.0")!=-1)||(findstr.find("229.0.0.0")!=-1))
				list->Delete(i--);
			else if ((findstr.find("230.0.0.0")!=-1)||(findstr.find("231.0.0.0")!=-1)||(findstr.find("232.0.0.0")!=-1))
				list->Delete(i--);
			else if ((findstr.find("233.0.0.0")!=-1)||(findstr.find("234.0.0.0")!=-1)||(findstr.find("235.0.0.0")!=-1))
				list->Delete(i--);
			else if ((findstr.find("236.0.0.0")!=-1)||(findstr.find("237.0.0.0")!=-1)||(findstr.find("238.0.0.0")!=-1)||(findstr.find("239.0.0.0")!=-1))
				list->Delete(i--);
			else if (findstr.find("0.0.0.0")==-1)
			list->Delete(i--);
			else if (findstr.find(IP)==-1)	list->Delete(i--);
		}
		temp=list->Text;
		findstr=temp.c_str();
		if (list->Text=="") { ShowMessage("Критическая ошибка! Невозможно получить основной шлюз!"); ConMan->Memo2->Clear(); return "404";}
		ConMan->Memo2->Clear();
		int pos;
		char IPftr[8]; ZeroMemory(IPftr,8);		char GW[15]; ZeroMemory(GW,15);
		for (unsigned int i=0; i <= strlen(IP); i++)
		if (IP[i]!='.') IPftr[i]=IP[i]; else { IPftr[i]='.'; break; }
		pos=findstr.find(IPftr);
		for (unsigned int i=pos; i < strlen((findstr).c_str()); i++)
			if ((findstr).c_str()[i]!=' ') GW[sr++]=(findstr).c_str()[i]; else break;
		list->Clear();
		delete list;
        return GW;
	}


//------------------------------------------

void __fastcall TConMan::Button5Click(TObject *Sender)
{
HelpForm->HelpFromConMan();
HelpForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConMan::Button6Click(TObject *Sender)
{
VPN2Form->Show();
this->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TConMan::Button8Click(TObject *Sender)
{
ovpncfg=ovpnpass="none";
VPN2Form->ovpncfg="none";VPN2Form->ovpnpass="none";
OpenDialog1->FileName=NULL;
OpenDialog2->FileName=NULL;
VPN2Form->OpenDialog1->FileName=NULL;
VPN2Form->OpenDialog2->FileName=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TConMan::Button9Click(TObject *Sender)
{
Csl->Show();
}

void __fastcall TConMan::GetEntryNode()
{
int a;
AnsiString dwl=Mainform->cwd; dwl+="//actualtorip.csv";
if (GetFileAttributes(dwl.c_str()) != DWORD(-1)==0) URLDownloadToFile( 0, "http://torstatus.blutmagie.de/ip_list_all.php/Tor_ip_list_ALL.csv", dwl.c_str(), 0, 0);
TStringList *tor = new TStringList();
tor->LoadFromFile(dwl);
randomize();
a=random(tor->Count);
ConMan->MyEntryNode=tor->Strings[a];
AnsiString mes="Ваш EntryNode: ";mes+=ConMan->MyEntryNode.c_str();
MessageBox(0 ,mes.c_str(),"TOR",MB_OK);
tor->Free();
}

void __fastcall TConMan::Button7Click(TObject *Sender)
{
GetEntryNode();
}
//---------------------------------------------------------------------------

void __fastcall TConMan::FormCloseQuery(TObject *Sender, bool &CanClose)
{
Mainform->Enabled=true;
Mainform->Show();
}
//---------------------------------------------------------------------------

