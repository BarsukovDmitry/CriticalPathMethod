//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <cctype.h>
#pragma hdrstop

#include "WPU.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
using namespace std;
TWorkProp *WorkProp;
Work *WPwork;
bool WPResult = false;
extern vector<Work> works;
extern vector<Event> events;
Work tempwork2;
extern int eventcount, w;

//---------------------------------------------------------------------------
__fastcall TWorkProp::TWorkProp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWorkProp::Button1Click(TObject *Sender)
{
	int i=0, j=0, k=0, i1, i2;
	vector<unsigned int> indexs;

	for(i=0; i<PWorksC->Items->Count; i++)
	{
		if(PWorksC->Items->Item[i]->Checked)
		{
			indexs.push_back(i);
		}
	}
    for(i=0; i<events.size(); i++)
	{
		if(events[i].number == StrToInt(Event1C->Text)) i1 = i;
		if(events[i].number == StrToInt(Event2C->Text)) i2 = i;
	}
	if(TC->Text == "") TC->Text = "0";
	if(TuC->Text == "") TuC->Text = "0";
	if(CostC->Text == "") CostC->Text = "0";
	if(CostUC->Text == "") CostUC->Text = "0";

	if(SetWork(WPwork, MarkC->Text, NameC->Text, StrToInt(TC->Text), StrToInt(TuC->Text),
		StrToFloat(CostC->Text), StrToFloat(CostUC->Text), RadioGroup1->ItemIndex ? 0 : 1,
		i1, i2, indexs))
	{
		WPResult = true;
		Close();
		MainForm->Draw();
		MainForm->ExplorerUpdate();
		MainForm->WorksTableUpdate();
		MainForm->StatusBar1->Panels->Items[1]->Text = "Изменён";
	}
	
}
//---------------------------------------------------------------------------
void __fastcall TWorkProp::Button2Click(TObject *Sender)
{
	WPResult = false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TWorkProp::FormShow(TObject *Sender)
{
    MarkC->Text = WPwork->mark;
	NameC->Text = WPwork->name;
	TC->Value = WPwork->t;
	if(WPwork->event1i != -10) Event1C->Text = events[WPwork->event1i].number;
	else Event1C->Text = "-10";
	if(WPwork->event2i != -10) Event2C->Text = events[WPwork->event2i].number;
	else Event2C->Text = "-10";
	TuC->Text = IntToStr(WPwork->tu);
	CostC->Text = FloatToStrF(WPwork->cost, ffFixed, 10, 3);
	CostUC->Text = FloatToStrF(WPwork->costu, ffFixed, 10, 3);
	PWorksC->Clear();
	for(unsigned int i=0; i<works.size(); i++)
	{
        PWorksC->Items->Add();
		PWorksC->Items->Item[i]->Caption = works[i].mark;
	}
	for(unsigned int i=0; i<works.size(); i++)
	{
		if(WPwork->event1i == works[i].event2i)
		{
			if(!works[i].t)
			{
				for(unsigned int j=0; j<works.size(); j++)
				{
					if(works[j].event2i == works[i].event1i && works[j].t)
					{
						PWorksC->Items->Item[j]->Checked = true;

					}
				}
			}
			else
			{
				PWorksC->Items->Item[i]->Checked = true;
				
			}

		}
	}
	
	RadioGroup1->ItemIndex = 0;
	MarkC->SetFocus();
	WPResult=false;
	if(WPwork->event1i == -10 && WPwork->event1i == -10)
    	WorkProp->Caption = "Создать работу";

	else
		WorkProp->Caption = "(" + IntToStr(events[WPwork->event1i].number) + ", " + IntToStr(events[WPwork->event2i].number) + ") - Свойства работы";
}
//---------------------------------------------------------------------------
void __fastcall TWorkProp::RadioGroup1Click(TObject *Sender)
{
	if(RadioGroup1->ItemIndex == 0)
	{
		Event1C->Enabled = true;
		Event2C->Enabled = true;
		PWorksC->Enabled = false;
		Label2->Enabled = false;
	}
	else if(RadioGroup1->ItemIndex == 1)
	{
		Event1C->Enabled = false;
		Event2C->Enabled = false;
		PWorksC->Enabled = true;
		Label2->Enabled = true;
    }	
}
//---------------------------------------------------------------------------

void __fastcall TWorkProp::FormClose(TObject *Sender, TCloseAction &Action)
{
	MainForm->StatusBar1->Panels->Items[2]->Text = "";	
}
//---------------------------------------------------------------------------

void __fastcall TWorkProp::TCKeyPress(TObject *Sender, char &Key)
{
	if(Key == 13) Button1Click(this);
	if(!isdigit(Key) && Key != 8) Key = 0;
	

}
//---------------------------------------------------------------------------

void __fastcall TWorkProp::CostCKeyPress(TObject *Sender, char &Key)
{
	//ShowMessage((int) Key);
	if(Key == 13) Button1Click(this);
	if(!isdigit(Key) && Key != 8 && Key != 46 && Key != 44) Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TWorkProp::TuCKeyPress(TObject *Sender, char &Key)
{
	if(Key == 13) Button1Click(this);
	if(!isdigit(Key) && Key != 8) Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TWorkProp::TCChange(TObject *Sender)
{
	TuC->Text = TC->Text;	
}
//---------------------------------------------------------------------------

int TWorkProp::SetWork(Work *WPwork, AnsiString mark, AnsiString name, int t, int tu, float cost, float costu, bool by_events, int event1i, int event2i, vector <unsigned int> indexs)
{
	int i=0, j=0, k=0;
	vector<unsigned int> indexs0;

    //ShowMessage("В SetWork()");

	//проверки
	for(i=0; i<works.size(); i++)
	{
		if(mark == works[i].mark && &works[i] != WPwork && Trim(mark) != "")
		{
			Application->MessageBoxA(("Указанная метка " + mark + " уже используется. Введите другую метку").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
			return 0;
        }
	}
	if(tu > t)
	{
    	Application->MessageBoxA(("Ускоренный срок работы " + mark + " не может быть больше нормального срока").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
		return 0;
	}

	//расположить работу по номерам событий
	if(by_events)
	{
		//проверки
		for(i=0; i<works.size(); i++)
		{
			if((works[i].event1i == event1i && works[i].event2i == event2i || works[i].event1i == event2i && works[i].event2i == event1i) && &works[i] != WPwork)
			{
				Application->MessageBoxA("Работа, соединяющая эти события уже существует", Application->Title.c_str(), MB_ICONERROR + MB_OK);
				return 0;
            }
        }

		if(event1i == event2i)
		{
			Application->MessageBoxA("Конечное событие не может совпадать\
 с начальным. Выберите другое конечное событие", Application->Title.c_str(), MB_ICONERROR + MB_OK);
        	return 0;
		}
		if(event1i < events.size() && event2i < events.size())
		{
			WPwork->event1i = event1i;
			WPwork->event2i = event2i;

		}
		else
		{
			Application->MessageBoxA("Указан неправильный номер начального события", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			Application->MessageBoxA("Указан неправильный номер конечного события", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			return 0;
		}
    }
	
    //расположить работу по списку предшествующих
	else
	{
        if(!indexs.size())
		{
			if(MainForm->FirstEvent() != WPwork->event1i)
			{
				if(MainForm->FirstEvent() > -1)
				{
					//ShowMessage("Начальная работа от существующего события");
					for(i=0; i<works.size(); i++)
					{
						if((works[i].event1i == MainForm->FirstEvent() && works[i].event2i == WPwork->event2i || works[i].event2i == MainForm->FirstEvent() && works[i].event1i == WPwork->event2i) && &works[i] != WPwork)
						{
                            works[i].fordelete = true;
                        }
					}

					WPwork->event1i = MainForm->FirstEvent();
				}
				else
				{
					//ShowMessage("Начальная работа от нового события");
					MainForm->NewEvent(eventcount*w/2 + 10, 10, true);
					WPwork->event1i = events.size() - 1;
				}
			}
			if(WPwork->event1i == WPwork->event2i || WPwork->event2i < 0)
			{
				//ShowMessage("Создали завершающее событие для начальноей работы");
				MainForm->NewEvent(eventcount*w/2 + 10, 10, true);
				WPwork->event2i = events.size() - 1;
			}
		}
		else
		{
			//ShowMessage("Работа предшествует другим работам");
			for(i=0; i<indexs.size(); i++)
			{
				if(WPwork == &works[indexs[i]])
				{
					Application->MessageBoxA(("Работа " + WPwork->mark + " не может предшествовать самой себе").c_str(), Application->Title.c_str(), MB_ICONERROR + MB_OK);
					return 0;
                }
			}

			//создать начальное событие, если есть работы, которые не должны предшествовать WPwork
            for(unsigned int i=0; i<works.size(); i++)
			{
				if(works[indexs[0]].event2i == works[i].event2i)
				{
					if(!works[i].t)
					{
						for(unsigned int j=0; j<works.size(); j++)
						{
							if(works[j].event2i == works[i].event1i && works[j].t)
							{
								indexs0.push_back(j);
								//ShowMessage("Добавили 1");
							}
						}
					}
					else
					{
						indexs0.push_back(i);
						//ShowMessage("Добавили 2");
					}

				}
			}
			for(i=0; i<indexs0.size(); i++)
			{
				if(works[indexs0[i]].event2i == works[indexs[0]].event2i)
				{
					//ShowMessage("Работа для проверки предшествования " + works[indexs0[i]].mark);
					for(j=0; j<indexs.size(); j++)
					{
						if(indexs[j] == indexs0[i]) break;
						
                    }
					if(j == indexs.size())
					{
                        //ShowMessage("Не все работы заданы предшествующими");
						break;
                    }
                }
			}
			if(i < indexs0.size())
			{
				MainForm->NewEvent(eventcount*w/2 + 10, 10, true);
				WPwork->event1i = events.size() - 1;
				works[indexs[0]].event2i = events.size() - 1;

			}
			//все работы заданы предшествующими
			else
			{
                WPwork->event1i = works[indexs[0]].event2i;
			}
			//создать фиктивные работы для создания предшествования
			for(i=1; i<indexs.size(); i++)
			{
				//ShowMessage(works[indexs[i]].event1i);
				//ShowMessage("Индекс first события = " + IntToStr(MainForm->FirstEvent()));
				//ShowMessage("Вторая работа из начального события");
				for(j=0; j<indexs0.size(); j++)
				{
					if(indexs[i] == indexs0[j]) break;
				}
				if(j == indexs0.size())
				{
					tempwork2.event1i = works[indexs[i]].event2i;
					tempwork2.event2i = works[indexs[0]].event2i;
					for(k=0; k<works.size(); k++)
					{
						if(works[k].event1i == tempwork2.event1i && works[k].event2i == tempwork2.event2i || works[k].event1i == tempwork2.event2i && works[k].event2i == tempwork2.event1i)
						{
							works[k].fordelete = true;
						}
					}
					tempwork2.t = 0;
					tempwork2.currentt = 0;
					tempwork2.mark = "";
					tempwork2.name = "";
					works.push_back(tempwork2);
				}
			}

			//ShowMessage("Индекс начального события работы = " + IntToStr(works[indexs[0]].event2i));
            if(WPwork->event1i == WPwork->event2i || WPwork->event2i < 0)
			{
				MainForm->NewEvent(eventcount*w/2 + 10, 10, true);
				WPwork->event2i = events.size() - 1;
			}
			else
			{
				for(i=0; i<works.size(); i++)
				{
					if((works[i].event1i == WPwork->event1i && works[i].event2i == WPwork->event2i || works[i].event1i == WPwork->event2i && works[i].event2i == WPwork->event1i) && &works[i] != WPwork)
					{
						works[i].fordelete = true;
					}
				}
            }

		}
	}

	WPwork->name = name;
    WPwork->mark = Trim(mark);
	WPwork->t = t;
	WPwork->currentt = t;
	WPwork->tu = tu;
	WPwork->cost = cost;
    WPwork->currentcost = cost;
	WPwork->costu = costu;
	
	return 1;
}

