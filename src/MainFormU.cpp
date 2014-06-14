//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <math.h>
#include <Math.hpp>
#include <IniFiles.hpp>
#pragma hdrstop

#include "MainFormU.h"
#include "EPU.h"
#include "WPU.h"
#include "PP.h"
#include "AboutU.h"
#include "DesignU.h"
#include "ImportU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
#pragma resource "resources.res"

#define ARROW_END_L 15
#define ARROW_END_A 15
#define ARROW_SENS 4
#define LEFT 10
#define RIGHT 10
#define HORIZ 155
#define VERT 140
#define WAVE 15

using namespace std;
TMainForm *MainForm;
AnsiString ProjectName="Безымянный", ProjectAuthor="", ProjectDefinition="", timeed="дн.", moneyed="тыс. руб.";
bool newevent = false, itsdouble = false, newwork=false, moving=false, issaved=false;
extern Event *EPev;
extern Work *WPwork;
extern bool EPResult, WPResult;
int h=70, w=70;
int actevent=-1, actwork =-1;
int EventImageX, EventImageY;
int x0, y0;
int workc=0;
int ColumnToSort;
int currentaccel=0;
int ExplorerPopupIndex;
int eventcount=0;
Work tempwork;
vector<Event> events;
vector<Work> works;
vector<vector <int> > KrWs;
vector<int> KrW;
vector <int> KrMinIxs, ShareWork;
vector <vector <int> > ShareWorks;
float Tkr=0, Tkru=0, s=0, su=0;
const EventCursor = 1;
const WorkCursor = 2;
TColor EventColor=clWhite, SelectColor=clLime;
AnsiString param;

//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void Event::deserialize(ifstream &s)
{
	//POD-данные
	//ShowMessage("POD");
	s.read((char *) &number, sizeof(number));
	s.read((char *) &x, sizeof(x));
	s.read((char *) &y, sizeof(y));
	//классы
	//ShowMessage("Классы");
	size_t len;
	s.read((char *) &len, sizeof(len));
	name.SetLength(len);
	s.read((char *) name.data(), len);
	//создание имэйджа
	TImage *image = new TImage(MainForm);
	image->Parent = MainForm->EventPanel;
	image->Left = x;
	image->Top = y;
	image->Width = w;
	image->Height = h;
	image->PopupMenu = MainForm->EventPopup;
	image->Transparent = true;
	image->OnMouseDown = MainForm->Image1MouseDown;
	image->OnMouseUp = MainForm->Image1MouseUp;
	image->OnMouseMove = MainForm->Image1MouseMove;
	image->OnDblClick = MainForm->Image1DblClick;
	image->OnClick = MainForm->Image1Click;
	image->ShowHint = true;
	image->Hint = name;
	link = image;

}
//---------------------------------------------------------------------------

void Event::serialize(ofstream &s)
{
	//POD-данные
	s.write((char *) &number, sizeof(number));
	s.write((char *) &x, sizeof(x));
	s.write((char *) &y, sizeof(y));
	//классы
	size_t len = name.Length();
	s.write((char *) &len, sizeof(len));
	s.write((char *) name.data(), len);
}
//---------------------------------------------------------------------------

void Work::deserialize(ifstream &s)
{
	s.read((char *) &event1i, sizeof(event1i));
	s.read((char *) &event2i, sizeof(event2i));
	s.read((char *) &x1, sizeof(x1));
	s.read((char *) &y1, sizeof(y1));
	s.read((char *) &x2, sizeof(x2));
	s.read((char *) &y2, sizeof(y2));
	s.read((char *) &t, sizeof(t));
	s.read((char *) &tu, sizeof(tu));
	currentt = t;
	s.read((char *) &cost, sizeof(cost));
	s.read((char *) &costu, sizeof(costu));
	currentcost = cost;
	size_t len;
	s.read((char *) &len, sizeof(len));
	name.SetLength(len);
	s.read((char *) name.data(), len);
	s.read((char *) &len, sizeof(len));
	mark.SetLength(len);
	s.read((char *) mark.data(), len);
}
//---------------------------------------------------------------------------

void Work::serialize(ofstream &s)
{
	s.write((char *) &event1i, sizeof(event1i));
	s.write((char *) &event2i, sizeof(event2i));
	s.write((char *) &x1, sizeof(x1));
	s.write((char *) &y1, sizeof(y1));
	s.write((char *) &x2, sizeof(x2));
	s.write((char *) &y2, sizeof(y2));
	s.write((char *) &t, sizeof(t));
	s.write((char *) &tu, sizeof(tu));
	s.write((char *) &cost, sizeof(cost));
	s.write((char *) &costu, sizeof(costu));
	size_t len;
	len = name.Length();
	s.write((char *) &len, sizeof(len));
	s.write((char *) name.data(), len);
	len = mark.Length();
	s.write((char *) &len, sizeof(len));
	s.write((char *) mark.data(), len);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N8Click(TObject *Sender)
{
	N12Click(this);
	newevent = true;
	N8->Checked = true;
	EventButton->Down = true;
	EventImage->Cursor = (TCursor) EventCursor;
	StatusBar1->Panels->Items[2]->Text = "Щёлкните на графике для создания события";
}
//---------------------------------------------------------------------------

void TMainForm::Draw()
{
	unsigned int i;
	int maxeventx=0, maxeventy=0;
	EventImage->Canvas->FillRect(Rect(0, 0, EventImage->Width, EventImage->Height));
	for(i=0; i<events.size(); i++)
	{
		events[i].link->Canvas->Brush->Color = clGreen;
		events[i].link->Canvas->FillRect(Rect(0, 0, events[i].link->Width, events[i].link->Height));
		events[i].link->Canvas->Brush->Color = EventColor;
		if(i == actevent) events[i].link->Canvas->Pen->Color = SelectColor;
		else events[i].link->Canvas->Pen->Color = clBlack;
		events[i].link->Canvas->Ellipse(0, 0, events[i].link->Width, events[i].link->Height);
		events[i].link->Canvas->PenPos = Point(w/2, 0);
		events[i].link->Canvas->LineTo(w/2, h);
		events[i].link->Canvas->PenPos = Point(0, h/2);
		events[i].link->Canvas->LineTo(w, h/2);
		events[i].link->Canvas->Font->Style = TFontStyles()<<fsBold;
		events[i].link->Canvas->TextOutA(w/4 - events[i].link->Canvas->TextWidth(IntToStr(events[i].number))/2 + 3, h/4, IntToStr(events[i].number));
		events[i].link->Canvas->Font->Style = TFontStyles()>>fsBold;
		if(events[i].t1 != -1) events[i].link->Canvas->TextOutA(3* w/4 - events[i].link->Canvas->TextWidth(IntToStr(events[i].t1))/2 - 2, h/4, IntToStr(events[i].t1));
		if(events[i].t2 != -1) events[i].link->Canvas->TextOutA(3* w/4 - events[i].link->Canvas->TextWidth(IntToStr(events[i].t2))/2 - 2, 3*h/4 - events[i].link->Canvas->TextHeight(IntToStr(events[i].t2)), IntToStr(events[i].t2));
		if(events[i].r != -1) events[i].link->Canvas->TextOutA(w/4 - events[i].link->Canvas->TextWidth(IntToStr(events[i].r))/2 + 3, 3*h/4 - events[i].link->Canvas->TextHeight(IntToStr(events[i].r)), IntToStr(events[i].r));
		events[i].link->Hint = events[i].name;
		if(maxeventx < events[i].x) maxeventx = events[i].x;
		if(maxeventy < events[i].y) maxeventy = events[i].y;
	}

	for(i=0; i<works.size(); i++)
	{
		int x1, x2, y1, y2, dx, dy, dx2, dy2;
		float angle;
		//линии стрелок
		if(i == actwork) EventImage->Canvas->Pen->Color = SelectColor;
		else if (works[i].Rp) EventImage->Canvas->Pen->Color = clBlack;
		else if (!works[i].Rp) EventImage->Canvas->Pen->Color = clRed;
		x1 = events[works[i].event1i].link->Left + w/2;
		x2 = events[works[i].event2i].link->Left + w/2;
		y1 = events[works[i].event1i].link->Top + h/2;
		y2 = events[works[i].event2i].link->Top + h/2;
		dx = x1 - x2;
		dy = y1 - y2;
		if(dx<0 && dy<=0) angle = ArcTan((float) dy/dx);
		else if(dx>0 && dy<0) angle = DegToRad(180) - ArcTan((float) -dy/dx);
		else if(dx>0 && dy>=0) angle = ArcTan((float) dy/dx) + DegToRad(180);
		else if(dx<0 && dy>=0) angle = DegToRad(360) - ArcTan((float) dy/-dx);
		else if(dx==0 && dy>0) angle = DegToRad(270);
		else if(dx==0 && dy<0) angle = DegToRad(90);
		else if(dx==0 && dy==0) continue;
        dx2 = Cos(angle)*h/2;
		dy2 = Sin(angle)*h/2;
        EventImage->Canvas->PenPos = Point(x1 + dx2, y1 + dy2);
		if(!works[i].currentt) EventImage->Canvas->Pen->Style = psDot;
		EventImage->Canvas->LineTo(x2 - dx2, y2 - dy2);
		EventImage->Canvas->Pen->Style = psSolid;
		works[i].x1 = x1 + dx2;
		works[i].y1 = y1 + dy2;
		works[i].x2 = x2 - dx2;
		works[i].y2 = y2 - dy2;
		//метка, длительность
		float len;
		len = Sqrt(Power((long double)(works[i].x1 - works[i].x2), 2) + Power((long double)(works[i].y1 - works[i].y2), 2));
		dx2 = Cos(angle)* len/2;
		dy2 = Sin(angle)* len/2;
		EventImage->Canvas->Font->Style = TFontStyles()>>fsBold;
		if(works[i].currentt) EventImage->Canvas->TextOutA(works[i].x1 + dx2 - EventImage->Canvas->TextWidth(works[i].mark + " (" + IntToStr(works[i].currentt) + ")") / 2, works[i].y1 + dy2 - EventImage->Canvas->TextHeight(works[i].mark + " (" + IntToStr(works[i].currentt) + ")") / 2, works[i].mark + " (" + IntToStr(works[i].currentt) + ")");
		//концы стрелок
		EventImage->Canvas->PenPos = Point(works[i].x2, works[i].y2);
		angle += DegToRad(ARROW_END_A);
		dx2 = Cos(angle) * ARROW_END_L;
		dy2 = Sin(angle) * ARROW_END_L;
		x1 = EventImage->Canvas->PenPos.x;
		y1 = EventImage->Canvas->PenPos.y;
		EventImage->Canvas->LineTo(x1-dx2, y1 - dy2);
		EventImage->Canvas->PenPos = Point(x1, y1);
		angle -= DegToRad(2*ARROW_END_A);
		dx2 = Cos(angle) * ARROW_END_L;
		dy2 = Sin(angle) * ARROW_END_L;
		EventImage->Canvas->LineTo(x1-dx2, y1 - dy2);
	}
	if(maxeventx + 500 > PageControl1->Pages[0]->Width - 4) EventPanel->Width = maxeventx + 500;
	else EventPanel->Width = PageControl1->Pages[0]->Width - 4;
	if(maxeventy + 500 > PageControl1->Pages[0]->Height - 4) EventPanel->Height = maxeventy + 500;
	else EventPanel->Height = PageControl1->Pages[0]->Height - 4;
	EventImage->Picture->Bitmap->Width = EventImage->Width;
	EventImage->Picture->Bitmap->Height = EventImage->Height;
		

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender)
{
	MainForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1MouseDown(TObject *Sender, TMouseButton Button,
	  TShiftState Shift, int X, int Y)
{
	if(!itsdouble && Button == mbLeft)
	{
		x0 = X;
		y0 = Y;
		moving = true;
	}
	itsdouble = false;
	actwork = -1;
	actevent = WhichEvent((TComponent *) Sender);
	N22->Enabled = true;
	N36->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
	moving = false;
	events[WhichEvent((TComponent *)Sender)].x = ((TImage *) Sender)->Left;
	events[WhichEvent((TComponent *) Sender)].y = ((TImage *) Sender)->Top;
	Draw();
	

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
	if(moving)
	{
		if((((TImage *) Sender)->Left + X - x0) > 0 && ((TImage *) Sender)->Top + Y - y0 > 0
			&& (((TImage *) Sender)->Left + X - x0 + w) < EventImage->Width && (((TImage *) Sender)->Top + Y - y0 + h) < EventImage->Height)
		{
        	((TImage *) Sender)->Left += X - x0;
			((TImage *) Sender)->Top += Y - y0;
			StatusBar1->Panels->Items[1]->Text = "Изменён";
		}

    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N9Click(TObject *Sender)
{
	EPev = &events[WhichEvent(EventPopup->PopupComponent)];
	EventProp->ShowModal();
}
//---------------------------------------------------------------------------

int TMainForm::WhichEvent(TComponent *Link)
{
	unsigned int i;
	for(i=0; i<events.size(); i++)
	{
		if (events[i].link == Link) break;

	}
	return i;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N10Click(TObject *Sender)
{
	DeleteEvent(WhichEvent(EventPopup->PopupComponent));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	Draw();
}
//---------------------------------------------------------------------------

void TMainForm::NewEvent(int X, int Y, bool quiet)
{
	Event ev;
	int max=0;
	for(unsigned int i=0; i< events.size(); i++)
	{
		if(events[i].number>max) max = events[i].number;
	}
	ev.number = max+1;
	EPev = &ev;
	if(quiet) EPResult = true;
	else EventProp->ShowModal();
	if (EPResult) {
		ev.x = X;
		ev.y = Y;
		TImage *image = new TImage(this);
		image->Parent = EventPanel;
		image->Left = X;
		image->Top = Y;
		image->Width = w;
		image->Height = h;
		image->PopupMenu = EventPopup;
		image->Transparent = true;
		image->OnMouseDown = Image1MouseDown;
		image->OnMouseUp = Image1MouseUp;
		image->OnMouseMove = Image1MouseMove;
		image->OnDblClick = Image1DblClick;
        image->OnClick = Image1Click;
		/*image->Canvas->Brush->Color = clWhite;
		image->Canvas->FillRect(Rect(0, 0, image->Width, image->Height));
		image->Canvas->Brush->Color = clAqua;
		image->Canvas->Ellipse(0, 0, image->Width, image->Height);
		image->Canvas->PenPos = Point(w/2, 0);
		image->Canvas->LineTo(w/2, h);
		image->Canvas->PenPos = Point(0, h/2);
		image->Canvas->LineTo(w, h/2);
		image->Canvas->Font->Style = TFontStyles()<<fsBold;
		image->Canvas->TextOutA(w/4 - image->Canvas->TextWidth(IntToStr(ev.number))/2 + 3, h/4, IntToStr(ev.number));
        */image->ShowHint = true;
		image->Hint = ev.name;
		ev.link = image;
		events.push_back(ev);
		if(eventcount < 20)  eventcount++;
		else eventcount = 0;
		Draw();
		ExplorerUpdate();
		EventsTableUpdate();
	}


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N11Click(TObject *Sender)
{
	NewEvent(EventImage->ScreenToClient(EventImagePopup->PopupPoint).x, EventImage->ScreenToClient(EventImagePopup->PopupPoint).y, false);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1DblClick(TObject *Sender)
{
	itsdouble=true;;
	EPev = &events[WhichEvent((TComponent *) Sender)];
	EventProp->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N13Click(TObject *Sender)
{
	N12Click(N12);
	newwork = true;
	workc = 0;
	N13->Checked = true;
	WorkButton->Down = true;
	EventImage->Cursor = (TCursor) WorkCursor;
	StatusBar1->Panels->Items[2]->Text = "Выберите начальное событие работы";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	actwork = -1;
	if (newevent) {
		NewEvent(X, Y, false);
		N12Click(this);;
	}
	else
	{
		unsigned int i;
		float a, b;
        bool workclick = false;
		for(i=0; i<works.size(); i++)
		{
			if(!(works[i].y1 - works[i].y2))
			{
				if(Y < (works[i].y1 + ARROW_SENS) && Y > (works[i].y1 -ARROW_SENS) && (abs(works[i].x1 - X) + abs(works[i].x2 - X)) == abs(works[i].x1 - works[i].x2))
					workclick = true;
			}
			else if(!(works[i].x1 - works[i].x2))
			{
				if(X < (works[i].x1 + ARROW_SENS) && X > (works[i].x1 -ARROW_SENS) && (abs(works[i].y1 - Y) + abs(works[i].y2 - Y)) == abs(works[i].y1 - works[i].y2))
					workclick = true;
			}
			else if((abs(works[i].x1 - X) + abs(works[i].x2 - X)) == abs(works[i].x1 - works[i].x2))
			{
				b = (float) (works[i].y1 - works[i].y2) / (works[i].x1 - works[i].x2);
				a = works[i].y1 - b*works[i].x1;
				if(Y < (a + b*X + ARROW_SENS) && Y > (a + b*X - ARROW_SENS)) workclick = true;
				if(X < ((Y - a)/b + ARROW_SENS)  && X >((Y - a)/b - ARROW_SENS)) workclick = true;
			}
			if(workclick)
			{
                actevent = -1;
				actwork = i;
				if(Button == mbRight)
				{
					EventImage->PopupMenu = WorkPopup;
                }
                break;
			}
			else
			{
				actwork = -1;
			}
		}
	}
	actevent = -1;
	if(actwork != -1)
	{
		N22->Enabled = true;
		N36->Enabled = true;
	}
	else
	{
		N22->Enabled = false;
		N36->Enabled = false;
	}
	Draw();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
	EventImage->Canvas->FillRect(Rect(0, 0, EventImage->Width, EventImage->Height));
	if(param.Length()) Open(param.SubString(2, param.Length() - 2));	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
	Draw();
	Chart1->Height = (PageControl1->Height-28)/2;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image1Click(TObject *Sender)
{
	if(newwork)
	{
		if(workc==0)
		{
			tempwork.event1i = WhichEvent((TComponent *) Sender);
			workc = 1;
			StatusBar1->Panels->Items[2]->Text = "Выберите конечное событие работы";
		}
		else if(workc==1 && WhichEvent((TComponent *) Sender) != tempwork.event1i)
		{
			NewWork(tempwork.event1i, WhichEvent((TComponent *) Sender));
			N12Click(this);
		}
		else Application->MessageBoxA("Конечное событие не может совпадать\
 с начальным. Выберите другое конечное событие", Application->Title.c_str(), MB_ICONERROR + MB_OK);
	}
	else
	{
		actwork = -1;
		actevent = WhichEvent((TComponent *) Sender);
		N22->Enabled = true;
		N36->Enabled = true;

    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N12Click(TObject *Sender)
{
	newevent = false;
	newwork = false;
	EventImage->Cursor = crDefault;
	N12->Checked = true;
	SelectButton->Down = true;
	StatusBar1->Panels->Items[2]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	Screen->Cursors[EventCursor] = LoadCursor(HInstance, "EVENT");
	Screen->Cursors[WorkCursor] = LoadCursor(HInstance, "WORK");
	if(FileExists(ExtractFilePath(Application->ExeName) + "\\settings.ini"))
	{
		TIniFile *inifile;
		inifile = new TIniFile(ExtractFilePath(Application->ExeName) + "\\settings.ini");
		EventColor = (TColor) inifile->ReadInteger("Color", "EventColor", 16777215);
		SelectColor = (TColor) inifile->ReadInteger("Color", "SelectColor", 65280);
		inifile->Free();
	}


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N26Click(TObject *Sender)
{
	StandartBar->Visible = !StandartBar->Visible;
	N26->Checked = !N26->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N27Click(TObject *Sender)
{
	ObjectsBar->Visible = !ObjectsBar->Visible;
	N27->Checked = !N27->Checked;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ControlBar1EndBandMove(TObject *Sender,
      TControl *Control)
{
	StandartBar->Top = 2;
	ObjectsBar->Top = 2;
	ProjectBar->Top = 2;	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkPopupPopup(TObject *Sender)
{
	EventImage->PopupMenu = EventImagePopup;	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N32Click(TObject *Sender)
{
	DeleteWork(actwork);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N33Click(TObject *Sender)
{
	WPwork = &works[actwork];
	WorkProp->ShowModal();
	DeleteWorks();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventImageDblClick(TObject *Sender)
{
	if(actwork != -1) N33Click(this);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N35Click(TObject *Sender)
{
	N13Click(this);
	tempwork.event1i = WhichEvent(EventPopup->PopupComponent);
	workc = 1;
    StatusBar1->Panels->Items[2]->Text = "Выберите конечное событие работы";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
	if(Key == VK_ESCAPE) N12Click(this);	
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N2Click(TObject *Sender)
{
	if(StatusBar1->Panels->Items[1]->Text != "")
	{
		switch(Application->MessageBoxA("Проект был изменён.\n\nСохранить изменения?", Application->Title.c_str(), MB_ICONWARNING + MB_YESNOCANCEL))
		{
			case IDYES:
				N29Click(this);
				if(StatusBar1->Panels->Items[1]->Text == "") CloseProject();
				break;
			case IDNO:
				CloseProject();
				break;
			case IDCANCEL:
				break;
		}
		
	}
	else
	{
		CloseProject();
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
	switch(Application->MessageBoxA("Проект был изменён.\n\nСохранить изменения?", Application->Title.c_str(), MB_ICONWARNING + MB_YESNOCANCEL))
	{
		case IDYES:

			break;
		case IDNO:
			for(unsigned int i=0; i<events.size(); i++)
			{
				delete events[i].link;
			}
			events.clear();
			works.clear();
			break;
		case IDCANCEL:
			break;

	}
	Draw();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N18Click(TObject *Sender)
{
	ProjectProp->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N36Click(TObject *Sender)
{
	actevent = -1;
	actwork = -1;
	N22->Enabled = false;
	N36->Enabled = false;
	Draw();	
}
//---------------------------------------------------------------------------

void TMainForm::DeleteEvent(int Index)
{
	unsigned int i;
	int tempnumber;
	vector<Event>::iterator p = events.begin();
	vector<Work>::iterator p2 = works.begin();
	p += Index;
	tempnumber = p->number;
	delete events[Index].link;
	events.erase(p);
	for(i=0; i<events.size(); i++)
	{
		if (events[i].number > tempnumber)
		{
			events[i].number--;
		}
	}
	for(i=0; i<works.size(); i++)
	{
		if(works[i].event1i == Index || works[i].event2i == Index)
		{
			p2 = works.begin();
			p2 += i;
			works.erase(p2);
			i--;
			
		}
		else
		{
			if(works[i].event1i > Index) works[i].event1i--;
			if(works[i].event2i > Index) works[i].event2i--;
		}
	}
	N36Click(this);
	Draw();
	ExplorerUpdate();
	EventsTableUpdate();
	WorksTableUpdate();
	StatusBar1->Panels->Items[1]->Text = "Изменён";

}
//---------------------------------------------------------------------------

void TMainForm::DeleteWork(int Index)
{
	vector<Work>::iterator p2 = works.begin();
	p2 += Index;
	works.erase(p2);
	N36Click(this);
	Draw();
	ExplorerUpdate();
	WorksTableUpdate();
	StatusBar1->Panels->Items[1]->Text = "Изменён";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N22Click(TObject *Sender)
{
	if(actevent != -1) DeleteEvent(actevent);
	else if(actwork != -1) DeleteWork(actwork);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N41Click(TObject *Sender)
{
	ProjectBar->Visible = !ProjectBar->Visible;
	N41->Checked = !N41->Checked; 	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1DblClick(TObject *Sender)
{
	if(ListView1->SelCount == 1)
	{
		WPwork = (Work *) ListView1->Selected->Data;
		WorkProp->ShowModal();
		DeleteWorks();
    }

}
//---------------------------------------------------------------------------

void TMainForm::WorksTableUpdate()
{
    AnsiString temp;
	FormResize(this);
	ListView1->Items->Clear();
	for(unsigned int i=0; i<works.size(); i++)
	{
		ListView1->Items->Add();
		ListView1->Items->Item[i]->Data = &works[i];
		ListView1->Items->Item[i]->ImageIndex = -1;
		ListView1->Items->Item[i]->Caption = works[i].mark;
		ListView1->Items->Item[i]->SubItems->Add(IntToStr(events[works[i].event1i].number) + "->" + IntToStr(events[works[i].event2i].number));
		AnsiString temp = "";
		for(unsigned int j=0; j<works.size(); j++)
		{
			if(works[j].event2i == works[i].event1i)
			{
				if(!works[j].currentt)
				{
					for(unsigned int k=0; k<works.size(); k++)
					{
					if(works[k].event2i == works[j].event1i && works[k].currentt)
					{
					   temp += works[k].mark + ", ";
					}
					}
				}
				else
				{
					temp += works[j].mark + ", ";
				}
					
			}
		}
		ListView1->Items->Item[i]->SubItems->Add(temp.SubString(1, temp.Length()-2));
		ListView1->Items->Item[i]->SubItems->Add(works[i].name);
		ListView1->Items->Item[i]->SubItems->Add(works[i].t);
		ListView1->Items->Item[i]->SubItems->Add(works[i].currentt);
		ListView1->Items->Item[i]->SubItems->Add(works[i].tu);
		ListView1->Items->Item[i]->SubItems->Add(FloatToStrF(works[i].cost, ffFixed, 10, 3));
        ListView1->Items->Item[i]->SubItems->Add(FloatToStrF(works[i].currentcost, ffFixed, 10, 3));
		ListView1->Items->Item[i]->SubItems->Add(FloatToStrF(works[i].costu, ffFixed, 10, 3));
		if(works[i].Trn != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Trn);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].Tro != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Tro);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].Tpn != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Tpn);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].Tpo != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Tpo);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].Rp != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Rs);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].Rs != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].Rp);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].maxaccel != -1) ListView1->Items->Item[i]->SubItems->Add(works[i].maxaccel);
		else ListView1->Items->Item[i]->SubItems->Add("");
		if(works[i].costuud != -1) ListView1->Items->Item[i]->SubItems->Add(FloatToStrF(works[i].costuud, ffFixed, 10, 3));
		else ListView1->Items->Item[i]->SubItems->Add("");
	}
	ListView1->AlphaSort();

}
//---------------------------------------------------------------------------

int TMainForm::FirstEvent()
{
	unsigned int i, j, count=0;
	int first=-1;
	for(i=0; i< events.size(); i++)
	{
		for(j=0; j<works.size(); j++)
		{
			if(works[j].event2i == i) break;
		}
		if(j == works.size())
		{
			first = i;
			count++;
			//ShowMessage("Найдено начальное событие с индексом" + IntToStr(i));
		}
	}
	if(count > 1) return -2;
    else return first;
}
//---------------------------------------------------------------------------
int TMainForm::LastEvent()
{
	unsigned int i, j;
	int last=-1, count=0;
	for(i=0; i< events.size(); i++)
	{
		for(j=0; j<works.size(); j++)
		{
			if(works[j].event1i == i) break;
		}
		if(j == works.size())
		{
			last = i;
			count++;
		}
	}
	if(count > 1) return -2;
	else return last;
}
//---------------------------------------------------------------------------
int TMainForm::UnlinkedEvents()
{
	unsigned int i, j;
	for(i=0; i<events.size(); i++)
	{
		for(j=0; j<works.size(); j++)
		{
			if(works[j].event1i == i || works[j].event2i == i)
			{
				break;
			}
		}
		if(j==works.size())
		{
            //ShowMessage("Найдено несвязанное событие");
			return 1;
		}
    }
    return 0;
}
//---------------------------------------------------------------------------
void TMainForm::NewWork(int e1, int e2)
{
	tempwork.mark = "";
	tempwork.t = 0;
	tempwork.name = "";
	tempwork.cost = 0;
	tempwork.costu = 0;
	tempwork.tu = 0;
    tempwork.event1i = e1;
	tempwork.event2i = e2;
	WPwork = &tempwork;
	WorkProp->ShowModal();
	if(WPResult)
	{
		workc=0;
		works.push_back(tempwork);
		DeleteWorks();

	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SelectButtonMouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Выбор объекта";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SelectButtonMouseLeave(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventButtonMouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Создать событие";	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkButtonMouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Создать работу";	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton1MouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Создать новый проект";	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton5MouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Открыть проект";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton6MouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Сохранить текущий проект";	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton2MouseEnter(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = "Рассчитать проект";	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N44Click(TObject *Sender)
{
	if(issaved) ExportBmp->FileName = ExtractFileName(SaveProject->FileName).SubString(1, ExtractFileName(SaveProject->FileName).LastDelimiter(".") - 1);
	else ExportBmp->FileName = ProjectName;
	if(ExportBmp->Execute())
	{
		N36Click(this);
		Graphics::TBitmap *grafic = new Graphics::TBitmap();
		grafic->Assign(EventImage->Picture);
		grafic->Width -= 400;
		grafic->Height -= 400;
		for(int i=0; i<events.size(); i++)
		{
			grafic->Canvas->Draw(events[i].link->Left, events[i].link->Top, events[i].link->Picture->Bitmap);
		}

    	grafic->SaveToFile(ExportBmp->FileName);
		grafic->Free();
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N46Click(TObject *Sender)
{
	NewWork(-10, -10);
	WorksTableUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N48Click(TObject *Sender)
{
	if(Totals->Visible && !StatusBar1->Visible)
	{
		N57Click(this);
		//ShowMessage("Скрыли итоги");
		StatusBar1->Visible = !StatusBar1->Visible;
		N48->Checked = !N48->Checked;
		FormResize(this);
		//ShowMessage("Показали строку");
		N57Click(this);
		Splitter2->Top = Totals->Top - 3;

    }
	else
	{
		StatusBar1->Visible = !StatusBar1->Visible;
		N48->Checked = !N48->Checked;
		FormResize(this);
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N47Click(TObject *Sender)
{
	ProjectExplorer->Visible = !ProjectExplorer->Visible;
	N47->Checked = !N47->Checked;
	FormResize(this);	
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Splitter1Moved(TObject *Sender)
{
	FormResize(this);	
}
//---------------------------------------------------------------------------

void TMainForm::CloseProject()
{
	for(unsigned int i=0; i<events.size(); i++)
	{
		delete events[i].link;
	}
	events.clear();
	works.clear();
	ProjectName = "Безымянный";
	ProjectAuthor = "";
	ProjectDefinition = "";
	timeed="дн.";
	moneyed="тыс. руб.";
	N36Click(this);
	N12Click(this);
	StatusBar1->Panels->Items[1]->Text = "";
	TreeView1->Items->Item[0]->DeleteChildren();
	TreeView1->Items->Item[1]->DeleteChildren();
	ListView1->Clear();
	ListView2->Clear();
	EventsTable->Clear();
	TkrC->Caption = "0";
	CostC->Caption = "0";
	CAccelC->Caption = "0";
	ListView1->Tag = 1;
	EventsTable->Tag = 1;
	AccelC->Text = "0";
	issaved = false;
	eventcount = 0;
	MainForm->Caption = "Безымянный - " + Application->Title;
	if(!Import->Showing) Import->Button4Click(this);
	
	
}
//---------------------------------------------------------------------------

void TMainForm::ExplorerUpdate()
{
	unsigned int i;
	TreeView1->Items->BeginUpdate();
	TreeView1->Items->Item[0]->DeleteChildren();
	TreeView1->Items->Item[1]->DeleteChildren();
	for(i=0; i<events.size(); i++)
	{
		TreeView1->Items->AddChildObject(TreeView1->Items->Item[0], events[i].number, &events[i]);
	}
	for(i=0; i<works.size(); i++)
	{
		TreeView1->Items->AddChildObject(TreeView1->Items->Item[TreeView1->Items->Item[0]->Count + 1], works[i].mark, &works[i]);
		TreeView1->Items->Item[TreeView1->Items->Item[0]->Count + 2 + i]->ImageIndex = 1;
		TreeView1->Items->Item[TreeView1->Items->Item[0]->Count + 2 + i]->SelectedIndex = 1;		
		
	}
    TreeView1->Items->Item[0]->AlphaSort(0);
	TreeView1->Items->Item[TreeView1->Items->Item[0]->Count + 1]->AlphaSort(0);
	TreeView1->Items->Item[0]->Expand(0);
	TreeView1->Items->Item[TreeView1->Items->Item[0]->Count + 1]->Expand(0);
	TreeView1->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TreeView1DblClick(TObject *Sender)
{
	int i;
	if(TreeView1->Selected->AbsoluteIndex > TreeView1->Items->Item[0]->Count + 1)
	{
		for(i=0; i<works.size(); i++)
		{
			if(&works[i]==TreeView1->Selected->Data)
			{
				WPwork = (Work *) TreeView1->Selected->Data;
				break;
			}
		}
		WorkProp->ShowModal();
		DeleteWorks();
	}
	else if(TreeView1->Selected->AbsoluteIndex > 0 && TreeView1->Selected->AbsoluteIndex < TreeView1->Items->Item[0]->Count + 1)
	{
		for(i=0; i<events.size(); i++)
		{
			if(&events[i]==TreeView1->Selected->Data)
			{
				EPev = (Event *) TreeView1->Selected->Data;
				break;
			}
		}
		EventProp->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TreeView1Click(TObject *Sender)
{
	int i;
	if(TreeView1->Selected->AbsoluteIndex > TreeView1->Items->Item[0]->Count + 1)
	{
		for(i=0; i<works.size(); i++)
		{
			if(&works[i]==TreeView1->Selected->Data)
			{
				actevent = -1;
				actwork = i;
				Draw();
				N22->Enabled = true;
				N36->Enabled = true;
				break;
			}
		}
	}
	else if(TreeView1->Selected->AbsoluteIndex > 0 && TreeView1->Selected->AbsoluteIndex < TreeView1->Items->Item[0]->Count + 1)
	{
		for(i=0; i<events.size(); i++)
		{
			if(&events[i]==TreeView1->Selected->Data)
			{
                actwork = -1;
				actevent = i;
				Draw();
				N22->Enabled = true;
				N36->Enabled = true;
				break;
			}
		}
    }
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N51Click(TObject *Sender)
{
	int i;
	for(i=0; i<works.size(); i++)
	{
		if(&works[i]==TreeView1->Items->Item[ExplorerPopupIndex]->Data)
		{
			DeleteWork(i);
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N54Click(TObject *Sender)
{
    unsigned int i;
	for(i=0; i<events.size(); i++)
	{
		if(&events[i]==TreeView1->Items->Item[ExplorerPopupIndex]->Data)
		{
			EPev = &events[i];
			EventProp->ShowModal();
			break;
		}
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExplorerPopupPopup(TObject *Sender)
{
	if(TreeView1->Selected->AbsoluteIndex > TreeView1->Items->Item[0]->Count + 1)
	{
		N53->Visible = false;
		N54->Visible = false;
		N51->Visible = true;
		N52->Visible = true;
		N55->Visible = false;
		N56->Visible = false;
	}
	else if(TreeView1->Selected->AbsoluteIndex > 0 && TreeView1->Selected->AbsoluteIndex < TreeView1->Items->Item[0]->Count + 1)
	{
		N53->Visible = true;
		N54->Visible = true;
		N51->Visible = false;
		N52->Visible = false;
		N55->Visible = false;
		N56->Visible = false;
	}
	else if(!TreeView1->Selected->AbsoluteIndex)
	{
		N53->Visible = false;
		N54->Visible = false;
		N51->Visible = false;
		N52->Visible = false;
		N55->Visible = true;
		N56->Visible = false;
	}
	else if(TreeView1->Selected->AbsoluteIndex == TreeView1->Items->Item[0]->Count + 1)
	{
    	N53->Visible = false;
		N54->Visible = false;
		N51->Visible = false;
		N52->Visible = false;
		N55->Visible = false;
		N56->Visible = true;
    }
	ExplorerPopupIndex = TreeView1->Selected->AbsoluteIndex;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
	TreeView1Click(this);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N53Click(TObject *Sender)
{
    int i;
	for(i=0; i<events.size(); i++)
	{
		if(&events[i]==TreeView1->Items->Item[ExplorerPopupIndex]->Data)
		{
			DeleteEvent(i);
			break;
		}
	}        
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N52Click(TObject *Sender)
{
    unsigned int i;
	for(i=0; i<works.size(); i++)
	{
		if(&works[i]==TreeView1->Items->Item[ExplorerPopupIndex]->Data)
		{
            WPwork = &works[i];
			WorkProp->ShowModal();
			DeleteWorks();
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N55Click(TObject *Sender)
{
	NewEvent(eventcount*w/2 + 10, 10, false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N56Click(TObject *Sender)
{
	NewWork(-10, -10);	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N57Click(TObject *Sender)
{
	Totals->Visible = !Totals->Visible;
	Splitter2->Visible = !Splitter2->Visible;
	N57->Checked = !N57->Checked;
	FormResize(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N59Click(TObject *Sender)
{
	unsigned int i, j, k;
	int countfounded=0, min=30000, max=0;
	int bufer;
	vector <int> level;
	
	if(Check())
	{
		//ранги для расстановки
		for(i=0; i < events.size(); i++)
		{
			events[i].rank2 = -1;
		}
		events[FirstEvent()].rank2 = 0;
		countfounded = 1;
		while(countfounded < events.size())
		{
			for(i=0; i<events.size(); i++)
			{
				if(events[i].rank2 == -1)
				{
					min = 30000;
					for(j=0; j<works.size(); j++)
					{
						if(works[j].event2i == i)
						{
							//ShowMessage("Текущее событие - конечное");
							if(events[works[j].event1i].rank2 != -1)
							{
								if(events[works[j].event1i].rank2 < min)
								{
									min = events[works[j].event1i].rank2;
									//ShowMessage("Изменён мин на " + IntToStr(min));
								}
							}
							else
							{
								break;
							}
						}
					}
					if(j==works.size())
					{
						//ShowMessage("Найден ранг " + IntToStr(min+1) + " у события с индексом = " + IntToStr(i));
						events[i].rank2 = min+1;
						if(max < events[i].rank2) max = events[i].rank2;
						countfounded++;
					}
				}
			}
		}
		//ShowMessage(max);
		for(i=0; i<= max; i++)
		{
			level.clear();
			for(j=0; j<events.size(); j++)
			{
				if(events[j].rank2==i) level.push_back(j);
			}
			//ShowMessage("Уровень");
			for(j=0; j<level.size(); j++)
			{
				for(k=j+1; k<level.size(); k++)
				{
					//ShowMessage("Сравниваем " + IntToStr(events[level[j]].number) + " и " + IntToStr(events[level[k]].number));
					if(events[level[j]].number > events[level[k]].number)
					{
						//ShowMessage("Меняем " + IntToStr(level[j]) + " и " +IntToStr(level[k]));
						bufer = level[j];
						level[j] = level[k];
						level[k] = bufer;
					}
				}
			}
			for(j=0; j<level.size(); j++)
			{
				events[level[j]].link->Left = LEFT + i * HORIZ + ((j + i) % 2 == 0 ? WAVE : -WAVE);
				events[level[j]].x = events[level[j]].link->Left;
				events[level[j]].link->Top = RIGHT + j * VERT;
				events[level[j]].y = events[level[j]].link->Top;
			}
		}

		Draw();
		EventsTableUpdate();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------

void TMainForm::EventsTableUpdate()
{
	int i;

	EventsTable->Clear();
	for(i=0; i<events.size(); i++)
	{
		EventsTable->Items->Add();
		EventsTable->Items->Item[i]->Data = &events[i];
		EventsTable->Items->Item[i]->ImageIndex = -1;
		EventsTable->Items->Item[i]->Caption = events[i].number;
		EventsTable->Items->Item[i]->SubItems->Add(events[i].name);
		if(events[i].t1 != -1) EventsTable->Items->Item[i]->SubItems->Add(events[i].t1);
		else EventsTable->Items->Item[i]->SubItems->Add("");
		if(events[i].t2 != -1) EventsTable->Items->Item[i]->SubItems->Add(events[i].t2);
		else EventsTable->Items->Item[i]->SubItems->Add("");
		if(events[i].r != -1) EventsTable->Items->Item[i]->SubItems->Add(events[i].r);
		else EventsTable->Items->Item[i]->SubItems->Add("");
		if(events[i].rank != -1) EventsTable->Items->Item[i]->SubItems->Add(events[i].rank);
		else EventsTable->Items->Item[i]->SubItems->Add("");
		if(events[i].rank2 != -1) EventsTable->Items->Item[i]->SubItems->Add(events[i].rank2);
		else EventsTable->Items->Item[i]->SubItems->Add("");						

	}
	EventsTable->AlphaSort();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PageControl1Change(TObject *Sender)
{
	if(PageControl1->TabIndex == 0) N67->Checked = true;
	else if(PageControl1->TabIndex == 1) N68->Checked = true;
	else if(PageControl1->TabIndex == 2) N69->Checked = true;
	else if(PageControl1->TabIndex == 3) N79->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N60Click(TObject *Sender)
{
	unsigned int i, j, k;
	int countfounded=0, max=0;
	int bufer;

	if(Check())
	{
		for(i=0; i < events.size(); i++)
		{
			events[i].rank = -1;
		}
		//нумерация событий по рангам
		events[FirstEvent()].rank = 0;
		countfounded = 1;
		while(countfounded < events.size())
		{
			for(i=0; i<events.size(); i++)
			{
				if(events[i].rank == -1)
				{
					max = 0;
					for(j=0; j<works.size(); j++)
					{
						if(works[j].event2i == i)
						{
							//ShowMessage("Текущее событие - конечное");
							if(events[works[j].event1i].rank != -1)
							{
								if(events[works[j].event1i].rank > max)
								{
									max = events[works[j].event1i].rank;
									//ShowMessage("Изменён макс на " + IntToStr(max));
								}
							}
							else
							{
								break;
							}
						}
					}
					if(j==works.size())
					{
						//ShowMessage("Найден ранг " + IntToStr(max+1) + " у события с индексом = " + IntToStr(i));
						events[i].rank = max+1;
						countfounded++;
					}
				}
			}
		}
		for(i=0; i<events.size(); i++)
		{
			if(max < events[i].rank) max = events[i].rank;
		}
		for(i=0; i<=max; i++)
		{
			for(j=0; j<events.size(); j++)
			{
				if(events[j].rank == i)
				{
					for(k=0; k<events.size(); k++)
					{
						if(events[j].rank < events[k].rank && events[j].number > events[k].number)
						{
							bufer = events[j].number;
							events[j].number = events[k].number;
							events[k].number = bufer;
						}
					}
				}
			}
		}

		Draw();
		EventsTableUpdate();
		WorksTableUpdate();
		ExplorerUpdate();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N21Click(TObject *Sender)
{
	About->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1ColumnClick(TObject *Sender,
      TListColumn *Column)
{
	bool asc(ListView1->Tag > 0);
	int Index(Column->Index);
	if((asc ? ListView1->Tag : -ListView1->Tag) - 1 != Index)
		ListView1->Tag = Index + 1;
	else ListView1->Tag = -ListView1->Tag; 


	// здесь можно установить соотв. картинку в заголовке столбца,
	// чтобы было видно, по какому столбцу и в каком направлении отсортировано,
	// 0 - индекс картинки "по возрастанию", 1 - "по убыванию"
	asc = (ListView1->Tag > 0);
	for (int colNo(0); colNo < ListView1->Columns->Count; colNo++ )
		ListView1->Column[colNo]->ImageIndex = (colNo == Index ? (asc ? 0 : 1) : -1);
	 
    ListView1->AlphaSort();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1Compare(TObject *Sender, TListItem *Item1,
      TListItem *Item2, int Data, int &Compare)
{
	bool asc(ListView1->Tag > 0);
	int Column((asc ? ListView1->Tag : -ListView1->Tag) - 1);
	TListItem
		* item1(asc ? Item1 : Item2),
		* item2(asc ? Item2 : Item1);
	//ShowMessage(Column);
	if(Column == 0 || Column == 1 || Column == 2 || Column == 3)
	{
		if (Column == 0)
			Compare = AnsiCompareText(item1->Caption, item2->Caption);
		else
			Compare = AnsiCompareText(item1->SubItems->Strings[Column - 1], item2->SubItems->Strings[Column - 1]);
	}
	else
	{
		Compare = (StrToFloatDef(item1->SubItems->Strings[Column - 1], 0) > StrToFloatDef(item2->SubItems->Strings[Column - 1], 0)) ? 1 : -1;
		if(StrToFloatDef(item1->SubItems->Strings[Column - 1], 0) == StrToFloatDef(item2->SubItems->Strings[Column - 1], 0)) Compare = 0;
	}
	//ShowMessage(Column);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventsTableColumnClick(TObject *Sender,
      TListColumn *Column)
{
	bool asc(EventsTable->Tag > 0);
	int Index(Column->Index);
	if((asc ? EventsTable->Tag : -EventsTable->Tag) - 1 != Index)
		EventsTable->Tag = Index + 1;
	else EventsTable->Tag = -EventsTable->Tag; 

	asc = (EventsTable->Tag > 0);
	for (int colNo(0); colNo < EventsTable->Columns->Count; colNo++ )
		EventsTable->Column[colNo]->ImageIndex = (colNo == Index ? (asc ? 0 : 1) : -1);
	 
	EventsTable->AlphaSort();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventsTableCompare(TObject *Sender, TListItem *Item1,
      TListItem *Item2, int Data, int &Compare)
{
	bool asc(EventsTable->Tag > 0);
	int Column((asc ? EventsTable->Tag : -EventsTable->Tag) - 1);
	TListItem
		* item1(asc ? Item1 : Item2),
		* item2(asc ? Item2 : Item1);
	//ShowMessage(Column);
	if(Column == 1)
	{
		Compare = AnsiCompareText(item1->SubItems->Strings[Column - 1], item2->SubItems->Strings[Column - 1]);
	}
	else
	{
		if(!Column)
		{
        	Compare = (StrToFloatDef(item1->Caption, 0) > StrToFloatDef(item2->Caption, 0)) ? 1 : -1;
		}
		else
		{
        	Compare = (StrToFloatDef(item1->SubItems->Strings[Column - 1], 0) > StrToFloatDef(item2->SubItems->Strings[Column - 1], 0)) ? 1 : -1;
			if(StrToFloatDef(item1->SubItems->Strings[Column - 1], 0) == StrToFloatDef(item2->SubItems->Strings[Column - 1], 0)) Compare = 0;
        }

	}
	//ShowMessage("ok");
}
//---------------------------------------------------------------------------

int TMainForm::Calculate()
{
	unsigned int i, k, l;
	int j, max=-1, min=30000, minwork, countfounded;
	int first=-1, last=-1;
	float mincost, isum=0;
	vector <int> idecrease;

	if(Check())
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].t1 = -1;
			events[i].t2 = -1;
			events[i].r = -1;
		}
		first = FirstEvent();
		last = LastEvent();
		events[first].t1 = 0;
		events[first].t2 = 0;
		events[first].r = 0;
		//ShowMessage("Начальное событие с индексом " + IntToStr(first));
		countfounded = 1;

		//раннее время для событий
		while(countfounded<events.size())
		{
			for(i=0; i<events.size(); i++)
			{
				max = -1;
				if(events[i].t1 == -1)
				{
					for(j=0; j<works.size(); j++)
					{
						//ShowMessage(i);
						if(works[j].event2i == i)
						{
							//ShowMessage("Конечное событие - текущее");
							if(events[works[j].event1i].t1 != -1)
							{
								//ShowMessage("Здесь");
								if(max < (events[works[j].event1i].t1 + works[j].currentt))
								{
									max = events[works[j].event1i].t1 + works[j].currentt;
									//ShowMessage(max);
								}
							}
							else
							{
								break;
							}
						}
					}
					if(j==works.size() && max > -1)
					{
						events[i].t1 = max;
						//ShowMessage("Записано макс значение" + IntToStr(max));
						countfounded++;
					}
				}
			}
		}

		//позднее время событий
		events[last].t2 = events[last].t1;
		events[last].r = 0;
		countfounded = 2;
		while(countfounded<events.size())
		{
			for(i=0; i<events.size(); i++)
			{
				min = 30000;
				if(events[i].t2 == -1)
				{
					for(j=0; j<works.size(); j++)
					{
						//ShowMessage(i);
						if(works[j].event1i == i)
						{
							//ShowMessage("Начальное событие - текущее");
							if(events[works[j].event2i].t2 != -1)
							{
								//ShowMessage("Здесь");
								if(min > (events[works[j].event2i].t2 - works[j].currentt))
								{
									min = events[works[j].event2i].t2 - works[j].currentt;
									//ShowMessage(min);
								}
							}
							else
							{
								break;
							}
						}
					}
					if(j==works.size() && min < 30000)
					{
						events[i].t2 = min;
						//ShowMessage("Записано мин значение" + IntToStr(min));
						countfounded++;
					}
				}
			}
		}

		//резервы времени для событий
		for(i=0; i<events.size(); i++)
		{
			if(events[i].r == -1) events[i].r = events[i].t2 - events[i].t1;
		}

		//работы
		s=0;
		for(i=0; i<works.size(); i++)
		{
			works[i].Trn = events[works[i].event1i].t1;
			works[i].Tro = works[i].Trn + works[i].currentt;
			works[i].Tpn = events[works[i].event2i].t1 - works[i].currentt;
			works[i].Tpo = events[works[i].event2i].t1;
			works[i].Rp = events[works[i].event2i].t2 - events[works[i].event1i].t1 - works[i].currentt;
			works[i].Rs = events[works[i].event2i].t1 - events[works[i].event1i].t1 - works[i].currentt;
			s += works[i].currentcost;
		}

		//критические пути
		KrWs.clear();
		KrW.clear();
		do   //первый критический путь
		{
			if(!KrW.size())
			{
				for(i=0; i<works.size(); i++)
				{
					if(works[i].event1i == FirstEvent() && !works[i].Rp)
					{
						KrW.push_back(i);
						//ShowMessage("Добавили в критический путь работу с индексом = " + IntToStr(i));
						break;
					}
				}
			}
			else
			{
				for(i=0; i<works.size(); i++)
				{
					if(works[i].event1i == works[KrW[KrW.size()-1]].event2i && !works[i].Rp)
					{
						KrW.push_back(i);
						//ShowMessage("2Добавили в критический путь работу с индексом = " + IntToStr(i));
						break;
					}
				}
			}
		}
		while(works[KrW[KrW.size()-1]].event2i != LastEvent());
		KrWs.push_back(KrW);
		for(i=0; i<KrWs.size(); i++) //остальные кр. пути
		{
			//ShowMessage("i = " + IntToStr(i));
			for(j=KrWs[i].size()-1; j>=0; j--)
			{
				for(int k=0; k<works.size(); k++)
				{
					//ShowMessage("До условия");
					if(works[k].event1i == works[KrWs[i][j]].event1i && k> KrWs[i][j] && !works[k].Rp)
					{
						//ShowMessage("Прошли условие");
						KrW.clear();
						for(l=0; l<j; l++)
						{
							KrW.push_back(KrWs[i][l]);
						}
						//ShowMessage("Найдена работа с индексом = " + IntToStr(k));
						KrW.push_back(k);
						do
						{
							for(l=0; l<works.size(); l++)
							{
								if(works[l].event1i == works[KrW[KrW.size()-1]].event2i && !works[l].Rp)
								{
									KrW.push_back(l);
									//ShowMessage("3Добавили в критический путь работу с индексом = " + IntToStr(l));
									break;
								}
							}
						}
						while(works[KrW[KrW.size()-1]].event2i != LastEvent());
						KrWs.push_back(KrW);
						goto calculate;
						/*for(int a=0; a<KrWs.size(); a++)
						{
							for(int b=0; b<KrWs[a].size(); b++)
							{
								ShowMessage("Путь " + IntToStr(a) + "Работа " + IntToStr(KrWs[a][b]));
							}
						}*/
					}
				}
			}
			calculate:
		}

		//ускорение проекта
		
        for(i=0; i<works.size(); i++)
		{
			works[i].maxaccel = works[i].t - works[i].tu;

			if(!works[i].maxaccel)
			{
			   works[i].costuud = -1;
			   continue;
			}
			works[i].costuud = works[i].costu / works[i].maxaccel;
			//ShowMessage(works[i].mark + " " + IntToStr(works[i].maxaccel));
		}
		if(AccelC->Text == "") AccelC->Text = "0";
		
		if(StrToInt(AccelC->Text) > 0 && currentaccel < StrToInt(AccelC->Text))
		{
			if(Verbose->Checked) ShowMessage("Расчёт ускорения. Шаг №" + IntToStr(currentaccel + 1));

			KrMinIxs.clear();

			for(i=0; i<KrWs.size(); i++)
			{
				mincost = 1000000;
				for(j=0; j<KrWs[i].size(); j++)
				{
					if(mincost > works[KrWs[i][j]].costuud && (works[KrWs[i][j]].t - works[KrWs[i][j]].currentt) < works[KrWs[i][j]].maxaccel && works[KrWs[i][j]].costuud != -1)
					{
						mincost = works[KrWs[i][j]].costuud;
						minwork = KrWs[i][j];

					}
				}
				if(mincost < 1000000)
				{
					if(Verbose->Checked) ShowMessage("На " + IntToStr(i+1) + " кр. пути дешевле ускорить работу " + works[minwork].mark + " с Су уд. = " + FloatToStr(works[minwork].costuud));
					KrMinIxs.push_back(minwork);

				}
				else
				{
					Application->MessageBoxA("Такое ускорение невозможно. Уменьшите величину ускорения", Application->Title.c_str(), MB_ICONERROR + MB_OK);
					return 0;
				}
			}

			//общие работы критических путей
			ShareWorks.clear();
			for(i=0; i<works.size(); i++)
			{
				ShareWork.clear();
				ShareWork.push_back(i);
				for(j=0; j<KrWs.size(); j++)
				{
					for(k=0; k<KrWs[j].size(); k++)
					{
						if(KrWs[j][k] == i)
						{
							ShareWork.push_back(j);
						}
					}
				}
				if(ShareWork.size() > 2)
				{
					ShareWorks.push_back(ShareWork);
					//ShowMessage("Общая для крит. путей работа " + works[ShareWork[0]].mark);
					/*for(j=0; j<ShareWork.size(); j++)
					{
						ShowMessage(ShareWork[j]);
					}*/
				}
			}

			//поиск работ для ускорения
			float sum=0;
            vector <int> decrease;
			for(i=0; i<KrMinIxs.size(); i++)
			{
				isum += works[KrMinIxs[i]].costuud;
				idecrease.push_back(KrMinIxs[i]);
			}

			if(ShareWorks.size())
			{
				for(i=0; i<ShareWorks.size(); i++)
				{
					sum=0;
					decrease.clear();
					//ShowMessage("Общая работа " + works[ShareWorks[i][0]].mark);
					for(j=1; j<ShareWorks[i].size(); j++)
					{
						for(k=0; k<decrease.size(); k++)
						{
							if(decrease[k] == KrMinIxs[ShareWorks[i][j]])
							{
								break;
							}
						}
						if(k == decrease.size())
						{
							sum += works[KrMinIxs[ShareWorks[i][j]]].costuud;
							decrease.push_back(KrMinIxs[ShareWorks[i][j]]);
							//ShowMessage("Одна из альтернативных работ - " + works[KrMinIxs[ShareWorks[i][j]]].mark);
							//ShowMessage("Общая работа номер " + IntToStr(i+1) + "Добавили минимум = " + FloatToStr(works[KrMinIxs[ShareWorks[i][j]]].costuud));
						}
					}
					if(Verbose->Checked) ShowMessage("Найдена общая работа " + works[ShareWorks[i][0]].mark + " с Су уд. = " + FloatToStr(works[ShareWorks[i][0]].costuud));
					//ShowMessage("Альтернативная сумма для общей работы " + works[ShareWorks[i][0]].mark + " = " + FloatToStr(sum));

					if(works[ShareWorks[i][0]].costuud <= sum && (works[ShareWorks[i][0]].t - works[ShareWorks[i][0]].currentt) < works[ShareWorks[i][0]].maxaccel && works[ShareWorks[i][0]].costuud != -1)
					{
						sum = works[ShareWorks[i][0]].costuud;
						decrease.clear();
						decrease.push_back(ShareWorks[i][0]);
					}
                    vector <int> checkedworks;
					sum += OtherWorks(i, checkedworks, decrease);

					if(sum < isum || sum == isum && decrease.size() < idecrease.size())
					{
						isum = sum;
						idecrease = decrease;
						/*ShowMessage("Найден более выгодный вариант: сумма = " + FloatToStr(isum));
						ShowMessage("Ускоряемые работы:");
						for(j=0; j<idecrease.size(); j++)
						{
                            ShowMessage(works[idecrease[j]].mark);
						}*/
					}
				}
			}

			for(i=0; i<idecrease.size(); i++)
			{
				if(Verbose->Checked) ShowMessage("На данном шаге ускоряется работа " + works[idecrease[i]].mark);
			}
			if(Verbose->Checked) ShowMessage("Итоговая Су на данном шаге = " + FloatToStr(isum));
			for(i=0; i<idecrease.size(); i++)
			{
				works[idecrease[i]].currentt--;
				works[idecrease[i]].currentcost += works[idecrease[i]].costuud;
			}
			
			Chart2->Series[0]->AddXY(currentaccel, s, "");
			currentaccel++;
			Chart1->Series[0]->AddXY(currentaccel, isum, "");
			//Chart1->ser
			Calculate();

		}
		else
		{
        	
			Chart2->Series[0]->AddXY(currentaccel, s, "");
        }
        
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------

float TMainForm::OtherWorks(int ShareWorkI, vector <int> checkedworks, vector <int> &decrease)
{
	int i, j, k, l;
	float othersum=0, iothersum=0;
    vector <int> otherdecrease, iotherdecrease;

	if(ShareWorks[ShareWorkI].size() < KrWs.size() + 1)
	{
		checkedworks.push_back(ShareWorkI);
		iotherdecrease = decrease;
		//ShowMessage("В OtherWorks");
		for(i=0; i<KrMinIxs.size(); i++)
		{
		    for(j=0; j<checkedworks.size(); j++)
			{
				for(k=1; k<ShareWorks[checkedworks[j]].size(); k++)
				{
					if(i == ShareWorks[checkedworks[j]][k]) goto IsNotOther;

				}
			}
			/*for(j=1; j<ShareWorks[ShareWorkI].size(); j++)
			{
				if(i==ShareWorks[ShareWorkI][j]) break;
			}*/
			if(j == checkedworks.size())
			{
				for(k=0; k<iotherdecrease.size(); k++)
				{
					if(iotherdecrease[k] == KrMinIxs[i])
					{
						break;
					}
				}
				if(k==iotherdecrease.size())
				{
					iothersum += works[KrMinIxs[i]].costuud;
					iotherdecrease.push_back(KrMinIxs[i]);
					//ShowMessage("Одна из прочих работ - " + works[KrMinIxs[i]].mark);
				}
			}
            IsNotOther:
		}
		
		for(i=0; i<ShareWorks.size(); i++)
		{

			for(j=0; j<checkedworks.size(); j++)
			{
				for(k=1; k<ShareWorks[checkedworks[j]].size(); k++)
				{
					for(l=1; l<ShareWorks[i].size(); l++)
					{
						if(ShareWorks[i][l] == ShareWorks[checkedworks[j]][k]) goto IsNotShareOther;
					}
				}
			}
			if(j==checkedworks.size())
			{
				othersum=0;
				//ShowMessage("Прочая общая работа - " + works[ShareWorks[i][0]].mark);
				otherdecrease = decrease;
				for(j=1; j<ShareWorks[i].size(); j++)
				{
					for(k=0; k<otherdecrease.size(); k++)
					{
						if(otherdecrease[k] == KrMinIxs[ShareWorks[i][j]])
						{
							break;
						}
					}
					if(k == otherdecrease.size())
					{
						othersum += works[KrMinIxs[ShareWorks[i][j]]].costuud;
						otherdecrease.push_back(KrMinIxs[ShareWorks[i][j]]);
						//ShowMessage("Одна из альтернативных работ - " + works[KrMinIxs[ShareWorks[i][j]]].mark);
						//ShowMessage("Общая работа номер " + IntToStr(i+1) + "Добавили минимум = " + FloatToStr(works[KrMinIxs[ShareWorks[i][j]]].costuud));
					}
				}
				//if(Verbose->Checked) ShowMessage("Найдена прочая общая работа " + works[ShareWorks[i][0]].mark + " с Су уд. = " + FloatToStr(works[ShareWorks[i][0]].costuud));
				//ShowMessage("Альтернативная сумма для прочей общей работы " + works[ShareWorks[i][0]].mark + " = " + FloatToStr(othersum));
				if(works[ShareWorks[i][0]].costuud <= othersum && (works[ShareWorks[i][0]].t - works[ShareWorks[i][0]].currentt) < works[ShareWorks[i][0]].maxaccel && works[ShareWorks[i][0]].costuud != -1)
				{
					othersum = works[ShareWorks[i][0]].costuud;
					otherdecrease = decrease;
					otherdecrease.push_back(ShareWorks[i][0]);
				}
				//ShowMessage("Подитог суммы = " + FloatToStr(othersum));
				//ShowMessage("Количество прочих работ для ускорения у прочей общей работы " + works[ShareWorks[i][0]].mark + "БЫЛО =" + IntToStr(otherdecrease.size()));
				othersum += OtherWorks(i, checkedworks, otherdecrease);
				//ShowMessage("После добавления прочих работ подитог стал = " + FloatToStr(othersum) + "iothersum = " + FloatToStr(iothersum));
				//ShowMessage("Количество прочих работ для ускорения у прочей общей работы " + works[ShareWorks[i][0]].mark + "СТАЛО =" + IntToStr(otherdecrease.size()));
				if(othersum < iothersum || othersum == iothersum && otherdecrease.size() < iotherdecrease.size())
				{
					iothersum = othersum;
					iotherdecrease = otherdecrease;
				}
				
            }
			IsNotShareOther:
		}
		/*for(i=decrease.size(); i<iotherdecrease.size(); i++)
		{
			ShowMessage("Добавили для ускорения работу " + works[iotherdecrease[i]].mark + " к общей работе " + works[ShareWorks[ShareWorkI][0]].mark);
		}*/
		decrease = iotherdecrease;

	}


	return iothersum;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N19Click(TObject *Sender)
{
	int i, j;
	AnsiString way;

	for(i=0; i<works.size(); i++)
	{
		works[i].currentt = works[i].t;
        works[i].currentcost = works[i].cost;
	}
	currentaccel=0;
	Chart1->Series[0]->Clear();
	Chart2->Series[0]->Clear();
	Chart1->LeftAxis->Title->Caption = "Приращение стоимости (" + moneyed + ")";
	Chart2->LeftAxis->Title->Caption = "Общая стоимость (" + moneyed + ")";
	Chart1->BottomAxis->Title->Caption = "Величина ускорения (" + timeed + ")";
	Chart2->BottomAxis->Title->Caption = "Величина ускорения (" + timeed + ")";	

	Chart1->Series[0]->AddXY(0, 0, "");
	if(Calculate())
	{
        Draw();
		WorksTableUpdate();
		EventsTableUpdate();

		//занесение критических путей в таблицу
		ListView2->Clear();
		for(i=0; i<KrWs.size(); i++)
		{
			ListView2->Items->Add();
			ListView2->Items->Item[i]->Caption = i+1;
			way = "";
			for(j=0; j<KrWs[i].size(); j++)
			{
				//ShowMessage(IntToStr(i) + " " + IntToStr(j));
				way += IntToStr(events[works[KrWs[i][j]].event1i].number) + "->";
				if(j == KrWs[i].size()-1) way += IntToStr(events[works[KrWs[i][j]].event2i].number);
			}
			ListView2->Items->Item[i]->SubItems->Add(way.SubString(1, way.Length()));
			way = "";
			for(j=0; j<KrWs[i].size(); j++)
			{
				//ShowMessage(IntToStr(i) + " " + IntToStr(j));
				way += works[KrWs[i][j]].mark + "->";
			}
			ListView2->Items->Item[i]->SubItems->Add(way.SubString(1, way.Length()-2));
			Tkr = events[LastEvent()].t1;
			TkrC->Caption = FloatToStr(Tkr) + " " + timeed;
			CostC->Caption = FloatToStrF(s, ffFixed, 10, 3) + " " + moneyed;
			CAccelC->Caption = IntToStr(currentaccel) + " " + timeed;
		}
    }	
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N62Click(TObject *Sender)
{
	int i, min=-1;

	for(i=0; i<events.size(); i++)
	{
		if(!i) min = events[i].link->Left;
		else
		{
			if(min > events[i].link->Left) min = events[i].link->Left;
		}
	}
	if(min != -1 && min - 10 >=0)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Left -= 10;
			events[i].x -= 10;
		}
		Draw();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N63Click(TObject *Sender)
{
	int i, max=-1;

	for(i=0; i<events.size(); i++)
	{
		if(!i) max = events[i].link->Left;
		else
		{
			if(max < events[i].link->Left) max = events[i].link->Left;
        }
	}
	if(max != -1)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Left += 10;
			events[i].x += 10;
		}
		Draw();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N64Click(TObject *Sender)
{
	int i, min=-1;

	for(i=0; i<events.size(); i++)
	{
		if(!i) min = events[i].link->Top;
		else
		{
			if(min > events[i].link->Top) min = events[i].link->Top;
        }
	}
	if(min != -1 && min - 10 >=0)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Top -= 10;
			events[i].y -= 10;
		}
		Draw();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N65Click(TObject *Sender)
{
	unsigned int i;
	int max=-1;

	for(i=0; i<events.size(); i++)
	{
		if(!i) max = events[i].link->Top;
		else
		{
			if(max < events[i].link->Top) max = events[i].link->Top;
        }
	}
	if(max != -1)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Top += 10;
			events[i].y += 10;
		}
		Draw();
		StatusBar1->Panels->Items[1]->Text = "Изменён";
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	
	if(PageControl1->TabIndex == 0 &&  Shift.Contains(ssCtrl))
	{
        TreeView1->SetFocus();
		if(Key == VK_LEFT) N62Click(this);
		else if(Key == VK_RIGHT) N63Click(this);
		else if(Key == VK_UP) N64Click(this);
		else if(Key == VK_DOWN) N65Click(this);
		else if(Key == VK_HOME) N66Click(this);
		
    }

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N66Click(TObject *Sender)
{
	int i, min=-1;

	for(i=0; i<events.size(); i++)
	{
		if(!i) min = events[i].link->Left;
		else
		{
			if(min > events[i].link->Left) min = events[i].link->Left;
		}
	}
	if(min != -1)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Left -= min - 10;
			events[i].x -= min - 10;
		}
	}

    min = -1;
	for(i=0; i<events.size(); i++)
	{
		if(!i) min = events[i].link->Top;
		else
		{
			if(min > events[i].link->Top) min = events[i].link->Top;
        }
	}
	if(min != -1)
	{
		for(i=0; i<events.size(); i++)
		{
			events[i].link->Top -= min - 10;
			events[i].y -= min - 10;
        }
	}
    StatusBar1->Panels->Items[1]->Text = "Изменён";
	Draw();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N3Click(TObject *Sender)
{
	if(StatusBar1->Panels->Items[1]->Text != "")
	{
		switch(Application->MessageBoxA("Проект был изменён.\n\nСохранить изменения?", Application->Title.c_str(), MB_ICONWARNING + MB_YESNOCANCEL))
		{
			case IDYES:
				N29Click(this);
				break;

			case IDNO:
				goto open;

				
			case IDCANCEL:

				return;
		}
		
	}
	if(StatusBar1->Panels->Items[1]->Text == "")
	{
		open:
		if(OpenProject->InitialDir.Length() == 0)
			OpenProject->InitialDir = ExtractFileDir(Application->ExeName);
		if(OpenProject->Execute())
		{
        	Open(OpenProject->FileName);
        }
	}

}
//---------------------------------------------------------------------------

void TMainForm::Open(AnsiString FileName)
{
	ifstream in;
	char buf[255];
	size_t len;
	Event tempi;
	int i;
	Work tempw;

	//ShowMessage(FileName);
	in.open(FileName.c_str(), ios::binary);
	if(!in)
	{
		Application->MessageBoxA("Ошибка при открытии файла", Application->Title.c_str(), MB_ICONERROR + MB_OK);
		return;
    }
	CloseProject();
	in.getline(buf, 255);
	ProjectName = buf;
	in.getline(buf, 255);
	ProjectAuthor = buf;
	in.read((char *) &len, sizeof(len));
	ProjectDefinition.SetLength(len);
	in.read((char *) ProjectDefinition.data(), len);
	in.getline(buf, 255);
	timeed = buf;
	in.getline(buf, 255);
	moneyed = buf;
	in.read((char *) &len, sizeof(len));
	//ShowMessage(len);
	for(i=0; i<len; i++)
	{
		tempi.deserialize(in);
		events.push_back(tempi);
	}
	in.read((char *) &len, sizeof(len));
	for(i=0; i<len; i++)
	{
		tempw.deserialize(in);
		works.push_back(tempw);
	}
	//ShowMessage("Всё загружено");
	in.close();
	issaved = true;
	SaveProject->FileName = FileName;
	MainForm->Caption = ExtractFileName(FileName).SubString(1, ExtractFileName(FileName).LastDelimiter(".") - 1) + " - " + Application->Title;
	Draw();
	ExplorerUpdate();
	WorksTableUpdate();
	EventsTableUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N30Click(TObject *Sender)
{
	if(!issaved) SaveProject->FileName = ProjectName;
	if(SaveProject->Execute())
	{
		issaved = true;
		N29Click(this);
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N29Click(TObject *Sender)
{
	ofstream out;
	size_t len;
	int i;

	if(issaved)
	{
    	out.open(SaveProject->FileName.c_str(), ios::binary);
		out << ProjectName.c_str() << "\n";
		out << ProjectAuthor.c_str() << "\n";
		len = ProjectDefinition.Length();
		out.write((char *) &len, sizeof(len));
		out.write((char *) ProjectDefinition.c_str(), len);
		out << timeed.c_str() << "\n";
		out << moneyed.c_str() << "\n";
		len = events.size();
		out.write((char *) &len, sizeof(len));
		for(i=0; i<events.size(); i++)
		{
			events[i].serialize(out);
		}
		len = works.size();
		out.write((char *) &len, sizeof(len));
		for(i=0; i<works.size(); i++)
		{
			works[i].serialize(out);
		}
        
		out.close();
		StatusBar1->Panels->Items[1]->Text = "";
		MainForm->Caption = ExtractFileName(SaveProject->FileName).SubString(1, ExtractFileName(SaveProject->FileName).LastDelimiter(".") - 1) + " - " + Application->Title;
	}
	else
	{
        N30Click(this);
    }	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
	if(StatusBar1->Panels->Items[1]->Text != "")
	{
		switch(Application->MessageBoxA("Проект был изменён.\n\nСохранить изменения?", Application->Title.c_str(), MB_ICONWARNING + MB_YESNOCANCEL))
		{
			case IDYES:
				N29Click(this);
				break;

			case IDNO:
                CanClose = true;
				break;
			case IDCANCEL:
				
				break;
		}

	}
	if(StatusBar1->Panels->Items[1]->Text == "")  CanClose = true;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N67Click(TObject *Sender)
{
	PageControl1->TabIndex = 0;
	N67->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N68Click(TObject *Sender)
{
	PageControl1->TabIndex = 1;
	N68->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N69Click(TObject *Sender)
{
	PageControl1->TabIndex = 2;
	N69->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N45Click(TObject *Sender)
{
	ofstream out;
	int i, j;
	if(issaved) HtmlExport->FileName = ExtractFileName(SaveProject->FileName).SubString(1, ExtractFileName(SaveProject->FileName).LastDelimiter(".") - 1);
	else HtmlExport->FileName = ProjectName;
	if(HtmlExport->Execute())
	{
		out.open(HtmlExport->FileName.c_str());

		out << "<html>\n<head>\n<title>" << ProjectName.c_str() << "</title>\n</head>\n<body>\n";
		out << "<h3>Название: " << ProjectName.c_str() << "</h3>\n";
		out << "<h3>Автор:  " << ProjectAuthor.c_str() << "</h3>\n";
		out << "<h3>Описание:  " << ProjectDefinition.c_str() << "</h3>\n";

		N36Click(this);
		Graphics::TBitmap *grafic = new Graphics::TBitmap();
		grafic->Assign(EventImage->Picture);
		grafic->Width -= 400;
		grafic->Height -= 400;
		for(int i=0; i<events.size(); i++)
		{
			grafic->Canvas->Draw(events[i].link->Left, events[i].link->Top, events[i].link->Picture->Bitmap);
		}
		grafic->SaveToFile(ExtractFilePath(HtmlExport->FileName) + "graph.bmp");
		grafic->Free();

		out << "<h3>Сетевой график:</h3>\n";
		out << "<img src=graph.bmp border=1>\n";
		out << "<h3>Итоги проекта:</h3>\n";
		out << "<p>Tкр = " << TkrC->Caption.c_str() << "</p>\n";
		out << "<p>S = " << CostC->Caption.c_str() << "</p>\n";
		out << "<p>Утек = " << CAccelC->Caption.c_str() << "</p>\n";

		out << "<h3>Критические пути:</h3>\n<table border=1>\n<tr>";
		for (i=0; i < ListView2->Columns->Count; i++)
		{
			out << "<td>";
			out << ListView2->Columns->Items[i]->Caption.c_str();
			out << "</td>";

		}
		out << "</tr>\n";
		for(i=0; i<KrWs.size(); i++)
		{
			out << "<tr><td>";
			out << ListView2->Items->Item[i]->Caption.c_str();
			out << "</td>";
			for (j=0; j < ListView2->Columns->Count-1; j++)
			{
				out << "<td>";
				out << (ListView2->Items->Item[i]->SubItems->Strings[j] != "" ? ListView2->Items->Item[i]->SubItems->Strings[j].c_str() : "&nbsp");
				out << "</td>";

			}
			out << "</tr>\n";
		}
		out << "</table>\n";

		out << "<h3>Работы:</h3>\n<table border=1>\n<tr>";
		for (i=0; i < ListView1->Columns->Count; i++)
		{
			out << "<td>";
			out << ListView1->Columns->Items[i]->Caption.c_str();
			out << "</td>";

		}
		out << "</tr>\n";
		for(i=0; i<works.size(); i++)
		{
			out << "<tr><td>";
			out << ListView1->Items->Item[i]->Caption.c_str();
			out << "</td>";
			for (j=0; j < ListView1->Columns->Count-1; j++)
			{
				out << "<td>";
				out << (ListView1->Items->Item[i]->SubItems->Strings[j] != "" ? ListView1->Items->Item[i]->SubItems->Strings[j].c_str() : "&nbsp");
				out << "</td>";

			}
			out << "</tr>\n";
		}
		out << "</table>\n";

		out << "<h3>События:</h3>\n<table border=1>\n<tr>";
		for (i=0; i < EventsTable->Columns->Count; i++)
		{
			out << "<td>";
			out << EventsTable->Columns->Items[i]->Caption.c_str();
			out << "</td>";

		}
		out << "</tr>\n";
		for(i=0; i<events.size(); i++)
		{
			out << "<tr><td>";
			out << EventsTable->Items->Item[i]->Caption.c_str();
			out << "</td>";
			for (j=0; j < EventsTable->Columns->Count-1; j++)
			{
				out << "<td>";
				out << (EventsTable->Items->Item[i]->SubItems->Strings[j] != "" ? EventsTable->Items->Item[i]->SubItems->Strings[j].c_str() : "&nbsp");
				out << "</td>";

			}
			out << "</tr>\n";
		}
		out << "</table>\n";

		out << "<h3>Обозначения.</h3>\n";
		out << "<p>Итоги проекта:</p>\n";
		out << "<p>Ткр - длительность критического пути</p>\n";
		out << "<p>S - общая стоимость проекта</p>\n";
		out << "<p>Утек - текущее время ускорения проекта (для данного ускорения выполнены все расчёты)</p>\n";
		out << "<br><p>Работы:</p>\n";
		out << "<p>t - нормальный срок выполнения работы</p>\n";
		out << "<p>tтек - текущий срок выполнения работы (при текущем ускорении)</p>\n";
		out << "<p>tу - ускоренный срок выполнения работы</p>\n";
		out << "<p>Сн - нормальная стоимость работы</p>\n";
		out << "<p>Стек - текущая стоимость выполнения работы (при текущем ускорении)</p>\n";
		out << "<p>Су - плата за ускорение выполнения работы</p>\n";
		out << "<p>Трн - раннее время начала работы</p>\n";
		out << "<p>Тро - раннее время окончания работы</p>\n";
		out << "<p>Тпн - поздне время начала работы</p>\n";
		out << "<p>Тпо - позднее время окончания работы</p>\n";
		out << "<p>Rс - свободный резерв работы</p>\n";
		out << "<p>Rп - полный резерв работы</p>\n";
		out << "<p>Уmax - максимально возможное ускорение работы</p>\n";
		out << "<p>Су уд - удельная стоимость ускорения работы</p>\n";
		out << "<br><p>События:</p>\n";
		out << "<p>Тр - раннее время наступления события</p>\n";
		out << "<p>Тп - позднее время наступления события</p>\n";
		out << "<p>R - резерв времени события</p>\n";

		out << "</body>\n</html>";
		out.close();
	}


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VerboseClick(TObject *Sender)
{
	Verbose->Checked = !Verbose->Checked;	
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N28Click(TObject *Sender)
{
	Design->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N20Click(TObject *Sender)
{
	ShellExecute(Handle, "open", (ExtractFilePath(Application->ExeName) + "\\help.chm").c_str(), NULL, NULL, SW_SHOWNORMAL);  	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N75Click(TObject *Sender)
{
	if(ListView1->SelCount == 1)
	{
		WPwork = (Work *) ListView1->Selected->Data;
		WorkProp->ShowModal();
		DeleteWorks();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N74Click(TObject *Sender)
{
	if(ListView1->SelCount == 1)
	{
		for(int i=0; i<works.size(); i++)
		{
			if(&works[i] == ListView1->Selected->Data)
			{
				DeleteWork(i);
				break;
			}
		}
	 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N73Click(TObject *Sender)
{
	if(EventsTable->SelCount == 1)
	{
		EPev = (Event *) EventsTable->Selected->Data;
		EventProp->ShowModal();
	}

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N72Click(TObject *Sender)
{
	if(EventsTable->SelCount == 1)
	{
		for(int i=0; i<events.size(); i++)
		{
			if(&events[i] == EventsTable->Selected->Data)
			{
				DeleteEvent(i);
				break;
            }
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EventsTableDblClick(TObject *Sender)
{
	if(EventsTable->SelCount == 1)
	{
		EPev = (Event *) EventsTable->Selected->Data;
		EventProp->ShowModal();
    }
}
//---------------------------------------------------------------------------
void TMainForm::DeleteWorks()
{
	for(unsigned int i=0; i<works.size(); i++)
	{
		if(works[i].fordelete)
		{
			DeleteWork(i);
			i--;
        }
	}
	Draw();
	WorksTableUpdate();
	ExplorerUpdate();
}
//---------------------------------------------------------------------------
//автокоррекция
void __fastcall TMainForm::N76Click(TObject *Sender)
{
	int i=0, j, k, count1=0, count2=0, wi, delevent;
	vector <int> lasts;

	//удаление избыточных фиктивных работ и событий
	for(i=0; i<works.size(); i++)
	{
		if(!works[i].t)
		{
			count1 = 0;
			count2 = 0;
			for(j=0; j<works.size(); j++)
			{
				if(works[j].event2i == works[i].event1i)
				{
					count1++;
					wi = j;
                }
				if(works[j].event1i == works[i].event1i)
				{
					count2++;
				}
			}
			if(count1 == 1 && count2 == 1)
			{
				for(j=0; j<works.size(); j++)
				{
                    if(works[j].event1i == works[wi].event1i && works[j].event2i == works[i].event2i) break;
				}
				if(j==works.size())
				{
					//ShowMessage(works[i].mark);
					works[wi].event2i = works[i].event2i;
					DeleteEvent(works[i].event1i);
					i=-1;
                }	
            }

        }
	}

	//перенесение работ в общее конечное событие
	correction:
	lasts.clear();
	for(i=0; i< events.size(); i++)
	{
		for(j=0; j<works.size(); j++)
		{
			if(works[j].event1i == i) break;
		}
		if(j == works.size())
		{
			lasts.push_back(i);
			//ShowMessage("Начальное событие " + IntToStr(events[i].number));
        }
	}
	for(i=1; i<lasts.size(); i++)
	{
		for(j=0; j<works.size(); j++)
		{
			if(works[j].event2i == lasts[i])
			{
				for(k=0; k<works.size(); k++)
				{
					if(works[k].event1i == works[j].event1i
						&& works[k].event2i == lasts[0]) break;
				}
				if(k == works.size())
				{
					delevent = works[j].event2i;
					//ShowMessage(events[delevent].number);
					works[j].event2i = lasts[0];
					DeleteEvent(delevent);
					goto correction;
				}
				else
				{
					tempwork.event1i = works[j].event2i;
					tempwork.event2i = lasts[0];
					tempwork.t = 0;
					tempwork.currentt = 0;
					tempwork.mark = "";
					tempwork.name = "";
					works.push_back(tempwork);
                }
            }
		}
    }
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N78Click(TObject *Sender)
{
	if(StatusBar1->Panels->Items[1]->Text != "")
	{
		switch(Application->MessageBoxA("Проект был изменён.\n\nСохранить изменения?", Application->Title.c_str(), MB_ICONWARNING + MB_YESNOCANCEL))
		{
			case IDYES:
				N29Click(this);

				break;

			case IDNO:
				goto showimport;
				
			case IDCANCEL:

				return;
		}

	}
	if(StatusBar1->Panels->Items[1]->Text == "")
	{
        showimport:
		Import->ShowModal();
	}
	
}
//---------------------------------------------------------------------------

int TMainForm::Check()
{
    int first=-1, last=-1, j;
	unsigned int i, k, l, m;
    vector<vector <int> > Ws;
	vector<int> W;
	
	if(!UnlinkedEvents())
	{
        first = FirstEvent();
		last = LastEvent();
		if(first > -1 && last > -1)
		{
			Ws.clear();
			W.clear();
			do   //первый путь
			{
				if(!W.size())
				{
					for(i=0; i<works.size(); i++)
					{
						if(works[i].event1i == FirstEvent())
						{
							W.push_back(i);
							//ShowMessage("Добавили в путь работу с индексом = " + IntToStr(i));
							break;
						}
					}
				}
				else
				{
					for(i=0; i<works.size(); i++)
					{
						if(works[i].event1i == works[W[W.size()-1]].event2i)
						{
							for(j=0; j<W.size(); j++)
							{
								if(W[j] == i) break;
							}
							if(j==W.size()) W.push_back(i);
							else
							{
								Application->MessageBoxA(("Найдена петля на работе " + works[W[W.size()-1]].mark + ". Измените график").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
								return 0;
                            }
							//ShowMessage("2Добавили в путь работу с индексом = " + IntToStr(i));
							break;
						}
					}
				}
			}
			while(works[W[W.size()-1]].event2i != LastEvent());
			Ws.push_back(W);

			for(i=0; i<Ws.size(); i++) //остальные пути
			{
				//ShowMessage("i = " + IntToStr(i));
				for(j=Ws[i].size()-1; j>=0; j--)
				{
					for(k=0; k<works.size(); k++)
					{
						//ShowMessage("До условия. k = " + IntToStr(k) + "j = " + IntToStr(j));
						//ShowMessage("Индекс пути" + IntToStr(i));
						//ShowMessage("works.size() = " + IntToStr(works.size()));
						if(works[k].event1i == works[Ws[i][j]].event1i && k> Ws[i][j])
						{
							//ShowMessage("Прошли условие");
							W.clear();
							for(l=0; l<j; l++)
							{
								W.push_back(Ws[i][l]);
							}
							//ShowMessage("Найдена работа с индексом = " + IntToStr(k));
							for(l=0; l<W.size(); l++)
							{
								if(W[l] == k) break;
							}
							if(l==W.size()) W.push_back(k);
							else
							{
								Application->MessageBoxA(("Найдена петля на работе " + works[W[W.size()-1]].mark + ". Измените график").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
								return 0;
							}
							do
							{
								for(l=0; l<works.size(); l++)
								{
									if(works[l].event1i == works[W[W.size()-1]].event2i)
									{
										for(m=0; m<W.size(); m++)
										{
											if(W[m] == l) break;
										}
										if(m==W.size()) W.push_back(l);
										else
										{
											Application->MessageBoxA(("Найдена петля на работе " + works[W[W.size()-1]].mark + ". Измените график").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
											return 0;
										}
										//ShowMessage("3Добавили в путь работу с индексом = " + IntToStr(l));
										break;
									}
								}
							}
							while(works[W[W.size()-1]].event2i != LastEvent());
							Ws.push_back(W);
							goto check;
							/*for(int a=0; a<Ws.size(); a++)
							{
								for(int b=0; b<Ws[a].size(); b++)
								{
									ShowMessage("Путь " + IntToStr(a) + "Работа " + IntToStr(Ws[a][b]));
								}
							}*/
						}
					}
				}
				check:
			}
            


			return 1;
		}
		else
		{
			if(first == -1) Application->MessageBoxA("Нет начального события. Требуется событие без входящих работ", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			if(first == -2) Application->MessageBoxA("Найдено более одного начального события. Оставьте только одно начальное событие", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			if(last == -1) Application->MessageBoxA("Нет конечного события. Требуется событие без исходящих работ", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			if(last == -2) Application->MessageBoxA("Найдено более одного конечного события. Оставьте только одно конечное событие", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			return 0;
		}
	}
	else
	{
		Application->MessageBoxA("Найдено несвязанное событие", Application->Title.c_str(), MB_ICONERROR + MB_OK);
		return 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AccelCKeyPress(TObject *Sender, char &Key)
{
	if(!isdigit(Key) && Key != 8) Key = 0;	
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N79Click(TObject *Sender)
{
	PageControl1->TabIndex = 3;
	N79->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MSProjecttxt1Click(TObject *Sender)
{
	if(issaved) ProjectExport->FileName = ExtractFileName(SaveProject->FileName).SubString(1, ExtractFileName(SaveProject->FileName).LastDelimiter(".") - 1);
	else ProjectExport->FileName = ProjectName;
	if(ProjectExport->Execute())
	{
		ofstream out;
		int i=0;

		out.open(ProjectExport->FileName.c_str());
		out << "Название\tДлительность\tПредшественники\tФиксированные_затраты\n";
		for(i=0; i<works.size(); i++)
		{
			out << (works[i].mark + " " + works[i].name + "\t").c_str();
			out << (IntToStr(works[i].currentt) + "\t").c_str();
			AnsiString temp="";
			for(unsigned int j=0; j<works.size(); j++)
			{
				if(works[i].event1i == works[j].event2i)
				{
					if(!works[j].t)
					{
						for(unsigned int k=0; k<works.size(); k++)
						{
							if(works[k].event2i == works[j].event1i && works[j].t)
							{
								temp += IntToStr(k+1) + ";";

							}
						}
					}
					else
					{
						temp += IntToStr(j+1) + ";";

					}

				}
			}
			out << temp.SubString(1, temp.Length()-1).c_str() << "\t";
			out << FloatToStrF(works[i].currentcost, ffFixed, 10, 3).c_str() << endl;

		}
		out.close();
	}
}
//---------------------------------------------------------------------------

