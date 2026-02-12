@echo off

set NAME=ANTHILL

rmdir "build"          /s /q
rmdir "%NAME%_windows" /s /q

del "%NAME%.exe" /f