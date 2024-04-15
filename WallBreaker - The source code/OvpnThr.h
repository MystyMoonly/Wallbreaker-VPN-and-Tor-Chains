//---------------------------------------------------------------------------

#ifndef OvpnThrH
#define OvpnThrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class ovpnth : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall ovpnth(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
