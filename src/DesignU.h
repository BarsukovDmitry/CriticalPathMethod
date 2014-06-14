//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef DesignH
#define DesignH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDesign : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TButton *Button1;
	TButton *Button2;
	TTabSheet *TabSheet1;
	TColorBox *ColorBox1;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label2;
	TColorBox *ColorBox2;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDesign(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDesign *Design;
//---------------------------------------------------------------------------
#endif
