object ConMan: TConMan
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1087#1086#1076#1082#1083#1102#1095#1077#1085#1080#1103
  ClientHeight = 310
  ClientWidth = 521
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 122
    Top = 8
    Width = 175
    Height = 29
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' VPN:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Status: TLabel
    Left = 48
    Top = 282
    Width = 223
    Height = 25
    Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077': '#1054#1090#1082#1083#1102#1095#1077#1085#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 39
    Width = 474
    Height = 19
    Caption = #1044#1083#1103' '#1087#1086#1076#1082#1083#1102#1095#1077#1085#1080#1103' VPN+TOR+VPN '#1058#1088#1077#1073#1091#1077#1090#1089#1103' '#1076#1074#1072' TAP '#1072#1076#1072#1087#1090#1077#1088#1072'!'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object Panel1: TPanel
    Left = 138
    Top = 60
    Width = 249
    Height = 130
    Caption = 'VPN '#8470'1'
    TabOrder = 8
  end
  object Button1: TButton
    Left = 183
    Top = 71
    Width = 163
    Height = 44
    Caption = #1042#1099#1073#1088#1072#1090#1100' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1102
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 170
    Top = 137
    Width = 187
    Height = 40
    Caption = #1042#1099#1073#1088#1072#1090#1100' '#1092#1072#1081#1083' '#1072#1074#1090#1086#1088#1080#1079#1072#1094#1080#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 183
    Top = 196
    Width = 163
    Height = 82
    Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button3Click
  end
  object Memo2: TMemo
    Left = 478
    Top = 306
    Width = 2
    Height = 9
    Lines.Strings = (
      '')
    TabOrder = 4
    Visible = False
  end
  object Button6: TButton
    Left = 48
    Top = 196
    Width = 170
    Height = 80
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' VPN '#8470'2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = Button6Click
  end
  object Button5: TButton
    Left = 8
    Top = 8
    Width = 67
    Height = 25
    Caption = #1057#1087#1088#1072#1074#1082#1072
    TabOrder = 6
    OnClick = Button5Click
  end
  object Button8: TButton
    Left = 406
    Top = 129
    Width = 107
    Height = 58
    Caption = #1057#1073#1088#1086#1089' '#1085#1072#1089#1090#1088#1086#1077#1082
    TabOrder = 7
    OnClick = Button8Click
  end
  object Button4: TButton
    Left = 183
    Top = 73
    Width = 163
    Height = 104
    Caption = #1054#1090#1082#1083#1102#1095#1080#1090#1100#1089#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Visible = False
    OnClick = Button4Click
  end
  object Button9: TButton
    Left = 138
    Top = 207
    Width = 249
    Height = 61
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1083#1086#1075' OpenVPN'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    Visible = False
    OnClick = Button9Click
  end
  object Button7: TButton
    Left = 408
    Top = 8
    Width = 105
    Height = 25
    Caption = #1057#1084#1077#1085#1080#1090#1100' EntryNode'
    TabOrder = 10
    OnClick = Button7Click
  end
  object OpenDialog1: TOpenDialog
    Top = 65531
  end
  object OpenDialog2: TOpenDialog
    Top = 65531
  end
end
