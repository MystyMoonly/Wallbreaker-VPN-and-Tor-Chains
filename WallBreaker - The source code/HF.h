//---------------------------------------------------------------------------

#ifndef HFH
#define HFH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THelpForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Name1;
	TLabel *Note1;
	TLabel *Name2;
	TLabel *Note2;
	TLabel *Name3;
	TLabel *Note3;
	TLabel *Infoc;
	TLabel *Info1;
	TLabel *Info2;
	TLabel *Info3;
private:	// User declarations
public:		// User declarations
	__fastcall THelpForm(TComponent* Owner);
	void HelpFromMain(); void HelpFromConMan();
};
//---------------------------------------------------------------------------
extern PACKAGE THelpForm *HelpForm;
//---------------------------------------------------------------------------
#endif
