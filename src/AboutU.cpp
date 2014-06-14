//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout *About;
//---------------------------------------------------------------------------
__fastcall TAbout::TAbout(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout::Button1Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TAbout::Button2Click(TObject *Sender)
{
	ShellExecute(Handle, "open", "mailto:barsdm-user@yandex.ru?subject=Программа%20CPM", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TAbout::FormShow(TObject *Sender)
{
	Button1->SetFocus();	
}
//---------------------------------------------------------------------------


