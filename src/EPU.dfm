object EventProp: TEventProp
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1089#1086#1073#1099#1090#1080#1103
  ClientHeight = 127
  ClientWidth = 231
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    0000FFFF0000F83F0000F6DF0000EEEF0000DEF70000DEF70000BEFB00008003
    0000BEFB0000DEF70000DEF70000EEEF0000F6DF0000F83F0000FFFF0000}
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object NameC: TLabeledEdit
    Left = 16
    Top = 64
    Width = 209
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
    TabOrder = 1
  end
  object Button1: TButton
    Left = 68
    Top = 95
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 149
    Top = 95
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 3
    OnClick = Button2Click
  end
  object NumberC: TLabeledEdit
    Left = 16
    Top = 24
    Width = 209
    Height = 21
    EditLabel.Width = 35
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1084#1077#1088':'
    Enabled = False
    TabOrder = 0
  end
end
