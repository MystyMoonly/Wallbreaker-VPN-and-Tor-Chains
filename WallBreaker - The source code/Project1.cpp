//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Mainfm.cpp", Mainform);
USEFORM("ConsoleOvpn.cpp", Csl);
USEFORM("ConnectManager.cpp", ConMan);
USEFORM("VPN2F.cpp", VPN2Form);
USEFORM("HF.cpp", HelpForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		//Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainform), &Mainform);
		Application->CreateForm(__classid(TConMan), &ConMan);
		Application->CreateForm(__classid(THelpForm), &HelpForm);
		Application->CreateForm(__classid(TVPN2Form), &VPN2Form);
		Application->CreateForm(__classid(TCsl), &Csl);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
