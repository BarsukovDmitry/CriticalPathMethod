//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include "cspin.h"
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <fstream>
#include <vector.h>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TImage *Image1;
	TPopupMenu *EventPopup;
	TMenuItem *N9;
	TMenuItem *N10;
	TPopupMenu *EventImagePopup;
	TMenuItem *N11;
	TMenuItem *N13;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N21;
	TMenuItem *N22;
	TPageControl *PageControl1;
	TStatusBar *StatusBar1;
	TTabSheet *TabSheet2;
	TMenuItem *N12;
	TMenuItem *N14;
	TMenuItem *N23;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *N30;
	TMenuItem *N24;
	TMenuItem *N31;
	TControlBar *ControlBar1;
	TToolBar *StandartBar;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TToolBar *ObjectsBar;
	TSpeedButton *SelectButton;
	TSpeedButton *EventButton;
	TSpeedButton *WorkButton;
	TPopupMenu *WorkPopup;
	TMenuItem *N32;
	TMenuItem *N33;
	TMenuItem *N34;
	TMenuItem *N35;
	TScrollBox *ScrollBox1;
	TPanel *EventPanel;
	TImage *EventImage;
	TMenuItem *N36;
	TMenuItem *N37;
	TMenuItem *N15;
	TMenuItem *N38;
	TMenuItem *N40;
	TMenuItem *N39;
	TToolBar *ProjectBar;
	TSpeedButton *SpeedButton2;
	TMenuItem *N41;
	TMenuItem *N42;
	TMenuItem *N43;
	TMenuItem *N44;
	TMenuItem *N45;
	TSaveDialog *ExportBmp;
	TPopupMenu *TablePopup;
	TMenuItem *N46;
	TTabSheet *TabSheet3;
	TListView *ListView1;
	TMenuItem *N47;
	TMenuItem *N48;
	TMenuItem *N49;
	TMenuItem *N50;
	TImageList *ImageList1;
	TPanel *ProjectExplorer;
	TTreeView *TreeView1;
	TSplitter *Splitter1;
	TStaticText *StaticText1;
	TPopupMenu *ExplorerPopup;
	TMenuItem *N53;
	TMenuItem *N54;
	TMenuItem *N51;
	TMenuItem *N52;
	TMenuItem *N55;
	TMenuItem *N56;
	TMenuItem *N57;
	TPanel *Totals;
	TStaticText *StaticText2;
	TListView *ListView2;
	TSplitter *Splitter2;
	TPanel *Panel2;
	TLabel *Label2;
	TLabel *CostC;
	TLabel *Label4;
	TLabel *TkrC;
	TMenuItem *N58;
	TMenuItem *N59;
	TTabSheet *TabSheet1;
	TListView *EventsTable;
	TMenuItem *N60;
	TCSpinEdit *AccelC;
	TLabel *Label1;
	TImageList *ImageList2;
	TLabel *Label3;
	TLabel *CAccelC;
	TMenuItem *N61;
	TMenuItem *N62;
	TMenuItem *N63;
	TMenuItem *N64;
	TMenuItem *N65;
	TMenuItem *N66;
	TSaveDialog *SaveProject;
	TOpenDialog *OpenProject;
	TMenuItem *N4;
	TMenuItem *N67;
	TMenuItem *N68;
	TMenuItem *N69;
	TSaveDialog *HtmlExport;
	TMenuItem *Verbose;
	TMenuItem *N71;
	TPopupMenu *EventsTablePopup;
	TMenuItem *N70;
	TMenuItem *N72;
	TMenuItem *N73;
	TMenuItem *N74;
	TMenuItem *N75;
	TMenuItem *N76;
	TMenuItem *N77;
	TMenuItem *N78;
	TTabSheet *TabSheet4;
	TMenuItem *N79;
	TMenuItem *MSProjecttxt1;
	TSaveDialog *ProjectExport;
	TChart *Chart1;
	TBarSeries *Series1;
	TChart *Chart2;
	TBarSeries *Series2;
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall Image1DblClick(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall EventImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N26Click(TObject *Sender);
	void __fastcall N27Click(TObject *Sender);
	void __fastcall ControlBar1EndBandMove(TObject *Sender, TControl *Control);
	void __fastcall WorkPopupPopup(TObject *Sender);
	void __fastcall N32Click(TObject *Sender);
	void __fastcall N33Click(TObject *Sender);
	void __fastcall EventImageDblClick(TObject *Sender);
	void __fastcall N35Click(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall N36Click(TObject *Sender);
	void __fastcall N22Click(TObject *Sender);
	void __fastcall N41Click(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall SelectButtonMouseEnter(TObject *Sender);
	void __fastcall SelectButtonMouseLeave(TObject *Sender);
	void __fastcall EventButtonMouseEnter(TObject *Sender);
	void __fastcall WorkButtonMouseEnter(TObject *Sender);
	void __fastcall SpeedButton1MouseEnter(TObject *Sender);
	void __fastcall SpeedButton5MouseEnter(TObject *Sender);
	void __fastcall SpeedButton6MouseEnter(TObject *Sender);
	void __fastcall SpeedButton2MouseEnter(TObject *Sender);
	void __fastcall N44Click(TObject *Sender);
	void __fastcall N46Click(TObject *Sender);
	void __fastcall N48Click(TObject *Sender);
	void __fastcall N47Click(TObject *Sender);
	void __fastcall Splitter1Moved(TObject *Sender);
	void __fastcall TreeView1DblClick(TObject *Sender);
	void __fastcall TreeView1Click(TObject *Sender);
	void __fastcall N51Click(TObject *Sender);
	void __fastcall N54Click(TObject *Sender);
	void __fastcall ExplorerPopupPopup(TObject *Sender);
	void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
	void __fastcall N53Click(TObject *Sender);
	void __fastcall N52Click(TObject *Sender);
	void __fastcall N55Click(TObject *Sender);
	void __fastcall N56Click(TObject *Sender);
	void __fastcall N57Click(TObject *Sender);
	void __fastcall N59Click(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall N60Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall ListView1ColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall ListView1Compare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
	void __fastcall EventsTableColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall EventsTableCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
	void __fastcall N19Click(TObject *Sender);
	void __fastcall N62Click(TObject *Sender);
	void __fastcall N63Click(TObject *Sender);
	void __fastcall N64Click(TObject *Sender);
	void __fastcall N65Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N66Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N30Click(TObject *Sender);
	void __fastcall N29Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall N67Click(TObject *Sender);
	void __fastcall N68Click(TObject *Sender);
	void __fastcall N69Click(TObject *Sender);
	void __fastcall N45Click(TObject *Sender);
	void __fastcall VerboseClick(TObject *Sender);
	void __fastcall N28Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall N75Click(TObject *Sender);
	void __fastcall N74Click(TObject *Sender);
	void __fastcall N73Click(TObject *Sender);
	void __fastcall N72Click(TObject *Sender);
	void __fastcall EventsTableDblClick(TObject *Sender);
	void __fastcall N76Click(TObject *Sender);
	void __fastcall N78Click(TObject *Sender);
	void __fastcall AccelCKeyPress(TObject *Sender, char &Key);
	void __fastcall N79Click(TObject *Sender);
	void __fastcall MSProjecttxt1Click(TObject *Sender);

private:	// User declarations
	int WhichEvent(TComponent *Link);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void Draw();
	void WorksTableUpdate();
	int FirstEvent();
	int LastEvent();
	int UnlinkedEvents();
	void NewWork(int e1, int e2);
	void NewEvent(int X, int Y, bool quiet);
	void DeleteEvent(int Index);
	void DeleteWork(int Index);
	void CloseProject();
	void ExplorerUpdate();
	void EventsTableUpdate();
	int Calculate();
	void DeleteWorks();
	int Check();
	float OtherWorks(int ShareWorkI, vector <int> checkedworks, vector <int> &decrease);
	void Open(AnsiString FileName);


};

class Event
{
public:
	int number, rank, rank2;
	AnsiString name;
	int t1, t2, r;
	int x, y;
	TImage *link;
	Event()
	{
		t1 = -1;
		t2 = -1;
		r = -1;
		rank = -1;
		rank2 = -1;
	}
	void deserialize(ifstream &s);
    void serialize(ofstream &s);
};
class Work
{
public:
	int event1i, event2i;
	int x1, y1, x2, y2;
	int t, tu, Trn, Tro, Tpn, Tpo, Rp, Rs, currentt, maxaccel;
	float cost, costu, costuud, currentcost;
	bool fordelete;
	AnsiString name;
	AnsiString mark;
	Work()
	{
		event1i = -10;
		event2i = -10;
		t = 0;
		tu = 0;
		cost = 0;
		costu = 0;
		name = "";
		Trn = -1;
		Tro = -1;
		Tpn = -1;
		Tpo = -1;
		Rp = -1;
		Rs = -1;
		currentt = -1;
		maxaccel = -1;
		costuud = -1;
		currentcost = 0;
		fordelete = false;
	}
	void deserialize(ifstream &s);
	void serialize(ofstream &s);
	
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
