//---------------------------------------------------------------------------

#ifndef ConsoleOvpnH
#define ConsoleOvpnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCsl : public TForm
{
__published:	// IDE-managed Components
	TMemo *Console;
private:	// User declarations
public:		// User declarations
	__fastcall TCsl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCsl *Csl;
//---------------------------------------------------------------------------
#endif
