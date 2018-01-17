@echo off
setlocal
set /p ncoinversion=<..\Ncoin\version.ncoin
set dd=%DATE:~0,2%
set mmm=%DATE:~2,3%
if "%mmm%" == "Jan" (
  set mm=01
)
if "%mmm%" == "Feb" (
  set mm=02
)
if "%mmm%" == "Mar" (
  set mm=03
)
if "%mmm%" == "Apr" (
  set mm=04
)
if "%mmm%" == "May" (
  set mm=05
)
if "%mmm%" == "Jun" (
  set mm=06
)
if "%mmm%" == "Jul" (
  set mm=07
)
if "%mmm%" == "Aug" (
  set mm=08
)
if "%mmm%" == "Sep" (
  set mm=09
)
if "%mmm%" == "Oct" (
  set mm=10
)
if "%mmm%" == "Nov" (
  set mm=11
)
if "%mmm%" == "Dec" (
  set mm=12
)
set yy=%DATE:~5,2%
set yyyy=20%DATE:~5,2%
set h=%TIME:~0,2%
if %h% LEQ 9 set h=0%h:~1,1%
set m=%TIME:~3,2%
set s=%TIME:~6,2%
rem echo tIs dag %dd% van de maand %mm% (%mmm%) in et jaar %yyyy%, ook wel afgekort als %yy%.
rem echo Et is %h% uur, %m% minuten en euh... %s% seconden!
rem echo En Ncoin is versie: %ncoinversion%!
echo #define BUILD_COMMIT_ID ^"%h%%m%%s%^" >..\Ncoin\src\version.h.in
echo #define PROJECT_VERSION ^"%ncoinversion%^" >>..\Ncoin\src\version.h.in
echo #define PROJECT_VERSION_BUILD_NO "%yyyy%%mm%%dd%" >>..\Ncoin\src\version.h.in
echo #define PROJECT_VERSION_LONG PROJECT_VERSION ^".^" PROJECT_VERSION_BUILD_NO ^"^(^" BUILD_COMMIT_ID ^"^)^" >>..\Ncoin\src\version.h.in
rem echo ^"version.h.in^" has been rebuild...
rem echo Comitting...
echo %ncoinversion%.%yyyy%%mm%%dd%.%h%%m%%s% >lastbuild.ver
