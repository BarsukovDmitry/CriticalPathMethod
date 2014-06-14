//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImportU.h"
#include "WPU.h"
#include "MainFOrmU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImport *Import;

extern Work *WPwork;
extern vector<Work> works;

//---------------------------------------------------------------------------
__fastcall TImport::TImport(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TImport::Button4Click(TObject *Sender)
{
	for(int i=0; i<6; i++)
	{
        StringGrid1->Rows[i]->Clear();
    }
	StringGrid1->Rows[0]->Add("Метка работы");
	StringGrid1->Rows[1]->Add("Опирается на работы");
	StringGrid1->Rows[2]->Add("Нормальный срок");
	StringGrid1->Rows[3]->Add("Ускоренный срок");
	StringGrid1->Rows[4]->Add("Нормальная стоимость");
	StringGrid1->Rows[5]->Add("Плата за ускорение");
	StringGrid1->ColWidths[0] = 130;
	StringGrid1->ColCount = 2;	
}
//---------------------------------------------------------------------------
void __fastcall TImport::Button2Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TImport::Button1Click(TObject *Sender)
{
	Work tempwork;
	int i=0, j=0, k=0, end, countbuilded=0;
	vector<unsigned int> indexs;
	AnsiString temp, mark;
	bool breakflag;


	MainForm->CloseProject();

	for(i=1; i<StringGrid1->ColCount-1; i++)
	{
		//ShowMessage(StringGrid1->Cols[i]->Strings[1].Length());
		if(Trim(StringGrid1->Cols[i]->Strings[1]) == "")
		{
			//ShowMessage("Создаём работу");
			tempwork.mark = "";
			tempwork.t = 0;
			tempwork.name = "";
			tempwork.cost = 0;
			tempwork.costu = 0;
			tempwork.tu = 0;
			tempwork.event1i = -10;
			tempwork.event2i = -10;
			WPwork = &tempwork;
			indexs.clear();
			if(WorkProp->SetWork(WPwork, StringGrid1->Cols[i]->Strings[0], "",
				StrToInt(StringGrid1->Cols[i]->Strings[2]), StrToInt(StringGrid1->Cols[i]->Strings[3]),
				StrToFloat(StringGrid1->Cols[i]->Strings[4]), StrToFloat(StringGrid1->Cols[i]->Strings[5]), 0, -9, -9, indexs))
			{
				works.push_back(tempwork);
				MainForm->DeleteWorks();
				countbuilded++;
			}
			else
			{
                return;
            }
        }
	}
	for(i=0; i < 50 && countbuilded < StringGrid1->ColCount-2; i++)
	{
		for(j=1; j<StringGrid1->ColCount-1; j++)
		{
			for(k=0; k<works.size(); k++)
			{
            	if(Trim(StringGrid1->Cols[j]->Strings[0]) == works[k].mark) break;
            }
			if(k == works.size())
			{
				breakflag = false;
				end = 1;
				temp = Trim(StringGrid1->Cols[j]->Strings[1]);
				indexs.clear();
				//ShowMessage("Работа с предшествующими");
				while(!breakflag)
				{
                	if(!temp.AnsiPos(","))
					{
						breakflag = true;
						end = temp.Length();
						mark = Trim(temp.SubString(1, end));
					}
					else
					{
						end = temp.AnsiPos(",");
						//ShowMessage("Метка не последняя. end = " + IntToStr(end));
						mark = Trim(temp.SubString(1, end - 1));
					}
					/*ShowMessage("Работа" + IntToStr(j));
					ShowMessage("end = " + IntToStr(end));*/

					for(k=0; k<works.size(); k++)
					{
						//ShowMessage("Сравниваются метки работ " + mark + " и " + works[k].mark);
						if(mark == works[k].mark)
						{
							//ShowMessage("mark = " + mark);
							indexs.push_back(k);
							break;
						}
					}
					if(k == works.size())
					{
                    	goto import;
                    }
					temp = temp.SubString(end + 1, temp.Length());
				}
				//ShowMessage("Найдена работа " + StringGrid1->Cols[j]->Strings[0]);
				//ShowMessage("Опирается на ");
				/*for(k=0; k<indexs.size(); k++)
				{
					ShowMessage(works[indexs[k]].mark);
                }*/
				tempwork.mark = "";
				tempwork.t = 0;
				tempwork.name = "";
				tempwork.cost = 0;
				tempwork.costu = 0;
				tempwork.tu = 0;
				tempwork.event1i = -10;
				tempwork.event2i = -10;
				WPwork = &tempwork;
				if(WorkProp->SetWork(WPwork, StringGrid1->Cols[j]->Strings[0], "",
					StrToInt(StringGrid1->Cols[j]->Strings[2]), StrToInt(StringGrid1->Cols[j]->Strings[3]),
					StrToFloat(StringGrid1->Cols[j]->Strings[4]), StrToFloat(StringGrid1->Cols[j]->Strings[5]), 0, -9, -9, indexs))
				{
					works.push_back(tempwork);
					MainForm->DeleteWorks();
                    countbuilded++;
				}
				else
                {
                	return;
                }

			}
			import:
		}
		//ShowMessage("Количество работ = " + IntToStr(countbuilded) + ", столбцов - " + IntToStr(StringGrid1->ColCount));
		if(i == 49)
		{
			Application->MessageBoxA("Не удалось построить все работы. Проверьте таблицу", Application->Title.c_str(), MB_ICONERROR + MB_OK);
			return;
		}

    }
    MainForm->StatusBar1->Panels->Items[1]->Text = "Изменён";
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TImport::Button3Click(TObject *Sender)
{
    int end=1, i=0, j=0, k=0;
	bool breakflag = false;
	AnsiString temp;
	TMemo *memo = new TMemo(Import);

	Button4Click(this);
	memo->Parent = Import;
	memo->WordWrap = false;
	memo->Visible = false;
	memo->PasteFromClipboard();
	for (i = 0; i < memo->Lines->Count && k < 6; i++)
	{
        breakflag = false;
		temp = memo->Lines->Strings[i];
		for(j=1; (temp[j]== ' ' || temp[j] == '\t') && j < temp.Length(); j++) ;
		if(j != temp.Length())
		{
			end = 1;
			for(j = 0; j < 50 && !breakflag; j++)
			{
				if(!temp.AnsiPos("\t")) 
				{
					breakflag = true;
					end = temp.Length();
					StringGrid1->Rows[k]->Add(Trim(temp.SubString(1, end)));
				}
				else
				{
					end = temp.AnsiPos("\t");
					StringGrid1->Rows[k]->Add(Trim(temp.SubString(1, end - 1)));
				}
				/*ShowMessage("Работа" + IntToStr(j));
                ShowMessage("end = " + IntToStr(end));*/
				temp = temp.SubString(end + 1, temp.Length());
				if(!k) StringGrid1->ColCount++;
			}
			k++;
		}
		
	}

	memo->Free();	
}
//---------------------------------------------------------------------------

void __fastcall TImport::StringGrid1SetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
	int i, j;
	
	if(ACol == StringGrid1->ColCount - 1)
	{
		for(i=0; i<StringGrid1->RowCount; i++)
		{
			if(StringGrid1->Cols[StringGrid1->ColCount-1]->Strings[i] != "")
			{
				//ShowMessage("Увеличиваем");
				StringGrid1->ColCount++;

				break;
			}
		}
	}
	else if(ACol == StringGrid1->ColCount - 2)
	{
		for(i=0; i<StringGrid1->RowCount; i++)
		{
			if(StringGrid1->Cols[StringGrid1->ColCount-2]->Strings[i] != "")
			{
				break;
			}
		}
		if(i == StringGrid1->RowCount)
		{
            StringGrid1->ColCount--;
        }
    }
	
}
//---------------------------------------------------------------------------

void __fastcall TImport::FormCreate(TObject *Sender)
{
	Button4Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TImport::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key == 'V' && Shift.Contains(ssCtrl)) Button3Click(this);	
}
//---------------------------------------------------------------------------

