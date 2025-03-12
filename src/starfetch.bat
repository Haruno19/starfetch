:TOP
@CLS
@ECHO OFF
:BEGIN
CLS
COPY starfetch.exe C:\MingW\bin\starfetch.exe
:loop
C:\MingW\bin\starfetch.exe -c blue
PAUSE
GOTO loop