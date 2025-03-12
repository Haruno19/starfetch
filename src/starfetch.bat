:TOP
@CLS
@ECHO OFF
:BEGIN
CLS
COPY main.exe C:\MingW\bin\starfetch.exe
:loop
C:\MingW\bin\starfetch.exe -c blue
PAUSE
GOTO loop