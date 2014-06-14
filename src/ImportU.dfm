object Import: TImport
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1048#1084#1087#1086#1088#1090
  ClientHeight = 223
  ClientWidth = 694
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = 8
    Top = 8
    Width = 678
    Height = 177
    ColCount = 2
    DefaultColWidth = 80
    RowCount = 6
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    PopupMenu = PopupMenu1
    TabOrder = 0
    OnSetEditText = StringGrid1SetEditText
  end
  object Button1: TButton
    Left = 525
    Top = 191
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 606
    Top = 191
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 194
    Width = 129
    Height = 25
    Caption = #1042#1089#1090#1072#1074#1080#1090#1100' '#1080#1079' '#1073#1091#1092#1077#1088#1072
    TabOrder = 1
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 143
    Top = 193
    Width = 90
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 2
    OnClick = Button4Click
  end
  object PopupMenu1: TPopupMenu
    Left = 240
    Top = 192
    object N1: TMenuItem
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100' '#1080#1079' '#1073#1091#1092#1077#1088#1072
      OnClick = Button3Click
    end
    object N2: TMenuItem
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      OnClick = Button4Click
    end
  end
end
