object Design: TDesign
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1054#1092#1086#1088#1084#1083#1077#1085#1080#1077
  ClientHeight = 208
  ClientWidth = 341
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 8
    Top = 7
    Width = 325
    Height = 162
    ActivePage = TabSheet1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1062#1074#1077#1090#1072
      object Label1: TLabel
        Left = 17
        Top = 20
        Width = 49
        Height = 13
        Caption = #1057#1086#1073#1099#1090#1080#1103':'
      end
      object Label2: TLabel
        Left = 17
        Top = 48
        Width = 61
        Height = 13
        Caption = #1042#1099#1076#1077#1083#1077#1085#1080#1077':'
      end
    end
  end
  object Button1: TButton
    Left = 176
    Top = 175
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 257
    Top = 175
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 5
    OnClick = Button2Click
  end
  object ColorBox1: TColorBox
    Left = 160
    Top = 48
    Width = 145
    Height = 22
    DefaultColorColor = clWhite
    Selected = clWhite
    ItemHeight = 16
    TabOrder = 1
  end
  object Button3: TButton
    Left = 8
    Top = 175
    Width = 90
    Height = 25
    Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
    TabOrder = 3
    OnClick = Button3Click
  end
  object ColorBox2: TColorBox
    Left = 160
    Top = 76
    Width = 145
    Height = 22
    DefaultColorColor = clLime
    Selected = clLime
    ItemHeight = 16
    TabOrder = 2
  end
end
