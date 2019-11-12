@echo off

if "%1"=="bm" goto make_bm
if "%1"=="macro" goto make_macro

gcc main.c -o main
goto end

:make_bm
gcc -Iscl bm\main.c -o bm
goto end

:make_macro
gcc -Iscl macro\*.c -o macro

:end
