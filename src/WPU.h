//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef WPUH
#define WPUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "cspin.h"
#include <ComCtrls.hpp>
#include <vector.h>

#include "MainFormU.h"
//---------------------------------------------------------------------------
class TWorkProp : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *NameC;
	TButton *Button1;
	TButton *Button2;
	TCSpinEdit *TC;
	TLabel *Label1;
	TLabeledEdit *Event1C;
	TLabeledEdit *Event2C;
	TLabeledEdit *MarkC;
	TListView *PWorksC;
	TLabel *Label2;
	TRadioGroup *RadioGroup1;
	TLabel *Label3;
	TCSpinEdit *TuC;
	TLabeledEdit *CostC;
	TLabeledEdit *CostUC;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TCKeyPress(TObject *Sender, char &Key);
	void __fastcall CostCKeyPress(TObject *Sender, char &Key);
	void __fastcall TuCKeyPress(TObject *Sender, char &Key);
	void __fastcall TCChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	int SetWork(Work *WPwork, AnsiString mark, AnsiString name, int t, int tu, float cost, float costu, bool by_events, int event1i, int event2i, vector <unsigned int> indexs);

	__fastcall TWorkProp(TComponent* Owner);

};

//---------------------------------------------------------------------------
extern PACKAGE TWorkProp *WorkProp;
//---------------------------------------------------------------------------
#endif
