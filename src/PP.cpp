//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PP.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProjectProp *ProjectProp;
extern AnsiString ProjectName, ProjectAuthor, ProjectDefinition, timeed, moneyed;
//---------------------------------------------------------------------------
__fastcall TProjectProp::TProjectProp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProjectProp::Button2Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TProjectProp::Button1Click(TObject *Sender)
{
	ProjectName = NameC->Text;
	ProjectAuthor = AuthorC->Text;
	ProjectDefinition = DefinitionC->Lines->Text;
	timeed = TimeEdC->Text;
	moneyed = MoneyEdC->Text;
	Close();
	MainForm->StatusBar1->Panels->Items[1]->Text = "Изменён";
	

}
//---------------------------------------------------------------------------
void __fastcall TProjectProp::FormShow(TObject *Sender)
{
	NameC->Text = ProjectName;
	AuthorC->Text = ProjectAuthor;
	DefinitionC->Lines->Text = ProjectDefinition;
	TimeEdC->Text = timeed;
	MoneyEdC->Text = moneyed;
	PageControl1->TabIndex = 0;
	NameC->SetFocus();
}
//---------------------------------------------------------------------------
