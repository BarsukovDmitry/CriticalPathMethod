//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "DesignU.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDesign *Design;
extern TColor EventColor, SelectColor;

//---------------------------------------------------------------------------
__fastcall TDesign::TDesign(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDesign::Button2Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TDesign::Button1Click(TObject *Sender)
{
	EventColor = ColorBox1->Selected;
	SelectColor = ColorBox2->Selected;
    if(FileExists(ExtractFilePath(Application->ExeName) + "\\settings.ini"))
	{
		TIniFile *inifile;
		inifile = new TIniFile(ExtractFilePath(Application->ExeName) + "\\settings.ini");
		inifile->WriteInteger("Color", "EventColor", EventColor);
		inifile->WriteInteger("Color", "SelectColor", SelectColor);
        inifile->UpdateFile();
		inifile->Free();
	}
	Close();
	MainForm->Draw();
}
//---------------------------------------------------------------------------
void __fastcall TDesign::FormShow(TObject *Sender)
{
	ColorBox1->Selected = EventColor;
	ColorBox2->Selected = SelectColor;
	Button1->SetFocus();	
}
//---------------------------------------------------------------------------
void __fastcall TDesign::Button3Click(TObject *Sender)
{
	ColorBox1->Selected = clWhite;
	ColorBox2->Selected = clLime;	
}
//---------------------------------------------------------------------------
