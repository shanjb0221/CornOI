@echo off

set /a cnt = 1

:orz

cls

echo Case %cnt%

Maker_Hack.exe

echo M

WA_WA.exe

echo W

WA_STD.exe

echo S

fc WA.out WA.ans

if errorlevel = 1 pause

echo AC

set /a cnt = %cnt% +1

goto orz 
