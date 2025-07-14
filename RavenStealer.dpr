program RavenStealer;



{$R *.dres}

uses
  Vcl.Forms,
  RavenStealerMain in 'RavenStealerMain.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
