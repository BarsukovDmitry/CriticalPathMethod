object WorkProp: TWorkProp
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1088#1072#1073#1086#1090#1099
  ClientHeight = 418
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 80
    Width = 93
    Height = 13
    Caption = #1053#1086#1088#1084#1072#1083#1100#1085#1099#1081' '#1089#1088#1086#1082':'
  end
  object Label2: TLabel
    Left = 8
    Top = 262
    Width = 138
    Height = 13
    Caption = #1055#1088#1077#1076#1096#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1088#1072#1073#1086#1090#1099':'
    Enabled = False
  end
  object Label3: TLabel
    Left = 159
    Top = 80
    Width = 92
    Height = 13
    Caption = #1059#1089#1082#1086#1088#1077#1085#1085#1099#1081' '#1089#1088#1086#1082':'
  end
  object NameC: TLabeledEdit
    Left = 8
    Top = 56
    Width = 271
    Height = 21
    EditLabel.Width = 93
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1088#1072#1073#1086#1090#1099':'
    TabOrder = 1
  end
  object Button1: TButton
    Left = 126
    Top = 387
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 10
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 207
    Top = 387
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 11
    OnClick = Button2Click
  end
  object TC: TCSpinEdit
    Left = 8
    Top = 96
    Width = 121
    Height = 22
    MaxValue = 30000
    TabOrder = 2
    OnChange = TCChange
    OnKeyPress = TCKeyPress
  end
  object Event1C: TLabeledEdit
    Left = 8
    Top = 235
    Width = 121
    Height = 21
    EditLabel.Width = 105
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1095#1072#1083#1100#1085#1086#1077' '#1089#1086#1073#1099#1090#1080#1077':'
    TabOrder = 7
    OnKeyPress = TCKeyPress
  end
  object Event2C: TLabeledEdit
    Left = 150
    Top = 235
    Width = 129
    Height = 21
    EditLabel.Width = 99
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1085#1077#1095#1085#1086#1077' '#1089#1086#1073#1099#1090#1080#1077':'
    TabOrder = 8
    OnKeyPress = TCKeyPress
  end
  object MarkC: TLabeledEdit
    Left = 8
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = #1052#1077#1090#1082#1072':'
    MaxLength = 20
    TabOrder = 0
  end
  object PWorksC: TListView
    Left = 8
    Top = 276
    Width = 271
    Height = 101
    Checkboxes = True
    Columns = <>
    Enabled = False
    TabOrder = 9
    ViewStyle = vsList
  end
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 164
    Width = 274
    Height = 48
    Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1080#1090#1100' '#1087#1086':'
    ItemIndex = 0
    Items.Strings = (
      #1057#1086#1073#1099#1090#1080#1103#1084
      #1055#1088#1077#1076#1096#1077#1089#1090#1074#1091#1102#1097#1080#1084' '#1088#1072#1073#1086#1090#1072#1084)
    TabOrder = 6
    OnClick = RadioGroup1Click
  end
  object TuC: TCSpinEdit
    Left = 159
    Top = 96
    Width = 121
    Height = 22
    MaxValue = 30000
    TabOrder = 3
    OnKeyPress = TuCKeyPress
  end
  object CostC: TLabeledEdit
    Left = 8
    Top = 137
    Width = 121
    Height = 21
    EditLabel.Width = 120
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1088#1084#1072#1083#1100#1085#1072#1103' '#1089#1090#1086#1080#1084#1086#1089#1090#1100':'
    TabOrder = 4
    OnKeyPress = CostCKeyPress
  end
  object CostUC: TLabeledEdit
    Left = 158
    Top = 137
    Width = 121
    Height = 21
    EditLabel.Width = 105
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1083#1072#1090#1072' '#1079#1072' '#1091#1089#1082#1086#1088#1077#1085#1080#1077':'
    TabOrder = 5
    OnKeyPress = CostCKeyPress
  end
end
