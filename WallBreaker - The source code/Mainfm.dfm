object Mainform: TMainform
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'WallBreaker'
  ClientHeight = 228
  ClientWidth = 423
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
  object AVTB: TLabel
    Left = 61
    Top = 10
    Width = 293
    Height = 33
    Caption = '"A -> VPN -> TOR -> B"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = AVTBClick
  end
  object ATVB: TLabel
    Left = 61
    Top = 66
    Width = 293
    Height = 33
    Caption = '"A -> TOR -> VPN -> B"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = ATVBClick
  end
  object AVTVB: TLabel
    Left = 45
    Top = 121
    Width = 324
    Height = 33
    Caption = '"A->VPN->TOR->VPN->B"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = AVTVBClick
  end
  object Note1: TLabel
    Left = 8
    Top = 160
    Width = 728
    Height = 13
    Caption = 
      #1055#1077#1088#1077#1076' '#1080#1089#1087#1086#1083#1100#1079#1086#1074#1072#1085#1080#1077#1084' OpenVPN '#1085#1077#1086#1073#1093#1086#1076#1080#1084#1086' '#1091#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1076#1088#1072#1081#1074#1077#1088' TAP '#1072 +
      #1076#1072#1087#1090#1077#1088#1072'\r\'#1042#1086' '#1074#1088#1077#1084#1103' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1084#1086#1078#1077#1090' '#1087#1086#1090#1088#1077#1073#1086#1074#1072#1090#1100#1089#1103' '#1087#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077'!'
  end
  object Panel1: TPanel
    Left = -8
    Top = 160
    Width = 455
    Height = 87
    TabOrder = 3
  end
  object InstallDriver: TButton
    Left = 86
    Top = 193
    Width = 81
    Height = 25
    Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
    TabOrder = 0
    OnClick = InstallDriverClick
  end
  object UninstallDrivers: TButton
    Left = 189
    Top = 193
    Width = 146
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077
    TabOrder = 1
    OnClick = UninstallDriversClick
  end
  object Help: TButton
    Left = -1
    Top = 0
    Width = 58
    Height = 25
    Caption = #1057#1087#1088#1072#1074#1082#1072
    TabOrder = 2
    OnClick = HelpClick
  end
end
