//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef AboutUH
#define AboutUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAbout : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TGroupBox *GroupBox1;
	TImage *Image1;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TStaticText *StaticText3;
	TStaticText *StaticText4;
	TStaticText *StaticText5;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout *About;
//---------------------------------------------------------------------------
#endif
