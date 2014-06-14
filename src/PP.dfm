object ProjectProp: TProjectProp
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1087#1088#1086#1077#1082#1090#1072
  ClientHeight = 270
  ClientWidth = 411
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
  object Button1: TButton
    Left = 248
    Top = 239
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 329
    Top = 239
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = Button2Click
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 396
    Height = 225
    ActivePage = TabSheet1
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label1: TLabel
        Left = 3
        Top = 79
        Width = 53
        Height = 13
        Caption = #1054#1087#1080#1089#1072#1085#1080#1077':'
      end
      object NameC: TLabeledEdit
        Left = 3
        Top = 16
        Width = 372
        Height = 21
        EditLabel.Width = 52
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
        MaxLength = 254
        TabOrder = 0
      end
      object AuthorC: TLabeledEdit
        Left = 3
        Top = 54
        Width = 372
        Height = 21
        EditLabel.Width = 35
        EditLabel.Height = 13
        EditLabel.Caption = #1040#1074#1090#1086#1088':'
        MaxLength = 254
        TabOrder = 1
      end
      object DefinitionC: TMemo
        Left = 3
        Top = 98
        Width = 372
        Height = 87
        MaxLength = 254
        TabOrder = 2
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1045#1076#1080#1085#1080#1094#1099' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object TimeEdC: TLabeledEdit
        Left = 3
        Top = 16
        Width = 121
        Height = 21
        EditLabel.Width = 34
        EditLabel.Height = 13
        EditLabel.Caption = #1042#1088#1077#1084#1103':'
        MaxLength = 254
        TabOrder = 0
        Text = #1076#1085'.'
      end
      object MoneyEdC: TLabeledEdit
        Left = 3
        Top = 56
        Width = 121
        Height = 21
        EditLabel.Width = 58
        EditLabel.Height = 13
        EditLabel.Caption = #1057#1090#1086#1080#1084#1086#1089#1090#1100':'
        MaxLength = 254
        TabOrder = 1
        Text = #1088#1091#1073'.'
      end
    end
  end
end
