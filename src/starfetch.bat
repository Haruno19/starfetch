:TOP
@CLS
@ECHO OFF
TITLE starfetch
:BEGIN
if not exist C:\MingW\bin\starfetch.exe (
COPY starfetch.exe C:\MingW\bin\starfetch.exe
)
CLS
:loop
C:\MingW\bin\starfetch.exe en -c blue
PAUSE
GOTO loop