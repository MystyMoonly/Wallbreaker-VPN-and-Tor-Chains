//---------------------------------------------------------------------------

#ifndef RouteThrH
#define RouteThrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class Route : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Route(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
