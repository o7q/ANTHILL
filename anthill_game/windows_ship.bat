@echo off

set NAME=ANTHILL
set ROOT=%NAME%_windows

mkdir "%ROOT%"
copy "%NAME%.exe"     "%ROOT%/%NAME%.exe"     /y
copy "README.txt"     "%ROOT%/README.txt"     /y
copy "SDL3.dll"       "%ROOT%/SDL3.dll"       /y
copy "SDL3_image.dll" "%ROOT%/SDL3_image.dll" /y
copy "SDL3_mixer.dll" "%ROOT%/SDL3_mixer.dll" /y
copy "SDL3_ttf.dll"   "%ROOT%/SDL3_ttf.dll"   /y

xcopy "assets" "%ROOT%/assets" /e /i /y
xcopy "licenses" "%ROOT%/licenses" /e /i /y