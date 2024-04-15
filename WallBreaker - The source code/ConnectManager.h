//---------------------------------------------------------------------------

#ifndef ConnectManagerH
#define ConnectManagerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <string>
#include <urlmon.h>
#include <windows.h>
#include <fstream>
#include <io.h>
//---------------------------------------------------------------------------
class TConMan : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TOpenDialog *OpenDialog2;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TMemo *Memo2;
	TButton *Button6;
	TButton *Button5;
	TButton *Button8;
	TPanel *Panel1;
	TButton *Button9;
	TLabel *Status;
	TLabel *Label2;
	TButton *Button7;
	void __fastcall Ovpncon(int cn, AnsiString App);
	void __fastcall Ovpnstat();
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
int st,fcnt;
public:		// User declarations
	AnsiString MyEntryNode,ovpnpass, ovpncfg, syscom, Stat;
	__fastcall TConMan(TComponent* Owner);
	char *IPFind();  char *Buffer;
	char *GateFind();
	int step,Ro,scnt;
	AnsiString Ctt,Ctn,VPN1LCGW, VPN1GLIP;
	void Torset();
	void __fastcall GetEntryNode();
};
//---------------------------------------------------------------------------
extern PACKAGE TConMan *ConMan;
//---------------------------------------------------------------------------
#endif
