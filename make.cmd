@echo off

if "%1"=="bm" goto make_bm

gcc main.c -o main
goto end

:make_bm
gcc -Iscl bm\bm.c -o bm

:end