//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef EPUH
#define EPUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEventProp : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *NameC;
	TButton *Button1;
	TButton *Button2;
	TLabeledEdit *NumberC;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TEventProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEventProp *EventProp;
//---------------------------------------------------------------------------
#endif
