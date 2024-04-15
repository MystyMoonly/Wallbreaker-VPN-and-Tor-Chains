//---------------------------------------------------------------------------

#ifndef TorThrH
#define TorThrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class Torcon : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Torcon(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
