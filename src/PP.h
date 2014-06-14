//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef PPH
#define PPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProjectProp : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TLabeledEdit *NameC;
	TLabeledEdit *AuthorC;
	TLabel *Label1;
	TMemo *DefinitionC;
	TLabeledEdit *TimeEdC;
	TLabeledEdit *MoneyEdC;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TProjectProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProjectProp *ProjectProp;
//---------------------------------------------------------------------------
#endif
