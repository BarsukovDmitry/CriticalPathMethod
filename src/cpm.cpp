//$$---- EXE CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>

#include "MainFormU.h" 

#pragma hdrstop
extern AnsiString param;
//---------------------------------------------------------------------------
USEFORM("MainFormU.cpp", MainForm);
USEFORM("EPU.cpp", EventProp);
USEFORM("WPU.cpp", WorkProp);
USEFORM("PP.cpp", ProjectProp);
USEFORM("AboutU.cpp", About);
USEFORM("DesignU.cpp", Design);
USEFORM("ImportU.cpp", Import);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR S, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "CPM";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TEventProp), &EventProp);
		Application->CreateForm(__classid(TWorkProp), &WorkProp);
		Application->CreateForm(__classid(TProjectProp), &ProjectProp);
		Application->CreateForm(__classid(TAbout), &About);
		Application->CreateForm(__classid(TDesign), &Design);
		Application->CreateForm(__classid(TImport), &Import);
		param = S;
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
