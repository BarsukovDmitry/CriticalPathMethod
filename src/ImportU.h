//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef ImportUH
#define ImportUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TImport : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TButton *Button4;
	TMenuItem *N2;
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const AnsiString Value);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TImport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImport *Import;
//---------------------------------------------------------------------------
#endif
