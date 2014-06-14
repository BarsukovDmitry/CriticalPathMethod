//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EPU.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEventProp *EventProp;
bool EPResult = false;
Event *EPev;
//---------------------------------------------------------------------------
__fastcall TEventProp::TEventProp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEventProp::Button1Click(TObject *Sender)
{
	EPev->name = NameC->Text;
	EPev->number = StrToInt(NumberC->Text);
	EPResult = true;
	Close();
	MainForm->Draw();
	MainForm->ExplorerUpdate();
	MainForm->StatusBar1->Panels->Items[1]->Text = "Изменён";
	MainForm->EventsTableUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TEventProp::Button2Click(TObject *Sender)
{
	EPResult = false;
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TEventProp::FormShow(TObject *Sender)
{
	NameC->Text = EPev->name;
	NumberC->Text = EPev->number;
	NameC->SetFocus();
	EPResult=false;
	EventProp->Caption = IntToStr(EPev->number) + " - Свойства события";

}
//---------------------------------------------------------------------------

void __fastcall TEventProp::FormClose(TObject *Sender, TCloseAction &Action)
{
	MainForm->StatusBar1->Panels->Items[2]->Text = "";	
}
//---------------------------------------------------------------------------

