//---------------------------------------------------------------------------

#ifndef MainfmH
#define MainfmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainform : public TForm
{
__published:	// IDE-managed Components
	TLabel *AVTB;
	TButton *InstallDriver;
	TButton *UninstallDrivers;
	TLabel *ATVB;
	TLabel *AVTVB;
	TButton *Help;
	TPanel *Panel1;
	TLabel *Note1;
	void __fastcall AVTBClick(TObject *Sender);
	void __fastcall InstallDriverClick(TObject *Sender);
	void __fastcall UninstallDriversClick(TObject *Sender);
	void __fastcall ATVBClick(TObject *Sender);
	void __fastcall AVTVBClick(TObject *Sender);
	void __fastcall HelpClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations

		AnsiString cmd;

public:		// User declarations
	char cwd[3000];
	int SetC;
	__fastcall TMainform(TComponent* Owner);
	char *Routes;
	AnsiString DefRoutes;
	int fr,IsConAct;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainform *Mainform;
//---------------------------------------------------------------------------
#endif
