//---------------------------------------------------------------------------

#ifndef VPN2FH
#define VPN2FH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TVPN2Form : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TOpenDialog *OpenDialog1;
	TOpenDialog *OpenDialog2;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
	AnsiString ovpnpass, ovpncfg, syscom2;
	__fastcall TVPN2Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVPN2Form *VPN2Form;
//---------------------------------------------------------------------------
#endif
